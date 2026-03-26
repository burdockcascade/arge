module;
#include <quickjs.h>

export module API:Canvas;
import :Common;
import Raylib;
import RaylibBindings;

static constexpr int DEFAULT_FONT_SIZE = 24;

export namespace API {

    // Draw
    JSValue API_DrawRectAdvanced(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {

        constexpr int min_args = 3;

        if (argc < min_args) {
            return JS_ThrowTypeError(ctx, "DrawRectangle expects %d arguments, but got %d", min_args, argc);
        }

        // Position
        Raylib::Vector2 *ptr_position;
        if (!try_get_opaque(ctx, ptr_position, argv[0], RaylibBindings::js_Vector2_class_id)) return JS_EXCEPTION;

        // Size
        Raylib::Vector2 *ptr_size;
        if (!try_get_opaque(ctx, ptr_size, argv[1], RaylibBindings::js_Vector2_class_id)) return JS_EXCEPTION;

        // Color
        Raylib::Color *ptr_color;
        if (!try_get_opaque(ctx, ptr_color, argv[2], RaylibBindings::js_Color_class_id)) return JS_EXCEPTION;

        // Default Optional Values
        float rotation = 0.0f;
        float roundness = 0.0f;
        int segments = 10;
        Raylib::Vector2 origin = { ptr_size->x / 2, ptr_size->y / 2 };

        // Check for Options Object (Argument 5)
        if (argc == min_args + 1 && JS_IsObject(argv[3])) {
            const JSValue options = argv[3];
            get_prop(ctx, options, "rotation", rotation);
            get_prop(ctx, options, "roundness", roundness);
            get_prop(ctx, options, "segments", segments);
            get_prop(ctx, options, "origin", origin);
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
    JSValue API_DrawTexture(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst argv[]) {
        if (constexpr int min_args = 2; argc < min_args) {
            return JS_ThrowTypeError(ctx, "DrawTexture expects %d arguments, but got %d", min_args, argc);
        }

        // Texture
        Raylib::Texture *ptr_texture;
        if (!try_get_opaque(ctx, ptr_texture, argv[0], RaylibBindings::js_Texture_class_id)) return JS_EXCEPTION;

        // Position
        Raylib::Vector2 *ptr_position;
        if (!try_get_opaque(ctx, ptr_position, argv[1], RaylibBindings::js_Vector2_class_id)) return JS_EXCEPTION;

        // Call
        Raylib::DrawTextureV(*ptr_texture, *ptr_position, Raylib::Color {255, 255, 255, 255});

        return JS_UNDEFINED;
    }

    JSValue API_DrawText(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst argv[]) {

        constexpr int min_args = 4;
        if (argc < min_args) {
            return JS_ThrowTypeError(ctx, "DrawText expects %d arguments, but got %d", min_args, argc);
        }

        // Text
        std::string text;
        if (!try_get_value(ctx, text, argv[0])) return JS_EXCEPTION;

        // Position
        Raylib::Vector2 *ptr_position;
        if (!try_get_opaque(ctx, ptr_position, argv[1], RaylibBindings::js_Vector2_class_id)) return JS_EXCEPTION;

        // Font Size
        int32_t font_size;
        if (!try_get_value(ctx, font_size, argv[2])) return JS_EXCEPTION;

        // Color
        Raylib::Color *ptr_color;
        if (!try_get_opaque(ctx, ptr_color, argv[3], RaylibBindings::js_Color_class_id)) return JS_EXCEPTION;

        // Defaults
        Raylib::Font font = Raylib::GetFontDefault();
        Raylib::Vector2 origin = { 0, 0 };
        float rotation = 0.0f;
        float spacing = 2.0f;

        if (argc > min_args && JS_IsObject(argv[4])) {
            const JSValue options = argv[4];
            get_prop(ctx, options, "font", font);
            get_prop(ctx, options, "origin", origin);
            get_prop(ctx, options, "rotation", rotation);
            get_prop(ctx, options, "spacing", spacing);
        }

        Raylib::DrawTextPro(font, text.c_str(), *ptr_position, origin, rotation, font_size, spacing, *ptr_color);

        return JS_UNDEFINED;
    }

    void create_canvas_object(JSContext* ctx, const JSValue draw_obj) {
        register_functions(ctx, draw_obj, {
            {"drawRect", API_DrawRectAdvanced, 4},
            {"drawTexture", API_DrawTexture, 2},
            {"drawText", API_DrawText, 2},
        });
    }

}