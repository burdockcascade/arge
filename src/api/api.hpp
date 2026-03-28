#pragma once
#include <quickjs.h>
#include <raylib.h>
#include <string>
#include "../wrapper/rl_bindings.hpp"

namespace API {

    static constexpr int DEFAULT_FONT_SIZE = 24;

    struct FunctionDef {
        std::string_view name{};
        JSCFunction* func{};
        int length{};
    };

    class App {
    public:


        // Configuration (Moved from Runner)
        int windowWidth = 800;
        int windowHeight = 600;
        std::string windowTitle = "untitled";

        // JS State
        JSValue instance = JS_UNDEFINED;
        JSAtom initAtom = JS_ATOM_NULL;
        JSAtom updateAtom = JS_ATOM_NULL;
        JSAtom drawAtom = JS_ATOM_NULL;

        void Free(JSContext* ctx) const {
            JS_FreeValue(ctx, instance);
            JS_FreeAtom(ctx, initAtom);
            JS_FreeAtom(ctx, updateAtom);
            JS_FreeAtom(ctx, drawAtom);
        }

    };

    void register_console(JSContext *ctx, JSValue global_obj);



    void InitEverything(JSContext* ctx, JSValue global);
    void RegisterSystemNamespace(JSContext* ctx, JSValue jsSystemContextObj);
    void RegisterDrawNamespace(JSContext* ctx, JSValue jsDrawContextObj);
    void register_functions(JSContext* ctx, JSValue obj, std::initializer_list<FunctionDef> funcs);

    void create_canvas_object(JSContext* ctx, JSValue draw_obj);

    void create_asset_object(JSContext* ctx, JSValue system_ns);
    void create_window_object(JSContext* ctx, JSValue system_ns);
    void create_input_object(JSContext* ctx, JSValue system_ns);

    static JSValue js_app_run(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv);
    static JSValue js_app_constructor(JSContext *ctx, JSValueConst new_target, int argc, JSValueConst *argv);

    void CreateAppClass(JSContext *ctx, JSValue global_obj);

    void RegisterEverything(JSContext* ctx, JSValue global_obj);

}