#include "rl_bindings.hpp"
#include "../qjs_wrapper.hpp"

namespace RaylibBindings {

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

}