#include "Screen.hpp"
#include "Specs.hpp"
#include "status.hpp"
#include "Keypad.hpp"

// All pixels start at 0 and unset
// The arrays are 1d
// To convert 2d coordinates (x, y) to 1d do (width * y + x)
// Which is size of row by the number of rows
// plus the remaining columns
// _pixelStates is used for timeouts on unset
// Link sprite and texture
// Scale the whole
Screen::Screen(uint32_t w, uint32_t h) :
  _pixels(w * h * 4, 0),
  _pixelStates(w * h, {0, false}),
  _window(sf::VideoMode(w * Specs::WINDOW_SCALE,
        h * Specs::WINDOW_SCALE), "Yache") {
  _window.setVerticalSyncEnabled(true);
  _window.setFramerateLimit(60);
  _texture.create(w, h);
  _sprite.setTexture(_texture);
  _sprite.scale(Specs::WINDOW_SCALE, Specs::WINDOW_SCALE);

  _width = w;
  _height = h;
}

// Get the memory adress of our pixels
const sf::Uint8 *Screen::raw(void) const {
  return _pixels.data();
}

const std::array<bool, Specs::NUMBER_OF_KEYS>&
  Screen::getKeys(void) const {
  return _keys;
}

// Set a pixel
// TODO: Change colour
void Screen::setPixel(uint32_t w, uint32_t h) {
  _pixels[(_width * h + w) * 4] = 255;
  _pixels[(_width * h + w) * 4 + 1] = 255;
  _pixels[(_width * h + w) * 4 + 2] = 255;
  _pixels[(_width * h + w) * 4 + 3] = 255;
  _pixelStates[_width * h + w].active = true;
}

// Uset a pixel
// Actually only set a timeout
// decAllStates() may unset the pixel if the timeout ends
void Screen::unsetPixel(uint32_t w, uint32_t h) {
  _pixelStates[_width * h + w].timeout = 1;
  _pixelStates[_width * h + w].active = false;
}

// on/off switch
// the chip8 screen works by xor
void Screen::toogle(uint32_t w, uint32_t h) {
  if (!isPixelSet(w, h))
    setPixel(w, h);
  else
    unsetPixel(w, h);
}

// Decrease all timeouts
// Unset the pixels when their timeouts reach zero
// Can be done at any cycle or at any draw
void Screen::decAllStates(void) {
  for (uint32_t i = 0; i < _width; ++i) {
    for (uint32_t j = 0; j < _height; ++j) {
      if (_pixelStates[_width * j + i].timeout > 0)
        --_pixelStates[_width * j + i].timeout;
      else if (!isPixelSet(i, j) &&
          _pixelStates[_width * j + i].timeout == 0)
        _pixels[(_width * j + i) * 4 + 3] = 0;
    }
  }
}

// _redraw attribute accessor
void Screen::setRedraw(bool state) {
  _redraw = state;
}

// Get pixel status
bool Screen::isPixelSet(uint32_t w, uint32_t h) const {
  return _pixelStates[(_width * h + w)].active;
}

// Get width of array
uint32_t Screen::width(void) const {
  return _width;
}

// Get height of array
uint32_t Screen::height(void) const {
  return _height;
}

// Get any keyboard activity
void Screen::_updateKeyStatus(void) {
  for (auto& key : Keypad::keys)
    if (sf::Keyboard::isKeyPressed(key.k))
      _keys[key.i] = true;
    else
      _keys[key.i] = false;
}

uint8_t Screen::getKeyPressed(void) const {
  for (uint8_t i = 0; i < Specs::NUMBER_OF_KEYS; ++i)
    if (_keys[i])
      return i;
  return FAILURE;
}

bool Screen::isAKeyPressed(void) const {
  for (auto& key : _keys)
    if (key)
      return true;
  return false;
}

// Update the window, every frame
// If events, deal with them
// Update all the pixel timeouts
// If needed, redraw the screen
void Screen::cycle(void) {
  while (_window.pollEvent(_windowEvent)) {
    switch (_windowEvent.type) {
      case sf::Event::Closed:
        _window.close();
        exit(SUCCESS);

      case sf::Event::KeyPressed:
        _updateKeyStatus();
        break;
      case sf::Event::KeyReleased:
        _updateKeyStatus();
        break;

      default:
        break;
    }
  }

  decAllStates();

  if (_redraw) {
    _texture.update(raw());
    _window.clear();
    _window.draw(_sprite);
    _window.display();

    _redraw = false;
  }
}

// Clear the screen
// Unset all pixels
void Screen::clear(void) {
  for (uint32_t i = 0; i < _width; ++i) {
    for (uint32_t j = 0; j < _height; ++j)
      unsetPixel(i, j);
  }
}
