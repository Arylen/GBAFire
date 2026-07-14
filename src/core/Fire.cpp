#include "Fire.h"
#include "core/gfx.h"
#include <gba_types.h>
#include <gba_video.h>

u32 randomState = 0x82BD18ACu;

[[gnu::always_inline]]
inline u32 nextRandom() noexcept {
    randomState ^= randomState << 13;
    randomState ^= randomState >> 17;
    randomState ^= randomState << 5;
    return randomState;
}

const u8 PALETTE_SIZE = 32;
constexpr u16 PALETTE[] {
    RGB5( 0,  0,  0),
    RGB5( 3,  0,  0),
    RGB5( 6,  0,  0),
    RGB5( 9,  0,  0),
    RGB5(12,  0,  0),
    RGB5(16,  0,  0),
    RGB5(20,  0,  0),
    RGB5(24,  0,  0),
    RGB5(28,  0,  0),
    RGB5(31,  1,  0),
    RGB5(31,  3,  0),
    RGB5(31,  5,  0),
    RGB5(31,  7,  0),
    RGB5(31,  9,  0),
    RGB5(31, 11,  0),
    RGB5(31, 13,  0),
    RGB5(31, 15,  0),
    RGB5(31, 17,  0),
    RGB5(31, 19,  0),
    RGB5(31, 21,  0),
    RGB5(31, 23,  0),
    RGB5(31, 25,  0),
    RGB5(31, 27,  0),
    RGB5(31, 29,  0),
    RGB5(31, 31,  0),
    RGB5(31, 31,  3),
    RGB5(31, 31,  6),
    RGB5(31, 31, 10),
    RGB5(31, 31, 14),
    RGB5(31, 31, 19),
    RGB5(31, 31, 25),
    RGB5(31, 31, 31),
};

constexpr int MIRROR_COUNT = 4;
constexpr int WIDTH = SCREEN_WIDTH / MIRROR_COUNT;
constexpr int HEIGHT = SCREEN_HEIGHT / 2;
constexpr int Y_DRAW_OFFSET = SCREEN_HEIGHT - HEIGHT;

#define CELL_IDX(x, y) (((y) * WIDTH) + (x))

u8 cells_[WIDTH * HEIGHT];

void Fire::init() {
    // Fill bottom row with pure white cells
    for (int x = 0; x < WIDTH; ++x) {
        cells_[CELL_IDX(x, HEIGHT - 1)] = PALETTE_SIZE - 1;;
    }
}

void Fire::update() {
    for (int y = 1; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            u8 cellValue = cells_[CELL_IDX(x, y)];
            if (cellValue == 0) {
                cells_[CELL_IDX(x, y - 1)] = 0;
                continue;
            }

            const u32 rng = nextRandom();

            const u8 upAmount = rng & 1;
            const u32 directionRoll = (rng >> 1) & 3;

            int horizontalDir = 0;
            if (directionRoll < 2) {
                horizontalDir = 1;
            } else if (directionRoll == 2) {
                horizontalDir = -1;
            }

            int randCellX = x + horizontalDir;
            if (randCellX < 0 || randCellX >= WIDTH) {
                continue;
            }

            cells_[CELL_IDX(randCellX, y - 1)] = cellValue - upAmount;
        }
    }
}

void Fire::draw() {
    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            u8 cellValue = cells_[CELL_IDX(x, y)];
            for (int xRepeat = 0; xRepeat < MIRROR_COUNT; xRepeat++) {
                gfx::putPixel(x + (WIDTH * xRepeat), y + Y_DRAW_OFFSET, PALETTE[cellValue]);
            }
        }
    }
}
