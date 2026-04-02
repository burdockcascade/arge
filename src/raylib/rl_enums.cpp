#include "rl_bindings.hpp"
#include "../qjs_wrapper.hpp"

namespace RaylibBindings {

    void InitAllEnums(qjs::ObjectBinder &ns) {

        // Enum: ConfigFlags
        auto config_flags = ns.create_object("ConfigFlags");
        config_flags.register_constant("FLAG_VSYNC_HINT", FLAG_VSYNC_HINT);
        config_flags.register_constant("FLAG_FULLSCREEN_MODE", FLAG_FULLSCREEN_MODE);
        config_flags.register_constant("FLAG_WINDOW_RESIZABLE", FLAG_WINDOW_RESIZABLE);
        config_flags.register_constant("FLAG_WINDOW_UNDECORATED", FLAG_WINDOW_UNDECORATED);
        config_flags.register_constant("FLAG_WINDOW_HIDDEN", FLAG_WINDOW_HIDDEN);
        config_flags.register_constant("FLAG_WINDOW_MINIMIZED", FLAG_WINDOW_MINIMIZED);
        config_flags.register_constant("FLAG_WINDOW_MAXIMIZED", FLAG_WINDOW_MAXIMIZED);
        config_flags.register_constant("FLAG_WINDOW_UNFOCUSED", FLAG_WINDOW_UNFOCUSED);
        config_flags.register_constant("FLAG_WINDOW_TOPMOST", FLAG_WINDOW_TOPMOST);
        config_flags.register_constant("FLAG_WINDOW_ALWAYS_RUN", FLAG_WINDOW_ALWAYS_RUN);
        config_flags.register_constant("FLAG_WINDOW_TRANSPARENT", FLAG_WINDOW_TRANSPARENT);
        config_flags.register_constant("FLAG_WINDOW_HIGHDPI", FLAG_WINDOW_HIGHDPI);
        config_flags.register_constant("FLAG_WINDOW_MOUSE_PASSTHROUGH", FLAG_WINDOW_MOUSE_PASSTHROUGH);
        config_flags.register_constant("FLAG_BORDERLESS_WINDOWED_MODE", FLAG_BORDERLESS_WINDOWED_MODE);
        config_flags.register_constant("FLAG_MSAA_4X_HINT", FLAG_MSAA_4X_HINT);
        config_flags.register_constant("FLAG_INTERLACED_HINT", FLAG_INTERLACED_HINT);

        // Enum: TraceLogLevel
        auto trace_log_level = ns.create_object("TraceLogLevel");
        trace_log_level.register_constant("LOG_ALL", LOG_ALL);
        trace_log_level.register_constant("LOG_TRACE", LOG_TRACE);
        trace_log_level.register_constant("LOG_DEBUG", LOG_DEBUG);
        trace_log_level.register_constant("LOG_INFO", LOG_INFO);
        trace_log_level.register_constant("LOG_WARNING", LOG_WARNING);
        trace_log_level.register_constant("LOG_ERROR", LOG_ERROR);
        trace_log_level.register_constant("LOG_FATAL", LOG_FATAL);
        trace_log_level.register_constant("LOG_NONE", LOG_NONE);

        // Enum: KeyboardKey
        auto keyboard_key = ns.create_object("KeyboardKey");
        keyboard_key.register_constant("KEY_NULL", KEY_NULL);
        keyboard_key.register_constant("KEY_APOSTROPHE", KEY_APOSTROPHE);
        keyboard_key.register_constant("KEY_COMMA", KEY_COMMA);
        keyboard_key.register_constant("KEY_MINUS", KEY_MINUS);
        keyboard_key.register_constant("KEY_PERIOD", KEY_PERIOD);
        keyboard_key.register_constant("KEY_SLASH", KEY_SLASH);
        keyboard_key.register_constant("KEY_ZERO", KEY_ZERO);
        keyboard_key.register_constant("KEY_ONE", KEY_ONE);
        keyboard_key.register_constant("KEY_TWO", KEY_TWO);
        keyboard_key.register_constant("KEY_THREE", KEY_THREE);
        keyboard_key.register_constant("KEY_FOUR", KEY_FOUR);
        keyboard_key.register_constant("KEY_SEVEN", KEY_SEVEN);
        keyboard_key.register_constant("KEY_SIX", KEY_SIX);
        keyboard_key.register_constant("KEY_FIVE", KEY_FIVE);
        keyboard_key.register_constant("KEY_EIGHT", KEY_EIGHT);
        keyboard_key.register_constant("KEY_NINE", KEY_NINE);
        keyboard_key.register_constant("KEY_SEMICOLON", KEY_SEMICOLON);
        keyboard_key.register_constant("KEY_EQUAL", KEY_EQUAL);
        keyboard_key.register_constant("KEY_A", KEY_A);
        keyboard_key.register_constant("KEY_B", KEY_B);
        keyboard_key.register_constant("KEY_C", KEY_C);
        keyboard_key.register_constant("KEY_D", KEY_D);
        keyboard_key.register_constant("KEY_E", KEY_E);
        keyboard_key.register_constant("KEY_F", KEY_F);
        keyboard_key.register_constant("KEY_G", KEY_G);
        keyboard_key.register_constant("KEY_H", KEY_H);
        keyboard_key.register_constant("KEY_I", KEY_I);
        keyboard_key.register_constant("KEY_J", KEY_J);
        keyboard_key.register_constant("KEY_K", KEY_K);
        keyboard_key.register_constant("KEY_L", KEY_L);
        keyboard_key.register_constant("KEY_M", KEY_M);
        keyboard_key.register_constant("KEY_N", KEY_N);
        keyboard_key.register_constant("KEY_O", KEY_O);
        keyboard_key.register_constant("KEY_P", KEY_P);
        keyboard_key.register_constant("KEY_Q", KEY_Q);
        keyboard_key.register_constant("KEY_R", KEY_R);
        keyboard_key.register_constant("KEY_S", KEY_S);
        keyboard_key.register_constant("KEY_T", KEY_T);
        keyboard_key.register_constant("KEY_U", KEY_U);
        keyboard_key.register_constant("KEY_V", KEY_V);
        keyboard_key.register_constant("KEY_W", KEY_W);
        keyboard_key.register_constant("KEY_X", KEY_X);
        keyboard_key.register_constant("KEY_Y", KEY_Y);
        keyboard_key.register_constant("KEY_Z", KEY_Z);
        keyboard_key.register_constant("KEY_LEFT_BRACKET", KEY_LEFT_BRACKET);
        keyboard_key.register_constant("KEY_BACKSLASH", KEY_BACKSLASH);
        keyboard_key.register_constant("KEY_RIGHT_BRACKET", KEY_RIGHT_BRACKET);
        keyboard_key.register_constant("KEY_GRAVE", KEY_GRAVE);
        keyboard_key.register_constant("KEY_SPACE", KEY_SPACE);
        keyboard_key.register_constant("KEY_ESCAPE", KEY_ESCAPE);
        keyboard_key.register_constant("KEY_ENTER", KEY_ENTER);
        keyboard_key.register_constant("KEY_TAB", KEY_TAB);
        keyboard_key.register_constant("KEY_BACKSPACE", KEY_BACKSPACE);
        keyboard_key.register_constant("KEY_INSERT", KEY_INSERT);
        keyboard_key.register_constant("KEY_DELETE", KEY_DELETE);
        keyboard_key.register_constant("KEY_RIGHT", KEY_RIGHT);
        keyboard_key.register_constant("KEY_LEFT", KEY_LEFT);
        keyboard_key.register_constant("KEY_DOWN", KEY_DOWN);
        keyboard_key.register_constant("KEY_UP", KEY_UP);
        keyboard_key.register_constant("KEY_PAGE_UP", KEY_PAGE_UP);
        keyboard_key.register_constant("KEY_PAGE_DOWN", KEY_PAGE_DOWN);
        keyboard_key.register_constant("KEY_HOME", KEY_HOME);
        keyboard_key.register_constant("KEY_END", KEY_END);
        keyboard_key.register_constant("KEY_CAPS_LOCK", KEY_CAPS_LOCK);
        keyboard_key.register_constant("KEY_SCROLL_LOCK", KEY_SCROLL_LOCK);
        keyboard_key.register_constant("KEY_NUM_LOCK", KEY_NUM_LOCK);
        keyboard_key.register_constant("KEY_PRINT_SCREEN", KEY_PRINT_SCREEN);
        keyboard_key.register_constant("KEY_PAUSE", KEY_PAUSE);
        keyboard_key.register_constant("KEY_F1", KEY_F1);
        keyboard_key.register_constant("KEY_F2", KEY_F2);
        keyboard_key.register_constant("KEY_F3", KEY_F3);
        keyboard_key.register_constant("KEY_F4", KEY_F4);
        keyboard_key.register_constant("KEY_F5", KEY_F5);
        keyboard_key.register_constant("KEY_F6", KEY_F6);
        keyboard_key.register_constant("KEY_F7", KEY_F7);
        keyboard_key.register_constant("KEY_F8", KEY_F8);
        keyboard_key.register_constant("KEY_F9", KEY_F9);
        keyboard_key.register_constant("KEY_F10", KEY_F10);
        keyboard_key.register_constant("KEY_F11", KEY_F11);
        keyboard_key.register_constant("KEY_F12", KEY_F12);
        keyboard_key.register_constant("KEY_LEFT_SHIFT", KEY_LEFT_SHIFT);
        keyboard_key.register_constant("KEY_LEFT_CONTROL", KEY_LEFT_CONTROL);
        keyboard_key.register_constant("KEY_LEFT_ALT", KEY_LEFT_ALT);
        keyboard_key.register_constant("KEY_LEFT_SUPER", KEY_LEFT_SUPER);
        keyboard_key.register_constant("KEY_RIGHT_SHIFT", KEY_RIGHT_SHIFT);
        keyboard_key.register_constant("KEY_RIGHT_CONTROL", KEY_RIGHT_CONTROL);
        keyboard_key.register_constant("KEY_RIGHT_ALT", KEY_RIGHT_ALT);
        keyboard_key.register_constant("KEY_RIGHT_SUPER", KEY_RIGHT_SUPER);
        keyboard_key.register_constant("KEY_KB_MENU", KEY_KB_MENU);
        keyboard_key.register_constant("KEY_KP_0", KEY_KP_0);
        keyboard_key.register_constant("KEY_KP_1", KEY_KP_1);
        keyboard_key.register_constant("KEY_KP_2", KEY_KP_2);
        keyboard_key.register_constant("KEY_KP_3", KEY_KP_3);
        keyboard_key.register_constant("KEY_KP_4", KEY_KP_4);
        keyboard_key.register_constant("KEY_KP_5", KEY_KP_5);
        keyboard_key.register_constant("KEY_KP_6", KEY_KP_6);
        keyboard_key.register_constant("KEY_KP_7", KEY_KP_7);
        keyboard_key.register_constant("KEY_KP_8", KEY_KP_8);
        keyboard_key.register_constant("KEY_KP_9", KEY_KP_9);
        keyboard_key.register_constant("KEY_KP_DECIMAL", KEY_KP_DECIMAL);
        keyboard_key.register_constant("KEY_KP_DIVIDE", KEY_KP_DIVIDE);
        keyboard_key.register_constant("KEY_KP_MULTIPLY", KEY_KP_MULTIPLY);
        keyboard_key.register_constant("KEY_KP_SUBTRACT", KEY_KP_SUBTRACT);
        keyboard_key.register_constant("KEY_KP_ADD", KEY_KP_ADD);
        keyboard_key.register_constant("KEY_KP_ENTER", KEY_KP_ENTER);
        keyboard_key.register_constant("KEY_KP_EQUAL", KEY_KP_EQUAL);
        keyboard_key.register_constant("KEY_BACK", KEY_BACK);
        keyboard_key.register_constant("KEY_MENU", KEY_MENU);
        keyboard_key.register_constant("KEY_VOLUME_UP", KEY_VOLUME_UP);
        keyboard_key.register_constant("KEY_VOLUME_DOWN", KEY_VOLUME_DOWN);

        // Enum: MouseButton
        auto mouse_button = ns.create_object("MouseButton");
        mouse_button.register_constant("MOUSE_BUTTON_LEFT", MOUSE_BUTTON_LEFT);
        mouse_button.register_constant("MOUSE_BUTTON_RIGHT", MOUSE_BUTTON_RIGHT);
        mouse_button.register_constant("MOUSE_BUTTON_MIDDLE", MOUSE_BUTTON_MIDDLE);
        mouse_button.register_constant("MOUSE_BUTTON_SIDE", MOUSE_BUTTON_SIDE);
        mouse_button.register_constant("MOUSE_BUTTON_EXTRA", MOUSE_BUTTON_EXTRA);
        mouse_button.register_constant("MOUSE_BUTTON_FORWARD", MOUSE_BUTTON_FORWARD);
        mouse_button.register_constant("MOUSE_BUTTON_BACK", MOUSE_BUTTON_BACK);

        // Enum: MouseCursor
        auto mouse_cursor = ns.create_object("MouseCursor");
        mouse_cursor.register_constant("MOUSE_CURSOR_DEFAULT", MOUSE_CURSOR_DEFAULT);
        mouse_cursor.register_constant("MOUSE_CURSOR_ARROW", MOUSE_CURSOR_ARROW);
        mouse_cursor.register_constant("MOUSE_CURSOR_IBEAM", MOUSE_CURSOR_IBEAM);
        mouse_cursor.register_constant("MOUSE_CURSOR_CROSSHAIR", MOUSE_CURSOR_CROSSHAIR);
        mouse_cursor.register_constant("MOUSE_CURSOR_POINTING_HAND", MOUSE_CURSOR_POINTING_HAND);
        mouse_cursor.register_constant("MOUSE_CURSOR_RESIZE_EW", MOUSE_CURSOR_RESIZE_EW);
        mouse_cursor.register_constant("MOUSE_CURSOR_RESIZE_NS", MOUSE_CURSOR_RESIZE_NS);
        mouse_cursor.register_constant("MOUSE_CURSOR_RESIZE_NWSE", MOUSE_CURSOR_RESIZE_NWSE);
        mouse_cursor.register_constant("MOUSE_CURSOR_RESIZE_NESW", MOUSE_CURSOR_RESIZE_NESW);
        mouse_cursor.register_constant("MOUSE_CURSOR_RESIZE_ALL", MOUSE_CURSOR_RESIZE_ALL);
        mouse_cursor.register_constant("MOUSE_CURSOR_NOT_ALLOWED", MOUSE_CURSOR_NOT_ALLOWED);

        // Enum: GamepadButton
        auto gamepad_button = ns.create_object("GamepadButton");
        gamepad_button.register_constant("GAMEPAD_BUTTON_UNKNOWN", GAMEPAD_BUTTON_UNKNOWN);
        gamepad_button.register_constant("GAMEPAD_BUTTON_LEFT_FACE_UP", GAMEPAD_BUTTON_LEFT_FACE_UP);
        gamepad_button.register_constant("GAMEPAD_BUTTON_LEFT_FACE_RIGHT", GAMEPAD_BUTTON_LEFT_FACE_RIGHT);
        gamepad_button.register_constant("GAMEPAD_BUTTON_LEFT_FACE_DOWN", GAMEPAD_BUTTON_LEFT_FACE_DOWN);
        gamepad_button.register_constant("GAMEPAD_BUTTON_LEFT_FACE_LEFT", GAMEPAD_BUTTON_LEFT_FACE_LEFT);
        gamepad_button.register_constant("GAMEPAD_BUTTON_RIGHT_FACE_UP", GAMEPAD_BUTTON_RIGHT_FACE_UP);
        gamepad_button.register_constant("GAMEPAD_BUTTON_RIGHT_FACE_RIGHT", GAMEPAD_BUTTON_RIGHT_FACE_RIGHT);
        gamepad_button.register_constant("GAMEPAD_BUTTON_RIGHT_FACE_DOWN", GAMEPAD_BUTTON_RIGHT_FACE_DOWN);
        gamepad_button.register_constant("GAMEPAD_BUTTON_RIGHT_FACE_LEFT", GAMEPAD_BUTTON_RIGHT_FACE_LEFT);
        gamepad_button.register_constant("GAMEPAD_BUTTON_LEFT_TRIGGER_1", GAMEPAD_BUTTON_LEFT_TRIGGER_1);
        gamepad_button.register_constant("GAMEPAD_BUTTON_LEFT_TRIGGER_2", GAMEPAD_BUTTON_LEFT_TRIGGER_2);
        gamepad_button.register_constant("GAMEPAD_BUTTON_RIGHT_TRIGGER_1", GAMEPAD_BUTTON_RIGHT_TRIGGER_1);
        gamepad_button.register_constant("GAMEPAD_BUTTON_RIGHT_TRIGGER_2", GAMEPAD_BUTTON_RIGHT_TRIGGER_2);
        gamepad_button.register_constant("GAMEPAD_BUTTON_MIDDLE_LEFT", GAMEPAD_BUTTON_MIDDLE_LEFT);
        gamepad_button.register_constant("GAMEPAD_BUTTON_MIDDLE", GAMEPAD_BUTTON_MIDDLE);
        gamepad_button.register_constant("GAMEPAD_BUTTON_MIDDLE_RIGHT", GAMEPAD_BUTTON_MIDDLE_RIGHT);
        gamepad_button.register_constant("GAMEPAD_BUTTON_LEFT_THUMB", GAMEPAD_BUTTON_LEFT_THUMB);
        gamepad_button.register_constant("GAMEPAD_BUTTON_RIGHT_THUMB", GAMEPAD_BUTTON_RIGHT_THUMB);

        // Enum: GamepadAxis
        auto gamepad_axis = ns.create_object("GamepadAxis");
        gamepad_axis.register_constant("GAMEPAD_AXIS_LEFT_X", GAMEPAD_AXIS_LEFT_X);
        gamepad_axis.register_constant("GAMEPAD_AXIS_LEFT_Y", GAMEPAD_AXIS_LEFT_Y);
        gamepad_axis.register_constant("GAMEPAD_AXIS_RIGHT_X", GAMEPAD_AXIS_RIGHT_X);
        gamepad_axis.register_constant("GAMEPAD_AXIS_RIGHT_Y", GAMEPAD_AXIS_RIGHT_Y);
        gamepad_axis.register_constant("GAMEPAD_AXIS_LEFT_TRIGGER", GAMEPAD_AXIS_LEFT_TRIGGER);
        gamepad_axis.register_constant("GAMEPAD_AXIS_RIGHT_TRIGGER", GAMEPAD_AXIS_RIGHT_TRIGGER);

        // Enum: CameraMode
        auto camera_mode = ns.create_object("CameraMode");
        camera_mode.register_constant("CAMERA_CUSTOM", CAMERA_CUSTOM);
        camera_mode.register_constant("CAMERA_FREE", CAMERA_FREE);
        camera_mode.register_constant("CAMERA_ORBITAL", CAMERA_ORBITAL);
        camera_mode.register_constant("CAMERA_FIRST_PERSON", CAMERA_FIRST_PERSON);
        camera_mode.register_constant("CAMERA_THIRD_PERSON", CAMERA_THIRD_PERSON);

        // Enum: CameraProjection
        auto camera_projection = ns.create_object("CameraProjection");
        camera_projection.register_constant("CAMERA_PERSPECTIVE", CAMERA_PERSPECTIVE);
        camera_projection.register_constant("CAMERA_ORTHOGRAPHIC", CAMERA_ORTHOGRAPHIC);

    }

}