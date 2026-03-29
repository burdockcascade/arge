export class Vector2 {
    constructor(x = 0, y = 0) {
        this.x = x;
        this.y = y;
    }
}

const DrawContext = {
    DrawFPS: (position) => _rl.DrawFPS(position.x, position.y),
    DrawRectangle: (position, size, color) => _rl.DrawRectangle(position.x, position.y, size.x, size.y, color),
    DrawCircle: (position, radius, color) => _rl.DrawCircle(position.x, position.y, radius, color),
    DrawText: (text, position, size, color) => _rl.DrawText(text, position.x, position.y, size, color)
}

export class App {

    constructor(height, width, title) {
        this.height = height;
        this.width = width;
        this.title = title;
    }

    run(game) {

        console.log("Running")

        _rl.InitWindow(this.width, this.height, this.title);

        _rl.SetTargetFPS(60);

        if (game.init) {
            game.init();
        }

        while (!_rl.WindowShouldClose()) {

            if (game.update) {
                game.update(_rl.GetFrameTime());
            }

            _rl.BeginDrawing();

            _rl.ClearBackground(_rl.Color.WHITE)

            if (game.draw) {
                game.draw(DrawContext);
            }

            _rl.EndDrawing();
        }

        _rl.CloseWindow();
    }

}

export class console {
    static log(msg) {
        _rl.TraceLog(_rl.TraceLogLevel.LOG_INFO, msg)
    }
}

globalThis.Vector2 = Vector2;
globalThis.App = App;
globalThis.Sandbox = Sandbox;
globalThis.console = console;
