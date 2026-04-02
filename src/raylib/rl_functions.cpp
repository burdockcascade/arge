#include "rl_bindings.hpp"
#include "../qjs/qjs_wrapper.hpp"

namespace RaylibBindings {

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

}