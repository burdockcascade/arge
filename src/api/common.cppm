module;
#include <quickjs.h>
#include <raylib.h>

export module API:Common;
import RaylibBindings;
import <string>;
import <string_view>;
import <optional>;
import <type_traits>;

export namespace API {

    struct FunctionDef {
        std::string_view name{};
        JSCFunction* func{};
        int length{};
    };

    inline void register_functions(JSContext* ctx, JSValue obj, std::initializer_list<FunctionDef> funcs) {
        for (const auto&[name, func, length] : funcs) {
            JS_SetPropertyStr(ctx, obj, name.data(), JS_NewCFunction2(ctx, func, name.data(), length, JS_CFUNC_generic, 0));
        }
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
        // 1. Handle Booleans
        if constexpr (std::is_same_v<T, bool>) {
            int res = JS_ToBool(ctx, val);
            if (res < 0) return false; // Error state
            out_ptr = (res != 0);
            return true;
        }
        // 2. Handle Integrals (int, int32_t, etc.)
        else if constexpr (std::is_integral_v<T>) {
            int32_t i;
            if (JS_ToInt32(ctx, &i, val) != 0) return false;
            out_ptr = static_cast<T>(i);
            return true;
        }
        // 3. Handle Floating Point (float, double)
        else if constexpr (std::is_floating_point_v<T>) {
            double d;
            if (JS_ToFloat64(ctx, &d, val) != 0) return false;
            out_ptr = static_cast<T>(d);
            return true;
        }
        // 4. Handle Strings
        else if constexpr (std::is_same_v<T, std::string>) {
            size_t len;
            const char* str = JS_ToCStringLen(ctx, &len, val);
            if (!str) return false;
            out_ptr = std::string(str, len);
            JS_FreeCString(ctx, str); // Clean up the QuickJS allocated string
            return true;
        }
        // 5. Fallback for Unsupported Types
        else {
            JS_ThrowTypeError(ctx, "Unsupported type for try_get_value");
            return false;
        }
    }

    template <typename T>
    bool get_prop(JSContext* ctx, JSValueConst obj, const char* prop, T& out) {
        const JSValue val = JS_GetPropertyStr(ctx, obj, prop);
        bool success = false;

        // We check for undefined/null first to ensure the property actually exists
        if (!JS_IsUndefined(val) && !JS_IsNull(val)) {

            // 1. Handle Vector2
            if constexpr (std::is_same_v<T, Vector2>) {
                if (JS_IsObject(val)) {
                    out = to_vector2(ctx, val);
                    success = true;
                }
            }
            // 2. Handle Booleans
            else if constexpr (std::is_same_v<T, bool>) {
                out = (JS_ToBool(ctx, val) != 0);
                success = true;
            }
            // 3. Handle Integrals
            else if constexpr (std::is_integral_v<T>) {
                if (JS_IsNumber(val)) {
                    int32_t i;
                    JS_ToInt32(ctx, &i, val);
                    out = static_cast<T>(i);
                    success = true;
                }
            }
            // 4. Handle Floating Point
            else if constexpr (std::is_floating_point_v<T>) {
                if (JS_IsNumber(val)) {
                    double d;
                    JS_ToFloat64(ctx, &d, val);
                    out = static_cast<T>(d);
                    success = true;
                }
            }
            // 5. Handle std::string (Optional but recommended)
            else if constexpr (std::is_same_v<T, std::string>) {
                size_t len;
                const char* str = JS_ToCStringLen(ctx, &len, val);
                if (str) {
                    out = std::string(str, len);
                    JS_FreeCString(ctx, str);
                    success = true;
                }
            }
        }

        JS_FreeValue(ctx, val);
        return success;
    }


}