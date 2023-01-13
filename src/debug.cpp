// Copyright (C) Tubbles github.com/Tubbles

#include "debug.hpp"
#include "imgui-SFML.h"
#include "imgui.h"
#include "log.hpp"

namespace debug {
void setup(fs::path &my_dir, sf::RenderWindow &window) {
    static const std::string imgui_ini_filename{my_dir.string() + std::string{"/imgui.ini"}};
    static const std::string imgui_log_filename{my_dir.string() + std::string{"/imgui_log.txt"}};

    if (!ImGui::SFML::Init(window)) {
        spdlog::error("ImGui initialization failed");
    }

    ImGui::GetIO().IniFilename = imgui_ini_filename.c_str();
    ImGui::GetIO().LogFilename = imgui_log_filename.c_str();

    spdlog::info("ImGui started, press F1 to toggle overlay");
}
} // namespace debug
