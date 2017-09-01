#pragma once

#include <cstdint>
#include <functional>

class Chip8;

typedef struct {
  uint16_t mask;
  uint16_t key;
  std::function<void(Chip8 *)> f;
} opcode;

