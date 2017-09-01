#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

class Pixels {
  public:
    explicit Pixels(uint32_t w, uint32_t h);

  private:
    std::vector<sf::Uint8> _pixels;
    uint32_t _width = 0;
    uint32_t _height = 0;

  public:
    sf::Uint8 *raw(void);
    void toogle(uint32_t w, uint32_t h);
    bool isSet(uint32_t w, uint32_t h);
    uint32_t width(void) const;
    uint32_t height(void) const;
};
