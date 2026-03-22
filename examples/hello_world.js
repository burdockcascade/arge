class HelloWorld {

    constructor() {

        // rect position
        this.pos = new Vector2(100, 400);
        this.size = new Vector2(100, 40);
        this.color = new Color(255, 0, 0, 255);

        this.speed = 5;

    }

    update(dt, app) {
        if (app.input.isKeyDown(KEY_RIGHT)) {
            this.pos.x += this.speed;
        } else if (app.input.isKeyDown(KEY_LEFT)) {
            this.pos.x -= this.speed;
        }

        if (app.input.isKeyDown(KEY_DOWN)) {
            this.pos.y += this.speed;
        } else if (app.input.isKeyDown(KEY_UP)) {
            this.pos.y -= this.speed;
        }
    }

    draw(ctx) {
        ctx.drawRect(this.pos, this.size, this.color);
    }
}

const app = new App({ width: 800, height: 600, title: "Hello World" });
app.run(new HelloWorld());