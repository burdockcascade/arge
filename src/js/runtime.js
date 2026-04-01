// === Contexts ===

const initContext = {
    GetScreenWidth: _rl.GetScreenWidth,
    GetScreenHeight: _rl.GetScreenHeight,
    GetMonitorPhysicalWidth: _rl.GetMonitorPhysicalWidth,
    GetMonitorPhysicalHeight: _rl.GetMonitorPhysicalHeight,
    GetMonitorCount: _rl.GetMonitorCount,
    GetMonitorRefreshRate: _rl.GetMonitorRefreshRate,
}

const updateContext = {
    GetFrameTime: _rl.GetFrameTime,
    Input: {
        IsKeyDown: _rl.IsKeyDown,
        IsKeyUp: _rl.IsKeyUp,
        IsKeyPressed: _rl.IsKeyPressed,
    },
    Mouse: {
        GetPosition: _rl.GetMousePosition,
        GetDelta: _rl.GetMouseDelta,
        IsButtonDown: _rl.IsMouseButtonDown,
        IsButtonUp: _rl.IsMouseButtonUp,
        IsButtonPressed: _rl.IsMouseButtonPressed,
    },
    Window: {
        IsReady: _rl.IsWindowReady,
        IsMinimized: _rl.IsWindowMinimized,
        IsResized: _rl.IsWindowResized,
        IsHidden: _rl.IsWindowHidden,
        IsFocused: _rl.IsWindowFocused,
        IsFullscreen: _rl.IsFullscreen,
        ToggleFullscreen: _rl.ToggleFullscreen,
        SetTitle: _rl.SetWindowTitle,
        SetTargetFPS: _rl.SetTargetFPS,
    },
    Screen: {
        GetWidth: _rl.GetScreenWidth,
        GetHeight: _rl.GetScreenHeight,
    },
    Monitor: {
        GetCount: _rl.GetMonitorCount,
        GetWidth: _rl.GetMonitorWidth,
        GetHeight: _rl.GetMonitorHeight,
        GetPhysicalWidth: _rl.GetMonitorPhysicalWidth,
        GetPhysicalHeight: _rl.GetMonitorPhysicalHeight,
        GetRefreshRate: _rl.GetMonitorRefreshRate,
    },

}

const drawContext2D = {
    DrawFPS: (position) => _rl.DrawFPS(position.x, position.y),
    DrawRectangle: (position, size, color) => _rl.DrawRectangle(position.x, position.y, size.x, size.y, color),
    DrawCircle: (position, radius, color) => _rl.DrawCircle(position.x, position.y, radius, color),
    DrawText: (text, position, size, color) => _rl.DrawText(text, position.x, position.y, size, color)
}

const renderContext = {
    WithLayer2D: (cb) => {
        cb(drawContext2D);
    }
}

class App {

    constructor(height, width, title, options = {}) {
        this.height = height;
        this.width = width;
        this.title = title;
        this.fps = options.fps || 60;
    }

    run(game) {

        _rl.InitWindow(this.width, this.height, this.title);

        _rl.SetTargetFPS(this.fps);

        if (game.start) {
            game.start(initContext);
        }

        while (!_rl.WindowShouldClose()) {

            if (game.update) {
                game.update(_rl.GetFrameTime(), updateContext);
            }

            _rl.BeginDrawing();

            _rl.ClearBackground(Color.WHITE);

            if (game.draw) {
                game.draw(renderContext);
            }

            _rl.EndDrawing();
        }

        if (game.end) {
            game.end();
        }

        _rl.CloseWindow();
    }

}

globalThis.App = App;
