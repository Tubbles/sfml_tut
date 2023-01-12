// Copyright (C) Tubbles github.com/Tubbles

#pragma once

#include "fs.hpp"
#include "imgui-SFML.h"
#include "imgui.h"
#include <SFML/Graphics/RenderWindow.hpp>

namespace debug {
void setup(fs::path &my_dir, sf::RenderWindow &window);
}
