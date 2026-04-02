set_project("arge")
set_description("Another Raylib Game Engine")
set_version("0.0.0") -- x-release-please-version
set_languages("cxx23")

add_rules("mode.debug", "mode.release")

add_requires("cli11 2.6.2")
add_requires("raylib master") -- develop against this until 6.0 is released
add_requires("quickjs-ng 0.13.0")

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
    add_files("src/*.cpp", "src/raylib/*.cpp")
    add_packages("cli11", "raylib", "quickjs-ng")


