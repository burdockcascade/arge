#include <quickjs.h>
#include <raylib.h>
#include <string>
#include <fstream>
#include <sstream>
#include "runner.hpp"
#include "raylib/rl_bindings.hpp"

Runner::Runner(std::string path) : scriptPath(std::move(path)) {

    rt = JS_NewRuntime();
    ctx = JS_NewContext(rt);

    const JSValue globalObj = JS_GetGlobalObject(ctx);
    RaylibBindings::InternalRegister(ctx, globalObj);
    JS_FreeValue(ctx, globalObj);

}

Runner::~Runner() {
    if (ctx) JS_FreeContext(ctx);
    if (rt) JS_FreeRuntime(rt);
}

void Runner::Run() const {
    std::ifstream t(scriptPath);
    if (!t.is_open()) return;

    std::stringstream buffer;
    buffer << t.rdbuf();

    if (const std::string code = buffer.str(); !EvalModule(code, scriptPath)) {
        TraceLog(LOG_ERROR, "Failed to load script: %s", scriptPath.c_str());
        return;
    }

}

[[nodiscard]] bool Runner::EvalModule(const std::string &code, const std::string &filename) const {
    const JSValue val = JS_Eval(ctx, code.c_str(), code.length(), filename.c_str(), JS_EVAL_TYPE_MODULE);
    if (JS_IsException(val)) {
        HandleException();
        JS_FreeValue(ctx, val);
        return false;
    }
    JS_FreeValue(ctx, val);
    return true;
}

void Runner::HandleException() const {
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

