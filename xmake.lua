add_rules("mode.debug", "mode.release")

add_requires("dpp", "fmt", "nlohmann_json", "spdlog")

add_rules("plugin.compile_commands.autoupdate")

target("rabbitbot")
    set_kind("binary")
    add_includedirs("src", "src/rabbit/commands/implementation")
    set_languages("c++20")
    add_files("src/**.cxx")
    add_packages("dpp", "fmt", "nlohmann_json", "spdlog")
