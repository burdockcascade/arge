// console.log("Checking globalThis...");
// console.log("App exists: " + (globalThis.App !== undefined));
// console.log("Color exists: " + (globalThis.Color !== undefined));
//

const target = globalThis;

Object.getOwnPropertyNames(target).forEach(prop => {
    try {
        const value = target[prop];
        const type = typeof value;
        console.log(`${prop} [${type}]: ${value}`);
    } catch (e) {
        console.log(`${prop}: <Access Denied>`);
    }
});

class Demo  {

    constructor() {
    }

    OnStart(ctx) {
        console.log("Game Started");

        // print number of monitors and their refresh rates
        const monitorCount = ctx.GetMonitorCount();
        console.log(`Number of monitors: ${monitorCount}`);
    }

    OnUpdate(dt, ctx) {

    }

    OnDraw(render) {

    }

    OnEnd() {
        console.log("Game Ended");
    }


}



const app = new App(600, 800, "Hello World");
app.SetWindowFlag(ConfigFlags.FLAG_WINDOW_RESIZABLE);
app.run(new Demo());