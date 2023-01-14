// Copyright (C) Tubbles github.com/Tubbles

#pragma once

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <vector>

namespace col {
struct Collision {
    enum Type {
        Circle,
        Rectangle,
    };

    Type other_type{};

    union {
        sf::RectangleShape *rect;
        sf::CircleShape *circle;
    };
};

enum class Move {
    Me,
    Them,
    Both,
};

void register_shape(sf::RectangleShape &);
void register_shape(sf::CircleShape &);
auto get(sf::RectangleShape &) -> std::vector<Collision>;
auto get(sf::CircleShape &) -> std::vector<Collision>;
void move(Collision, sf::RectangleShape &, Move);
void move(Collision, sf::CircleShape &, Move);
} // namespace col
