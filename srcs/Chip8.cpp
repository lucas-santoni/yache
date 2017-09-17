#include <fstream>

#include "Chip8.hpp"
#include "Screen.hpp"
#include "status.hpp"
#include "colors.hpp"

// Clear memory
// Get an SFML window
// Load the fonset
// Link sprite and texture
// Scale the whole
Chip8::Chip8(void) :
  _screen() {
  _loadFontset();
}

// Put the font bytes at the right place in memory
constexpr void Chip8::_loadFontset(void) {
  constexpr std::array<uint8_t, Specs::FONTSET_SIZE> fontSet = {{
    0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
    0x20, 0x60, 0x20, 0x20, 0x70, // 1
    0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
    0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
    0x90, 0x90, 0xF0, 0x10, 0x10, // 4
    0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
    0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
    0xF0, 0x10, 0x20, 0x40, 0x40, // 7
    0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
    0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
    0xF0, 0x90, 0xF0, 0x90, 0x90, // A
    0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
    0xF0, 0x80, 0x80, 0x80, 0xF0, // C
    0xE0, 0x90, 0x90, 0x90, 0xE0, // D
    0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
    0xF0, 0x80, 0xF0, 0x80, 0x80  // F
  }};

  for (uint32_t i = 0; i < fontSet.size(); ++i)
    _memory[i] = fontSet[i];
}

// Map the ROM in memory
// This function is really cpp overkill
// Plain C would be much clearer
// TODO: Error handling
void Chip8::loadRomFromFile(const std::string& filePath) {
  std::ifstream rom;

  rom.open(filePath, std::ios::binary);
  if (!rom.good())
    return;

  rom.read(reinterpret_cast<char *>(_memory.data() + Specs::ROM_OFFSET),
      Specs::MEMORY_SIZE);
  rom.close();
}

// Get a reference to the keys
const std::array<bool, Specs::NUMBER_OF_KEYS>& Chip8::getKeys(void) const {
  return _screen.getKeys();
}

// Get all the potential opcodes
// arguments
void Chip8::_updateOpcodeArguments(void) {
  _arguments.x = (_currentOpcode & 0x0F00) >> 8;
  _arguments.y = (_currentOpcode & 0x00F0) >> 4;
  _arguments.n = _currentOpcode & 0x000F;
  _arguments.nn = _currentOpcode & 0x00FF;
  _arguments.nnn = _currentOpcode & 0x0FFF;
}

// A CPU cycle
// Fetch opcode
// If known, run the code
// TODO: Cleaner error handling
void Chip8::cycle(void) {
  _screen.cycle();

  _currentOpcode = _memory[_pc] << 8 | _memory[_pc + 1];
  _updateOpcodeArguments();
  _pc += 2;

  for (auto& op : _opcodes)
    if ((_currentOpcode & op.mask) == op.key) {
      op.f(this);
      break;
    }

  if (_delayTimer > 0)
    --_delayTimer;
  if (_soundTimer > 0)
    --_soundTimer;
}
