#include "Yachel.hpp"

// Attach debugger to running
// We do not do anything to verify the lifetime
// of the chip8 object
// It this object dies before the debugger, the program
// will most likely crash
// TODO: fix this ?
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

// Dump the memory
std::array<uint8_t, Yachel::Specs::MEMORY_SIZE>&
Yachel::Debugger::ram(void) const {
  return _debugged._ram;
}

// Get the current registers state
std::array<uint8_t, Yachel::Specs::NUMBER_OF_REGISTERS>&

Yachel::Debugger::registers(void) const {
  return _debugged._registers;
}

// Get the current key states
std::array<bool, Yachel::Specs::NUMBER_OF_KEYS>&
Yachel::Debugger::keys(void) const {
  return _debugged._keys;
}

// Get the current stack
std::stack<uint16_t>& Yachel::Debugger::callStack(void) const {
  return _debugged._stack;
}

// Get the current index
uint16_t Yachel::Debugger::index(void) const {
  return _debugged._index;
}

// Get the current program counter
uint16_t Yachel::Debugger::pc(void) const {
  return _debugged._pc;
}

// Add a new breakpoint
void Yachel::Debugger::breakOn(uint16_t addr, bool active) {
  _breakpoints.push_back(Breakpoint(addr, active));
}

// One cycle and debugger refresh
void Yachel::Debugger::step(void) {
  update();
  _debugged.resume();
  _debugged.cycle();
  _debugged.pause();
}
