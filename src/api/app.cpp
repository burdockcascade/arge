#include <quickjs.h>
#include <raylib.h>

#include "api.hpp"
#include "common.hpp"
#include "../script_engine.hpp"

namespace API {

    static JSValue JS_App_Run(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
        if (auto* app = ScriptEngine::GetHostInstance<App>(ctx); app && argc >= 1) {
            if (!JS_IsUndefined(app->instance)) {
                JS_FreeValue(ctx, app->instance);
            }
            app->instance = JS_DupValue(ctx, argv[0]);
        } else {
            TraceLog(LOG_ERROR, "App run called but no App instance found");
        }
        return JS_UNDEFINED;
    }

    static JSValue JS_App_Constructor(JSContext *ctx, JSValueConst new_target, int argc, JSValueConst *argv) {
        const JSValue obj = JS_NewObject(ctx);

        if (auto* app = ScriptEngine::GetHostInstance<App>(ctx); app) {
            JS_SetPropertyStr(ctx, obj, "run", JS_NewCFunction2(ctx, JS_App_Run, "run", 1, JS_CFUNC_generic, 0));

            if (!try_get_value(ctx, app->windowHeight, argv[0])) return JS_EXCEPTION;
            if (!try_get_value(ctx, app->windowWidth, argv[1])) return JS_EXCEPTION;
            if (!try_get_value(ctx, app->windowTitle, argv[2])) return JS_EXCEPTION;

        } else {
            TraceLog(LOG_ERROR, "App constructor called but no App instance found");
        }
        return obj;
    }

    void CreateAppClass(JSContext* ctx, JSValue global_obj) {
        const JSValue ctor = JS_NewCFunction2(ctx, JS_App_Constructor, "App", 1, JS_CFUNC_constructor, 0);
        JS_SetPropertyStr(ctx, global_obj, "App", ctor);
    }

}