class HelloWorld {

    init(app) {
        console.log(app.window.isReady());
    }

    update(dt, app) {
        if (app.input.isKeyPressed(KEY_TAB)) {
            console.log("Tab key pressed!");
        }
    }

    draw(ctx) {
    }
}

const app = new App({ width: 800, height: 600, title: "Hello World" });
app.run(new HelloWorld());