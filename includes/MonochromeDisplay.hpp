#pragma once

#include <SFML/Graphics.hpp>

// A monochromatic display built on top of SFML
// Takes an array of booleans to display things
namespace sf {
  class MonochromeDisplay {
    public:
      explicit MonochromeDisplay(uint32_t w, uint32_t h, uint32_t scale = 1,
          const std::string& title = "Monochromatic Window");

    private:
      std::vector<sf::Uint8> _pixels;

    protected:
      sf::RenderWindow _window;
      sf::Texture _texture;
      sf::Sprite _sprite;
      sf::Event _windowEvent;
      sf::Color _background = sf::Color::Black;
      sf::Color _foreground = sf::Color::White;

    private:
      uint32_t _width = 0;
      uint32_t _height = 0;

    public:
      template <typename T>
      void update(const T& booleans);
      virtual void refresh(void);
      bool isOpen(void) const;
      void setColors(const sf::Color& background,
          const sf::Color &foreground);
      void changePixelColor(uint32_t w, uint32_t h, const sf::Color& color);
  };
}

// Takes any sort of container
// The elements will be evaluated as booleans
// If true, then the pixel is set
// If false, the the pixel is unset
template <typename T>
void sf::MonochromeDisplay::update(const T& booleans) {
  for (uint32_t x = 0; x < _width; ++x) {
    for (uint32_t y = 0; y < _height; ++y) {
      if (booleans[y * _width + x])
        changePixelColor(x, y, _foreground);
      else
        changePixelColor(x, y, _background);
    }
  }

  _texture.update(_pixels.data());
}
