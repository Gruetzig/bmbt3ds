#include "types.h"
#include "buttons.h"
#include "i2c.h"
#include "draw.h"

void poweroff() {
	i2cWriteRegister(I2C_DEV_MCU, 0x20, 1 << 0);
	while (1);
}

int main(int argc, char *argv[]) {
    InitScreenFbs(argc, argv);
    
    while (!(HID_PAD & BUTTON_START)) {
        u8 funi = i2cReadRegister(17, 1); //this is a test for reading zl/zr, currently broken
        if ((funi >> 2) & 1) {
            DrawRecFull(20, 20, 10, 10, COLOR_WHITE, GetScreen(1));
        }
        if ((funi >> 3) & 1) {
            DrawRecFull(40, 20, 10, 10, COLOR_WHITE, GetScreen(1));
        }
        if ((funi >> 4) & 1) {
            DrawRecFull(60, 20, 10, 10, COLOR_WHITE, GetScreen(1));
        }
        if ((funi >> 5) & 1) {
            DrawRecFull(80, 20, 10, 10, COLOR_WHITE, GetScreen(1));
        }
        if ((funi >> 6) & 1) {
            DrawRecFull(100, 20, 10, 10, COLOR_WHITE, GetScreen(1));
        }
        if ((funi >> 7) & 1) {
            DrawRecFull(120, 20, 10, 10, COLOR_WHITE, GetScreen(1));
        }
    }
    poweroff();
    return 0;
}