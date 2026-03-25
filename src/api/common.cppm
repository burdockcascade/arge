module;
#include <quickjs.h>

export module API:Common;
import <string_view>;
import Raylib;
import RaylibBindings;

export namespace API {

    struct FunctionDef {
        std::string_view name{};
        JSCFunction* func{};
        int length{};
    };

    inline void register_functions(JSContext* ctx, JSValue obj, std::initializer_list<FunctionDef> funcs) {
        for (const auto&[name, func, length] : funcs) {
            JS_SetPropertyStr(ctx, obj, name.data(), JS_NewCFunction(ctx, func, name.data(), length));
        }
    }

    template <typename T>
    bool try_get_opaque(JSContext* ctx, T*& out_ptr, JSValueConst val, JSClassID class_id) {
        out_ptr = static_cast<T*>(JS_GetOpaque2(ctx, val, class_id));
        if (!out_ptr) {
            JS_ThrowTypeError(ctx, "Expected specialized Raylib object (wrong class type)");
            return false;
        }
        return true;
    }

    inline Raylib::Vector2 to_vector2(JSContext* ctx, JSValueConst val) {
        // 1. Try to get it as an opaque C++ struct (fastest)
        if (const auto* ptr = static_cast<Raylib::Vector2*>(JS_GetOpaque(val, RaylibBindings::js_Vector2_class_id))) return *ptr;

        // 2. Fallback: Try to read it as a plain JS object {x: 10, y: 20}
        Raylib::Vector2 vec = { 0, 0 };
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

    inline bool get_prop_vec2(JSContext* ctx, JSValueConst obj, const char* prop, Raylib::Vector2& out) {
        const JSValue val = JS_GetPropertyStr(ctx, obj, prop);
        bool success = false;

        if (JS_IsObject(val)) {
            out = to_vector2(ctx, val);
            success = true;
        }

        JS_FreeValue(ctx, val);
        return success;
    }

    inline bool get_prop_bool(JSContext* ctx, JSValueConst obj, const char* prop, bool& out) {
        const JSValue val = JS_GetPropertyStr(ctx, obj, prop); //
        bool success = false;

        // Check if the property is actually present and not undefined/null
        if (!JS_IsUndefined(val) && !JS_IsNull(val)) {
            out = JS_ToBool(ctx, val); // QuickJS handles truthy/falsy conversion
            success = true;
        }

        JS_FreeValue(ctx, val); //
        return success;
    }

}