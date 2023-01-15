// Copyright (C) Tubbles github.com/Tubbles

#pragma once

#include "body.hpp"
#include <SFML/Graphics/Shape.hpp>
#include <variant>
#include <vector>

namespace col {
struct Collision {
    Body other{};
};

enum class Move {
    Me,
    Them,
    Both,
};

void register_body(const Body &);
auto get(const Body &) -> std::vector<Collision>;
void move(const Body &, const Collision &, Move);
} // namespace col
