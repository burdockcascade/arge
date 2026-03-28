#pragma once
#include <quickjs.h>
#include "script_engine.hpp"
#include "api/api.hpp"

static constexpr int DEFAULT_WINDOW_HEIGHT = 600;
static constexpr int DEFAULT_WINDOW_WIDTH = 800;
static constexpr int DEFAULT_TARGET_FPS = 60;
static constexpr Color DEFAULT_BACKGROUND_COLOR = Color { 0, 0, 0, 255 };
static constexpr std::string DEFAULT_WINDOW_TITLE = "untitled";

class Runner {
public:
    // Lifecycle
    explicit Runner(std::string path);
    ~Runner();

    // Deleted Copy/Assignment
    Runner(const Runner&) = delete;
    Runner& operator=(const Runner&) = delete;

    // Execution
    bool Initialize();
    void Run() const;
    static void Shutdown();

    void BindAPI() const;

    // Accessors
    [[nodiscard]] ScriptEngine& GetEngine() const { return *qjs; }

    // Configuration & State
    bool isRunning = false;
    int targetFPS = DEFAULT_TARGET_FPS;
    Color backgroundColor = DEFAULT_BACKGROUND_COLOR;

    [[nodiscard]] API::App& GetApp() const { return *app; }

private:
    // Internal Logic
    void ProcessFrame() const;

    // Internal Resources
    std::unique_ptr<ScriptEngine> qjs = nullptr;
    std::string scriptPath;

    std::unique_ptr<API::App> app;

};