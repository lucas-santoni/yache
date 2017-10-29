#pragma once

#include "MonochromeDisplay.hpp"
#include "HexKeypad.hpp"

namespace sf {
  // Add keypad support to a monochrome display
  // Reimplements the refresh method in order to get the pressed keys
  // Keys are then forwarded to the backend
  // Backend is any device implementing keyPressed/Released methods
  class MonochromeDisplayKeypad : public sf::MonochromeDisplay {
    private:
      HexKeypad _keypad;

    public:
      using MonochromeDisplay::MonochromeDisplay;
      template <typename T>
      void refresh(T& backend);
  };
}

// Refresh the window like the abstract class
// Add keypad support
template <typename T>
void sf::MonochromeDisplayKeypad::refresh(T& backend) {
  while (_window.pollEvent(_windowEvent)) {
    switch (_windowEvent.type) {
      case sf::Event::Closed:
        _window.close();
        break;
      case::sf::Event::KeyPressed:
        backend.keyPressed(_keypad.getKeyId(_windowEvent.key.code));
        break;
      case::sf::Event::KeyReleased:
        backend.keyReleased(_keypad.getKeyId(_windowEvent.key.code));
        break;
      default:
        break;
    }
  }

  _window.clear(_background);
  _window.draw(_sprite);
  _window.display();
}
