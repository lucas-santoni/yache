#pragma once

#include <stdint.h>
#include <array>

#include "specs.h"

class Memory {
  private:
    std::array<uint8_t, Specs::RAM_SIZE> ram;

  public:
    void reset(void);
};
