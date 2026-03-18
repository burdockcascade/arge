#include "app.hpp"
#include <iostream>
#include <fstream>
#include <utility>
#include <raylib.h>

static JSValue js_app_run(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    if (auto* engine = static_cast<App*>(JS_GetContextOpaque(ctx)); engine && argc >= 1) {
        JS_FreeValue(ctx, engine->appInstance);
        engine->appInstance = JS_DupValue(ctx, argv[0]);
    }
    return JS_UNDEFINED;
}

static JSValue js_app_constructor(JSContext *ctx, JSValueConst new_target, int argc, JSValueConst *argv) {
    const JSValue obj = JS_NewObject(ctx);
    JS_SetPropertyStr(ctx, obj, "run", JS_NewCFunction(ctx, js_app_run, "run", 1));
    return obj;
}

static JSValue js_print(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    for (int i = 0; i < argc; i++) {
        const char *str = JS_ToCString(ctx, argv[i]);
        if (!str) return JS_EXCEPTION;
        TraceLog(LOG_INFO, "%s", str);
        JS_FreeCString(ctx, str);
    }
    return JS_UNDEFINED;
}

static void register_console(JSContext *ctx) {
    const JSValue global_obj = JS_GetGlobalObject(ctx);
    const JSValue console = JS_NewObject(ctx);

    // Add 'log' method to the console object
    JS_SetPropertyStr(ctx, console, "log",
        JS_NewCFunction(ctx, js_print, "log", 1));

    // Add the console object to the global scope
    JS_SetPropertyStr(ctx, global_obj, "console", console);

    JS_FreeValue(ctx, global_obj);
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
    register_console(ctx);

    // Create Context
    jsCtxObj = JS_NewObject(ctx);

    // Create System
    jsSystemObj = JS_NewObject(ctx);

    // App
    const JSValue global_obj = JS_GetGlobalObject(ctx);
    const JSValue app_ctor = JS_NewCFunction2(ctx, js_app_constructor, "App", 1, JS_CFUNC_constructor, 0);
    JS_SetPropertyStr(ctx, global_obj, "App", app_ctor);

}

void App::Run() {

    InitWindow(800, 600, "C++/QuickJS Engine");
    SetTargetFPS(60);

    // Load script
    std::ifstream t(scriptPath);
    if (!t.is_open()) {
        TraceLog(LOG_ERROR, "Failed to open script: %s", scriptPath.c_str());
        return;
    }
    std::string code((std::istreambuf_iterator(t)), std::istreambuf_iterator<char>());

    // Evaluate script
    JSValue eval_ret = JS_Eval(ctx, code.c_str(), code.length(), scriptPath.c_str(), JS_EVAL_TYPE_MODULE);
    if (JS_IsException(eval_ret)) {
        JSValue exception = JS_GetException(ctx);
        const char* msg = JS_ToCString(ctx, exception);
        std::cerr << "JS Error: " << msg << std::endl;
        JS_FreeCString(ctx, msg);
        JS_FreeValue(ctx, exception);
        return;
    }
    JS_FreeValue(ctx, eval_ret);

    if (JS_IsUndefined(appInstance)) {
        TraceLog(LOG_WARNING, "No app instance found. Make sure to call 'app.run(yourAppInstance)' in your script.");
    }

    // Get callbacks
    JSValue initFunc = JS_GetProperty(ctx, appInstance, initAtom);
    JSValue updateFunc = JS_GetProperty(ctx, appInstance, updateAtom);
    JSValue drawFunc = JS_GetProperty(ctx, appInstance, drawAtom);

    // Call Init
    if (JS_IsFunction(ctx, initFunc)) {

        JSValue args[1];
        args[0] = JS_DupValue(ctx, jsSystemObj);

        JSValue ret = JS_Call(ctx, initFunc, appInstance, 1, args);
        if (JS_IsException(ret)) HandleJSException();

        JS_FreeValue(ctx, ret);
        JS_FreeValue(ctx, args[0]);

    }

    // App Loop
    while (!WindowShouldClose()) {
        const float dt = GetFrameTime();

        BeginDrawing();
        ClearBackground(BLACK);

        // Update
        if (JS_IsFunction(ctx, updateFunc)) {

            JSValue args[2];
            args[0] = JS_NewFloat64(ctx, dt);
            args[1] = JS_DupValue(ctx, jsSystemObj);

            JSValue ret = JS_Call(ctx, updateFunc, appInstance, 2, args);
            if (JS_IsException(ret)) HandleJSException();

            JS_FreeValue(ctx, ret);
            JS_FreeValue(ctx, args[0]);
            JS_FreeValue(ctx, args[1]);

        }

        // Draw
        if (JS_IsFunction(ctx, drawFunc)) {
            JSValue args[1] = { JS_DupValue(ctx, jsCtxObj) };
            JSValue ret = JS_Call(ctx, drawFunc, appInstance, 1, args);
            if (JS_IsException(ret)) HandleJSException();
            JS_FreeValue(ctx, ret);
            JS_FreeValue(ctx, args[0]);
        }

        EndDrawing();
    }

    JS_FreeValue(ctx, initFunc);
    JS_FreeValue(ctx, updateFunc);
    JS_FreeValue(ctx, drawFunc);

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