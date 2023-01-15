// Copyright (C) Tubbles github.com/Tubbles

#include "collision.hpp"
#include "log.hpp"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

namespace col {

// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
static std::vector<Body> bodies{};

// NOLINTNEXTLINE(readability-identifier-length)
static auto rect_col(const sf::RectangleShape &r1, const sf::RectangleShape &r2) -> bool {
    auto pos = r1.getPosition();
    auto size = r1.getSize();
    auto opos = r2.getPosition();
    auto osize = r2.getSize();

    // clang-format off
    return ((pos.x < (opos.x + osize.x)) && ((pos.x + size.x) > opos.x) &&
            (pos.y < (opos.y + osize.y)) && ((pos.y + size.y) > opos.y));
    // clang-format on
}

// // NOLINTNEXTLINE(readability-identifier-length)
// static auto circ_col(const sf::CircleShape &c1, const sf::CircleShape &c2) -> bool {
//     (void)c1;
//     (void)c2;
//     // TODO
//     return false;
// }

// // NOLINTNEXTLINE(readability-identifier-length)
// static auto rect_circ_col(const sf::RectangleShape &r, const sf::CircleShape &c) -> bool {
//     (void)r;
//     (void)c;
//     // TODO
//     return false;
// }

static auto check_cols(const sf::RectangleShape &shape, const std::vector<Body> &bodies) -> std::vector<Collision> {
    std::vector<Collision> vec{};

    for (auto body : bodies) {
        if (&shape == body.shape) {
            continue;
        }
        if (auto *oshape = dynamic_cast<sf::RectangleShape *>(body.shape); oshape) {
            if (rect_col(shape, *oshape)) {
                vec.push_back({.other = body});
            }
        } else if (auto *oshape = dynamic_cast<sf::CircleShape *>(body.shape); oshape) {
            (void)oshape;
            // TODO
        }
    }

    return vec;
}

void register_body(const Body &body) { bodies.push_back(body); }

auto get(const Body &body) -> std::vector<Collision> {
    std::vector<Collision> vec{};
    (void)body;
    if (auto *shape = dynamic_cast<sf::RectangleShape *>(body.shape); shape) {
        vec = check_cols(*shape, bodies);
    } else if (auto *shape = dynamic_cast<sf::CircleShape *>(body.shape); shape) {
        (void)shape;
        // TODO
    }

    return vec;
}

void move(const Body &body, const Collision &col, Move move) {
    (void)body;
    (void)col;
    (void)move;
}
} // namespace col