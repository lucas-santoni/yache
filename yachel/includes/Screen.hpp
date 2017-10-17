#pragma once

#include <cstdint>
#include <vector>

#define TIMEOUT (8)

// TODO: Fix bug in INVADERS
namespace Yachel {
  typedef struct {
    bool active = false;
    uint32_t timeout = 0;
  } PixelMeta;

  class Screen {
    public:
      explicit Screen(uint32_t w, uint32_t h);

    private:
      std::vector<bool> _screen;
      std::vector<PixelMeta> _meta;
      uint32_t _width;

    public:
      const std::vector<bool>& what(void) const;
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
