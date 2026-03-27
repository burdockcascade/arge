#include <quickjs.h>
#include <raylib.h>
#include <string>
#include <memory>
#include <fstream>
#include <sstream>
#include <ranges>
#include "app.hpp"
#include "script_engine.hpp"
#include "api/api.hpp"

App::App(std::string path) : scriptPath(std::move(path)) {
    qjs = std::make_unique<ScriptEngine>();

    initAtom = qjs->CreateAtom("init");
    updateAtom = qjs->CreateAtom("update");
    drawAtom = qjs->CreateAtom("draw");

    qjs->SetOpaque(this);
    BindAPI();
}

App::~App() {

    qjs->FreeValue(appInstance);
    qjs->FreeValue(jsDrawContextObj);
    qjs->FreeValue(jsSystemContextObj);
    qjs->FreeAtom(initAtom);
    qjs->FreeAtom(updateAtom);
    qjs->FreeAtom(drawAtom);

    if (IsWindowReady()) {
        CloseWindow();
    }
}

bool App::Initialize() {
    std::ifstream t(scriptPath);
    if (!t.is_open()) return false;

    std::stringstream buffer;
    buffer << t.rdbuf();
    const std::string code = buffer.str();

    if (!qjs->EvalModule(code, scriptPath)) return false;

    InitWindow(windowWidth, windowHeight, windowTitle.c_str());
    SetTargetFPS(targetFPS);

    JSValue args[] = { JS_DupValue(qjs->GetContext(), jsSystemContextObj) };
    qjs->FreeValue(qjs->CallMethod(appInstance, initAtom, 1, args));
    qjs->FreeValue(args[0]);

    isRunning = true;
    return true;
}

void App::Run() const {
    while (!WindowShouldClose() && isRunning) {
        ProcessFrame();
    }
}

void App::Shutdown() {
    CloseWindow();
}

void App::BindAPI() {
    JSContext* ctx = qjs->GetContext();
    const JSValue globalObj = JS_GetGlobalObject(ctx);

    API::register_console(ctx, globalObj);
    create_app_class(ctx, globalObj);

    jsDrawContextObj = JS_NewObject(ctx);
    jsSystemContextObj = JS_NewObject(ctx);

    API::InitEverything(ctx, globalObj);
    API::RegisterSystemNamespace(ctx, jsSystemContextObj);
    API::RegisterDrawNamespace(ctx, jsDrawContextObj);

    JS_FreeValue(ctx, globalObj);
}

void App::ProcessFrame() const {
    JSContext* ctx = qjs->GetContext();

    if (int err = JS_ExecutePendingJob(JS_GetRuntime(ctx), &ctx); err < 0) {
        qjs->HandleException();
    }

    // Update
    JSValue uArgs[] = { JS_NewFloat64(ctx, GetFrameTime()), JS_DupValue(ctx, jsSystemContextObj) };
    qjs->FreeValue(qjs->CallMethod(appInstance, updateAtom, 2, uArgs));
    qjs->FreeValue(uArgs[0]);
    qjs->FreeValue(uArgs[1]);

    // Draw
    BeginDrawing();
    ClearBackground(backgroundColor);

    JSValue dArgs[] = { JS_DupValue(ctx, jsDrawContextObj) };
    qjs->FreeValue(qjs->CallMethod(appInstance, drawAtom, 1, dArgs));
    qjs->FreeValue(dArgs[0]);

    EndDrawing();
}

JSValue App::js_app_run(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    if (auto* app = ScriptEngine::GetHostInstance<App>(ctx); app && argc >= 1) {
        app->GetEngine().SetStoredValue(app->appInstance, argv[0]);
    }
    return JS_UNDEFINED;
}

JSValue App::js_app_constructor(JSContext *ctx, JSValueConst new_target, int argc, JSValueConst *argv) {
    const JSValue obj = JS_NewObject(ctx);

    if (auto* app = ScriptEngine::GetHostInstance<App>(ctx); app) {
        app->GetEngine().RegisterFunction(obj, "run", js_app_run, 1);

        if (argc >= 1 && JS_IsObject(argv[0])) {
            app->GetEngine().GetPropertyInt(argv[0], "width", &app->windowWidth);
            app->GetEngine().GetPropertyInt(argv[0], "height", &app->windowHeight);
            app->GetEngine().GetPropertyString(argv[0], "title", app->windowTitle);
        }
    } else {
        TraceLog(LOG_ERROR, "App constructor called but no App instance found");
    }
    return obj;
}

void App::create_app_class(JSContext* ctx, JSValue global_obj) {
    const JSValue ctor = JS_NewCFunction2(ctx, js_app_constructor, "App", 1, JS_CFUNC_constructor, 0);
    JS_SetPropertyStr(ctx, global_obj, "App", ctor);
}