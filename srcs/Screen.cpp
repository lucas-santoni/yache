#include "Screen.hpp"

Screen::Screen(void) {
  reset();
}

void Screen::reset(void) {
  vram.fill(0);
}
