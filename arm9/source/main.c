/*  Copyright (C) 2023 Gruetzig

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "types.h"
#include "hid/hid.h"
#include "hid/spi.h"
#include "hid/codec.h"
#include "i2c.h"
#include "draw.h"
#include "timer.h"
#include "print.h"
#include "console.h"

static inline void poweroff() {
	i2cWriteRegister(I2C_DEV_MCU, 0x20, 1 << 0);
	while (1);
}

int main(int argc, char *argv[]) {
    i2cInit();
    SPI_Init();
    CODEC_Init();
    InitScreenFbs(argc, argv);
    ClearScreenFull(true, false);
    printf("Hello from ARM9\nGo Press some buttons on your %s 3DS ^^", (((*(vu16*) 0x10140FFC) & 2) == 0) ? "Old" : "New");
    drawConsole();
    u32 ctx, oldctx;
    analog actx, oldactx;
    setupHIDBorders();
    setupAnalogLabels();
    readHID(&ctx);
    readAnalog(&actx);
    oldctx = ~ctx; // force first draw
    DrawAnalog(&actx, 0);
    while (!(ctx & BUTTON_POWER)) {
        readHID(&ctx);
        if (ctx != oldctx) {
            DrawHID(&ctx, &oldctx);
            oldctx = ctx;
        }
        readAnalog(&actx);
        u16 analog_diff = cmpAnalog(&actx, &oldactx);
        if (analog_diff != 0) {
            DrawAnalog(&actx, analog_diff);
            copyAnalog(&oldactx, &actx);
        }
        wait_msec(10);
    }
    poweroff();
    return 0;
}
