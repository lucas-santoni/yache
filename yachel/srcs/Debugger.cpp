#include "Yachel.hpp"

// Attach debugger to running
Yachel::Debugger::Debugger(Chip8& debugged) :
  _debugged(debugged) {}

void Yachel::Debugger::update(void) {
  for (auto& b : _breakpoints) {
    if (b.isBreakingOn() == _debugged._pc) {
      b.hit();
      _debugged.pause();
    }
  }
}

std::array<uint8_t, Yachel::Specs::NUMBER_OF_REGISTERS>&
Yachel::Debugger::registers(void) const {
  return _debugged._registers;
}

uint16_t Yachel::Debugger::pc(void) const {
  return _debugged._pc;
}

void Yachel::Debugger::breakOn(uint16_t addr, bool active) {
  _breakpoints.push_back(Breakpoint(addr, active));
}
