module;
#include <quickjs.h>

export module API:Common;
import <string_view>;

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

}