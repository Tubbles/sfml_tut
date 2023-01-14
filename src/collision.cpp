// Copyright (C) Tubbles github.com/Tubbles

#include "collision.hpp"

namespace col {

// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
static std::vector<sf::RectangleShape *> rects{};
void register_shape(sf::RectangleShape &shape) { rects.push_back(&shape); }

// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
static std::vector<sf::CircleShape *> circles{};
void register_shape(sf::CircleShape &shape) { circles.push_back(&shape); }

auto get(sf::RectangleShape &shape) -> std::vector<Collision> {
    std::vector<Collision> vec{};

    auto pos = shape.getPosition();
    auto size = shape.getSize();
    for (auto *other : rects) {
        if (other == &shape) {
            continue;
        }
        auto opos = other->getPosition();
        auto osize = other->getSize();
        // clang-format off
        if ((pos.x < (opos.x + osize.x)) && ((pos.x + size.x) > opos.x) &&
            (pos.y < (opos.y + osize.y)) && ((pos.y + size.y) > opos.y)) {
            // clang-format on
            // Collision!
            vec.push_back({.other_type = Collision::Rectangle, .rect = other});
        }
    }
    // TODO : Add CircleShape detection as well
    return vec;
}

auto get(sf::CircleShape &shape) -> std::vector<Collision> {
    // TODO
    (void)shape;
    std::vector<Collision> vec{};
    //
    return vec;
}

void move(Collision col, sf::RectangleShape &shape, Move move) {
    (void)col;
    (void)shape;
    (void)move;
    auto pos = shape.getPosition();
    auto size = shape.getSize();
    switch (col.other_type) {
    case col::Collision::Rectangle: {
        auto opos = col.rect->getPosition();
        auto osize = col.rect->getSize();
        if ((pos.x < (opos.x + osize.x)) && ((pos.x + size.x) > opos.x)) {
            shape.setPosition(pos.x, pos.y);
        }
        break;
    }
    case col::Collision::Circle: {
        // TODO
        break;
    }
    default: {
        break;
    }
    }
}

void move(Collision col, sf::CircleShape &shape, Move move) {
    (void)col;
    (void)shape;
    (void)move;
    // TODO
}
} // namespace col