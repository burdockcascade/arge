module;
#include <raylib.h>
#include <quickjs.h>

export module API:System;
import RaylibBindings;
import :Common;

export namespace API {

    void init_raylib_enums(JSContext* ctx, JSValue global) {
        RaylibBindings::InitAllEnums(ctx, global);
    }

    // Register the Window API functions to the JavaScript context
    void create_window_object(JSContext* ctx, JSValue system_ns) {
        JSValue window_ns = JS_NewObject(ctx);

        register_functions(ctx, window_ns, {
            {"isReady",         RaylibBindings::JS_IsWindowReady,     0},
            {"isFullscreen",    RaylibBindings::JS_IsWindowFullscreen,0},
            {"isHidden",        RaylibBindings::JS_IsWindowHidden,    0},
            {"isMinimized",     RaylibBindings::JS_IsWindowMinimized, 0},
            {"isMaximized",     RaylibBindings::JS_IsWindowMaximized, 0},
            {"isFocused",       RaylibBindings::JS_IsWindowFocused,   0},
            {"isResized",       RaylibBindings::JS_IsWindowResized,   0},
            {"isState",         RaylibBindings::JS_IsWindowState,     1},
            {"setState",        RaylibBindings::JS_SetWindowState,    1},
            {"clearState",      RaylibBindings::JS_ClearWindowState,  1},
            {"getScreenWidth",  RaylibBindings::JS_GetScreenWidth,    0},
            {"getScreenHeight", RaylibBindings::JS_GetScreenHeight,   0},
            {"getRenderWidth",  RaylibBindings::JS_GetRenderWidth,    0},
            {"getRenderHeight", RaylibBindings::JS_GetRenderHeight,   0}
        });

        JS_SetPropertyStr(ctx, system_ns, "window", window_ns);
    }

    // Register the Input API functions to the JavaScript context
    void create_input_object(JSContext* ctx, JSValue system_ns) {
        JSValue input_ns = JS_NewObject(ctx);

        register_functions(ctx, input_ns, {
            {"isKeyDown",            RaylibBindings::JS_IsKeyDown,            1},
            {"isKeyPressed",         RaylibBindings::JS_IsKeyPressed,         1},
            {"isKeyPressedRepeat",   RaylibBindings::JS_IsKeyPressedRepeat,   1},
            {"isKeyReleased",        RaylibBindings::JS_IsKeyReleased,        1},
            {"isKeyUp",              RaylibBindings::JS_IsKeyUp,              1},
            {"getKeyPressed",        RaylibBindings::JS_GetKeyPressed,        0},
            {"setExitKey",           RaylibBindings::JS_SetExitKey,           1},
            {"isMouseButtonPressed", RaylibBindings::JS_IsMouseButtonPressed, 1},
            {"isMouseButtonDown",    RaylibBindings::JS_IsMouseButtonDown,    1}
        });

        JS_SetPropertyStr(ctx, system_ns, "input", input_ns);
    }

}