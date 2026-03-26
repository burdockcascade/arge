class ExampleApp {

    constructor() {
        this.samepleTexture;
    }

    init(engine) {
        this.samepleTexture = engine.assets.loadTexture("C:\\workspace\\raylib\\arge\\assets\\sample.png");

    }

    draw(ctx) {
        ctx.drawTexture(this.samepleTexture, new Vector2(10, 10));
    }
}

const app = new App({ width: 800, height: 600, title: "Hello Texture" });
app.run(new ExampleApp());