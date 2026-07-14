#include "Fire.h"
#include "core/gfx.h"
#include <gba_types.h>
#include <gba_video.h>

const int WIDTH = SCREEN_WIDTH - 10;
const int HEIGHT = SCREEN_HEIGHT - 20;

#define CELL_IDX(x, y) (((y) * WIDTH) + (x))

u8 cells_[WIDTH * HEIGHT];

const u8 PALETTE_SIZE = 8;
constexpr u16 PALETTE[] {
    RGB5( 0,  0,  0),
    RGB5( 8,  0,  0),
    RGB5(16,  0,  0),
    RGB5(24,  1,  0),
    RGB5(31,  6,  0),
    RGB5(31, 15,  0),
    RGB5(31, 27,  2),
    RGB5(31, 31, 31),
};

void Fire::init() {
    // Fill bottom row with pure white cells
    for (int x = 0; x < WIDTH; ++x) {
        cells_[CELL_IDX(x, HEIGHT - 1)] = PALETTE_SIZE - 1;;
    }
}

void Fire::update() {
    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            u8 cellValue = cells_[CELL_IDX(x, y)];
            // if (cellValue > 0)
        }
    }
}

void Fire::draw() {
    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            u8 cellValue = cells_[CELL_IDX(x, y)];
            gfx::putPixel(x, y, PALETTE[cellValue]);
        }
    }
}
