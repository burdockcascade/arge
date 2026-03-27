module;
#include <quickjs.h>
#include <raylib.h>

export module API:Console;
import :Common;
import <iostream>;
import <fstream>;


export namespace API {

    JSValue JS_Print(JSContext *ctx, int argc, JSValueConst *argv, const int logLevel) {
        for (int i = 0; i < argc; i++) {

            std::string text;
            if (!try_get_value(ctx, text, argv[i])) return JS_EXCEPTION;

            // Using %s prevents issues if the JS string contains '%' characters
            TraceLog(logLevel, "%s", text.c_str());
        }
        return JS_UNDEFINED;
    }

    JSValue JS_Console_Log(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
        return JS_Print(ctx, argc, argv, LOG_INFO);
    }

    JSValue JS_Console_Error(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
        return JS_Print(ctx, argc, argv, LOG_ERROR);
    }

    JSValue JS_Console_Warn(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
        return JS_Print(ctx, argc, argv, LOG_WARNING);
    }

    void register_console(JSContext *ctx, JSValue global_obj) {
        const JSValue console_ns = JS_NewObject(ctx);

        register_functions(ctx, console_ns, {
            {"log", JS_Console_Log, 1},
            {"error", JS_Console_Error, 1},
            {"warn", JS_Console_Warn, 1}
        });

        JS_SetPropertyStr(ctx, global_obj, "console", console_ns);
    }
}