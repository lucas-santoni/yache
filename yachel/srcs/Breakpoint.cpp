#include "Yachel.hpp"

// Build a breakpoint from address
// Eventually set default activity
Yachel::Breakpoint::Breakpoint(uint16_t addr, bool active) {
  _addr = addr;
  _active = active;
}

// Has this breakpoint been hit yet ?
uint32_t Yachel::Breakpoint::isHit(void) const {
  return _count;
}

// This breakpoint has been hit
void Yachel::Breakpoint::hit(void) {
  ++_count;
}

// Arm the breakpoint, now it can be hit on
void Yachel::Breakpoint::arm(void) {
  _active = true;
}

// Disarm the breakpoint, it can not be
// hit on anymore
void Yachel::Breakpoint::disarm(void) {
  _active = false;
}

// Can we hit on this breakpoint ?
bool Yachel::Breakpoint::armed(void) const {
  return _active;
}

// Toogle activity
void Yachel::Breakpoint::toogle(void) {
  if (armed())
    disarm();
  else
    arm();
}

// Reset breakpoint
void Yachel::Breakpoint::reset(void) {
  _count = 0;
  arm();
}

uint16_t Yachel::Breakpoint::isBreakingOn(void) const {
  return _addr;
}
