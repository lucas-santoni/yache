#include "Chip8.hpp"
#include "Color.hpp"

void Chip8::dumpMemory(uint32_t from, uint32_t to) {
  int32_t line = 1;

  if (to <= from || to > Specs::MEMORY_SIZE)
    return;

  for (; from < to; ++from) {
    if (_pc == from)
      printf(RED "%02x " RESET, _memory[from]);
    else
      printf("%02x ", _memory[from]);
    if (line++ % 64 == 0)
      printf("\n");
  }

  printf("%02x\n", _memory[to]);
}
