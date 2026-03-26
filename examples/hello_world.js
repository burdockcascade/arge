class HelloWorld {

    constructor() {

        // rect position
        this.pos = new Vector2(100, 400);
        this.size = new Vector2(100, 40);
        this.color = Color.SKYBLUE;

        this.speed = 5;
        this.samepleTexture;

    }

    init(engine) {
        this.samepleTexture = engine.assets.loadTexture("C:\\workspace\\raylib\\arge\\assets\\sample.png");

    }

    update(dt, app) {
        if (app.input.isKeyDown(KEY_RIGHT)) {
            this.pos.x += this.speed;
        }
        if (app.input.isKeyDown(KEY_LEFT)) {
            this.pos.x -= this.speed;
        }
        if (app.input.isKeyDown(KEY_DOWN)) {
            this.pos.y += this.speed;
        }
        if (app.input.isKeyDown(KEY_UP)) {
            this.pos.y -= this.speed;
        }
    }

    draw(ctx) {
        ctx.drawRect(this.pos, this.size, this.color, { fill: true, rotation: 45 });
        ctx.drawTexture(this.samepleTexture, new Vector2(10, 10));
    }
}

const app = new App({ width: 800, height: 600, title: "Hello World" });
app.run(new HelloWorld());