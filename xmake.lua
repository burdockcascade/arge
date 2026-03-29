set_project("arge")
set_description("Another Raylib Game Engine")
set_version("0.0.0") -- x-release-please-version
set_languages("cxx23")

add_rules("mode.debug", "mode.release")

add_requires("cli11 2.6.2")
add_requires("raylib master") -- develop against this until 6.0 is released
add_requires("quickjs-ng 0.13.0")
add_requires("spdlog 1.16")

target("arge")
    set_kind("binary")
    add_files("src/*.cpp")
    add_files("src/raylib/*.cpp")
    add_packages("cli11", "raylib", "quickjs-ng")