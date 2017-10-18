#include "../includes/Screen.hpp"

// Build the vectors from screen size
// Save the width for framebuffer index calculation
// Set timeout if passed
Yachel::Screen::Screen(uint32_t w, uint32_t h, uint32_t timeout) :
  _screen(w * h),
  _meta(w * h) {
  _width = w;
  _timeout = timeout;
}

// Return the vector of booleans
const std::vector<bool>& Yachel::Screen::what(void) const {
  return _screen;
}

// Change timeout
void Yachel::Screen::setTimeout(uint32_t timeout) {
  _timeout = timeout;
}

// Is a pixel set ?
// A pixel can be unset and still visible because of the timeout system
// This function is based on the activity and not the visibility
// Mostly for collision detections
bool Yachel::Screen::isPixelSet(uint32_t w, uint32_t h) const {
  return _meta[h * _width + w].active;
}

// Same but with raw index
bool Yachel::Screen::isPixelSet(uint32_t i) const {
  return _meta[i].active;
}

// Set a pixel
void Yachel::Screen::setPixel(uint32_t w, uint32_t h) {
  _screen[h * _width + w] = true;
  _meta[h * _width + w].active = true;
}

// Same with raw index
void Yachel::Screen::setPixel(uint32_t i) {
  _screen[i] = true;
  _meta[i].active = true;
}

// Unset a pixel
// Record activity for collision detection
// Set a timeout
// Pixel is still visible, it will not be only if timeout
// reaches 0 in handleMeta()
void Yachel::Screen::unsetPixel(uint32_t w, uint32_t h) {
  _meta[h * _width + w].active = false;
  _meta[h * _width + w ].timeout = _timeout;
}

// Same with raw index
void Yachel::Screen::unsetPixel(uint32_t i) {
  _meta[i].active = false;
  _meta[i].timeout = _timeout;
}

// Toogle a pixel
void Yachel::Screen::tooglePixel(uint32_t w, uint32_t h) {
  if (isPixelSet(w, h))
    unsetPixel(w, h);
  else
    setPixel(w, h);
}

// Same with raw index
void Yachel::Screen::tooglePixel(uint32_t i) {
  if (isPixelSet(i))
    unsetPixel(i);
  else
    setPixel(i);
}

// Decrease all the set timeouts
// If one reaches zero and pixel is not supposed to be visible
// (= is inactive) then makes it invisible
void Yachel::Screen::handleMeta(void) {
  for (uint32_t i = 0; i < _meta.size(); ++i) {
    if (_meta[i].timeout > 0)
      --_meta[i].timeout;
    else if (_meta[i].timeout == 0 && !isPixelSet(i))
      _screen[i] = false;
  }
}
