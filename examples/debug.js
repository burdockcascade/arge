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