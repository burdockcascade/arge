#include <iostream>
#include <fstream>
#include <quickjs.h>
#include <raylib.h>

namespace Console {

    static JSValue js_print(JSContext *ctx, int argc, JSValueConst *argv, const int logLevel) {
        for (int i = 0; i < argc; i++) {
            const char *str = JS_ToCString(ctx, argv[i]);
            if (!str) return JS_EXCEPTION;

            // Using %s prevents issues if the JS string contains '%' characters
            TraceLog(logLevel, "%s", str);

            JS_FreeCString(ctx, str);
        }
        return JS_UNDEFINED;
    }

    static JSValue js_console_log(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
        return js_print(ctx, argc, argv, LOG_INFO);
    }

    static JSValue js_console_error(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
        return js_print(ctx, argc, argv, LOG_ERROR);
    }

    static JSValue js_console_warn(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
        return js_print(ctx, argc, argv, LOG_WARNING);
    }

    void register_console(JSContext *ctx) {
        const JSValue global_obj = JS_GetGlobalObject(ctx);
        const JSValue console = JS_NewObject(ctx);

        JS_SetPropertyStr(ctx, console, "log", JS_NewCFunction(ctx, js_console_log, "log", 1));
        JS_SetPropertyStr(ctx, console, "error", JS_NewCFunction(ctx, js_console_error, "error", 1));
        JS_SetPropertyStr(ctx, console, "warn", JS_NewCFunction(ctx, js_console_warn, "warn", 1));

        JS_SetPropertyStr(ctx, global_obj, "console", console);
        JS_FreeValue(ctx, global_obj);
    }
}