#include <fstream>

#include "Chip8.hpp"
#include "status.hpp"

// TODO: Error handling
void Chip8::loadRomFromFile(const std::string& filePath) {
  std::ifstream rom;

  rom.open(filePath, std::ios::binary);
  if (!rom.good())
    return;

  rom.read(reinterpret_cast<char *>(_memory.data() + Specs::ROM_OFFSET),
      Specs::MEMORY_SIZE);
  rom.close();
}

// TODO: Error handling
void Chip8::dumpMemory(uint32_t from, uint32_t to) const {
  if (from > to || to > Specs::MEMORY_SIZE)
    return;

  uint32_t line = 1;
  for (uint32_t i = from; i < to; ++i) {
    if (line++ % 16 == 0)
      printf("%02x\n", _memory[i]);
    else
      printf("%02x ", _memory[i]);
  }
}

void Chip8::cycle(void) {
  _currentOpcode = _memory[_pc] << 8 | _memory[_pc + 1];

  for (auto& op : _opcodes) {
    if ((_currentOpcode & op.mask) == op.key) {
      printf("%04x\n", _currentOpcode);
      op.f(this);
      break;
    }
  }
  _pc += sizeof(uint16_t);
}
