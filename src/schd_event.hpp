// Copyright (C) Tubbles github.com/Tubbles

#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Time.hpp>
#include <memory>

namespace schd {
struct Event {
    struct UpdateEvent {
        sf::Time delta{};
    };

    struct DrawEvent {
        sf::RenderWindow *window{};
    };

    struct ShutdownEvent {};

    enum EventType {
        Update,
        Draw,
        Shutdown,
    };

    EventType type{};

    union {
        UpdateEvent update;
        DrawEvent draw;
        ShutdownEvent shutdown;
    };
};
} // namespace schd