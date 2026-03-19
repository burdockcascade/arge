#include "app.hpp"
#include <iostream>
#include <fstream>
#include <utility>
#include <raylib.h>
#include "console.hpp"

static JSValue js_app_run(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    if (auto* engine = static_cast<App*>(JS_GetContextOpaque(ctx)); engine && argc >= 1) {
        JS_FreeValue(ctx, engine->appInstance);
        engine->appInstance = JS_DupValue(ctx, argv[0]);
    }
    return JS_UNDEFINED;
}

static JSValue js_app_constructor(JSContext *ctx, JSValueConst new_target, int argc, JSValueConst *argv) {
    const JSValue obj = JS_NewObject(ctx);

    if (auto* engine = static_cast<App*>(JS_GetContextOpaque(ctx)); engine && argc >= 1 && JS_IsObject(argv[0])) {

        // Extract Width
        const JSValue w = JS_GetPropertyStr(ctx, argv[0], "width");
        if (JS_IsNumber(w)) JS_ToInt32(ctx, &engine->windowWidth, w);
        JS_FreeValue(ctx, w);

        // Extract Height
        const JSValue h = JS_GetPropertyStr(ctx, argv[0], "height");
        if (JS_IsNumber(h)) JS_ToInt32(ctx, &engine->windowHeight, h);
        JS_FreeValue(ctx, h);

        // Extract Title
        const JSValue t = JS_GetPropertyStr(ctx, argv[0], "title");
        if (JS_IsString(t)) {
            const char* titleStr = JS_ToCString(ctx, t);
            engine->windowTitle = titleStr;
            JS_FreeCString(ctx, titleStr);
        }
        JS_FreeValue(ctx, t);
    }

    JS_SetPropertyStr(ctx, obj, "run", JS_NewCFunction(ctx, js_app_run, "run", 1));
    return obj;
}

App::App(std::string path) : scriptPath(std::move(path)) {

    // Core
    rt = JS_NewRuntime();
    ctx = JS_NewContext(rt);

    // Atomic
    initAtom = JS_NewAtom(ctx, "init");
    updateAtom = JS_NewAtom(ctx, "update");
    drawAtom = JS_NewAtom(ctx, "draw");

    // Set CTX
    JS_SetContextOpaque(ctx, this);

    BindAPI();

}

void App::BindAPI() {

    // Register Console
    Console::register_console(ctx);

    // Create Context
    jsCtxObj = JS_NewObject(ctx);

    // Create System
    jsSystemObj = JS_NewObject(ctx);

    // App
    const JSValue global_obj = JS_GetGlobalObject(ctx);
    const JSValue app_ctor = JS_NewCFunction2(ctx, js_app_constructor, "App", 1, JS_CFUNC_constructor, 0);
    JS_SetPropertyStr(ctx, global_obj, "App", app_ctor);

}

[[nodiscard]] bool App::LoadScript() const {
    // Read the script file from disk
    std::ifstream t(scriptPath);
    if (!t.is_open()) {
        TraceLog(LOG_ERROR, "Failed to open script: %s", scriptPath.c_str());
        return false;
    }

    // Read file content into a string
    const std::string code((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());

    // Evaluate the script in the QuickJS context
    const JSValue eval_ret = JS_Eval(ctx, code.c_str(), code.length(), scriptPath.c_str(), JS_EVAL_TYPE_MODULE);

    // Check for syntax or evaluation errors
    if (JS_IsException(eval_ret)) {
        HandleJSException(); // Uses the existing error handler
        return false;
    }
    JS_FreeValue(ctx, eval_ret);

    // Verify that the user called 'app.run(instance)' in their script
    if (JS_IsUndefined(appInstance)) {
        TraceLog(LOG_WARNING, "No app instance found. Ensure 'app.run(new YourClass())' is called in %s", scriptPath.c_str());
        return false;
    }

    TraceLog(LOG_INFO, "Script loaded and evaluated successfully: %s", scriptPath.c_str());
    return true;
}

bool App::Initialize() {

    // Load and Eval Script
    if (!LoadScript()) return false;

    // Initialize Window
    InitWindow(windowWidth, windowHeight, windowTitle.c_str());
    SetTargetFPS(targetFPS);

    // Call init
    const JSValue initFunc = JS_GetProperty(ctx, appInstance, initAtom);
    if (JS_IsFunction(ctx, initFunc)) {
        JSValue args[1];
        args[0] = JS_DupValue(ctx, jsSystemObj);

        const JSValue ret = JS_Call(ctx, initFunc, appInstance, 1, args);
        if (JS_IsException(ret)) HandleJSException();

        JS_FreeValue(ctx, ret);
        JS_FreeValue(ctx, args[0]);
    }
    JS_FreeValue(ctx, initFunc);

    isRunning = true;
    return true;
}

void App::Run() const {
    while (!WindowShouldClose() && isRunning) {
        ProcessFrame();
    }
}

void App::ProcessFrame() const {
    const float dt = GetFrameTime();

    // Logic/Update Phase
    const JSValue updateFunc = JS_GetProperty(ctx, appInstance, updateAtom);
    if (JS_IsFunction(ctx, updateFunc)) {
        JSValue args[2] = { JS_NewFloat64(ctx, dt), JS_DupValue(ctx, jsSystemObj) };
        JSValue ret = JS_Call(ctx, updateFunc, appInstance, 2, args);
        if (JS_IsException(ret)) HandleJSException();
        JS_FreeValue(ctx, ret);
        JS_FreeValue(ctx, args[0]);
        JS_FreeValue(ctx, args[1]);
    }
    JS_FreeValue(ctx, updateFunc);

    // Rendering Phase
    BeginDrawing();
    ClearBackground(BLACK);

    const JSValue drawFunc = JS_GetProperty(ctx, appInstance, drawAtom);
    if (JS_IsFunction(ctx, drawFunc)) {
        JSValue args[1] = { JS_DupValue(ctx, jsCtxObj) };
        JSValue ret = JS_Call(ctx, drawFunc, appInstance, 1, args);
        if (JS_IsException(ret)) HandleJSException();
        JS_FreeValue(ctx, ret);
        JS_FreeValue(ctx, args[0]);
    }
    JS_FreeValue(ctx, drawFunc);

    EndDrawing();
}

void App::Shutdown() {
    CloseWindow();
}


void App::HandleJSException() const {
    const JSValue exception = JS_GetException(ctx);
    const char* msg = JS_ToCString(ctx, exception);
    TraceLog(LOG_ERROR, "JS EXECUTION ERROR: %s", msg);

    // Check for stack trace
    JSValue stack = JS_GetPropertyStr(ctx, exception, "stack");
    if (!JS_IsUndefined(stack)) {
        const char* stackStr = JS_ToCString(ctx, stack);
        TraceLog(LOG_ERROR, "Stack Trace: %s", stackStr);
        JS_FreeCString(ctx, stackStr);
    }

    JS_FreeCString(ctx, msg);
    JS_FreeValue(ctx, stack);
    JS_FreeValue(ctx, exception);
}

App::~App() {
    JS_FreeValue(ctx, appInstance);

    JS_FreeAtom(ctx, initAtom);
    JS_FreeAtom(ctx, updateAtom);
    JS_FreeAtom(ctx, drawAtom);

    JS_FreeContext(ctx);
    JS_FreeRuntime(rt);
}