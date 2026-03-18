#pragma once
#include <string>
#include <quickjs.h>

class App {
public:
    explicit App(std::string  path);

    void BindAPI();

    ~App();
    void Run();
    void HandleJSException() const;
    JSValue appInstance = JS_UNDEFINED;

private:
    JSRuntime* rt;
    JSContext* ctx;
    std::string scriptPath;
    JSAtom initAtom = 0;
    JSAtom updateAtom = 0;
    JSAtom drawAtom = 0;
    JSValue jsCtxObj = JS_UNDEFINED;
    JSValue jsSystemObj = JS_UNDEFINED;

};