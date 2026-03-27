class HelloWorld {

    constructor() {

        // rect position
        this.pos = new Vector2(100, 400);
        this.size = new Vector2(100, 40);
        this.color = Color.ORANGE;

        this.speed = 5;
        this.rotation = 0;

        this.circlePosition = new Vector2(100, 100);
        this.circleRadius = 24;

    }

    update(dt, engine) {
        if (engine.input.isKeyDown(KeyboardKey.KEY_RIGHT)) {
            this.pos.x += this.speed;
        }
        if (engine.input.isKeyDown(KeyboardKey.KEY_LEFT)) {
            this.pos.x -= this.speed;
        }
        if (engine.input.isKeyDown(KeyboardKey.KEY_DOWN)) {
            this.pos.y += this.speed;
        }
        if (engine.input.isKeyDown(KeyboardKey.KEY_UP)) {
            this.pos.y -= this.speed;
        }

        // rotate shape
        this.rotation += 1;

        // Pulsate the radius of the circle
        this.elapsedTime = (this.elapsedTime || 0) + dt;
        const baseRadius = 50;   // The starting size
        const amplitude = 10;    // How much it grows and shrinks
        const frequency = 4;     // How fast it pulses

        // Math.sin returns a value between -1 and 1
        this.circleRadius = baseRadius + Math.sin(this.elapsedTime * frequency) * amplitude;

    }

    draw(ctx) {
        ctx.drawRect(this.pos, this.size, this.color, { fill: true, rotation: this.rotation });
        ctx.drawCircle(this.circlePosition, this.circleRadius, Color.SKYBLUE);
    }
}

const app = new App({ width: 800, height: 600, title: "Hello World" });
app.run(new HelloWorld());