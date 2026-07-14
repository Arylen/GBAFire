#include <gba.h>
#include <gba_interrupt.h>
#include <gba_systemcalls.h>
#include <gba_video.h>

#include "core/Fire.h"

int main() {
    irqInit();
    irqEnable(IRQ_VBLANK);

    REG_DISPCNT = MODE_3 | BG2_ON;

    Fire fire {};

    fire.init();

    while (true) {
        fire.update();
        fire.draw();
        VBlankIntrWait();
    }
}
