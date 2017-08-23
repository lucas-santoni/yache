#pragma once

#include <stdint.h>

namespace Specs {
  constexpr uint32_t RAM_SIZE = 4096;
  constexpr uint32_t VRAM_SIZE = 64 * 32;

  constexpr uint32_t GENERAL_REGISTERS_NUMBER = 15;
  constexpr uint32_t KEY_NUMBERS = 16;
  constexpr uint32_t CALL_STACK_LIMIT = 16;
}
