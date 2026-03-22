module;
#include <raylib.h>
#include <quickjs.h>

export module App;

import <string>;
import <memory>;
import <vector>;
import <fstream>;
import <sstream>;
import ScriptEngine;
import API;

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
        engine->FreeValue(jsCtxObj);
        engine->FreeValue(jsSystemObj);
        engine->FreeAtom(initAtom);
        engine->FreeAtom(updateAtom);
        engine->FreeAtom(drawAtom);

        if (IsWindowReady()) {
            CloseWindow();
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

        InitWindow(windowWidth, windowHeight, windowTitle.c_str());
        SetTargetFPS(targetFPS);

        JSValue args[] = { JS_DupValue(engine->GetContext(), jsSystemObj) };
        engine->FreeValue(engine->CallMethod(appInstance, initAtom, 1, args));
        engine->FreeValue(args[0]);

        isRunning = true;
        return true;
    }

    void Run() const {
        while (!WindowShouldClose() && isRunning) {
            ProcessFrame();
        }
    }

    static void Shutdown() {
        CloseWindow();
    }

    // Helper to allow static callbacks to access the engine wrapper
    [[nodiscard]]ScriptEngine& GetEngine() const { return *engine; }

    // App State
    bool isRunning = false;
    int windowWidth = 800;
    int windowHeight = 600;
    int targetFPS = 60;
    Color backgroundColor = BLACK;
    std::string windowTitle = "Untitled";

    // JS Object References (Managed via engine->FreeValue in destructor)
    JSValue appInstance = JS_UNDEFINED;

private:

    // Core Components
    std::unique_ptr<ScriptEngine> engine{};
    std::string scriptPath{};

    // Cached Atoms for performance in the game loop
    JSAtom initAtom = 0;
    JSAtom updateAtom = 0;
    JSAtom drawAtom = 0;

    // Shared JS Objects
    JSValue jsCtxObj = JS_UNDEFINED;
    JSValue jsSystemObj = JS_UNDEFINED;

    void BindAPI() {
        JSContext* ctx = engine->GetContext();
        const JSValue global = JS_GetGlobalObject(ctx);

        // Core Systems
        API::register_console(ctx);
        create_app_class(ctx, global);

        // Namespaces
        jsCtxObj = JS_NewObject(ctx);
        jsSystemObj = JS_NewObject(ctx);

        // Raylib Bindings
        API::init_raylib_enums(ctx, global);
        API::create_window_object(ctx, jsSystemObj);
        API::create_input_object(ctx, jsSystemObj);

        JS_FreeValue(ctx, global);
    }

    void ProcessFrame() const {
        JSContext* ctx = engine->GetContext();

        // Update
        JSValue uArgs[] = { JS_NewFloat64(ctx, GetFrameTime()), JS_DupValue(ctx, jsSystemObj) };
        engine->FreeValue(engine->CallMethod(appInstance, updateAtom, 2, uArgs));
        engine->FreeValue(uArgs[0]);
        engine->FreeValue(uArgs[1]);

        // Draw
        BeginDrawing();

        ClearBackground(backgroundColor);

        JSValue dArgs[] = { JS_DupValue(ctx, jsCtxObj) };
        engine->FreeValue(engine->CallMethod(appInstance, drawAtom, 1, dArgs));
        engine->FreeValue(dArgs[0]);

        EndDrawing();
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
            TraceLog(LOG_ERROR, "App constructor called but no App instance found in context opaque");
        }
        return obj;
    }

    static void create_app_class(JSContext* ctx, JSValue global_obj) {
        const JSValue ctor = JS_NewCFunction2(ctx, js_app_constructor, "App", 1, JS_CFUNC_constructor, 0);
        JS_SetPropertyStr(ctx, global_obj, "App", ctor);
    }
};



