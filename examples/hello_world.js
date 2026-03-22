class HelloWorld {

    constructor() {

        // rect position
        this.pos = new Vector2(100, 400);
        this.size = new Vector2(100, 40);
        this.color = new Color(255, 0, 0, 255);

    }

    update(dt, app) {
        if (app.input.isKeyDown(KEY_RIGHT)) {
            this.pos.x += 10;
        } else if (app.input.isKeyDown(KEY_LEFT)) {
            this.pos.x -= 10;
        }

        if (app.input.isKeyDown(KEY_DOWN)) {
            this.pos.y += 10;
        } else if (app.input.isKeyDown(KEY_UP)) {
            this.pos.y -= 10;
        }
    }

    draw(ctx) {
        ctx.drawRect(this.pos, this.size, this.color);
    }
}

const app = new App({ width: 800, height: 600, title: "Hello World" });
app.run(new HelloWorld());