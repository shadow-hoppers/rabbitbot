add_rules("mode.debug", "mode.release")

add_requires("dpp", "chaiscript", "fmt", "nlohmann_json", "spdlog")

target("rabbitbot")
    set_kind("binary")
    set_languages("c++20")
    add_files("src/*.cxx")
    add_packages("dpp", "chaiscript", "fmt", "nlohmann_json", "spdlog")
