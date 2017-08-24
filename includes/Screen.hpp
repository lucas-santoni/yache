#pragma once

#include <cstdint>
#include <array>

#include "Specs.h"

class Screen {
  private:
    std::array<uint8_t, Specs::VRAM_SIZE> vram;

  public:
    explicit Screen(void);

  public:
    void reset(void);
};
