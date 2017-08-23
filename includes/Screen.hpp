#pragma once

#include <stdint.h>
#include <array>

#include "specs.h"

class Screen {
  private:
    std::array<uint8_t, Specs::VRAM_SIZE> vram;

  public:
    void reset(void);
};
