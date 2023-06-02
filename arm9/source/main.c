#include "types.h"
#include "drawhid.h"
#include "i2c.h"
#include "draw.h"
#include "timer.h"

void poweroff() {
	i2cWriteRegister(I2C_DEV_MCU, 0x20, 1 << 0);
	while (1);
}

int main(int argc, char *argv[]) {
    i2cInit();
    InitScreenFbs(argc, argv);
    ClearScreenFull(true, false);
    HIDContext ctx;
    readHID(&ctx);
    while (!(ctx.power)) {
        readHID(&ctx);
        DrawHID(&ctx);
        wait_msec(10);
    }
    poweroff();
    return 0;
}