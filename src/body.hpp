// Copyright (C) Tubbles github.com/Tubbles

#pragma once

#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <memory>

struct Body {
    sf::Shape *shape{};
    sf::Vector2f velocity{};
    bool is_static{false};
};
