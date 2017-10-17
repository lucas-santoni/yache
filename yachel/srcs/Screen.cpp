#include "../includes/Screen.hpp"

Yachel::Screen::Screen(uint32_t w, uint32_t h) :
  _screen(w * h),
  _meta(w * h) {
  _width = w;
}

const std::vector<bool>& Yachel::Screen::what(void) const {
  return _screen;
}

bool Yachel::Screen::isPixelSet(uint32_t w, uint32_t h) const {
  return _meta[h * _width + w].active;
}

bool Yachel::Screen::isPixelSet(uint32_t i) const {
  return _meta[i].active;
}

void Yachel::Screen::setPixel(uint32_t w, uint32_t h) {
  _screen[h * _width + w] = true;
  _meta[h * _width + w].active = true;
}

void Yachel::Screen::setPixel(uint32_t i) {
  _screen[i] = true;
}

void Yachel::Screen::unsetPixel(uint32_t w, uint32_t h) {
  _meta[h * _width + w].active = false;
  _meta[h * _width + w ].timeout = TIMEOUT;
}

void Yachel::Screen::unsetPixel(uint32_t i) {
  _screen[i] = false;
}

void Yachel::Screen::tooglePixel(uint32_t w, uint32_t h) {
  if (isPixelSet(w, h))
    unsetPixel(w, h);
  else
    setPixel(w, h);
}

void Yachel::Screen::tooglePixel(uint32_t i) {
  if (isPixelSet(i))
    unsetPixel(i);
  else
    setPixel(i);
}

void Yachel::Screen::handleMeta(void) {
  for (uint32_t i = 0; i < _meta.size(); ++i) {
    if (_meta[i].timeout > 0)
      --_meta[i].timeout;
    else if (_meta[i].timeout == 0 && !isPixelSet(i))
      unsetPixel(i);
  }
}
