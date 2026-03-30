set_project("arge")
set_description("Another Raylib Game Engine")
set_version("0.0.0") -- x-release-please-version
set_languages("cxx23")

add_rules("mode.debug", "mode.release")

add_requires("cli11 2.6.2")
add_requires("raylib master") -- develop against this until 6.0 is released
add_requires("quickjs-ng 0.13.0")

task("bind-raylib")
    on_run(function ()
        local script_dir = path.join(os.projectdir(), "tools/autobind")
        local script_path = "bind.py"
        os.execv("python", {script_path}, {curdir = script_dir})
        print("Raylib bindings generated successfully from: %s", script_dir)
    end)
    set_menu {
        usage = "xmake bind-raylib",
        description = "Generate C++ bindings for Raylib using the python script"
    }

task("compile-runtime")
    on_run(function ()
        os.execv("qjsc", {"-N", "qjsc_runtime", "-C", "-m", "-o", "src/js/runtime.h", "src/js/runtime.js"})
        print("JavaScript runtime compiled to src/js/runtime.h")
    end)
    set_menu {
        usage = "xmake compile-runtime",
        description = "Compile runtime.js to a C header using qjsc"
    }

target("arge")
    set_kind("binary")
    add_files("src/*.cpp")
    add_files("src/raylib/*.cpp")
    add_packages("cli11", "raylib", "quickjs-ng")


