#pragma once
#include <quickjs.h>
#include "../wrapper/rl_bindings.hpp"

namespace API {

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
    bool try_get_opaque(JSContext* ctx, T*& out_ptr, JSValue const val, JSClassID class_id) {
        out_ptr = static_cast<T*>(JS_GetOpaque2(ctx, val, class_id));
        if (!out_ptr) {
            JS_ThrowTypeError(ctx, "Expected specialized Raylib object (wrong class type)");
            return false;
        }
        return true;
    }

    template <typename T>
    bool try_get_value(JSContext* ctx, T& out_ptr, JSValue const val) {
        // 1. Handle Vector2 (Moved from get_prop)
        if constexpr (std::is_same_v<T, Vector2>) {
            if (JS_IsObject(val)) {
                out_ptr = to_vector2(ctx, val);
                return true;
            }
            return false;
        }
        // 2. Handle Booleans
        else if constexpr (std::is_same_v<T, bool>) {
            int res = JS_ToBool(ctx, val);
            if (res < 0) return false;
            out_ptr = (res != 0);
            return true;
        }
        // 3. Handle Integrals
        else if constexpr (std::is_integral_v<T>) {
            int32_t i;
            if (JS_ToInt32(ctx, &i, val) != 0) return false;
            out_ptr = static_cast<T>(i);
            return true;
        }
        // 4. Handle Floating Point
        else if constexpr (std::is_floating_point_v<T>) {
            double d;
            if (JS_ToFloat64(ctx, &d, val) != 0) return false;
            out_ptr = static_cast<T>(d);
            return true;
        }
        // 5. Handle Strings
        else if constexpr (std::is_same_v<T, std::string>) {
            size_t len;
            const char* str = JS_ToCStringLen(ctx, &len, val);
            if (!str) return false;
            out_ptr = std::string(str, len);
            JS_FreeCString(ctx, str);
            return true;
        }
        else {
            return false;
        }
    }

    template <typename T>
    bool get_prop(JSContext* ctx, JSValueConst obj, const char* prop, T& out) {
        // Fetch the property value from the object
        const JSValue val = JS_GetPropertyStr(ctx, obj, prop);

        bool success = false;

        // QuickJS returns an 'exception' or 'undefined' if property access fails
        // We only attempt conversion if the value is not null/undefined
        if (!JS_IsUndefined(val) && !JS_IsNull(val)) {
            success = try_get_value<T>(ctx, out, val);
        }

        // IMPORTANT: JS_GetPropertyStr increments the ref count.
        // We must free it to avoid memory leaks!
        JS_FreeValue(ctx, val);

        return success;
    }
}