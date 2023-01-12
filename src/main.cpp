// Copyright (C) Tubbles github.com/Tubbles

#include "event.hpp"
#include "log.hpp"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <fmt/core.h>

#ifndef NDEBUG
#include "debug.hpp"
#endif

auto main(int argc, char *argv[]) -> int {
    std::vector<std::string> args(argv, argv + argc);
    fs::path prog{args[0]};
    fs::path my_dir{fs::canonical(prog.parent_path()).string()};

    lg::setup(my_dir);
    spdlog::info("Application started");

    for (auto &arg : args) {
        spdlog::info("Arg #{}#", arg);
    }

    sf::RenderWindow window(sf::VideoMode(640, 480), "SFML Tutorial");
    window.setVerticalSyncEnabled(true); // Cap at 60 Hz

#ifndef NDEBUG
    debug::setup(my_dir, window);
#endif

    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    sf::Clock deltaClock;

#ifndef NDEBUG
    bool show_imgui = false;

    event::register_callback(event::Event::KeyPressed, 500, [&show_imgui](event::Event &event) {
        if (event.key.code == sf::Keyboard::F1) {
            show_imgui = !show_imgui;
        }
        return false;
    });
#endif

    event::register_callback(event::Event::Closed, 999, [&window](event::Event &event) {
        (void)event;
        window.close();
        return true;
    });

    event::register_callback(event::Event::KeyPressed, 999, [&window](event::Event &event) {
        if (event.key.code == sf::Keyboard::Escape) {
            window.close();
            return true;
        }
        return false;
    });

    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
#ifndef NDEBUG
            ImGui::SFML::ProcessEvent(window, event);
#endif

            event::execute_callbacks(event);
        }

#ifndef NDEBUG
        ImGui::SFML::Update(window, deltaClock.restart());

        if (show_imgui) {
            ImGui::Begin("FPS");
            ImGui::Text("%s", fmt::format("{:.1f}", ImGui::GetIO().Framerate).c_str());
            ImGui::End();
        }
#endif

        window.clear();
        window.draw(shape);

#ifndef NDEBUG
        if (show_imgui) {
            ImGui::SFML::Render(window);
        } else {
            ImGui::EndFrame();
        }
#endif

        window.display();
    }

#ifndef NDEBUG
    ImGui::SFML::Shutdown();
#endif

    return 0;
}
