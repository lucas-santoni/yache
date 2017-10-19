#pragma once

#include "Chip8.hpp"
#include "Breakpoint.hpp"

namespace Yachel {
  class Debugger {
    public:
      explicit Debugger(Chip8& debugged);

    public:
      void update(void);
      std::array<uint8_t, Yachel::Specs::NUMBER_OF_REGISTERS>&
        registers(void) const;
      uint16_t pc(void) const;
      void breakOn(uint16_t addr, bool active = false);

    private:
      Chip8& _debugged;
      std::vector<Breakpoint> _breakpoints;
  };
}
