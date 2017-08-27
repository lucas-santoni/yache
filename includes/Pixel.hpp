#pragma once

#include <array>

#include <SFML/Graphics.hpp>

class Pixel {
  private:
    std::array<sf::Uint8, 4> _pixel = {};
    bool _set = false;

  public:
    void color(uint8_t r, uint8_t g, uint8_t b);
    void reset(void);
    bool isSet(void) const;
};
