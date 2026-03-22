module;
#include <raylib.h>
#include <quickjs.h>

export module ScriptEngine;
import <string>;
import <string_view>;
import <vector>;

export class ScriptEngine {
public:
    ScriptEngine() {
        rt = JS_NewRuntime(); 
        ctx = JS_NewContext(rt); 
    }

    ~ScriptEngine() {
        if (ctx) JS_FreeContext(ctx);
        if (rt) JS_FreeRuntime(rt); 
    }

    // Prevent copying
    ScriptEngine(const ScriptEngine&) = delete;
    ScriptEngine& operator=(const ScriptEngine&) = delete;

    // Execution
    [[nodiscard]] bool EvalModule(const std::string& code, const std::string& filename) const {
        JSValue val = JS_Eval(ctx, code.c_str(), code.length(), filename.c_str(), JS_EVAL_TYPE_MODULE);
        if (JS_IsException(val)) {
            HandleException(); 
            return false; 
        }
        JS_FreeValue(ctx, val); 
        return true; 
    }

    JSValue CallMethod(JSValueConst obj, const JSAtom method, const int argc, JSValueConst* argv) const {
        TraceLog(LOG_DEBUG, "Calling method with atom: %d", method);
        const JSValue func = JS_GetProperty(ctx, obj, method);
        JSValue ret = JS_UNDEFINED; 
        if (JS_IsFunction(ctx, func)) {
            ret = JS_Call(ctx, func, obj, argc, argv);
            if (JS_IsException(ret)) HandleException();
        }
        JS_FreeValue(ctx, func); 
        return ret; 
    }

    // Property Helpers
    bool GetPropertyInt(const JSValue obj, const char* prop, int* out_val) const {
        JSValue val = JS_GetPropertyStr(ctx, obj, prop);
        bool success = JS_IsNumber(val) && JS_ToInt32(ctx, out_val, val) == 0; 
        JS_FreeValue(ctx, val); 
        return success; 
    }

    bool GetPropertyString(const JSValue obj, const char* prop, std::string& out_val) const {
        JSValue val = JS_GetPropertyStr(ctx, obj, prop);
        bool success = false; 
        if (JS_IsString(val)) {
            const char* str = JS_ToCString(ctx, val);
            if (str) {
                out_val = str; 
                JS_FreeCString(ctx, str); 
                success = true; 
            }
        }
        JS_FreeValue(ctx, val); 
        return success; 
    }

    // Utility
    void RegisterFunction(const JSValue obj, const char* name, JSCFunction* func, const int length) const {
        JS_SetPropertyStr(ctx, obj, name, JS_NewCFunction(ctx, func, name, length)); 
    }

    void SetStoredValue(JSValue& storage, const JSValue newValue) const {
        if (!JS_IsUndefined(storage)) {
            JS_FreeValue(ctx, storage); 
        }
        storage = JS_DupValue(ctx, newValue); 
    }

    static bool IsUndefined(const JSValue v) { return JS_IsUndefined(v); }

    // Resource Management
    [[nodiscard]] JSAtom CreateAtom(const std::string_view name) const {
        return JS_NewAtomLen(ctx, name.data(), name.size()); 
    }

    void FreeValue(const JSValue v) const { JS_FreeValue(ctx, v); }
    void FreeAtom(const JSAtom a) const { JS_FreeAtom(ctx, a); }
    
    void SetHostInstance(void* instance) const { JS_SetContextOpaque(ctx, instance); }

    template<typename T>
    static T* GetHostInstance(JSContext* ctx) {
        return static_cast<T*>(JS_GetContextOpaque(ctx));
    }

    [[nodiscard]] JSContext* GetContext() const { return ctx; }
    void SetOpaque(void* data) const { JS_SetContextOpaque(ctx, data); } 

    void HandleException() const {
        const JSValue exception = JS_GetException(ctx);
        const char* msg = JS_ToCString(ctx, exception); 
        TraceLog(LOG_ERROR, "JS ERROR: %s", msg); 

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

private:
    JSRuntime* rt = nullptr;
    JSContext* ctx = nullptr;
};