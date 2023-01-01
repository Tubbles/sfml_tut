#include "modules/spdlog/include/spdlog/sinks/basic_file_sink.h"
#include "modules/spdlog/include/spdlog/sinks/stdout_color_sinks.h"
#include "modules/spdlog/include/spdlog/spdlog.h"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <filesystem>
#include <fmt/core.h>

#ifndef NDEBUG
#include "modules/imgui-sfml/imgui-SFML.h"
#include "modules/imgui/imgui.h"
#endif

namespace fs = std::filesystem;

static void setup_spdlog(fs::path &my_dir) {
    static const std::string log_filename{my_dir.string() + std::string{"/log.txt"}};

    auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    console_sink->set_level(spdlog::level::warn);
    auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(log_filename.c_str(), true);
    file_sink->set_level(spdlog::level::trace);
    spdlog::sinks_init_list sinks{console_sink, file_sink};

    auto logger = std::make_shared<spdlog::logger>("main", sinks);
    logger.get()->set_level(spdlog::level::debug);
    spdlog::set_default_logger(logger);
}

#ifndef NDEBUG
static void setup_imgui(fs::path &my_dir, sf::RenderWindow &window) {
    static const std::string imgui_ini_filename{my_dir.string() + std::string{"/imgui.ini"}};
    static const std::string imgui_log_filename{my_dir.string() + std::string{"/imgui_log.txt"}};

    if (!ImGui::SFML::Init(window)) {
        spdlog::error("ImGui initialization failed");
    }

    ImGui::GetIO().IniFilename = imgui_ini_filename.c_str();
    ImGui::GetIO().LogFilename = imgui_log_filename.c_str();
}
#endif

int main(int argc, char *argv[]) {
    std::vector<std::string> args(argv, argv + argc);
    fs::path prog{args[0]};
    fs::path my_dir{fs::canonical(prog.parent_path()).string()};

    setup_spdlog(my_dir);
    spdlog::info("Application started");

    sf::RenderWindow window(sf::VideoMode(640, 480), "SFML Tutorial");
    window.setVerticalSyncEnabled(true);

#ifndef NDEBUG
    setup_imgui(my_dir, window);
    spdlog::info("ImGui started");
#endif

    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    sf::Clock deltaClock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
#ifndef NDEBUG
            ImGui::SFML::ProcessEvent(window, event);
#endif

            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))
                window.close();
        }

#ifndef NDEBUG
        ImGui::SFML::Update(window, deltaClock.restart());

        ImGui::Begin("FPS");
        ImGui::Text("%.1f", ImGui::GetIO().Framerate);
        ImGui::End();
#endif

        window.clear();
        window.draw(shape);

#ifndef NDEBUG
        ImGui::SFML::Render(window);
#endif

        window.display();
    }

#ifndef NDEBUG
    ImGui::SFML::Shutdown();
#endif

    return 0;
}
