#pragma once

#include <stdint.h>
#include <array>

#include "specs.h"

class Keypad {
  private:
    std::array<uint8_t, Specs::KEY_NUMBERS> keyStates;

  public:
    void reset(void);
};
