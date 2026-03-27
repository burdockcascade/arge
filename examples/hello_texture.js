class ExampleApp {

    init(engine) {
        this.samepleTexture = engine.assets.loadTexture("C:\\workspace\\raylib\\arge\\assets\\sample.png");

    }

    draw(ctx) {
        ctx.drawTexture(this.samepleTexture, new Vector2(10, 10));
    }
}

const app = new Runtime(600, 800, "Hello World");
app.run(new ExampleApp());