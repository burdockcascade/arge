#include "../qjs/qjs_wrapper.hpp"
#include <raylib.h>
#include "rl_bindings.hpp"

namespace RaylibBindings {

    // void InitAllStructs(qjs::ObjectBinder &ns) {
        
    //     // Vector2 
    //     ns.register_class<Vector2>("Vector2")
    //         .constructor()
    //         .constructor<float, float>()
    //         .field("x", &Vector2::x)
    //         .field("y", &Vector2::y);

    //     // Vector3 
    //     ns.register_class<Vector3>("Vector3")
    //         .constructor()
    //         .constructor<float, float, float>()
    //         .field("x", &Vector3::x)
    //         .field("y", &Vector3::y)
    //         .field("z", &Vector3::z);

    //     // Vector4 
    //     ns.register_class<Vector4>("Vector4")
    //         .constructor()
    //         .constructor<float, float, float, float>()
    //         .field("x", &Vector4::x)
    //         .field("y", &Vector4::y)
    //         .field("z", &Vector4::z)
    //         .field("w", &Vector4::w);

    //     // Matrix 
    //     ns.register_class<Matrix>("Matrix")
    //         .constructor()
    //         .field("m0", &Matrix::m0)
    //         .field("m4", &Matrix::m4)
    //         .field("m8", &Matrix::m8)
    //         .field("m12", &Matrix::m12)
    //         .field("m1", &Matrix::m1)
    //         .field("m5", &Matrix::m5)
    //         .field("m9", &Matrix::m9)
    //         .field("m13", &Matrix::m13)
    //         .field("m2", &Matrix::m2)
    //         .field("m6", &Matrix::m6)
    //         .field("m10", &Matrix::m10)
    //         .field("m14", &Matrix::m14)
    //         .field("m3", &Matrix::m3)
    //         .field("m7", &Matrix::m7)
    //         .field("m11", &Matrix::m11)
    //         .field("m15", &Matrix::m15);

    //     // Color 
    //     ns.register_class<Color>("Color")
    //         .constructor()
    //         .constructor<uint8_t, uint8_t, uint8_t, uint8_t>()
    //         .field("r", &Color::r)
    //         .field("g", &Color::g)
    //         .field("b", &Color::b)
    //         .field("a", &Color::a)
    //         .static_constant("LIGHTGRAY", LIGHTGRAY)
    //         .static_constant("GRAY", GRAY)
    //         .static_constant("DARKGRAY", DARKGRAY)
    //         .static_constant("YELLOW", YELLOW)
    //         .static_constant("GOLD", GOLD)
    //         .static_constant("ORANGE", ORANGE)
    //         .static_constant("PINK", PINK)
    //         .static_constant("RED", RED)
    //         .static_constant("MAROON", MAROON)
    //         .static_constant("GREEN", GREEN)
    //         .static_constant("LIME", LIME)
    //         .static_constant("DARKGREEN", DARKGREEN)
    //         .static_constant("SKYBLUE", SKYBLUE)
    //         .static_constant("BLUE", BLUE)
    //         .static_constant("DARKBLUE", DARKBLUE)
    //         .static_constant("PURPLE", PURPLE)
    //         .static_constant("VIOLET", VIOLET)
    //         .static_constant("DARKPURPLE", DARKPURPLE)
    //         .static_constant("BEIGE", BEIGE)
    //         .static_constant("BROWN", BROWN)
    //         .static_constant("DARKBROWN", DARKBROWN)
    //         .static_constant("WHITE", WHITE)
    //         .static_constant("BLACK", BLACK)
    //         .static_constant("BLANK", BLANK)
    //         .static_constant("MAGENTA", MAGENTA)
    //         .static_constant("RAYWHITE", RAYWHITE)
    //         .static_method("GetRandomColor", []() {
    //             Color c;
    //             c.r = GetRandomValue(0, 255);
    //             c.g = GetRandomValue(0, 255);
    //             c.b = GetRandomValue(0, 255);
    //             c.a = 255;
    //             return c;
    //         });

    //     // Rectangle 
    //     ns.register_class<Rectangle>("Rectangle")
    //         .constructor()
    //         .constructor<float, float, float, float>()
    //         .field("x", &Rectangle::x)
    //         .field("y", &Rectangle::y)
    //         .field("width", &Rectangle::width)
    //         .field("height", &Rectangle::height);

    //     // Image 
    //     ns.register_class<Image>("Image")
    //         .constructor()
    //         .field("data", &Image::data)
    //         .field("width", &Image::width)
    //         .field("height", &Image::height)
    //         .field("mipmaps", &Image::mipmaps)
    //         .field("format", &Image::format);

    //     // Texture 
    //     ns.register_class<Texture>("Texture")
    //         .constructor()
    //         .field("id", &Texture::id)
    //         .field("width", &Texture::width)
    //         .field("height", &Texture::height)
    //         .field("mipmaps", &Texture::mipmaps)
    //         .field("format", &Texture::format);


    // }

    void InitAllFunctions(qjs::ObjectBinder &ns) {

        ns.register_function("InitWindow", [](int width, int height, const std::string& title) {
           ::InitWindow(width, height, title.c_str());
        });

        ns.register_function("CloseWindow", ::CloseWindow);
        ns.register_function("WindowShouldClose", ::WindowShouldClose);
        ns.register_function("IsWindowReady", ::IsWindowReady);
        ns.register_function("IsWindowFullscreen", ::IsWindowFullscreen);
        ns.register_function("IsWindowHidden", ::IsWindowHidden);
        ns.register_function("IsWindowMinimized", ::IsWindowMinimized);
        ns.register_function("IsWindowMaximized", ::IsWindowMaximized);
        ns.register_function("IsWindowFocused", ::IsWindowFocused);
        ns.register_function("IsWindowResized", ::IsWindowResized);
        ns.register_function("IsWindowState", ::IsWindowState);
        ns.register_function("SetWindowState", ::SetWindowState);
        ns.register_function("ClearWindowState", ::ClearWindowState);

        ns.register_function("SetWindowTitle", [](const std::string& title) {
            ::SetWindowTitle(title.c_str());
        });

        ns.register_function("GetScreenWidth", ::GetScreenWidth);
        ns.register_function("GetScreenHeight", ::GetScreenHeight);
        ns.register_function("GetRenderWidth", ::GetRenderWidth);
        ns.register_function("GetRenderHeight", ::GetRenderHeight);
        ns.register_function("GetMonitorCount", ::GetMonitorCount);
        ns.register_function("GetMonitorWidth", ::GetMonitorWidth);
        ns.register_function("GetMonitorHeight", ::GetMonitorHeight);
        ns.register_function("GetMonitorPhysicalWidth", ::GetMonitorPhysicalWidth);
        ns.register_function("GetMonitorPhysicalHeight", ::GetMonitorPhysicalHeight);
        ns.register_function("GetMonitorRefreshRate", ::GetMonitorRefreshRate);
        ns.register_function("GetWindowPosition", ::GetWindowPosition);
        ns.register_function("GetWindowScaleDPI", ::GetWindowScaleDPI);

        ns.register_function("ClearBackground", ::ClearBackground);
        ns.register_function("BeginDrawing", ::BeginDrawing);
        ns.register_function("EndDrawing", ::EndDrawing);
        ns.register_function("SetTargetFPS", ::SetTargetFPS);
        ns.register_function("GetFrameTime", ::GetFrameTime);

        ns.register_function("TraceLog", [](const int level, const std::string& message) {
            ::TraceLog(level, "%s", message.c_str());
        });

        // Keyboard
        ns.register_function("IsKeyPressed", ::IsKeyPressed);
        ns.register_function("IsKeyPressedRepeat", ::IsKeyPressedRepeat);
        ns.register_function("IsKeyDown", ::IsKeyDown);
        ns.register_function("IsKeyReleased", ::IsKeyReleased);
        ns.register_function("IsKeyUp", ::IsKeyUp);
        ns.register_function("GetKeyPressed", ::GetKeyPressed);
        ns.register_function("SetExitKey", ::SetExitKey);

        // Mouse
        ns.register_function("IsMouseButtonPressed", ::IsMouseButtonPressed);
        ns.register_function("IsMouseButtonDown", ::IsMouseButtonDown);
        ns.register_function("IsMouseButtonReleased", ::IsMouseButtonReleased);
        ns.register_function("IsMouseButtonUp", ::IsMouseButtonUp);
        ns.register_function("GetMouseX", ::GetMouseX);
        ns.register_function("GetMouseY", ::GetMouseY);
        ns.register_function("GetMousePosition", ::GetMousePosition);
        ns.register_function("SetMousePosition", ::SetMousePosition);
        ns.register_function("SetMouseOffset", ::SetMouseOffset);
        ns.register_function("SetMouseScale", ::SetMouseScale);
        ns.register_function("GetMouseWheelMove", ::GetMouseWheelMove);
        ns.register_function("GetMouseWheelMoveV", ::GetMouseWheelMoveV);

        // Draw
        ns.register_function("DrawPixel", ::DrawPixel);
        ns.register_function("DrawPixelV", ::DrawPixelV);
        ns.register_function("DrawLine", ::DrawLine);
        ns.register_function("DrawLineV", ::DrawLineV);
        ns.register_function("DrawLineEx", ::DrawLineEx);
        ns.register_function("DrawLineStrip", ::DrawLineStrip);
        ns.register_function("DrawLineBezier", ::DrawLineBezier);
        ns.register_function("DrawCircle", ::DrawCircle);
        ns.register_function("DrawRectangle", ::DrawRectangle);
        ns.register_function("DrawTexture", ::DrawTexture);
        ns.register_function("DrawFPS", ::DrawFPS);
        ns.register_function("DrawText", [](const std::string& text, int x, int y, int fontSize, Color color) {
            ::DrawText(text.c_str(), x, y, fontSize, color);
        });

        // Textures
        ns.register_function("LoadTexture", [](const std::string& filename) {
            return ::LoadTexture(filename.c_str());
        });
        ns.register_function("UnloadTexture", ::UnloadTexture);
    }

    void InitAllEnums(qjs::ObjectBinder &ns) {

        // Enum: ConfigFlags
        auto ConfigFlags_ns = ns.create_object("ConfigFlags");
        ConfigFlags_ns.register_constant("FLAG_VSYNC_HINT", FLAG_VSYNC_HINT);
        ConfigFlags_ns.register_constant("FLAG_FULLSCREEN_MODE", FLAG_FULLSCREEN_MODE);
        ConfigFlags_ns.register_constant("FLAG_WINDOW_RESIZABLE", FLAG_WINDOW_RESIZABLE);
        ConfigFlags_ns.register_constant("FLAG_WINDOW_UNDECORATED", FLAG_WINDOW_UNDECORATED);
        ConfigFlags_ns.register_constant("FLAG_WINDOW_HIDDEN", FLAG_WINDOW_HIDDEN);
        ConfigFlags_ns.register_constant("FLAG_WINDOW_MINIMIZED", FLAG_WINDOW_MINIMIZED);
        ConfigFlags_ns.register_constant("FLAG_WINDOW_MAXIMIZED", FLAG_WINDOW_MAXIMIZED);
        ConfigFlags_ns.register_constant("FLAG_WINDOW_UNFOCUSED", FLAG_WINDOW_UNFOCUSED);
        ConfigFlags_ns.register_constant("FLAG_WINDOW_TOPMOST", FLAG_WINDOW_TOPMOST);
        ConfigFlags_ns.register_constant("FLAG_WINDOW_ALWAYS_RUN", FLAG_WINDOW_ALWAYS_RUN);
        ConfigFlags_ns.register_constant("FLAG_WINDOW_TRANSPARENT", FLAG_WINDOW_TRANSPARENT);
        ConfigFlags_ns.register_constant("FLAG_WINDOW_HIGHDPI", FLAG_WINDOW_HIGHDPI);
        ConfigFlags_ns.register_constant("FLAG_WINDOW_MOUSE_PASSTHROUGH", FLAG_WINDOW_MOUSE_PASSTHROUGH);
        ConfigFlags_ns.register_constant("FLAG_BORDERLESS_WINDOWED_MODE", FLAG_BORDERLESS_WINDOWED_MODE);
        ConfigFlags_ns.register_constant("FLAG_MSAA_4X_HINT", FLAG_MSAA_4X_HINT);
        ConfigFlags_ns.register_constant("FLAG_INTERLACED_HINT", FLAG_INTERLACED_HINT);

        // Enum: KeyboardKey
        auto KeyboardKey_ns = ns.create_object("KeyboardKey");
        KeyboardKey_ns.register_constant("KEY_NULL", KEY_NULL);
        KeyboardKey_ns.register_constant("KEY_APOSTROPHE", KEY_APOSTROPHE);
        KeyboardKey_ns.register_constant("KEY_COMMA", KEY_COMMA);
        KeyboardKey_ns.register_constant("KEY_MINUS", KEY_MINUS);
        KeyboardKey_ns.register_constant("KEY_PERIOD", KEY_PERIOD);
        KeyboardKey_ns.register_constant("KEY_SLASH", KEY_SLASH);
        KeyboardKey_ns.register_constant("KEY_ZERO", KEY_ZERO);
        KeyboardKey_ns.register_constant("KEY_ONE", KEY_ONE);
        KeyboardKey_ns.register_constant("KEY_TWO", KEY_TWO);
        KeyboardKey_ns.register_constant("KEY_THREE", KEY_THREE);
        KeyboardKey_ns.register_constant("KEY_FOUR", KEY_FOUR);
        KeyboardKey_ns.register_constant("KEY_FIVE", KEY_FIVE);
        KeyboardKey_ns.register_constant("KEY_SIX", KEY_SIX);
        KeyboardKey_ns.register_constant("KEY_SEVEN", KEY_SEVEN);
        KeyboardKey_ns.register_constant("KEY_EIGHT", KEY_EIGHT);
        KeyboardKey_ns.register_constant("KEY_NINE", KEY_NINE);
        KeyboardKey_ns.register_constant("KEY_SEMICOLON", KEY_SEMICOLON);
        KeyboardKey_ns.register_constant("KEY_EQUAL", KEY_EQUAL);
        KeyboardKey_ns.register_constant("KEY_A", KEY_A);
        KeyboardKey_ns.register_constant("KEY_B", KEY_B);
        KeyboardKey_ns.register_constant("KEY_C", KEY_C);
        KeyboardKey_ns.register_constant("KEY_D", KEY_D);
        KeyboardKey_ns.register_constant("KEY_E", KEY_E);
        KeyboardKey_ns.register_constant("KEY_F", KEY_F);
        KeyboardKey_ns.register_constant("KEY_G", KEY_G);
        KeyboardKey_ns.register_constant("KEY_H", KEY_H);
        KeyboardKey_ns.register_constant("KEY_I", KEY_I);
        KeyboardKey_ns.register_constant("KEY_J", KEY_J);
        KeyboardKey_ns.register_constant("KEY_K", KEY_K);
        KeyboardKey_ns.register_constant("KEY_L", KEY_L);
        KeyboardKey_ns.register_constant("KEY_M", KEY_M);
        KeyboardKey_ns.register_constant("KEY_N", KEY_N);
        KeyboardKey_ns.register_constant("KEY_O", KEY_O);
        KeyboardKey_ns.register_constant("KEY_P", KEY_P);
        KeyboardKey_ns.register_constant("KEY_Q", KEY_Q);
        KeyboardKey_ns.register_constant("KEY_R", KEY_R);
        KeyboardKey_ns.register_constant("KEY_S", KEY_S);
        KeyboardKey_ns.register_constant("KEY_T", KEY_T);
        KeyboardKey_ns.register_constant("KEY_U", KEY_U);
        KeyboardKey_ns.register_constant("KEY_V", KEY_V);
        KeyboardKey_ns.register_constant("KEY_W", KEY_W);
        KeyboardKey_ns.register_constant("KEY_X", KEY_X);
        KeyboardKey_ns.register_constant("KEY_Y", KEY_Y);
        KeyboardKey_ns.register_constant("KEY_Z", KEY_Z);
        KeyboardKey_ns.register_constant("KEY_LEFT_BRACKET", KEY_LEFT_BRACKET);
        KeyboardKey_ns.register_constant("KEY_BACKSLASH", KEY_BACKSLASH);
        KeyboardKey_ns.register_constant("KEY_RIGHT_BRACKET", KEY_RIGHT_BRACKET);
        KeyboardKey_ns.register_constant("KEY_GRAVE", KEY_GRAVE);
        KeyboardKey_ns.register_constant("KEY_SPACE", KEY_SPACE);
        KeyboardKey_ns.register_constant("KEY_ESCAPE", KEY_ESCAPE);
        KeyboardKey_ns.register_constant("KEY_ENTER", KEY_ENTER);
        KeyboardKey_ns.register_constant("KEY_TAB", KEY_TAB);
        KeyboardKey_ns.register_constant("KEY_BACKSPACE", KEY_BACKSPACE);
        KeyboardKey_ns.register_constant("KEY_INSERT", KEY_INSERT);
        KeyboardKey_ns.register_constant("KEY_DELETE", KEY_DELETE);
        KeyboardKey_ns.register_constant("KEY_RIGHT", KEY_RIGHT);
        KeyboardKey_ns.register_constant("KEY_LEFT", KEY_LEFT);
        KeyboardKey_ns.register_constant("KEY_DOWN", KEY_DOWN);
        KeyboardKey_ns.register_constant("KEY_UP", KEY_UP);
        KeyboardKey_ns.register_constant("KEY_PAGE_UP", KEY_PAGE_UP);
        KeyboardKey_ns.register_constant("KEY_PAGE_DOWN", KEY_PAGE_DOWN);
        KeyboardKey_ns.register_constant("KEY_HOME", KEY_HOME);
        KeyboardKey_ns.register_constant("KEY_END", KEY_END);
        KeyboardKey_ns.register_constant("KEY_CAPS_LOCK", KEY_CAPS_LOCK);
        KeyboardKey_ns.register_constant("KEY_SCROLL_LOCK", KEY_SCROLL_LOCK);
        KeyboardKey_ns.register_constant("KEY_NUM_LOCK", KEY_NUM_LOCK);
        KeyboardKey_ns.register_constant("KEY_PRINT_SCREEN", KEY_PRINT_SCREEN);
        KeyboardKey_ns.register_constant("KEY_PAUSE", KEY_PAUSE);
        KeyboardKey_ns.register_constant("KEY_F1", KEY_F1);
        KeyboardKey_ns.register_constant("KEY_F2", KEY_F2);
        KeyboardKey_ns.register_constant("KEY_F3", KEY_F3);
        KeyboardKey_ns.register_constant("KEY_F4", KEY_F4);
        KeyboardKey_ns.register_constant("KEY_F5", KEY_F5);
        KeyboardKey_ns.register_constant("KEY_F6", KEY_F6);
        KeyboardKey_ns.register_constant("KEY_F7", KEY_F7);
        KeyboardKey_ns.register_constant("KEY_F8", KEY_F8);
        KeyboardKey_ns.register_constant("KEY_F9", KEY_F9);
        KeyboardKey_ns.register_constant("KEY_F10", KEY_F10);
        KeyboardKey_ns.register_constant("KEY_F11", KEY_F11);
        KeyboardKey_ns.register_constant("KEY_F12", KEY_F12);
        KeyboardKey_ns.register_constant("KEY_LEFT_SHIFT", KEY_LEFT_SHIFT);
        KeyboardKey_ns.register_constant("KEY_LEFT_CONTROL", KEY_LEFT_CONTROL);
        KeyboardKey_ns.register_constant("KEY_LEFT_ALT", KEY_LEFT_ALT);
        KeyboardKey_ns.register_constant("KEY_LEFT_SUPER", KEY_LEFT_SUPER);
        KeyboardKey_ns.register_constant("KEY_RIGHT_SHIFT", KEY_RIGHT_SHIFT);
        KeyboardKey_ns.register_constant("KEY_RIGHT_CONTROL", KEY_RIGHT_CONTROL);
        KeyboardKey_ns.register_constant("KEY_RIGHT_ALT", KEY_RIGHT_ALT);
        KeyboardKey_ns.register_constant("KEY_RIGHT_SUPER", KEY_RIGHT_SUPER);
        KeyboardKey_ns.register_constant("KEY_KB_MENU", KEY_KB_MENU);
        KeyboardKey_ns.register_constant("KEY_KP_0", KEY_KP_0);
        KeyboardKey_ns.register_constant("KEY_KP_1", KEY_KP_1);
        KeyboardKey_ns.register_constant("KEY_KP_2", KEY_KP_2);
        KeyboardKey_ns.register_constant("KEY_KP_3", KEY_KP_3);
        KeyboardKey_ns.register_constant("KEY_KP_4", KEY_KP_4);
        KeyboardKey_ns.register_constant("KEY_KP_5", KEY_KP_5);
        KeyboardKey_ns.register_constant("KEY_KP_6", KEY_KP_6);
        KeyboardKey_ns.register_constant("KEY_KP_7", KEY_KP_7);
        KeyboardKey_ns.register_constant("KEY_KP_8", KEY_KP_8);
        KeyboardKey_ns.register_constant("KEY_KP_9", KEY_KP_9);
        KeyboardKey_ns.register_constant("KEY_KP_DECIMAL", KEY_KP_DECIMAL);
        KeyboardKey_ns.register_constant("KEY_KP_DIVIDE", KEY_KP_DIVIDE);
        KeyboardKey_ns.register_constant("KEY_KP_MULTIPLY", KEY_KP_MULTIPLY);
        KeyboardKey_ns.register_constant("KEY_KP_SUBTRACT", KEY_KP_SUBTRACT);
        KeyboardKey_ns.register_constant("KEY_KP_ADD", KEY_KP_ADD);
        KeyboardKey_ns.register_constant("KEY_KP_ENTER", KEY_KP_ENTER);
        KeyboardKey_ns.register_constant("KEY_KP_EQUAL", KEY_KP_EQUAL);
        KeyboardKey_ns.register_constant("KEY_BACK", KEY_BACK);
        KeyboardKey_ns.register_constant("KEY_MENU", KEY_MENU);
        KeyboardKey_ns.register_constant("KEY_VOLUME_UP", KEY_VOLUME_UP);
        KeyboardKey_ns.register_constant("KEY_VOLUME_DOWN", KEY_VOLUME_DOWN);

        // Enum: MouseButton
        auto MouseButton_ns = ns.create_object("MouseButton");
        MouseButton_ns.register_constant("MOUSE_BUTTON_LEFT", MOUSE_BUTTON_LEFT);
        MouseButton_ns.register_constant("MOUSE_BUTTON_RIGHT", MOUSE_BUTTON_RIGHT);
        MouseButton_ns.register_constant("MOUSE_BUTTON_MIDDLE", MOUSE_BUTTON_MIDDLE);
        MouseButton_ns.register_constant("MOUSE_BUTTON_SIDE", MOUSE_BUTTON_SIDE);
        MouseButton_ns.register_constant("MOUSE_BUTTON_EXTRA", MOUSE_BUTTON_EXTRA);
        MouseButton_ns.register_constant("MOUSE_BUTTON_FORWARD", MOUSE_BUTTON_FORWARD);
        MouseButton_ns.register_constant("MOUSE_BUTTON_BACK", MOUSE_BUTTON_BACK);

        // Enum: MouseCursor
        auto MouseCursor_ns = ns.create_object("MouseCursor");
        MouseCursor_ns.register_constant("MOUSE_CURSOR_DEFAULT", MOUSE_CURSOR_DEFAULT);
        MouseCursor_ns.register_constant("MOUSE_CURSOR_ARROW", MOUSE_CURSOR_ARROW);
        MouseCursor_ns.register_constant("MOUSE_CURSOR_IBEAM", MOUSE_CURSOR_IBEAM);
        MouseCursor_ns.register_constant("MOUSE_CURSOR_CROSSHAIR", MOUSE_CURSOR_CROSSHAIR);
        MouseCursor_ns.register_constant("MOUSE_CURSOR_POINTING_HAND", MOUSE_CURSOR_POINTING_HAND);
        MouseCursor_ns.register_constant("MOUSE_CURSOR_RESIZE_EW", MOUSE_CURSOR_RESIZE_EW);
        MouseCursor_ns.register_constant("MOUSE_CURSOR_RESIZE_NS", MOUSE_CURSOR_RESIZE_NS);
        MouseCursor_ns.register_constant("MOUSE_CURSOR_RESIZE_NWSE", MOUSE_CURSOR_RESIZE_NWSE);
        MouseCursor_ns.register_constant("MOUSE_CURSOR_RESIZE_NESW", MOUSE_CURSOR_RESIZE_NESW);
        MouseCursor_ns.register_constant("MOUSE_CURSOR_RESIZE_ALL", MOUSE_CURSOR_RESIZE_ALL);
        MouseCursor_ns.register_constant("MOUSE_CURSOR_NOT_ALLOWED", MOUSE_CURSOR_NOT_ALLOWED);

        // Enum: GamepadButton
        auto GamepadButton_ns = ns.create_object("GamepadButton");
        GamepadButton_ns.register_constant("GAMEPAD_BUTTON_UNKNOWN", GAMEPAD_BUTTON_UNKNOWN);
        GamepadButton_ns.register_constant("GAMEPAD_BUTTON_LEFT_FACE_UP", GAMEPAD_BUTTON_LEFT_FACE_UP);
        GamepadButton_ns.register_constant("GAMEPAD_BUTTON_LEFT_FACE_RIGHT", GAMEPAD_BUTTON_LEFT_FACE_RIGHT);
        GamepadButton_ns.register_constant("GAMEPAD_BUTTON_LEFT_FACE_DOWN", GAMEPAD_BUTTON_LEFT_FACE_DOWN);
        GamepadButton_ns.register_constant("GAMEPAD_BUTTON_LEFT_FACE_LEFT", GAMEPAD_BUTTON_LEFT_FACE_LEFT);
        GamepadButton_ns.register_constant("GAMEPAD_BUTTON_RIGHT_FACE_UP", GAMEPAD_BUTTON_RIGHT_FACE_UP);
        GamepadButton_ns.register_constant("GAMEPAD_BUTTON_RIGHT_FACE_RIGHT", GAMEPAD_BUTTON_RIGHT_FACE_RIGHT);
        GamepadButton_ns.register_constant("GAMEPAD_BUTTON_RIGHT_FACE_DOWN", GAMEPAD_BUTTON_RIGHT_FACE_DOWN);
        GamepadButton_ns.register_constant("GAMEPAD_BUTTON_RIGHT_FACE_LEFT", GAMEPAD_BUTTON_RIGHT_FACE_LEFT);
        GamepadButton_ns.register_constant("GAMEPAD_BUTTON_LEFT_TRIGGER_1", GAMEPAD_BUTTON_LEFT_TRIGGER_1);
        GamepadButton_ns.register_constant("GAMEPAD_BUTTON_LEFT_TRIGGER_2", GAMEPAD_BUTTON_LEFT_TRIGGER_2);
        GamepadButton_ns.register_constant("GAMEPAD_BUTTON_RIGHT_TRIGGER_1", GAMEPAD_BUTTON_RIGHT_TRIGGER_1);
        GamepadButton_ns.register_constant("GAMEPAD_BUTTON_RIGHT_TRIGGER_2", GAMEPAD_BUTTON_RIGHT_TRIGGER_2);
        GamepadButton_ns.register_constant("GAMEPAD_BUTTON_MIDDLE_LEFT", GAMEPAD_BUTTON_MIDDLE_LEFT);
        GamepadButton_ns.register_constant("GAMEPAD_BUTTON_MIDDLE", GAMEPAD_BUTTON_MIDDLE);
        GamepadButton_ns.register_constant("GAMEPAD_BUTTON_MIDDLE_RIGHT", GAMEPAD_BUTTON_MIDDLE_RIGHT);
        GamepadButton_ns.register_constant("GAMEPAD_BUTTON_LEFT_THUMB", GAMEPAD_BUTTON_LEFT_THUMB);
        GamepadButton_ns.register_constant("GAMEPAD_BUTTON_RIGHT_THUMB", GAMEPAD_BUTTON_RIGHT_THUMB);

        // Enum: GamepadAxis
        auto GamepadAxis_ns = ns.create_object("GamepadAxis");
        GamepadAxis_ns.register_constant("GAMEPAD_AXIS_LEFT_X", GAMEPAD_AXIS_LEFT_X);
        GamepadAxis_ns.register_constant("GAMEPAD_AXIS_LEFT_Y", GAMEPAD_AXIS_LEFT_Y);
        GamepadAxis_ns.register_constant("GAMEPAD_AXIS_RIGHT_X", GAMEPAD_AXIS_RIGHT_X);
        GamepadAxis_ns.register_constant("GAMEPAD_AXIS_RIGHT_Y", GAMEPAD_AXIS_RIGHT_Y);
        GamepadAxis_ns.register_constant("GAMEPAD_AXIS_LEFT_TRIGGER", GAMEPAD_AXIS_LEFT_TRIGGER);
        GamepadAxis_ns.register_constant("GAMEPAD_AXIS_RIGHT_TRIGGER", GAMEPAD_AXIS_RIGHT_TRIGGER);

        // Enum: CameraMode
        auto CameraMode_ns = ns.create_object("CameraMode");
        CameraMode_ns.register_constant("CAMERA_CUSTOM", CAMERA_CUSTOM);
        CameraMode_ns.register_constant("CAMERA_FREE", CAMERA_FREE);
        CameraMode_ns.register_constant("CAMERA_ORBITAL", CAMERA_ORBITAL);
        CameraMode_ns.register_constant("CAMERA_FIRST_PERSON", CAMERA_FIRST_PERSON);
        CameraMode_ns.register_constant("CAMERA_THIRD_PERSON", CAMERA_THIRD_PERSON);

        // Enum: CameraProjection
        auto CameraProjection_ns = ns.create_object("CameraProjection");
        CameraProjection_ns.register_constant("CAMERA_PERSPECTIVE", CAMERA_PERSPECTIVE);
        CameraProjection_ns.register_constant("CAMERA_ORTHOGRAPHIC", CAMERA_ORTHOGRAPHIC);

    }

    void InitRaylib(qjs::Engine &engine) {

        SetRandomSeed(static_cast<unsigned int>(time(NULL)));

        auto global = engine.get_global_object();
        auto rl = global.create_object("_rl");
        InitAllFunctions(rl);
        InitAllEnums(global);
        //InitAllStructs(global);
    }

}