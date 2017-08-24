#include <fstream>
#include "Chip8.hpp"

void Chip8::reset(void) {
  cpu.reset();
  memory.reset();
  screen.reset();
  keypad.reset();
}

void Chip8::dumpMemory(uint32_t from, uint32_t to) const {
  if (to > Specs::RAM_SIZE || from > to)
    return;

  memory.dump(from, to);
}

void Chip8::dumpMemory(void) const {
  dumpMemory(0, Specs::RAM_SIZE);
}

void Chip8::loadRomFromFile(const std::string& filePath) {
  std::ifstream rom;

  rom.open(filePath, std::ios::binary);
  rom.read(memory.getCharRamPointer(), Specs::RAM_SIZE);
  rom.close();
}
