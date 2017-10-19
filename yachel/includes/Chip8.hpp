#pragma once

#include <string>
#include <array>
#include <stack>

#include "Status.hpp"
#include "Specs.hpp"
#include "Opcode.hpp"
#include "OpcodeArguments.hpp"
#include "Screen.hpp"

// A chip8 device
namespace Yachel {
  class Chip8 {
    friend class Debugger;

    public:
      explicit Chip8(void);

    public:
      void load(const std::string& romPath);
      void setClock(uint32_t customClock,
          uint32_t customFps = Yachel::Specs::DEFAULT_FPS);
      void setTimeout(uint32_t timeout);
      void cycle(void);
      void tick(void);
      void pause(void);
      bool paused(void) const;
      void resume(void);
      const std::vector<bool>& getScreen(void) const;
      bool shouldRedraw(void) const;
      void keyPressed(uint8_t id);
      void keyReleased(uint8_t id);

    private:
      constexpr void _loadFontset(void);
      void _updateOpcodeArguments(void);

    private:
      bool _redraw = false;
      bool _paused = false;
      uint32_t _clock = Yachel::Specs::DEFAULT_RATE /
        Yachel::Specs::DEFAULT_FPS;
      Screen _vram;

    private:
      std::array<uint8_t, Specs::MEMORY_SIZE> _ram = {};
      std::array<uint8_t, Specs::NUMBER_OF_REGISTERS> _registers = {};
      std::array<bool, Specs::NUMBER_OF_KEYS> _keys = {};
      std::stack<uint16_t> _stack;

    private:
      uint16_t _index = 0x000;
      uint16_t _pc = Specs::ROM_OFFSET;
      uint16_t _currentOpcode = 0x0000;
      OpcodeArguments _arguments = {};

    private:
      uint8_t _delayTimer = 0x000;
      uint8_t _soundTimer = 0x000;
      int32_t _keyPressed = Yachel::FAILURE;

    private:
      void _op_0NNN(void);
      void _op_00E0(void);
      void _op_00EE(void);
      void _op_1NNN(void);
      void _op_2NNN(void);
      void _op_3XNN(void);
      void _op_4XNN(void);
      void _op_5XY0(void);
      void _op_6XNN(void);
      void _op_7XNN(void);
      void _op_8XY0(void);
      void _op_8XY1(void);
      void _op_8XY2(void);
      void _op_8XY3(void);
      void _op_8XY4(void);
      void _op_8XY5(void);
      void _op_8XY6(void);
      void _op_8XY7(void);
      void _op_8XYE(void);
      void _op_9XY0(void);
      void _op_ANNN(void);
      void _op_BNNN(void);
      void _op_CXNN(void);
      void _op_DXYN(void);
      void _op_EX9E(void);
      void _op_EXA1(void);
      void _op_FX07(void);
      void _op_FX0A(void);
      void _op_FX15(void);
      void _op_FX18(void);
      void _op_FX1E(void);
      void _op_FX29(void);
      void _op_FX33(void);
      void _op_FX55(void);
      void _op_FX65(void);

    private:
      std::array<Opcode, Specs::NUMBER_OF_OPCODES> _opcodes = {{
        {0x0000, 0x0FFF, &Chip8::_op_0NNN}, /* 0NNN */
          {0xFFFF, 0x00E0, &Chip8::_op_00E0}, /* 00E0 */
          {0xFFFF, 0x00EE, &Chip8::_op_00EE}, /* 00EE */
          {0xF000, 0x1000, &Chip8::_op_1NNN}, /* 1NNN */
          {0xF000, 0x2000, &Chip8::_op_2NNN}, /* 2NNN */
          {0xF000, 0x3000, &Chip8::_op_3XNN}, /* 3XNN */
          {0xF000, 0x4000, &Chip8::_op_4XNN}, /* 4XNN */
          {0xF00F, 0x5000, &Chip8::_op_5XY0}, /* 5XY0 */
          {0xF000, 0x6000, &Chip8::_op_6XNN}, /* 6XNN */
          {0xF000, 0x7000, &Chip8::_op_7XNN}, /* 7XNN */
          {0xF00F, 0x8000, &Chip8::_op_8XY0}, /* 8XY0 */
          {0xF00F, 0x8001, &Chip8::_op_8XY1}, /* 8XY1 */
          {0xF00F, 0x8002, &Chip8::_op_8XY2}, /* 8XY2 */
          {0xF00F, 0x8003, &Chip8::_op_8XY3}, /* BXY3 */
          {0xF00F, 0x8004, &Chip8::_op_8XY4}, /* 8XY4 */
          {0xF00F, 0x8005, &Chip8::_op_8XY5}, /* 8XY5 */
          {0xF00F, 0x8006, &Chip8::_op_8XY6}, /* 8XY6 */
          {0xF00F, 0x8007, &Chip8::_op_8XY7}, /* 8XY7 */
          {0xF00F, 0x800E, &Chip8::_op_8XYE}, /* 8XYE */
          {0xF00F, 0x9000, &Chip8::_op_9XY0}, /* 9XY0 */
          {0xF000, 0xA000, &Chip8::_op_ANNN}, /* ANNN */
          {0xF000, 0xB000, &Chip8::_op_BNNN}, /* BNNN */
          {0xF000, 0xC000, &Chip8::_op_CXNN}, /* CXNN */
          {0xF000, 0xD000, &Chip8::_op_DXYN}, /* DXYN */
          {0xF0FF, 0xE09E, &Chip8::_op_EX9E}, /* EX9E */
          {0xF0FF, 0xE0A1, &Chip8::_op_EXA1}, /* EXA1 */
          {0xF0FF, 0xF007, &Chip8::_op_FX07}, /* FX07 */
          {0xF0FF, 0xF00A, &Chip8::_op_FX0A}, /* FX0A */
          {0xF0FF, 0xF015, &Chip8::_op_FX15}, /* FX15 */
          {0xF0FF, 0xF018, &Chip8::_op_FX18}, /* FX18 */
          {0xF0FF, 0xF01E, &Chip8::_op_FX1E}, /* FX1E */
          {0xF0FF, 0xF029, &Chip8::_op_FX29}, /* FX29 */
          {0xF0FF, 0xF033, &Chip8::_op_FX33}, /* FX33 */
          {0xF0FF, 0xF055, &Chip8::_op_FX55}, /* FX55 */
          {0xF0FF, 0xF065, &Chip8::_op_FX65}, /* FX65 */
      }};
  };
}
