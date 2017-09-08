#include "Pixels.hpp"

// All pixels start at 0 and unset
// Our arrays are 1d
// To convert 2d coordinates (x, y) to 1d do (width * y + x)
// Which is size of row by the number of rows
// plus the remaining columns
// _pixelStates is used for timeouts on unset
Pixels::Pixels(uint32_t w, uint32_t h) :
  _pixels(w * h * 4, 0),
  _pixelStates(w * h, {0, false})
{
  _width = w;
  _height = h;
}

// Get the memory adress of our pixels
sf::Uint8 *Pixels::raw(void) {
  return _pixels.data();
}

// Set a pixel
// TODO: Change colour
void Pixels::_setPixel(uint32_t w, uint32_t h) {
  _pixels[(_width * h + w) * 4] = 255;
  _pixels[(_width * h + w) * 4 + 1] = 255;
  _pixels[(_width * h + w) * 4 + 2] = 255;
  _pixels[(_width * h + w) * 4 + 3] = 255;
  _pixelStates[_width * h + w].active = true;
}

// Uset a pixel
// Actually only set a timeout
// decAllStates() may unset the pixel if the timeout ends
void Pixels::_unsetPixel(uint32_t w, uint32_t h) {
  _pixelStates[_width * h + w].timeout = 1;
  _pixelStates[_width * h + w].active = false;
}

// on/off switch
// the chip8 screen works by xor
// TODO: Error handling
void Pixels::toogle(uint32_t w, uint32_t h) {
  if (!isSet(w, h))
    _setPixel(w, h);
  else
    _unsetPixel(w, h);
}

// Decrease all timeouts
// Unset the pixels when their timeouts reach zero
// Can be done at any cycle or at any draw
void Pixels::decAllStates(void) {
  for (uint32_t i = 0; i < _width; ++i) {
    for (uint32_t j = 0; j < _height; ++j) {
      if (_pixelStates[_width * j + i].timeout > 0)
        --_pixelStates[_width * j + i].timeout;
      else if (!isSet(i, j) &&
          _pixelStates[_width * j + i].timeout == 0)
        _pixels[(_width * j + i) * 4 + 3] = 0;
    }
  }
}

// Get pixel status
bool Pixels::isSet(uint32_t w, uint32_t h) {
  return _pixelStates[(_width * h + w)].active;
}

// Get width of array
uint32_t Pixels::width(void) const {
  return _width;
}

// Get height of array
uint32_t Pixels::height(void) const {
  return _height;
}
