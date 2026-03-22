/**
 * Global definitions for the Arge Multimedia Engine
 */

declare class Vector2 {
    constructor(x: number, y: number);
    x: number;
    y: number;
}

declare class Color {
    constructor(r: number, g: number, b: number, a: number);
    r: number; g: number; b: number; a: number;
}

declare interface AppConfig {
    width?: number;
    height?: number;
    title?: string;
}

declare class App {
    constructor(config: AppConfig);
    run(instance: any): void;
}

// System and Drawing interfaces for JSDoc
interface Engine {
    input: { isKeyDown(key: number): boolean };
    audio: { play(name: string): void };
    getMonitorCount(): number;
    getFrameTime(): number;
    isWindowFocused(): boolean;
}

interface Context {
    with_layer_2d(cameraMode: number, callback: (canvas: Canvas) => void): void;
}

interface Canvas {
    drawRect(position: Vector2, size: Vector2, color: Color, options?: object): void;
}

// Raylib Constants
const KEY_SPACE: number;
const KEY_LEFT: number;
const KEY_RIGHT: number;
const KEY_UP: number;
const KEY_DOWN: number;
const RED: Color;
const BLUE: Color;