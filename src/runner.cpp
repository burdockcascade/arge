#include <string>
#include <fstream>
#include "runner.hpp"
#include "js/runtime.h"
#include "qjs/qjs_wrapper.hpp"
#include "raylib/rl_bindings.hpp"

static void add_console_utilities(qjs::Engine& engine) {
    auto global = engine.get_global_object();
    auto console = engine.create_object("console");
    console.register_function("log", [](std::string msg) {
        std::cout << "[QJS] " << msg << std::endl;
    });
}

Runner::Runner(std::string path) : scriptPath(std::move(path)) {
    add_console_utilities(engine);
    RaylibBindings::InternalRegister(engine);
}

void Runner::Run() const {

    // Check if script exists
    if (const std::ifstream t(scriptPath); !t.is_open()) {
        TraceLog(LOG_ERROR, "Failed to open script: %s", scriptPath.c_str());
        return;
    }

    // Load runtime bytecode
    TraceLog(LOG_INFO, "Loading runtime");
    if (auto result = engine.run_bytecode(qjsc_runtime, qjsc_runtime_size); !result) {
        TraceLog(LOG_ERROR, "Failed to load runtime bytecode: %s", result.error().c_str());
        return;
    }

    // Run user script
    TraceLog(LOG_INFO, "Running script: %s", scriptPath.c_str());
    if (auto result = engine.run_file(scriptPath.c_str()); !result) {
        TraceLog(LOG_ERROR, "Failed to run script: %s", result.error().c_str());
        return;
    }

}

