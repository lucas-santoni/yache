#pragma once

#include "Cpu.hpp"
#include "Memory.hpp"
#include "Screen.hpp"
#include "Keypad.hpp"

class Chip8 {
  private:
    Cpu cpu;
    Memory memory;
    Screen screen;
    Keypad keypad;

  public:
    void reset(void);
};
