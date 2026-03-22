export module API;

export import :Common;
export import :Console;
export import :System;
export import :Canvas;

export namespace API {

    void InitEverything(JSContext* ctx, JSValue global) {

        RaylibBindings::InitAllStructs(ctx, global);
        RaylibBindings::InitAllEnums(ctx, global);

    }

}