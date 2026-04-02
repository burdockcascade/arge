#include "rl_bindings.hpp"
#include "qjs_wrapper.hpp"

// fixme: constructors are optional

namespace RaylibBindings {

    void InitAllStructs(qjs::ObjectBinder &ns) {
        
        // Vector2 
        ns.register_class<Vector2>("Vector2")
            .constructor()
            .constructor<float, float>()
            .field("x", &Vector2::x)
            .field("y", &Vector2::y)
            ;

        // Vector3 
        ns.register_class<Vector3>("Vector3")
            .constructor()
            .constructor<float, float, float>()
            .field("x", &Vector3::x)
            .field("y", &Vector3::y)
            .field("z", &Vector3::z)
            ;

        // Vector4 
        ns.register_class<Vector4>("Vector4")
            .constructor()
            .constructor<float, float, float, float>()
            .field("x", &Vector4::x)
            .field("y", &Vector4::y)
            .field("z", &Vector4::z)
            .field("w", &Vector4::w)
            ;

        // Matrix 
        ns.register_class<Matrix>("Matrix")
            .constructor()
            .field("m0", &Matrix::m0)
            .field("m4", &Matrix::m4)
            .field("m8", &Matrix::m8)
            .field("m12", &Matrix::m12)
            .field("m1", &Matrix::m1)
            .field("m5", &Matrix::m5)
            .field("m9", &Matrix::m9)
            .field("m13", &Matrix::m13)
            .field("m2", &Matrix::m2)
            .field("m6", &Matrix::m6)
            .field("m10", &Matrix::m10)
            .field("m14", &Matrix::m14)
            .field("m3", &Matrix::m3)
            .field("m7", &Matrix::m7)
            .field("m11", &Matrix::m11)
            .field("m15", &Matrix::m15)
            ;

        // Color 
        ns.register_class<Color>("Color")
            .constructor()
            .constructor<uint8_t, uint8_t, uint8_t, uint8_t>()
            .field("r", &Color::r)
            .field("g", &Color::g)
            .field("b", &Color::b)
            .field("a", &Color::a)
            .static_constant("LIGHTGRAY", LIGHTGRAY)
            .static_constant("GRAY", GRAY)
            .static_constant("DARKGRAY", DARKGRAY)
            .static_constant("YELLOW", YELLOW)
            .static_constant("GOLD", GOLD)
            .static_constant("ORANGE", ORANGE)
            .static_constant("PINK", PINK)
            .static_constant("RED", RED)
            .static_constant("MAROON", MAROON)
            .static_constant("GREEN", GREEN)
            .static_constant("LIME", LIME)
            .static_constant("DARKGREEN", DARKGREEN)
            .static_constant("SKYBLUE", SKYBLUE)
            .static_constant("BLUE", BLUE)
            .static_constant("DARKBLUE", DARKBLUE)
            .static_constant("PURPLE", PURPLE)
            .static_constant("VIOLET", VIOLET)
            .static_constant("DARKPURPLE", DARKPURPLE)
            .static_constant("BEIGE", BEIGE)
            .static_constant("BROWN", BROWN)
            .static_constant("DARKBROWN", DARKBROWN)
            .static_constant("WHITE", WHITE)
            .static_constant("BLACK", BLACK)
            .static_constant("BLANK", BLANK)
            .static_constant("MAGENTA", MAGENTA)
            .static_constant("RAYWHITE", RAYWHITE)
            ;

        // Rectangle 
        ns.register_class<Rectangle>("Rectangle")
            .constructor()
            .constructor<float, float, float, float>()
            .field("x", &Rectangle::x)
            .field("y", &Rectangle::y)
            .field("width", &Rectangle::width)
            .field("height", &Rectangle::height)
            ;

        // Image 
        ns.register_class<Image>("Image")
            .constructor()
            .field("data", &Image::data)
            .field("width", &Image::width)
            .field("height", &Image::height)
            .field("mipmaps", &Image::mipmaps)
            .field("format", &Image::format)
            ;

        // Texture 
        ns.register_class<Texture>("Texture")
            .constructor()
            .field("id", &Texture::id)
            .field("width", &Texture::width)
            .field("height", &Texture::height)
            .field("mipmaps", &Texture::mipmaps)
            .field("format", &Texture::format)
            ;


    }

    void InitAllFunctions(qjs::ObjectBinder &global) {
        
        global.register_function("InitWindow", [](int width, int height, const std::string& title) {
           ::InitWindow(width, height, title.c_str());
        });

        global.register_function("CloseWindow", ::CloseWindow);
        global.register_function("WindowShouldClose", ::WindowShouldClose);
        global.register_function("IsWindowReady", ::IsWindowReady);
        global.register_function("IsWindowFullscreen", ::IsWindowFullscreen);
        global.register_function("IsWindowHidden", ::IsWindowHidden);
        global.register_function("IsWindowMinimized", ::IsWindowMinimized);
        global.register_function("IsWindowMaximized", ::IsWindowMaximized);
        global.register_function("IsWindowFocused", ::IsWindowFocused);
        global.register_function("IsWindowResized", ::IsWindowResized);
        global.register_function("IsWindowState", ::IsWindowState);
        global.register_function("SetWindowState", ::SetWindowState);
        global.register_function("ClearWindowState", ::ClearWindowState);

        global.register_function("SetWindowTitle", [](const std::string& title) {
            ::SetWindowTitle(title.c_str());
        });

        global.register_function("GetScreenWidth", ::GetScreenWidth);
        global.register_function("GetScreenHeight", ::GetScreenHeight);
        global.register_function("GetRenderWidth", ::GetRenderWidth);
        global.register_function("GetRenderHeight", ::GetRenderHeight);
        global.register_function("GetMonitorCount", ::GetMonitorCount);
        global.register_function("GetMonitorWidth", ::GetMonitorWidth);
        global.register_function("GetMonitorHeight", ::GetMonitorHeight);
        global.register_function("GetMonitorPhysicalWidth", ::GetMonitorPhysicalWidth);
        global.register_function("GetMonitorPhysicalHeight", ::GetMonitorPhysicalHeight);
        global.register_function("GetMonitorRefreshRate", ::GetMonitorRefreshRate);
        global.register_function("GetWindowPosition", ::GetWindowPosition);
        global.register_function("GetWindowScaleDPI", ::GetWindowScaleDPI);
        global.register_function("ClearBackground", ::ClearBackground);
        global.register_function("BeginDrawing", ::BeginDrawing);
        global.register_function("EndDrawing", ::EndDrawing);
        global.register_function("SetTargetFPS", ::SetTargetFPS);
        global.register_function("GetFrameTime", ::GetFrameTime);

        global.register_function("TraceLog", [](const int level, const std::string& message) {
            ::TraceLog(level, "%s", message.c_str());
        });

        global.register_function("IsKeyPressed", ::IsKeyPressed);
        global.register_function("IsKeyPressedRepeat", ::IsKeyPressedRepeat);
        global.register_function("IsKeyDown", ::IsKeyDown);
        global.register_function("IsKeyReleased", ::IsKeyReleased);
        global.register_function("IsKeyUp", ::IsKeyUp);
        global.register_function("GetKeyPressed", ::GetKeyPressed);
        global.register_function("SetExitKey", ::SetExitKey);
        global.register_function("IsMouseButtonPressed", ::IsMouseButtonPressed);
        global.register_function("IsMouseButtonDown", ::IsMouseButtonDown);
        global.register_function("IsMouseButtonReleased", ::IsMouseButtonReleased);
        global.register_function("IsMouseButtonUp", ::IsMouseButtonUp);
        global.register_function("GetMouseX", ::GetMouseX);
        global.register_function("GetMouseY", ::GetMouseY);
        global.register_function("GetMousePosition", ::GetMousePosition);
        global.register_function("SetMousePosition", ::SetMousePosition);
        global.register_function("SetMouseOffset", ::SetMouseOffset);
        global.register_function("SetMouseScale", ::SetMouseScale);
        global.register_function("GetMouseWheelMove", ::GetMouseWheelMove);
        global.register_function("GetMouseWheelMoveV", ::GetMouseWheelMoveV);
        global.register_function("DrawPixel", ::DrawPixel);
        global.register_function("DrawPixelV", ::DrawPixelV);
        global.register_function("DrawLine", ::DrawLine);
        global.register_function("DrawLineV", ::DrawLineV);
        global.register_function("DrawLineEx", ::DrawLineEx);
        global.register_function("DrawLineStrip", ::DrawLineStrip);
        global.register_function("DrawLineBezier", ::DrawLineBezier);
        global.register_function("DrawCircle", ::DrawCircle);
        global.register_function("DrawRectangle", ::DrawRectangle);
        global.register_function("LoadTexture", [](const std::string& filename) {
            return ::LoadTexture(filename.c_str());
        });
        global.register_function("UnloadTexture", ::UnloadTexture);
        global.register_function("DrawTexture", ::DrawTexture);
        global.register_function("DrawFPS", ::DrawFPS);
        global.register_function("DrawText", [](const std::string& text, int x, int y, int fontSize, Color color) {
            ::DrawText(text.c_str(), x, y, fontSize, color);
        });
    }

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

    void InternalRegister(qjs::Engine &engine) {
        auto global = engine.get_global_object();
        auto rl = global.create_object("_rl");
        InitAllFunctions(rl);
        InitAllEnums(global);
        InitAllStructs(global);
    }

}