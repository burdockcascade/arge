#include <CLI/CLI.hpp>
#include <raylib.h>
#include <string>
#include <exception> // Added for std::exception

// Replace internal includes with module imports
import App;

int main(const int argc, char** argv) {

    SetTraceLogLevel(LOG_INFO);

    CLI::App args{"QuickJS Raylib Runner"};

    // Required option for script path
    std::string scriptPath;
    args.add_option("-s,--script", scriptPath, "Path to the JS game script")
        ->required();

    // Optional flag for verbose logging
    bool verbose = false;
    args.add_flag("-v,--verbose", verbose, "Enable verbose logging");

    // Enable verbose logging if the flag is set
    if (verbose) {
        SetTraceLogLevel(LOG_DEBUG);
    }

    CLI11_PARSE(args, argc, argv);

    try {
        if (App app(scriptPath); app.Initialize()) {
            app.Run();
        }
        App::Shutdown();
    } catch (const std::exception& e) {
        TraceLog(LOG_ERROR, "%s", e.what());
    }

    return 0;
}