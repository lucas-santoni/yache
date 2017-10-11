#pragma once

#include <cstdint>
#include <functional>

namespace Yachel {
  class Chip8;
}

// Strucutre representing a chip8 opcode
// If current opcode & mask == key
// Then we can call function
typedef struct {
  uint16_t mask;
  uint16_t key;
  std::function<void(Yachel::Chip8 *)> f;
} Opcode;

