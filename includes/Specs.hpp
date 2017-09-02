#include <cstdint>

namespace Specs {
  constexpr uint32_t MEMORY_SIZE = 4096;
  constexpr uint32_t ROM_OFFSET = 0x200;

  constexpr uint32_t NUMBER_OF_OPCODES = 35;
  constexpr uint32_t NUMBER_OF_REGISTERS = 16;
  constexpr uint32_t NUMBER_OF_KEYS = 16;

  constexpr uint32_t WINDOW_WIDTH = 64;
  constexpr uint32_t WINDOW_HEIGHT = 32;
}
