#include "types.h"
#include "buttons.h"
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
    u8 _funi[2];
    while (!(HID_PAD & BUTTON_START)) {
        wait_msec(10);
        i2cReadRegisterBuffer(17, 0, _funi, 2);
        u8 funi = _funi[1];
        if ((funi >> 1) & 1) {
            DrawRecFull(40, 20, 10, 10, COLOR_WHITE, GetScreen(1));
        }
        if ((funi >> 2) & 1) {
            DrawRecFull(60, 20, 10, 10, COLOR_WHITE, GetScreen(1));
        }
    }
    poweroff();
    return 0;
}