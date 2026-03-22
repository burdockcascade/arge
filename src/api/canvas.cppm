module;
#include <quickjs.h>
#include <raylib.h>

export module API:Canvas;
import RaylibBindings;
import :Common;

export namespace API {

    template <typename T>
    bool try_get_opaque(JSContext* ctx, T*& out_ptr, JSValueConst val, JSClassID class_id) {
        out_ptr = static_cast<T*>(JS_GetOpaque2(ctx, val, class_id));
        if (!out_ptr) {
            JS_ThrowTypeError(ctx, "Expected specialized Raylib object (wrong class type)");
            return false;
        }
        return true;
    }

    inline Vector2 to_vector2(JSContext* ctx, JSValueConst val) {
        // 1. Try to get it as an opaque C++ struct (fastest)
        if (const auto* ptr = static_cast<Vector2*>(JS_GetOpaque(val, RaylibBindings::js_Vector2_class_id))) return *ptr;

        // 2. Fallback: Try to read it as a plain JS object {x: 10, y: 20}
        Vector2 vec = { 0, 0 };
        const JSValue x_val = JS_GetPropertyStr(ctx, val, "x");
        const JSValue y_val = JS_GetPropertyStr(ctx, val, "y");

        double dx, dy;
        if (JS_ToFloat64(ctx, &dx, x_val) == 0) vec.x = static_cast<float>(dx);
        if (JS_ToFloat64(ctx, &dy, y_val) == 0) vec.y = static_cast<float>(dy);

        JS_FreeValue(ctx, x_val);
        JS_FreeValue(ctx, y_val);
        return vec;
    }

    template <typename T>
    bool get_prop_num(JSContext* ctx, JSValueConst obj, const char* prop, T& out) {
        const JSValue val = JS_GetPropertyStr(ctx, obj, prop);
        bool success = false;

        if (JS_IsNumber(val)) {
            if constexpr (std::is_integral_v<T>) {
                int32_t i;
                JS_ToInt32(ctx, &i, val);
                out = static_cast<T>(i);
            } else {
                double d;
                JS_ToFloat64(ctx, &d, val);
                out = static_cast<T>(d);
            }
            success = true;
        }

        JS_FreeValue(ctx, val);
        return success;
    }

    inline bool get_prop_vec2(JSContext* ctx, JSValueConst obj, const char* prop, Vector2& out) {
        const JSValue val = JS_GetPropertyStr(ctx, obj, prop);
        bool success = false;

        if (JS_IsObject(val)) {
            out = to_vector2(ctx, val);
            success = true;
        }

        JS_FreeValue(ctx, val);
        return success;
    }

    JSValue js_DrawRectAdvanced(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {

        if (argc < 3) {
            return JS_ThrowTypeError(ctx, "DrawRectangle expects 3 arguments, but got %d", argc);
        }

        Vector2 *ptr_position;
        Vector2 *ptr_size;
        Color *ptr_color;

        if (!try_get_opaque(ctx, ptr_position, argv[0], RaylibBindings::js_Vector2_class_id)) return JS_EXCEPTION;
        if (!try_get_opaque(ctx, ptr_size, argv[1], RaylibBindings::js_Vector2_class_id)) return JS_EXCEPTION;
        if (!try_get_opaque(ctx, ptr_color, argv[2], RaylibBindings::js_Color_class_id)) return JS_EXCEPTION;

        // Default Optional Values
        float rotation = 0.0f;
        float roundness = 0.0f;
        int segments = 10;
        Vector2 origin = { ptr_size->x / 2, ptr_size->y / 2 };

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
            DrawRectangleRounded({ ptr_position->x, ptr_position->y, ptr_size->x, ptr_size->y }, roundness, segments, *ptr_color);
        } else {
            DrawRectanglePro({ ptr_position->x, ptr_position->y, ptr_size->x, ptr_size->y }, origin, rotation, *ptr_color);
        }

        return JS_UNDEFINED;
    }

    void create_canvas_object(JSContext* ctx, const JSValue draw_obj) {
        register_functions(ctx, draw_obj, {
            {"drawRect", js_DrawRectAdvanced, 4}
        });
    }

}