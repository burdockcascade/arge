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

    struct App {
        // Window Configuration
        int windowWidth = 800;
        int windowHeight = 600;
        std::string windowTitle = "untitled";

        // JavaScript Object Handles
        JSValue instance = JS_UNDEFINED;
        JSValue jsDrawContextObj = JS_UNDEFINED;
        JSValue jsSystemContextObj = JS_UNDEFINED;

        // Cached Atoms for Performance
        JSAtom initAtom = JS_ATOM_NULL;
        JSAtom updateAtom = JS_ATOM_NULL;
        JSAtom drawAtom = JS_ATOM_NULL;

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

    static JSValue JS_App_Run(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv);
    static JSValue JS_App_Constructor(JSContext *ctx, JSValueConst new_target, int argc, JSValueConst *argv);

    void CreateAppClass(JSContext *ctx, JSValue global_obj);

    void RegisterEverything(JSContext* ctx, JSValue global_obj);

}