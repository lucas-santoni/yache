#pragma once

#include <cstdint>
#include <array>

#include "Specs.h"

class Memory {
  private:
    uint8_t ram[Specs::RAM_SIZE] = {0};

  public:
    void reset(void);
    void dump(uint32_t from, uint32_t to) const;
    char *getCharRamPointer(void) const;
};
