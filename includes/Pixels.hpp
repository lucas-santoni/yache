#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

#include "state.hpp"

class Pixels {
  public:
    explicit Pixels(uint32_t w, uint32_t h);

  private:
    std::vector<sf::Uint8> _pixels;
    std::vector<state> _pixelStates;
    uint32_t _width = 0;
    uint32_t _height = 0;

  private:
    void _setPixel(uint32_t w, uint32_t h);
    void _unsetPixel(uint32_t w, uint32_t h);

  public:
    sf::Uint8 *raw(void);
    void toogle(uint32_t w, uint32_t h);
    void decAllStates(void);
    bool isSet(uint32_t w, uint32_t h);
    uint32_t width(void) const;
    uint32_t height(void) const;
};
