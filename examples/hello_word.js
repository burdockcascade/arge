class HelloWorld {

    init(engine) {
        console.log("Init");
    }

    update(dt, engine) {
        console.log("Update");
    }

    draw(ctx) {
        console.log("Draw");
    }
}

const app = new App({ width: 800, height: 600, title: "Hello World" });
app.run(new HelloWorld());