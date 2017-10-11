#include "MonochromeDisplay.hpp"

// Setup the SFML stuff
// Takes window size, window scale and window title
// Most of the default stuff is set in the class
// definition
sf::MonochromeDisplay::MonochromeDisplay(uint32_t w,
    uint32_t h, uint32_t scale, const std::string& title) :
  _pixels(w * h * 4, 0),
  _window(sf::VideoMode(w * scale,
        h * scale), title) {
  _window.setVerticalSyncEnabled(true);
  _window.setFramerateLimit(60);
  _texture.create(w, h);
  _sprite.setTexture(_texture);
  _sprite.scale(scale, scale);

  _width = w;
  _height = h;
}

// Change the colors
// This is monochrome so we only accept two colors
// We could accept only one (MONOchrome) but chosing
// the background color is still a nice feature to have
void sf::MonochromeDisplay::setColors(const sf::Color& background,
    const sf::Color& foreground) {
  _foreground = foreground;
  _background = background;
}

// Change the color of one pixel
void sf::MonochromeDisplay::changePixelColor(uint32_t w, uint32_t h,
    const sf::Color& color) {
  _pixels[(h * _width + w) * 4] = color.r;
  _pixels[(h * _width + w) * 4 + 1] = color.g;
  _pixels[(h * _width + w) * 4 + 2] = color.b;
  _pixels[(h * _width + w) * 4 + 3] = color.a;
}

// Handle events
// Refresh window
// The screen is not updated when it does not need to
// See update() for sprite update
void sf::MonochromeDisplay::refresh(void) {
  while (_window.pollEvent(_windowEvent)) {
    switch (_windowEvent.type) {
      case sf::Event::Closed:
        _window.close();
        break;
      default:
        break;
    }
  }

  _window.clear(_background);
  _window.draw(_sprite);
  _window.display();
}

// Check if underlying SFML window is still alive
bool sf::MonochromeDisplay::isOpen(void) const {
  return _window.isOpen();
}
