// Copyright (C) Tubbles github.com/Tubbles

#pragma once

#include <SFML/Window/Event.hpp>
#include <functional>

namespace event {
typedef sf::Event Event;
typedef sf::Event::EventType Type;
// event::Callback typedef, return true if the event processing is finished
typedef std::function<bool(Event&)> Callback;
void register_callback(Type type, uint32_t priority, Callback callback);
void execute_callbacks(Event &event);
} // namespace event
