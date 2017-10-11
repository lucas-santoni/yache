#include "HexKeypad.hpp"
#include "Status.hpp"

// Check if the pressed key is interesting for us
int32_t HexKeypad::getKeyId(const sf::Keyboard::Key& k) const {
  static constexpr std::array<Key, Yachel::Specs::NUMBER_OF_KEYS> _keys = {{
    {sf::Keyboard::Num1, 0x1},
    {sf::Keyboard::Num2, 0x2},
    {sf::Keyboard::Num3, 0x3},
    {sf::Keyboard::Num4, 0xc},
    {sf::Keyboard::A, 0x4},
    {sf::Keyboard::Z, 0x5},
    {sf::Keyboard::E, 0x6},
    {sf::Keyboard::R, 0xd},
    {sf::Keyboard::Q, 0x7},
    {sf::Keyboard::S, 0x8},
    {sf::Keyboard::D, 0x9},
    {sf::Keyboard::F, 0xe},
    {sf::Keyboard::W, 0xa},
    {sf::Keyboard::X, 0x0},
    {sf::Keyboard::C, 0xb},
    {sf::Keyboard::V, 0xf}
  }};

  // Return id if key is interesting
  // id can then be passed to chip8
  for (const auto& key : _keys) {
    if (key.k == k) {
      return key.id;
    }
  }

  // If not, return -1
  return FAILURE;
}
