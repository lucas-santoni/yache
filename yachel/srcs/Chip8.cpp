#include <fstream>

#include "../includes/Chip8.hpp"

// Basic constructor
Yachel::Chip8::Chip8(void) :
  _vram(Specs::WINDOW_WIDTH, Specs::WINDOW_HEIGHT) {
  _loadFontset();
}

// Load a ROM into emulator
// TODO: Better error handling
void Yachel::Chip8::load(const std::string& romPath) {
  std::ifstream rom;

  rom.open(romPath, std::ios::binary);
  if (!rom.good())
    return;

  rom.read(reinterpret_cast<char *>(_ram.data() +
        Specs::ROM_OFFSET), Specs::MEMORY_SIZE);
  rom.close();
}

// Get a custom clock rate
// Default is 500
void Yachel::Chip8::setClock(uint32_t customRate, uint32_t customFps) {
  _clock = customRate / customFps;
}

// Change timeout of underlying Screen
void Yachel::Chip8::setTimeout(uint32_t timeout) {
  _vram.setTimeout(timeout);
}

// A CPU cycle
// Fetch opcode
// Get all potential arguments
// If opcode is known, run the code
// Update timers
// Does not do anything if paused
// TODO: Cleaner error handling
void Yachel::Chip8::cycle(void) {
  if (paused())
    return;

  _vram.handleMeta();

  _currentOpcode = _ram[_pc] << 8 | _ram[_pc + 1];
  _updateOpcodeArguments();
  _pc += 2;

  for (auto& op : _opcodes)
    if ((_currentOpcode & op.mask) == op.key) {
      op.f(this);
      break;
    }
}

// Cycle for _clock times
// _clock is the number of opcodes to be executed
// in one frame
// This number is calculated based on the desired rate for the emulator,
// divided by the number of FPS the screen will be displayed at
// _redraw is false at beginning of tick and my be set to true by any
// of the cycles
void Yachel::Chip8::tick(void) {
  _redraw = false;

  for (uint32_t i = 0; i < _clock ; ++i)
    cycle();

  if (_delayTimer > 0)
    --_delayTimer;
  if (_soundTimer > 0)
    --_soundTimer;

  _keyPressed = Yachel::FAILURE;
}

// Pause emulation
// Cycles does nothing during the pause
// _pc is not incremented
void Yachel::Chip8::pause(void) {
  _paused = true;
}

// Resume emulation
void Yachel::Chip8::resume(void) {
  _paused = false;
}

// Is the emulation paused ?
bool Yachel::Chip8::paused(void) const {
  return _paused;
}

// Get screen state
const std::vector<bool>&
  Yachel::Chip8::getScreen(void) const {
    return _vram.what();
}

// Has the vram changed ?
bool Yachel::Chip8::shouldRedraw(void) const {
  return _redraw;
}

// Recieve a key pressed event
// Keep an eye on the first pressed key
// in case there is more than one per tick
// TODO: Error handling
void Yachel::Chip8::keyPressed(uint8_t id) {
  _keys[id] = true;

  if (_keyPressed == Yachel::FAILURE)
    _keyPressed = id;
}

// Recieve a key released event
// TODO: Error handling
void Yachel::Chip8::keyReleased(uint8_t id) {
  _keys[id] = false;
}

// Put the font bytes at the right place in memory
constexpr void Yachel::Chip8::_loadFontset(void) {
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
    _ram[i] = fontSet[i];
}

// Get all the potential arguments
// for current opcode
void Yachel::Chip8::_updateOpcodeArguments(void) {
  _arguments.x = (_currentOpcode & 0x0F00) >> 8;
  _arguments.y = (_currentOpcode & 0x00F0) >> 4;
  _arguments.n = _currentOpcode & 0x000F;
  _arguments.nn = _currentOpcode & 0x00FF;
  _arguments.nnn = _currentOpcode & 0x0FFF;
}
