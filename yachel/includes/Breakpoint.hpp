#pragma once

#include <cstdint>

// This class represents a breakpoint
// A breakpoint can be armed and/or hit
// A breakpoint breaks on a specific pc
// We store the number of times a breakpoint has been it
// since room execution
namespace Yachel {
  class Breakpoint {
    public:
      explicit Breakpoint(uint16_t addr, bool active = false);

    public:
      uint32_t isHit(void) const;
      void hit(void);
      void arm(void);
      void disarm(void);
      void rearm(void);
      bool armed(void) const;
      void toogle(void);
      void breakOn(uint16_t addr);
      void reset(void);
      uint16_t isBreakingOn(void) const;

    private:
      bool _active = false;
      uint16_t _addr = 0x0000;
      uint32_t _count = false;
  };
}
