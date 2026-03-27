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

    void register_console(JSContext *ctx, JSValue global_obj);



    void InitEverything(JSContext* ctx, JSValue global);
    void RegisterSystemNamespace(JSContext* ctx, JSValue jsSystemContextObj);
    void RegisterDrawNamespace(JSContext* ctx, JSValue jsDrawContextObj);
    void register_functions(JSContext* ctx, JSValue obj, std::initializer_list<FunctionDef> funcs);

    void create_canvas_object(JSContext* ctx, JSValue draw_obj);

    void create_asset_object(JSContext* ctx, JSValue system_ns);
    void create_window_object(JSContext* ctx, JSValue system_ns);
    void create_input_object(JSContext* ctx, JSValue system_ns);

}