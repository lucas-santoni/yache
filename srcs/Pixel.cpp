#include "Pixel.hpp"

void Pixel::color(uint8_t r, uint8_t g, uint8_t b) {
  _pixel[0] = r;
  _pixel[1] = g;
  _pixel[2] = b;
  _pixel[3] = 255;

  _set = true;
}

 void Pixel::reset(void) {
  _pixel.fill(0);
  _set = false;
 }

bool Pixel::isSet(void) const {
  return _set;
}
