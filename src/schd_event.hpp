// Copyright (C) Tubbles github.com/Tubbles

#pragma once

#include <SFML/System/Time.hpp>

namespace schd {
struct Event {
    struct InitEvent {
        int a;
    };

    struct UpdateEvent {
        sf::Time delta;
    };

    struct DrawEvent {
        int a;
    };

    struct ShutdownEvent {
        int a;
    };

    enum EventType {
        Init,
        Update,
        Draw,
        Shutdown,
    };

    EventType type;

    union {
        InitEvent init;
        UpdateEvent update;
        DrawEvent draw;
        ShutdownEvent shutdown;
    };
};
} // namespace schd