#pragma once
#include <raylib.h>
#include <quickjs.h>
#include <string>
#include <string_view>
#include <vector>

class ScriptEngine {
public:
    ScriptEngine();
    ~ScriptEngine();

    [[nodiscard]] JSValue MakeNewObject() const;

    // Prevent copying
    ScriptEngine(const ScriptEngine&) = delete;
    ScriptEngine& operator=(const ScriptEngine&) = delete;

    // Execution
    [[nodiscard]] bool EvalModule(const std::string& code, const std::string& filename) const;

    JSValue CallMethod(JSValueConst obj, JSAtom method, int argc, JSValueConst* argv) const;

    bool GetPropertyString(JSValue obj, const char* prop, std::string& out_val) const;

    // Utility
    void RegisterFunction(JSValue obj, const char* name, JSCFunction* func, int length) const;

    void SetStoredValue(JSValue& storage, JSValue newValue) const;

    static bool IsUndefined(JSValue v);

    // Resource Management
    [[nodiscard]] JSAtom CreateAtom(std::string_view name) const;

    void FreeValue(JSValue v) const;
    void FreeAtom(JSAtom a) const;

    void SetHostInstance(void* instance) const;

    template<typename T>
    static T* GetHostInstance(JSContext* ctx) {
        return static_cast<T*>(JS_GetContextOpaque(ctx));
    }

    [[nodiscard]] JSContext* GetContext() const;

    [[nodiscard]] JSValue GetGlobalObject() const;

    void SetOpaque(void* data) const;

    void HandleException() const;

private:
    JSRuntime* rt = nullptr;
    JSContext* ctx = nullptr;
};