#include "Memory.hpp"

void Memory::reset(void) {
  for (uint32_t i = 0; i < sizeof(ram); ++i)
    ram[i] = 0;
}

void Memory::dump(uint32_t from=0, uint32_t to=Specs::RAM_SIZE) const {
  uint32_t line = 1;

  for (uint32_t i = from; i < to; ++i) {
    printf("%02x", ram[i]);
    if (line % 16 == 0)
      printf("\n");
    else
      printf(" ");
    ++line;
  }
}

char *Memory::getCharRamPointer(void) const {
  return (char *)ram;
}
