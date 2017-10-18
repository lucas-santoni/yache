#pragma once

#include <cstdint>

// Pixel metadatas
namespace Yachel {
  typedef struct {
    bool active = false;
    uint32_t timeout = 0;
  } PixelMeta;
}
