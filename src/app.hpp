#pragma once
#include <quickjs.h>
#include "script_engine.hpp"

static constexpr int DEFAULT_WINDOW_HEIGHT = 600;
static constexpr int DEFAULT_WINDOW_WIDTH = 800;
static constexpr int DEFAULT_TARGET_FPS = 60;
static constexpr Color DEFAULT_BACKGROUND_COLOR = Color { 0, 0, 0, 255 };
static constexpr std::string DEFAULT_WINDOW_TITLE = "untitled";

class App {
public:
    // Lifecycle
    explicit App(std::string path);
    ~App();

    // Deleted Copy/Assignment
    App(const App&) = delete;
    App& operator=(const App&) = delete;

    // Execution
    bool Initialize();
    void Run() const;
    static void Shutdown();

    void BindAPI();

    // Accessors
    [[nodiscard]] ScriptEngine& GetEngine() const { return *qjs; }

    // Configuration & State
    bool isRunning = false;
    int windowWidth = DEFAULT_WINDOW_WIDTH;
    int windowHeight = DEFAULT_WINDOW_HEIGHT;
    int targetFPS = DEFAULT_TARGET_FPS;
    Color backgroundColor = DEFAULT_BACKGROUND_COLOR;
    std::string windowTitle = DEFAULT_WINDOW_TITLE;

private:
    // Internal Logic
    void ProcessFrame() const;

    // Internal Resources
    std::unique_ptr<ScriptEngine> qjs = nullptr;
    std::string scriptPath;
    JSValue appInstance = JS_UNDEFINED;

    // Cached Atoms
    JSAtom initAtom = JS_ATOM_NULL;
    JSAtom updateAtom = JS_ATOM_NULL;
    JSAtom drawAtom = JS_ATOM_NULL;

    // Shared JS Objects
    JSValue jsDrawContextObj = JS_UNDEFINED;
    JSValue jsSystemContextObj = JS_UNDEFINED;

    // QuickJS Static Callbacks
    static JSValue js_app_run(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv);
    static JSValue js_app_constructor(JSContext *ctx, JSValueConst new_target, int argc, JSValueConst *argv);

    static void create_app_class(JSContext *ctx, JSValue global_obj);

    static JSValue js_sandbox_constructor(JSContext *ctx, JSValue new_target, int argc, JSValue *argv);


};