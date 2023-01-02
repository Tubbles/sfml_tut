// Copyright (C) Tubbles github.com/Tubbles

#include "event.hpp"
#include "spdlog/spdlog.h"
#include <fmt/core.h>
#include <map>
#include <vector>

namespace event {
struct PrioCallback {
    Callback callback;
    uint32_t prio;
};

static std::map<Type, std::vector<PrioCallback>> callbacks;

void register_callback(sf::Event::EventType type, uint32_t priority, Callback callback) {
    spdlog::debug("Attempting to register callback for event type {} with priority {}", type, priority);
    auto &vec = callbacks[type];

    for (auto it = vec.begin(); it != vec.end(); ++it) {
        if (priority < (*it).prio) {
            vec.insert(it, {callback, priority});
            spdlog::debug("Registered callback for event type {} with priority {} (insert)", type, priority);
            return;
        }
    }

    vec.push_back({callback, priority});
    spdlog::debug("Registered callback for event type {} with priority {} (push)", type, priority);
}

void execute_callbacks(Event &event) {
    auto &vec = callbacks[event.type];
    for (auto &elem : vec) {
        if (elem.callback(event)) {
            break;
        }
    }
}
} // namespace event
