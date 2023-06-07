#include "types.h"
#include "hid/drawhid.h"
#include "i2c.h"
#include "draw.h"
#include "timer.h"

static inline void poweroff() {
	i2cWriteRegister(I2C_DEV_MCU, 0x20, 1 << 0);
	while (1);
}

int main(int argc, char *argv[]) {
    i2cInit();
    InitScreenFbs(argc, argv);
    ClearScreenFull(true, false);
    u32 ctx;
    readHID(&ctx);
    while (!(ctx & BUTTON_POWER)) {
        readHID(&ctx);
        DrawHID(&ctx);
        wait_msec(10);
    }
    poweroff();
    return 0;
}