module;
#include <quickjs.h>

export module App;

import <string>;
import <memory>;
import <vector>;
import <fstream>;
import <sstream>;
import ScriptEngine;
import API;
import Raylib;

static constexpr int DEFAULT_WINDOW_HEIGHT = 600;
static constexpr int DEFAULT_WINDOW_WIDTH = 800;
static constexpr int DEFAULT_TARGET_FPS = 60;
static constexpr Raylib::Color DEFAULT_BACKGROUND_COLOR = Raylib::Color { 0, 0, 0, 255};
static constexpr std::string DEFAULT_WINDOW_TITLE = "untitled";

export class App {
public:

    explicit App(std::string path) : scriptPath(std::move(path)) {

        // Initialize the script engine and cache method atoms for efficient lookup
        engine = std::make_unique<ScriptEngine>();

        // Cache method atoms for efficient lookup during the game loop
        initAtom = engine->CreateAtom("init");
        updateAtom = engine->CreateAtom("update");
        drawAtom = engine->CreateAtom("draw");

        // Set the opaque pointer to allow static callbacks to access this App instance
        engine->SetOpaque(this);

        // Bind the API before loading the script so it's available during module evaluation
        BindAPI();
    }

    ~App() {
        engine->FreeValue(appInstance);
        engine->FreeValue(jsDrawContextObj);
        engine->FreeValue(jsSystemContextObj);
        engine->FreeAtom(initAtom);
        engine->FreeAtom(updateAtom);
        engine->FreeAtom(drawAtom);

        if (Raylib::IsWindowReady()) {
            Raylib::CloseWindow();
        }
    }

    // Prevent copying to ensure unique ownership of the script engine
    App(const App&) = delete;
    App& operator=(const App&) = delete;

    bool Initialize() {

        std::ifstream t(scriptPath);
        if (!t.is_open()) return false;

        std::stringstream buffer;
        buffer << t.rdbuf();
        const std::string code = buffer.str();

        if (!engine->EvalModule(code, scriptPath)) return false;

        Raylib::InitWindow(windowWidth, windowHeight, windowTitle.c_str());
        Raylib::SetTargetFPS(targetFPS);

        JSValue args[] = { JS_DupValue(engine->GetContext(), jsSystemContextObj) };
        engine->FreeValue(engine->CallMethod(appInstance, initAtom, 1, args));
        engine->FreeValue(args[0]);

        isRunning = true;
        return true;
    }

    void Run() const {
        while (!Raylib::WindowShouldClose() && isRunning) {
            ProcessFrame();
        }
    }

    static void Shutdown() {
        Raylib::CloseWindow();
    }

    // Helper to allow static callbacks to access the engine wrapper
    [[nodiscard]] ScriptEngine& GetEngine() const { return *engine; }

    // App State
    bool isRunning = false;
    int windowWidth = DEFAULT_WINDOW_WIDTH;
    int windowHeight = DEFAULT_WINDOW_HEIGHT;
    int targetFPS = DEFAULT_TARGET_FPS;
    Raylib::Color backgroundColor = DEFAULT_BACKGROUND_COLOR;
    std::string windowTitle = DEFAULT_WINDOW_TITLE;

private:

    // Core Components
    std::unique_ptr<ScriptEngine> engine = nullptr;
    std::string scriptPath = "";

    JSValue appInstance = JS_UNDEFINED;

    // Cached Atoms for performance in the game loop
    JSAtom initAtom = JS_ATOM_NULL;
    JSAtom updateAtom = JS_ATOM_NULL;
    JSAtom drawAtom = JS_ATOM_NULL;

    // Shared JS Objects
    JSValue jsDrawContextObj = JS_UNDEFINED;
    JSValue jsSystemContextObj = JS_UNDEFINED;

    void BindAPI() {
        JSContext* ctx = engine->GetContext();
        const JSValue globalObj = JS_GetGlobalObject(ctx);

        // Core Systems
        API::register_console(ctx);
        create_app_class(ctx, globalObj);

        // Namespaces
        jsDrawContextObj = JS_NewObject(ctx);
        jsSystemContextObj = JS_NewObject(ctx);

        // Raylib Bindings
        API::InitEverything(ctx, globalObj);
        API::create_window_object(ctx, jsSystemContextObj);
        API::create_input_object(ctx, jsSystemContextObj);
        API::create_canvas_object(ctx, jsDrawContextObj);

        JS_FreeValue(ctx, globalObj);
    }

    void ProcessFrame() const {
        JSContext* ctx = engine->GetContext();

        if (int err = JS_ExecutePendingJob(JS_GetRuntime(ctx), &ctx); err < 0) {
            engine->HandleException();
        }

        // Update
        JSValue uArgs[] = { JS_NewFloat64(ctx, Raylib::GetFrameTime()), JS_DupValue(ctx, jsSystemContextObj) };
        engine->FreeValue(engine->CallMethod(appInstance, updateAtom, 2, uArgs));
        engine->FreeValue(uArgs[0]);
        engine->FreeValue(uArgs[1]);

        // Draw
        Raylib::BeginDrawing();

        Raylib::ClearBackground(backgroundColor);

        JSValue dArgs[] = { JS_DupValue(ctx, jsDrawContextObj) };
        engine->FreeValue(engine->CallMethod(appInstance, drawAtom, 1, dArgs));
        engine->FreeValue(dArgs[0]);

        Raylib::EndDrawing();
    }

    static JSValue js_app_run(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
        if (auto* app = ScriptEngine::GetHostInstance<App>(ctx); app && argc >= 1) {
            app->GetEngine().SetStoredValue(app->appInstance, argv[0]);
        }
        return JS_UNDEFINED;
    }

    static JSValue js_app_constructor(JSContext *ctx, JSValueConst new_target, int argc, JSValueConst *argv) {
        const JSValue obj = JS_NewObject(ctx);

        if (auto* app = ScriptEngine::GetHostInstance<App>(ctx); app) {

            app->GetEngine().RegisterFunction(obj, "run", js_app_run, 1);

            if (argc >= 1 && JS_IsObject(argv[0])) {
                app->GetEngine().GetPropertyInt(argv[0], "width", &app->windowWidth);
                app->GetEngine().GetPropertyInt(argv[0], "height", &app->windowHeight);
                app->GetEngine().GetPropertyString(argv[0], "title", app->windowTitle);
            }
        } else {
            Raylib::TraceLog(Raylib::LOG_ERROR, "App constructor called but no App instance found in context opaque");
        }
        return obj;
    }

    static void create_app_class(JSContext* ctx, JSValue global_obj) {
        const JSValue ctor = JS_NewCFunction2(ctx, js_app_constructor, "App", 1, JS_CFUNC_constructor, 0);
        JS_SetPropertyStr(ctx, global_obj, "App", ctor);
    }
};