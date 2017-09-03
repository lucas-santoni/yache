#pragma once

#include <array>
#include <SFML/Graphics.hpp>

#include "Specs.hpp"

namespace Keypad {
  typedef struct {
    sf::Keyboard::Key k;
    uint32_t i;
  } key;

  constexpr std::array<key, Specs::NUMBER_OF_KEYS> keys = {{
    {sf::Keyboard::Numpad0, 0x0},
    {sf::Keyboard::Numpad1, 0x1},
    {sf::Keyboard::Numpad2, 0x2},
    {sf::Keyboard::Numpad3, 0x3},
    {sf::Keyboard::Numpad4, 0x4},
    {sf::Keyboard::Numpad5, 0x5},
    {sf::Keyboard::Numpad6, 0x6},
    {sf::Keyboard::Numpad7, 0x7},
    {sf::Keyboard::Numpad8, 0x8},
    {sf::Keyboard::Numpad9, 0x9},
    {sf::Keyboard::A, 0xa},
    {sf::Keyboard::B, 0xb},
    {sf::Keyboard::C, 0xc},
    {sf::Keyboard::D, 0xd},
    {sf::Keyboard::E, 0xe},
    {sf::Keyboard::F, 0xf}
  }};
}
