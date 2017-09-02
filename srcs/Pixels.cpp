#include "Pixels.hpp"

Pixels::Pixels(uint32_t w, uint32_t h) :
  _pixels(w * h * 4)
{
  _width = w;
  _height = h;
}

sf::Uint8 *Pixels::raw(void) {
  return _pixels.data();
}

// TODO: Error handling
void Pixels::toogle(uint32_t w, uint32_t h) {
  if (_pixels[(_width * h + w) * 4 + 3] != 255) {
    _pixels[(_width * h + w) * 4] = 255;
    _pixels[(_width * h + w) * 4 + 1] = 255;
    _pixels[(_width * h + w) * 4 + 2] = 255;
    _pixels[(_width * h + w) * 4 + 3] = 255;
  } else
    _pixels[(_width * h + w) * 4 + 3] = 0;
}

bool Pixels::isSet(uint32_t w, uint32_t h) {
  return _pixels[(_width * h + w) + 3] != 0;
}

uint32_t Pixels::width(void) const {
  return _width;
}

uint32_t Pixels::height(void) const {
  return _height;
}
