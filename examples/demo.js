class Demo  {

    constructor() {
        this.speed = 200;

        this.rectPos1 = new Vector2(50, 50);
        this.rectDim1 = new Vector2(30, 60);

        this.rectPos2 = new Vector2(150, 250);
        this.rectDim2 = new Vector2(90, 20);

        this.circlePos = new Vector2(300, 300);
        this.circleColor = Color.GetRandomColor();

        this.fpsPos = new Vector2(10, 10);
    }

    OnStart(ctx) {
        console.log("Game Started");

        // print number of monitors and their refresh rates
        const monitorCount = ctx.GetMonitorCount();
        console.log(`Number of monitors: ${monitorCount}`);
    }

    OnUpdate(dt, ctx) {

        const { Input, Mouse } = ctx;

        const moveStep = this.speed * dt;

        if (Input.IsKeyDown(KeyboardKey.KEY_RIGHT)) {
            this.rectPos1.x += moveStep;
        }
        if (Input.IsKeyDown(KeyboardKey.KEY_LEFT)) {
            this.rectPos1.x -= moveStep;
        }
        if (Input.IsKeyDown(KeyboardKey.KEY_DOWN)) {
            this.rectPos1.y += moveStep;
        }
        if (Input.IsKeyDown(KeyboardKey.KEY_UP)) {
            this.rectPos1.y -= moveStep;
        }

        // new random color on space press
        if (Input.IsKeyPressed(KeyboardKey.KEY_SPACE)) {
            this.circleColor = Color.GetRandomColor();
        }

        if (Mouse.IsButtonPressed(MouseButton.MOUSE_LEFT_BUTTON)) {
            this.circleColor = Color.GetRandomColor();
        }

    }

    OnDraw(render) {

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

    OnEnd() {
        console.log("Game Ended");
    }


}



const app = new App(600, 800, "Hello World");
app.Run(new Demo());