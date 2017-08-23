#include "Chip8.hpp"

void Chip8::reset(void) {
  cpu.reset();
  memory.reset();
  screen.reset();
  keypad.reset();
}
