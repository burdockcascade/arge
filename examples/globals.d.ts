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
    static SKYBLUE: Color;
    static GRAY: Color;
    static BLACK: Color;
    static WHITE: Color;
    static RED: Color;
    static GREEN: Color;
    static BLUE: Color;
    static YELLOW: Color;
    static MAGENTA: Color;
    static CYAN: Color;
    static ORANGE: Color;
    static PINK: Color;
    static PURPLE: Color;
    static BROWN: Color;
    static LIGHTGRAY: Color;
    static DARKGRAY: Color;
    static LIGHTBLUE: Color;
    static LIGHTGREEN: Color;
    static LIGHTYELLOW: Color;
}

declare interface AppConfig {
    width?: number;
    height?: number;
    title?: string;
}

declare class App {
    constructor(height: number, width: number, title: string);
    run(instance: Sandbox): void;
}

interface Context {
    with_layer_2d(cameraMode: number, callback: (canvas: Canvas) => void): void;
}

interface Canvas {
    drawRect(position: Vector2, size: Vector2, color: Color, options?: object): void;
    drawTexture(texture: Texture2D, position: Vector2): void;
    drawText(text: string, position: Vector2, fontSize: number, color: Color): void;
    drawCircle(position: Vector2, radius: number, color: Color): void;
}

declare class Texture2D {
    id: number;
    width: number;
    height: number;
    mipmaps: number;
    format: number;
}

declare class KeyboardKey {

// Raylib Constants
    static KEY_SPACE: number;
    static KEY_LEFT: number;
    static KEY_RIGHT: number;
    static KEY_UP: number;
    static KEY_DOWN: number;
}

declare class Sandbox {

    /** Called once when the game starts */
    init?(): void;

    /** Called every frame for logic. 'dt' is delta time. */
    update(dt: number, ctx: UpdateContext): void;

    /** Called every frame for rendering. */
    draw(ctx: Canvas): void;
}

type SandboxClass = new () => Sandbox;

interface UpdateContext {
    input: {
        isKeyDown(key: string | number): boolean;
        getMousePosition(): { x: number, y: number };
    };
}