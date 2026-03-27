#include "api.hpp"

namespace API {

    void InitEverything(JSContext* ctx, JSValue global) {
        RaylibBindings::InitAllStructs(ctx, global);
        RaylibBindings::InitAllEnums(ctx, global);
    }

    void RegisterSystemNamespace(JSContext* ctx, JSValue jsSystemContextObj) {
        create_window_object(ctx, jsSystemContextObj);
        create_input_object(ctx, jsSystemContextObj);
        create_asset_object(ctx, jsSystemContextObj);
    }

    void RegisterDrawNamespace(JSContext* ctx, JSValue jsDrawContextObj) {
        create_canvas_object(ctx, jsDrawContextObj);
    }

}