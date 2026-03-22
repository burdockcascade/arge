module;
#include <raylib.h>
#include <quickjs.h>

export module API:Console;
import <iostream>;
import <fstream>;
import :Common;

export namespace API {

    JSValue js_print(JSContext *ctx, int argc, JSValueConst *argv, const int logLevel) {
        for (int i = 0; i < argc; i++) {
            const char *str = JS_ToCString(ctx, argv[i]);
            if (!str) return JS_EXCEPTION;

            // Using %s prevents issues if the JS string contains '%' characters
            TraceLog(logLevel, "%s", str);

            JS_FreeCString(ctx, str);
        }
        return JS_UNDEFINED;
    }

    JSValue js_console_log(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
        return js_print(ctx, argc, argv, LOG_INFO);
    }

    JSValue js_console_error(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
        return js_print(ctx, argc, argv, LOG_ERROR);
    }

    JSValue js_console_warn(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
        return js_print(ctx, argc, argv, LOG_WARNING);
    }

    void register_console(JSContext *ctx) {
        const JSValue global_obj = JS_GetGlobalObject(ctx);
        JSValue console_ns = JS_NewObject(ctx);

        register_functions(ctx, console_ns, {
            {"log", js_console_log, 1},
            {"error", js_console_error, 1},
            {"warn", js_console_warn, 1}
        });

        JS_SetPropertyStr(ctx, global_obj, "console", console_ns);
        JS_FreeValue(ctx, global_obj);
    }
}