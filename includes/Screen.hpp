#pragma once

#include <vector>
#include <array>
#include <SFML/Graphics.hpp>

#include "Specs.hpp"
#include "state.hpp"

class Screen {
  public:
    explicit Screen(uint32_t w = Specs::WINDOW_WIDTH,
        uint32_t h = Specs::WINDOW_HEIGHT);

  private:
    std::vector<sf::Uint8> _pixels;
    std::vector<state> _pixelStates;
    std::array<bool, Specs::NUMBER_OF_KEYS> _keys = {{false}};
    uint32_t _width = 0;
    uint32_t _height = 0;

  private:
    sf::RenderWindow _window;
    sf::Texture _texture;
    sf::Sprite _sprite;
    sf::Event _windowEvent;

  private:
    bool _redraw = true;

  private:
    void _updateKeyStatus(void);

  public:
    void cycle(void);
    void clear(void);

  public:
    void unsetPixel(uint32_t w, uint32_t h);
    void setPixel(uint32_t w, uint32_t h);
    void toogle(uint32_t w, uint32_t h);
    void decAllStates(void);
    void setRedraw(bool state);

  public:
    const sf::Uint8 *raw(void) const;
    const std::array<bool, Specs::NUMBER_OF_KEYS>&
      getKeys(void) const;
    bool isPixelSet(uint32_t w, uint32_t h) const;
    uint32_t width(void) const;
    uint32_t height(void) const;
    uint8_t getKeyPressed(void) const;
    bool isAKeyPressed(void) const;
};
