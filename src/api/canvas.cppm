module;
#include <quickjs.h>

export module API:Canvas;
import Raylib;
import RaylibBindings;
import :Common;

export namespace API {

    // Draw
    JSValue JS_DrawRectAdvanced(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {

        if (argc < 3) {
            return JS_ThrowTypeError(ctx, "DrawRectangle expects 3 arguments, but got %d", argc);
        }

        Raylib::Vector2 *ptr_position;
        Raylib::Vector2 *ptr_size;
        Raylib::Color *ptr_color;

        if (!try_get_opaque(ctx, ptr_position, argv[0], RaylibBindings::js_Vector2_class_id)) return JS_EXCEPTION;
        if (!try_get_opaque(ctx, ptr_size, argv[1], RaylibBindings::js_Vector2_class_id)) return JS_EXCEPTION;
        if (!try_get_opaque(ctx, ptr_color, argv[2], RaylibBindings::js_Color_class_id)) return JS_EXCEPTION;

        // Default Optional Values
        float rotation = 0.0f;
        float roundness = 0.0f;
        int segments = 10;
        Raylib::Vector2 origin = { ptr_size->x / 2, ptr_size->y / 2 };

        // Check for Options Object (Argument 5)
        if (argc >= 4 && JS_IsObject(argv[3])) {
            const JSValue options = argv[3];
            get_prop_num(ctx, options, "rotation", rotation);
            get_prop_num(ctx, options, "roundness", roundness);
            get_prop_num(ctx, options, "segments", segments);
            get_prop_vec2(ctx, options, "origin", origin);
        }

        // Raylib logic: Decide which function to call
        if (roundness > 0.0f) {
            Raylib::DrawRectangleRounded({ ptr_position->x, ptr_position->y, ptr_size->x, ptr_size->y }, roundness, segments, *ptr_color);
        } else {
            Raylib::DrawRectanglePro({ ptr_position->x, ptr_position->y, ptr_size->x, ptr_size->y }, origin, rotation, *ptr_color);
        }

        return JS_UNDEFINED;
    }

    // Draw Texture
    JSValue JS_DrawTexture(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst argv[]) {
        if (argc < 2) {
            return JS_DrawRectAdvanced(ctx, this_val, argc, argv);
        }

        Raylib::Texture *ptr_texture;
        if (!try_get_opaque(ctx, ptr_texture, argv[0], RaylibBindings::js_Texture_class_id)) return JS_EXCEPTION;

        Raylib::Vector2 *ptr_position;
        if (!try_get_opaque(ctx, ptr_position, argv[1], RaylibBindings::js_Vector2_class_id)) return JS_EXCEPTION;

        Raylib::DrawTextureV(*ptr_texture, *ptr_position, Raylib::Color {255, 255, 255, 255});

        return JS_UNDEFINED;
    }


    void create_canvas_object(JSContext* ctx, const JSValue draw_obj) {
        register_functions(ctx, draw_obj, {
            {"drawRect", JS_DrawRectAdvanced, 4},
            {"drawTexture", JS_DrawTexture, 2}
        });
    }

}