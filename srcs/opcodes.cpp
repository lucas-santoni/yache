#include <cstdlib>

#include "Chip8.hpp"
#include "status.hpp"

// This opcode is generally not used
void Chip8::_op_0NNN(void) {
  return;
}

// Clear the screen
void Chip8::_op_00E0(void) {
  for (uint32_t i = 0; i < _screen.width(); ++i)
    for (uint32_t j = 0; j < _screen.height(); ++j)
      _screen.unsetPixel(i, j);
}

// Return from subroutine
// Pop address on top of stack onto pc
void Chip8::_op_00EE(void) {
  _pc = _stack.top();
  _stack.pop();
}

// Redirect execution flow
// Set pc to raw address
void Chip8::_op_1NNN(void) {
  _pc = _arguments.nnn;
}

// Call subroutine
// Push current pc on the stack
void Chip8::_op_2NNN(void) {
  if (_stack.size() < Specs::STACK_LIMIT) {
    _stack.push(_pc);
    _pc = _arguments.nnn;
  }
}

// Skip an instruction if a register
// equals value
// Next instruction is generally a jump
void Chip8::_op_3XNN(void) {
  if (_registers[_arguments.x] == _arguments.nn)
    _pc += 2;
}

// Same but if not equal
void Chip8::_op_4XNN(void) {
  if (_registers[_arguments.x] != _arguments.nn)
    _pc += 2;
}

// Same if register equals register
void Chip8::_op_5XY0(void) {
  if (_registers[_arguments.x] == _registers[_arguments.y])
    _pc += 2;
}

// Store value onto register
void Chip8::_op_6XNN(void) {
  _registers[_arguments.x] = _arguments.nn;
}

// Add value to register
void Chip8::_op_7XNN(void) {
  _registers[_arguments.x] += _arguments.nn;
}

// Register equals other register
void Chip8::_op_8XY0(void) {
  _registers[_arguments.x] = _registers[_arguments.y];
}

// Register OR register
void Chip8::_op_8XY1(void) {
  _registers[_arguments.x] |= _registers[_arguments.y];
}

// Register AND register
void Chip8::_op_8XY2(void) {
  _registers[_arguments.x] &= _registers[_arguments.y];
}

// Register XOR register
void Chip8::_op_8XY3(void) {
  _registers[_arguments.x] ^= _registers[_arguments.y];
}

// Addition
// Set register f if carry
void Chip8::_op_8XY4(void) {
  int32_t r = _registers[_arguments.x] + _registers[_arguments.y];

  _registers[0xf] = (r > 0xff);
  _registers[_arguments.x] += _registers[_arguments.y];
}

// Soustraction
void Chip8::_op_8XY5(void) {
  int32_t r = _registers[_arguments.x] - _registers[_arguments.y];

  _registers[0xf] = (r > 0x0);
  _registers[_arguments.x] -= _registers[_arguments.y];
}

// Get LSB
// Bit shift
void Chip8::_op_8XY6(void) {
  bool lsb = _registers[_arguments.y] & true;

  _registers[0xf] = lsb;
  _registers[_arguments.x] = _registers[_arguments.y] >> 0x1;
}

// Another soustraction
void Chip8::_op_8XY7(void) {
  int32_t r = _registers[_arguments.y] - _registers[_arguments.x];

  _registers[0xf] = (r > 0x0);
  _registers[_arguments.x] = _registers[_arguments.y] - _registers[_arguments.x];
}

// Get MSB
// Bit shift
void Chip8::_op_8XYE(void) {
  bool msb = (_registers[_arguments.y] & 0x80) != false;

  _registers[0xf] = msb;
  _registers[_arguments.x] = _registers[_arguments.y] << 1;

}

// If registers differ
// Skip next instructions
void Chip8::_op_9XY0(void) {
  if (_registers[_arguments.x] != _registers[_arguments.y])
    _pc += 2;
}

// Hard set index
void Chip8::_op_ANNN(void) {
  _index = _arguments.nnn;
}

// Hard set pc
void Chip8::_op_BNNN(void) {
  _pc = _registers[0] + _arguments.nnn;
}

// Random
void Chip8::_op_CXNN(void) {
  uint8_t r = rand() % 0xff;

  _registers[_arguments.x] = r & _arguments.nn;
}

// Drawing
// Update screen via xor (toggle) method
void Chip8::_op_DXYN(void) {
  uint16_t x = _registers[_arguments.x];
  uint16_t y = _registers[_arguments.y];

  _registers[0xf] = false;
  for (auto h = 0; h < _arguments.n; ++h) {
    uint16_t pixel = _memory[_index + h];
    for (auto w = 0; w < 8; ++w) {
      if ((pixel & (0x80 >> w)) != 0) {
        if (_screen.isPixelSet(x + w, y + h))
          _registers[0xf] = true;
        _screen.toogle(x + w, y + h);
      }
    }
  }

  _screen.setRedraw(true);
}

// If a key at register x is pressed,
// skip next instruction
void Chip8::_op_EX9E(void) {
  uint8_t k = _registers[_arguments.x];

  if (getKeys()[k])
    _pc += 2;
}

// If key at register x is not pressed,
// skip next instruction
void Chip8::_op_EXA1(void) {
  uint8_t k = _registers[_arguments.x];

  if (getKeys()[k])
    _pc += 2;
}

// Set register from delay timer
void Chip8::_op_FX07(void) {
  _registers[_arguments.x] = _delayTimer;
}

// Wait for a keypress (blocking)
// and store result in register x
void Chip8::_op_FX0A(void) {
  if (!_screen.isAKeyPressed())
    _pc -= 2;
  else
    _registers[_arguments.x] = _screen.getKeyPressed();
}

// Set delay timer
void Chip8::_op_FX15(void) {
  _delayTimer = _registers[_arguments.x];
}

// Set sound timer
void Chip8::_op_FX18(void) {
  _soundTimer = _registers[_arguments.x];
}

// Add something to index
void Chip8::_op_FX1E(void) {
  _index += _registers[_arguments.x];
}

// Hard set index
void Chip8::_op_FX29(void) {
  _index = (_registers[_arguments.x]) * 0x5;
}

// Spread byte in memory
void Chip8::_op_FX33(void) {
  _memory[_index] = _registers[_arguments.x] / 100;
  _memory[_index + 1] = (_registers[_arguments.x] / 10) % 10;
  _memory[_index + 2] = _registers[_arguments.x] % 10;
}

// Set portion of memories from register
void Chip8::_op_FX55(void) {
  for (auto i = 0; i <= _arguments.x; ++i)
    _memory[_index + i] = _registers[i];

  _index += _arguments.x + 1;
}

// Set registers from a portion of memory
void Chip8::_op_FX65(void) {
  for (auto i = 0; i <= _arguments.x; ++i)
    _registers[i] = _memory[_index + i];

  _index += _arguments.x + 1;
}
