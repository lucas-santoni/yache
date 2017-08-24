#pragma once

#include <cstdint>
#include <array>

#include "Specs.h"

class Cpu {
  private:
    std::array<uint8_t, Specs::GENERAL_REGISTERS_NUMBER> generalRegisters;
    std::array<uint16_t, Specs::CALL_STACK_LIMIT> callStack;
    uint8_t carry;
    uint16_t index;
    uint16_t pc;
    uint16_t sp;

  public:
    explicit Cpu(void);

  public:
    void reset(void);
};
