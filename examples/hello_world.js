class HelloWorld {

    constructor() {

        // rect position
        this.pos = new Vector2(100, 400);
        this.size = new Vector2(100, 40);
        this.color = Color.ORANGE;

        this.speed = 5;
        this.rotation = 0;

    }

    update(dt, app) {
        if (app.input.isKeyDown(KeyboardKey.KEY_RIGHT)) {
            this.pos.x += this.speed;
        }
        if (app.input.isKeyDown(KeyboardKey.KEY_LEFT)) {
            this.pos.x -= this.speed;
        }
        if (app.input.isKeyDown(KeyboardKey.KEY_DOWN)) {
            this.pos.y += this.speed;
        }
        if (app.input.isKeyDown(KeyboardKey.KEY_UP)) {
            this.pos.y -= this.speed;
        }

        // rotate shape
        this.rotation += 1;

    }

    draw(ctx) {
        ctx.drawRect(this.pos, this.size, this.color, { fill: true, rotation: this.rotation });
        ctx.drawText("Hello!", new Vector2(50, 50), 24, Color.SKYBLUE);
    }
}

const app = new App({ width: 800, height: 600, title: "Hello World" });
app.run(new HelloWorld());