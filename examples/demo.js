class HelloWorld  {

    update(dt, ctx) {
    }

    draw(ctx) {
        ctx.DrawFPS(new Vector2(10, 10));
        ctx.DrawRectangle(new Vector2(90, 90), new Vector2(50, 50), _rl.Color.RED);
        ctx.DrawRectangle(new Vector2(230, 80), new Vector2(75, 90), _rl.Color.SKYBLUE);
    }
}

const app = new App(600, 800, "Hello World");
app.run(new HelloWorld());