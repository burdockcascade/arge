#include <quickjs.h>
#include <raylib.h>
#include <string>
#include <memory>
#include <fstream>
#include <sstream>
#include "runner.hpp"
#include "script_engine.hpp"
#include "api/api.hpp"

Runner::Runner(std::string path) : scriptPath(std::move(path)), app(std::make_unique<API::App>()) {
    qjs = std::make_unique<ScriptEngine>();

    app->initAtom = qjs->CreateAtom("init");
    app->updateAtom = qjs->CreateAtom("update");
    app->drawAtom = qjs->CreateAtom("draw");

    qjs->SetOpaque(app.get());
    BindAPI();
}

Runner::~Runner() {

    qjs->FreeValue(app->instance);
    qjs->FreeValue(app->jsDrawContextObj);
    qjs->FreeValue(app->jsSystemContextObj);

    qjs->FreeAtom(app->initAtom);
    qjs->FreeAtom(app->updateAtom);
    qjs->FreeAtom(app->drawAtom);

    if (IsWindowReady()) {
        CloseWindow();
    }
}

bool Runner::Initialize() {
    std::ifstream t(scriptPath);
    if (!t.is_open()) return false;

    std::stringstream buffer;
    buffer << t.rdbuf();

    if (const std::string code = buffer.str(); !qjs->EvalModule(code, scriptPath)) {
        return false;
    }

    InitWindow(app->windowWidth, app->windowHeight, app->windowTitle.c_str());
    SetTargetFPS(targetFPS);

    JSValue args[] = { JS_DupValue(qjs->GetContext(), app->jsSystemContextObj) };
    qjs->FreeValue(qjs->CallMethod(app->instance, app->initAtom, 1, args));
    qjs->FreeValue(args[0]);

    isRunning = true;
    return true;
}

void Runner::Run() const {
    while (!WindowShouldClose() && isRunning) {
        ProcessFrame();
    }
}

void Runner::Shutdown() {
    CloseWindow();
}

void Runner::BindAPI() const {
    JSContext* ctx = qjs->GetContext();
    const JSValue globalObj = JS_GetGlobalObject(ctx);

    API::register_console(ctx, globalObj);

    app->jsDrawContextObj = JS_NewObject(ctx);
    app->jsSystemContextObj = JS_NewObject(ctx);

    API::InitEverything(ctx, globalObj);
    API::RegisterSystemNamespace(ctx, app->jsSystemContextObj);
    API::RegisterDrawNamespace(ctx, app->jsDrawContextObj);

    JS_FreeValue(ctx, globalObj);
}

void Runner::ProcessFrame() const {
    JSContext* ctx = qjs->GetContext();

    if (int err = JS_ExecutePendingJob(JS_GetRuntime(ctx), &ctx); err < 0) {
        qjs->HandleException();
    }

    // Update
    JSValue uArgs[] = { JS_NewFloat64(ctx, GetFrameTime()), JS_DupValue(ctx, app->jsSystemContextObj) };
    qjs->FreeValue(qjs->CallMethod(app->instance, app->updateAtom, 2, uArgs));
    qjs->FreeValue(uArgs[0]);
    qjs->FreeValue(uArgs[1]);

    // Draw
    BeginDrawing();
    ClearBackground(backgroundColor);

    JSValue dArgs[] = { JS_DupValue(ctx, app->jsDrawContextObj) };
    qjs->FreeValue(qjs->CallMethod(app->instance, app->drawAtom, 1, dArgs));
    qjs->FreeValue(dArgs[0]);

    EndDrawing();
}
