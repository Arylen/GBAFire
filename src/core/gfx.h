#pragma once

#include <gba_video.h>

namespace gfx {
    [[gnu::always_inline]]
    inline void putPixel(int x, int y, u16 color) noexcept {
        ((volatile u16*)VRAM)[y * SCREEN_WIDTH + x] = color;
    }

    [[gnu::always_inline]]
    inline void fillScreen(u16 color) noexcept {
        for (int y = 0; y < SCREEN_HEIGHT; ++y) {
            for (int x = 0; x < SCREEN_WIDTH; ++x) {
                putPixel(x, y, color);
            }
        }
    }
}
