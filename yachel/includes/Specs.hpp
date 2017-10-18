#pragma once

#include <cstdint>

// Chip8 specs
namespace Yachel {
  namespace Specs {
    constexpr uint32_t MEMORY_SIZE = 4096;
    constexpr uint32_t ROM_OFFSET = 0x200;

    constexpr uint32_t NUMBER_OF_OPCODES = 35;
    constexpr uint32_t NUMBER_OF_REGISTERS = 16;
    constexpr uint32_t NUMBER_OF_KEYS = 16;

    constexpr uint32_t WINDOW_WIDTH = 64;
    constexpr uint32_t WINDOW_HEIGHT = 32;
    constexpr uint32_t WINDOW_SIZE = WINDOW_WIDTH * WINDOW_HEIGHT;

    constexpr uint32_t FONTSET_SIZE = 80;
    constexpr uint32_t STACK_LIMIT = 16;

    constexpr uint32_t DEFAULT_RATE = 500;
    constexpr uint32_t DEFAULT_FPS = 60;
    constexpr uint32_t DEFAULT_TIMEOUT = 8;
  }
}
