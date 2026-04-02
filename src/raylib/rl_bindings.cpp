#include "../qjs_wrapper.hpp"
#include "rl_bindings.hpp"

namespace RaylibBindings {

    void InternalRegister(qjs::Engine &engine) {
        auto global = engine.get_global_object();
        auto rl = global.create_object("_rl");
        InitAllFunctions(rl);
        InitAllEnums(global);
        InitAllStructs(global);
    }

}