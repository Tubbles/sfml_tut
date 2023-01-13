// Copyright (C) Tubbles github.com/Tubbles

#pragma once

#include <SFML/Window/Event.hpp>
#include <functional>

namespace event {
using sf::Event;
using Type = sf::Event::EventType;
// event::Callback typedef, return true if the event processing is finished
using Callback = std::function<bool(Event &)>;
void register_callback(Type type, uint32_t priority, const Callback &callback);
void execute_callbacks(Event &event);
} // namespace event
