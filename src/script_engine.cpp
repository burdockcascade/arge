#include "script_engine.hpp"
#include <quickjs.h>

ScriptEngine::ScriptEngine() {
    rt = JS_NewRuntime();
    ctx = JS_NewContext(rt);
}

ScriptEngine::~ScriptEngine() {
    if (ctx) JS_FreeContext(ctx);
    if (rt) JS_FreeRuntime(rt);
}

// Execution
[[nodiscard]] bool ScriptEngine::EvalModule(const std::string &code, const std::string &filename) const {
    const JSValue val = JS_Eval(ctx, code.c_str(), code.length(), filename.c_str(), JS_EVAL_TYPE_MODULE);
    if (JS_IsException(val)) {
        HandleException();
        JS_FreeValue(ctx, val);
        return false;
    }
    JS_FreeValue(ctx, val);
    return true;
}

JSValue ScriptEngine::CallMethod(JSValueConst obj, const JSAtom method, const int argc, JSValueConst *argv) const {
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
bool ScriptEngine::GetPropertyInt(const JSValue obj, const char *prop, int *out_val) const {
    JSValue val = JS_GetPropertyStr(ctx, obj, prop);
    bool success = JS_IsNumber(val) && JS_ToInt32(ctx, out_val, val) == 0;
    JS_FreeValue(ctx, val);
    return success;
}

bool ScriptEngine::GetPropertyString(const JSValue obj, const char *prop, std::string &out_val) const {
    JSValue val = JS_GetPropertyStr(ctx, obj, prop);
    bool success = false;
    if (JS_IsString(val)) {
        const char *str = JS_ToCString(ctx, val);
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
void ScriptEngine::RegisterFunction(const JSValue obj, const char *name, JSCFunction *func, const int length) const {
    JS_SetPropertyStr(ctx, obj, name, JS_NewCFunction2(ctx, func, name, length, JS_CFUNC_generic, 0));
}

void ScriptEngine::SetStoredValue(JSValue &storage, const JSValue newValue) const {
    if (!JS_IsUndefined(storage)) {
        JS_FreeValue(ctx, storage);
    }
    storage = JS_DupValue(ctx, newValue);
}

bool ScriptEngine::IsUndefined(const JSValue v) { return JS_IsUndefined(v); }

// Resource Management
[[nodiscard]] JSAtom ScriptEngine::CreateAtom(const std::string_view name) const {
    return JS_NewAtomLen(ctx, name.data(), name.size());
}

void ScriptEngine::FreeValue(const JSValue v) const { JS_FreeValue(ctx, v); }
void ScriptEngine::FreeAtom(const JSAtom a) const { JS_FreeAtom(ctx, a); }

void ScriptEngine::SetHostInstance(void *instance) const { JS_SetContextOpaque(ctx, instance); }

[[nodiscard]] JSContext *ScriptEngine::GetContext() const { return ctx; }

void ScriptEngine::SetOpaque(void *data) const { JS_SetContextOpaque(ctx, data); }

void ScriptEngine::HandleException() const {
    const JSValue exception = JS_GetException(ctx);
    const char *msg = JS_ToCString(ctx, exception);
    TraceLog(LOG_ERROR, "JS ERROR: %s", msg);

    const JSValue stack = JS_GetPropertyStr(ctx, exception, "stack");
    if (!JS_IsUndefined(stack)) {
        const char *stackStr = JS_ToCString(ctx, stack);
        TraceLog(LOG_ERROR, "Stack Trace: %s", stackStr);
        JS_FreeCString(ctx, stackStr);
    }

    JS_FreeCString(ctx, msg);
    JS_FreeValue(ctx, stack);
    JS_FreeValue(ctx, exception);
}
