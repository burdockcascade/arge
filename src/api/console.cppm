module;
#include <quickjs.h>

export module API:Console;

import <iostream>;
import <fstream>;
import Raylib;
import :Common;

export namespace API {

    JSValue JS_Print(JSContext *ctx, int argc, JSValueConst *argv, const int logLevel) {
        for (int i = 0; i < argc; i++) {
            const char *str = JS_ToCString(ctx, argv[i]);
            if (!str) return JS_EXCEPTION;

            // Using %s prevents issues if the JS string contains '%' characters
            Raylib::TraceLog(logLevel, "%s", str);

            JS_FreeCString(ctx, str);
        }
        return JS_UNDEFINED;
    }

    JSValue JS_Console_Log(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
        return JS_Print(ctx, argc, argv, Raylib::LOG_INFO);
    }

    JSValue JS_Console_Error(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
        return JS_Print(ctx, argc, argv, Raylib::LOG_ERROR);
    }

    JSValue JS_Console_Warn(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
        return JS_Print(ctx, argc, argv, Raylib::LOG_WARNING);
    }

    void register_console(JSContext *ctx) {
        const JSValue global_obj = JS_GetGlobalObject(ctx);
        const JSValue console_ns = JS_NewObject(ctx);

        register_functions(ctx, console_ns, {
            {"log", JS_Console_Log, 1},
            {"error", JS_Console_Error, 1},
            {"warn", JS_Console_Warn, 1}
        });

        JS_SetPropertyStr(ctx, global_obj, "console", console_ns);
        JS_FreeValue(ctx, global_obj);
    }
}