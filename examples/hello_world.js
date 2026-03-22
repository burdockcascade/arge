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

    draw(ctx) {
        ctx.drawRect(this.pos, this.size, this.color);
    }
}

const app = new App({ width: 800, height: 600, title: "Hello World" });
app.run(new HelloWorld());