#pragma once

#include <string>

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

  public:
    void dumpMemory(uint32_t from, uint32_t to) const;
    void dumpMemory() const;

  public:
    void loadRomFromFile(const std::string& filePath);
};
