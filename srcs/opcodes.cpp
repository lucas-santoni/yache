#include <stdlib.h>

#include "Chip8.hpp"
#include "status.hpp"

// This opcode is generally not used
void Chip8::_op_0NNN(void) {
  return;
}

// Clear the screen
void Chip8::_op_00E0(void) {
  for (uint32_t i = 0; i < _vmemory.width(); ++i)
    for (uint32_t j = 0; j < _vmemory.height(); ++j)
      _vmemory.unsetPixel(i, j);
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
  _pc = _nnn;
}

// Call subroutine
// Push current pc on the stack
void Chip8::_op_2NNN(void) {
  if (_stack.size() < Specs::STACK_LIMIT) {
    _stack.push(_pc);
    _pc = _nnn;
  }
}

// Skip an instruction if a register
// equals value
// Next instruction is generally a jump
void Chip8::_op_3XNN(void) {
  if (_registers[_x] == _nn)
    _pc += 2;
}

// Same but if not equal
void Chip8::_op_4XNN(void) {
  if (_registers[_x] != _nn)
    _pc += 2;
}

// Same if register equals register
void Chip8::_op_5XY0(void) {
  if (_registers[_x] == _registers[_y])
    _pc += 2;
}

// Store value onto register
void Chip8::_op_6XNN(void) {
  _registers[_x] = _nn;
}

// Add value to register
void Chip8::_op_7XNN(void) {
  _registers[_x] += _nn;
}

// Register equals other register
void Chip8::_op_8XY0(void) {
  _registers[_x] = _registers[_y];
}

// Register OR register
void Chip8::_op_8XY1(void) {
  _registers[_x] |= _registers[_y];
}

// Register AND register
void Chip8::_op_8XY2(void) {
  _registers[_x] &= _registers[_y];
}

// Register XOR register
void Chip8::_op_8XY3(void) {
  _registers[_x] ^= _registers[_y];
}

// Addition
// Set register f if carry
void Chip8::_op_8XY4(void) {
  int32_t r = _registers[_x] + _registers[_y];

  _registers[0xf] = (r > 0xff);
  _registers[_x] += _registers[_y];

}

// Soustraction
void Chip8::_op_8XY5(void) {
  int32_t r = _registers[_x] - _registers[_y];

  _registers[0xf] = (r > 0x0);
  _registers[_x] -= _registers[_y];
}

// Get LSB
// Bit shift
// TODO: Not sure
void Chip8::_op_8XY6(void) {
  bool lsb = _registers[_y] & true;

  _registers[0xf] = lsb;
  _registers[_x] = _registers[_y] >> 0x1;
}

// Another soustraction
void Chip8::_op_8XY7(void) {
  int32_t r = _registers[_y] - _registers[_x];

  _registers[0xf] = (r > 0x0);
  _registers[_x] = _registers[_y] - _registers[_x];
}

// Get MSB
// Bit shift
// TODO: Not sure
void Chip8::_op_8XYE(void) {
  bool msb = (_registers[_y] & 0x80) != false;

  _registers[0xf] = msb;
  _registers[_x] = _registers[_y] << 1;

}

// If registers differ
// Skip next instructions
void Chip8::_op_9XY0(void) {
  if (_registers[_x] != _registers[_y])
    _pc += 2;
}

// Hard set index
void Chip8::_op_ANNN(void) {
  _index = _nnn;
}

// Hard set pc
void Chip8::_op_BNNN(void) {
  _pc = _registers[0] + _nnn;
}

// Random
void Chip8::_op_CXNN(void) {
  uint8_t r = rand() % 0xff;

  _registers[_x] = r & _nn;
}

// Drawing
// Update screen via xor (toggle) method
void Chip8::_op_DXYN(void) {
  uint16_t x = _registers[_x];
  uint16_t y = _registers[_y];

  _registers[0xf] = false;
  for (auto h = 0; h < _n; ++h) {
    uint16_t pixel = _memory[_index + h];
    for (auto w = 0; w < 8; ++w) {
      if ((pixel & (0x80 >> w)) != 0) {
        if (_vmemory.isSet(x + w, y + h))
          _registers[0xf] = true;
        _vmemory.toogle(x + w, y + h);
      }
    }
  }

  _redraw = true;
}

// If a key at register x is pressed,
// skip next instruction
void Chip8::_op_EX9E(void) {
  uint8_t k = _registers[_x];

  if (_keys[k])
    _pc += 2;
}

// If key at register x is not pressed,
// skip next instruction
void Chip8::_op_EXA1(void) {
  uint8_t k = _registers[_x];

  if (!_keys[k])
    _pc += 2;
}

// Set register from delay timer
void Chip8::_op_FX07(void) {
  _registers[_x] = _delayTimer;
}

void Chip8::_op_FX0A(void) {
  printf("Not implemented.\n");
  exit(SUCCESS);
}

// Set delay timer
void Chip8::_op_FX15(void) {
  _delayTimer = _registers[_x];
}

// Set sound timer
void Chip8::_op_FX18(void) {
  _soundTimer = _registers[_x];
}

// Add something to index
void Chip8::_op_FX1E(void) {
  _index += _registers[_x];
}

// Hard set index
void Chip8::_op_FX29(void) {
  _index = _registers[_x] * 0x5;
}

// Spread byte in memory
void Chip8::_op_FX33(void) {
  _memory[_index] = _registers[_x] / 100;
  _memory[_index + 1] = (_registers[_x] / 10) % 10;
  _memory[_index + 2] = _registers[_x] % 10;
}

// Set portion of memories from register
void Chip8::_op_FX55(void) {
  for (auto i = 0; i <= _x; ++i)
    _memory[_index + i] = _registers[i];

  _index += _x + 1;
}

// Set registers from a portion of memory
void Chip8::_op_FX65(void) {
  for (auto i = 0; i <= _x; ++i)
    _registers[i] = _memory[_index];

  _index += _x + 1;
}
