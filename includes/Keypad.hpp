#pragma once

#include <cstdint>
#include <array>

#include "Specs.h"

class Keypad {
  private:
    std::array<uint8_t, Specs::KEY_NUMBERS> keyStates;

  public:
    explicit Keypad(void);

  public:
    void reset(void);
};
