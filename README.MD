# ARGE
Another Raylib Game Engine

## Status
ARGE is currently in early development, and is not yet ready for production use.

ARGE needs a better name.

## Example

```js
class HelloWorld {

    constructor() {

        // rect position
        this.pos = new Vector2(100, 400);
        this.size = new Vector2(100, 40);
        this.color = new Color(255, 0, 0, 255);

    }

    init(app) {
        console.log(app.window.isReady());
    }

    update(dt, app) {
        // do nothing
    }

    draw(render) {
        // Debug Layer
        render.WithLayer2D((ctx) => {
            ctx.DrawFPS(this.fpsPos);
        });

        // 2D Graphics Layer
        render.WithLayer2D((ctx) => {
            ctx.DrawRectangle(this.rectPos2, this.rectDim2, Color.RED);
            ctx.DrawRectangle(this.rectPos1, this.rectDim1, Color.SKYBLUE);
            ctx.DrawCircle(this.circlePos, 90, this.circleColor);
            ctx.DrawText("hello", new Vector2(190, 190), 24.0, Color.BLUE);
        });
    }
}

const app = new Runtime(800, 600, "Hello World");
app.run(new HelloWorld());
```