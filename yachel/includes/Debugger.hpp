#pragma once

#include "Chip8.hpp"
#include "Breakpoint.hpp"

// This class represents a debugger
// The debugger is "attached" to a running chip8
// As it is a friend of the chip8, it can directly expose
// its private stuff
//
// Logic:
// Chip8 runs in infinite loop, can be paused/resumed or whatever
// Breakpoints can also be added at anytime, as long as the debugger
// is attached
// The debugger has to be refreshed in the loop too so that it can catch
// any breakpoints
// When a breakpoint is catched, the chip8 is paused
// Execution can continue using steps, debugger is automatically refreshed
// there
// When done, execution can be resumed
namespace Yachel {
  class Debugger {
    public:
      explicit Debugger(Chip8& debugged);

    public:
      void update(void);
      std::array<uint8_t, Yachel::Specs::NUMBER_OF_REGISTERS>&
        registers(void) const;
      std::array<uint8_t, Yachel::Specs::MEMORY_SIZE>&
        ram(void) const;
      std::array<bool, Yachel::Specs::NUMBER_OF_KEYS>&
        keys(void) const;
      std::stack<uint16_t>& callStack(void) const;
      uint16_t index(void) const;
      uint16_t pc(void) const;
      void breakOn(uint16_t addr, bool active = false);
      void step(void);

    private:
      Chip8& _debugged;
      std::vector<Breakpoint> _breakpoints;
  };
}
