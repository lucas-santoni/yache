#pragma once

#include <cstdint>
#include <vector>

#include "Specs.hpp"
#include "PixelMeta.hpp"

// This class is a container for a vector of booleans
// This vector represents a screen
// This screen is flickering-proof using a timeout system
// Because of the way it is built, the Chip8 flickers and this class
// can fix that
namespace Yachel {
  class Screen {
    public:
      explicit Screen(uint32_t w, uint32_t h,
          uint32_t timeout=Yachel::Specs::DEFAULT_TIMEOUT);

    private:
      std::vector<bool> _screen;
      std::vector<PixelMeta> _meta;

    private:
      uint32_t _width;
      uint32_t _timeout;

    public:
      const std::vector<bool>& what(void) const;
      void setTimeout(uint32_t timeout);

    public:
      bool isPixelSet(uint32_t w, uint32_t h) const;
      bool isPixelSet(uint32_t i) const;
      void setPixel(uint32_t w, uint32_t h);
      void setPixel(uint32_t i);
      void unsetPixel(uint32_t w, uint32_t h);
      void unsetPixel(uint32_t i);
      void tooglePixel(uint32_t w, uint32_t h);
      void tooglePixel(uint32_t i);

    public:
      void handleMeta(void);
  };
}
