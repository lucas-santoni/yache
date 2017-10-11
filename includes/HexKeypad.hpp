#pragma once

#include <array>
#include <SFML/Graphics.hpp>

#include "Yachel.hpp"
#include "Key.hpp"

class HexKeypad {
  public:
    int32_t getKeyId(const sf::Keyboard::Key& k) const;
};
