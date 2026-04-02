class Demo  {

    constructor() {
        this.speed = 200;
        this.rectPos = new Vector2(50, 50);
        this.circleColor = Color.GREEN;
    }

    start(ctx) {
        console.log("Game Started");

        // print number of monitors and their refresh rates
        const monitorCount = ctx.GetMonitorCount();
        console.log(`Number of monitors: ${monitorCount}`);
    }

    update(dt, ctx) {

        const { Input, Mouse } = ctx;

        const moveStep = this.speed * dt;

        if (Input.IsKeyDown(KeyboardKey.KEY_RIGHT)) {
            this.rectPos.x += moveStep;
        }
        if (Input.IsKeyDown(KeyboardKey.KEY_LEFT)) {
            this.rectPos.x -= moveStep;
        }
        if (Input.IsKeyDown(KeyboardKey.KEY_DOWN)) {
            this.rectPos.y += moveStep;
        }
        if (Input.IsKeyDown(KeyboardKey.KEY_UP)) {
            this.rectPos.y -= moveStep;
        }

        if (Input.IsKeyPressed(KeyboardKey.KEY_SPACE)) {
            this.circleColor = Color.ORANGE;
        }

        if (Mouse.IsButtonPressed(MouseButton.MOUSE_LEFT_BUTTON)) {
            this.circleColor = Color.MAROON;
        }

    }

    draw(render) {

        // Debug Layer
        render.WithLayer2D((ctx) => {
            ctx.DrawFPS(new Vector2(10, 10));
        });

        // 2D Graphics Layer
        render.WithLayer2D((ctx) => {
            ctx.DrawRectangle(new Vector2(90, 90), new Vector2(50, 50), Color.RED);
            ctx.DrawRectangle(this.rectPos, new Vector2(50, 90), Color.SKYBLUE);
            ctx.DrawCircle(new Vector2(300, 300), 90, this.circleColor);
        });

    }
    
    end() {
        console.log("Game Ended");
    }


}

// console.log("Checking globalThis...");
// console.log("App exists: " + (globalThis.App !== undefined));
// console.log("Color exists: " + (globalThis.Color !== undefined));
//
Object.getOwnPropertyNames(globalThis).forEach(prop => {
    try {
        const value = globalThis[prop];
        const type = typeof value;
        console.log(`${prop} [${type}]: ${value}`);
    } catch (e) {
        console.log(`${prop}: <Access Denied>`);
    }
});

const app = new App(600, 800, "Hello World");
app.run(new Demo());