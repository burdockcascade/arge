#pragma once
#include <string>
#include <quickjs.h>

class App {
public:
    explicit App(std::string  path);

    void BindAPI();

    ~App();



    bool Initialize();
    void Run() const;
    void Shutdown();


    void HandleJSException() const;
    JSValue appInstance = JS_UNDEFINED;

private:
    void ProcessFrame() const;
    [[nodiscard]] bool LoadScript() const;

    JSRuntime* rt;
    JSContext* ctx;
    std::string scriptPath;
    JSAtom initAtom = 0;
    JSAtom updateAtom = 0;
    JSAtom drawAtom = 0;
    JSValue jsCtxObj = JS_UNDEFINED;
    JSValue jsSystemObj = JS_UNDEFINED;

    bool isRunning = false;
    int windowWidth = 800;
    int windowHeight = 600;
    std::string windowTitle = "Arge Engine";
    int targetFPS = 60;
};