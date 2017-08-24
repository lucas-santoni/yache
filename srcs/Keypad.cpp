#include "Keypad.hpp"

Keypad::Keypad(void) {
  reset();
}

void Keypad::reset(void) {
  keyStates.fill(0);
}
