#pragma once

#include <cstdint>

// This structure holds all the potential
// opcode arguments
typedef struct {
  uint8_t x;
  uint8_t y;
  uint8_t n;
  uint8_t nn;
  uint16_t nnn;
} OpcodeArguments;
