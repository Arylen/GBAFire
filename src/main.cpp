#include <gba.h>
#include <gba_interrupt.h>
#include <gba_systemcalls.h>
#include <stdio.h>

int main() {
    irqInit();
    irqEnable(IRQ_VBLANK);

    consoleDemoInit();
    iprintf("Meow!");

    while (true) {
        VBlankIntrWait();
    }
}
