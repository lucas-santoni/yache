#pragma once

#include <cstdint>

#include <SFML/Graphics.hpp>

typedef struct {
  sf::Keyboard::Key k;
  uint8_t id;
} Key;
