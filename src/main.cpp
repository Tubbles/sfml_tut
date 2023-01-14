// Copyright (C) Tubbles github.com/Tubbles

#include "event.hpp"
#include "imgui-SFML.h"
#include "imgui.h"
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

    event::schd::post(event::schd::Event{.type = event::schd::Type::Init, .init = {}});

    sf::RenderWindow window(sf::VideoMode(640, 480), "SFML Tutorial");
    window.setVerticalSyncEnabled(true); // Cap at 60 Hz

#ifndef NDEBUG
    debug::setup(my_dir, window);
#endif

    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    sf::Clock deltaClock;

    event::sfml::register_callback(event::sfml::Type::Closed, 999, [&window](event::sfml::Event event) {
        (void)event;
        window.close();
        return event::Action::Block;
    });

    event::sfml::register_callback(event::sfml::Type::KeyPressed, 999, [&window](event::sfml::Event event) {
        if (event.key.code == sf::Keyboard::Escape) {
            window.close();
            return event::Action::Block;
        }
        return event::Action::Pass;
    });

    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
#ifndef NDEBUG
            ImGui::SFML::ProcessEvent(window, event);
#endif

            event::sfml::post(event);
        }

        // Update
        event::schd::post(event::schd::Event{.type = event::schd::Type::Update, .update = {deltaClock.restart()}});

        // Draw
        window.clear();
        window.draw(shape);
        event::schd::post(event::schd::Event{.type = event::schd::Type::Draw, .draw = {}});
        window.display();
    }

    // Shutdown
    event::schd::post(event::schd::Event{.type = event::schd::Type::Shutdown, .shutdown = {}});

    return 0;
}
