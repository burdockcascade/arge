set_description("Arge")

set_version("0.0.0") -- x-release-please-version
set_languages("cxx23")

add_rules("mode.debug", "mode.release")

add_requires("cli11 2.6.1")
add_requires("raylib 5.5")
add_requires("quickjs-ng 0.12.1")

target("arge")
    set_kind("binary")
    add_files("src/*.cpp")
    add_packages("cli11", "raylib", "quickjs-ng")