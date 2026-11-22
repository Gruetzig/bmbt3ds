/* Copyright (C) 2023 Gruetzig

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

#include <string.h>

#include "hid/hid.h"
#include "hid/codec.h"

#define CPAD_DIFF_LIMIT   0x8
#define CSTICK_DIFF_LIMIT 0x8
#define TOUCH_DIFF_LIMIT  0x8
#define SLIDER_DIFF_LIMIT 0x1

#define withinDiff(n1, n2, limit, bit) \
    ((((n1)-(n2)) > -limit && ((n1)-(n2)) < limit ? 0 : 1) << bit)

u8 zlzrbuf[2];

u8 powhomebuf[0x13];

void readZLZR() {
    i2cReadRegisterBuffer(17, 0, zlzrbuf, 2);
}

bool readZL() {
    return (bool) ((zlzrbuf[1] >> 2) & 1);
    
}

bool readZR() {
    return (bool) ((zlzrbuf[1] >> 1) & 1);
}

void readpowhomefromI2C() {
    i2cReadRegisterBuffer(I2C_DEV_MCU, 0x7F, powhomebuf, 0x13);
}

bool readHOMEfromI2C() {
    return (bool)( (~powhomebuf[0x12] >> 1) & 1);
}

bool readPOWfromI2C() {
    return (bool)( (~powhomebuf[0x12] >> 0) & 1);
}

void readHID(u32 *ctx) {
    *ctx = 0;
    readpowhomefromI2C();
    readZLZR();
    *ctx += (HID_PAD & _BUTTON_A)        ? BUTTON_A     : 0;
    *ctx += (HID_PAD & _BUTTON_B)        ? BUTTON_B     : 0;
    *ctx += (HID_PAD & _BUTTON_X)        ? BUTTON_X     : 0;
    *ctx += (HID_PAD & _BUTTON_Y)        ? BUTTON_Y     : 0;
    *ctx += (HID_PAD & _BUTTON_DOWN)     ? BUTTON_DOWN  : 0;
    *ctx += (HID_PAD & _BUTTON_UP)       ? BUTTON_UP    : 0;
    *ctx += (HID_PAD & _BUTTON_LEFT)     ? BUTTON_LEFT  : 0;
    *ctx += (HID_PAD & _BUTTON_RIGHT)    ? BUTTON_RIGHT : 0;
    *ctx += (HID_PAD & _BUTTON_START)    ? BUTTON_START : 0;
    *ctx += (HID_PAD & _BUTTON_SELECT)   ? BUTTON_SELECT: 0;
    *ctx += (HID_PAD & _BUTTON_R1)       ? BUTTON_R1    : 0;
    *ctx += (HID_PAD & _BUTTON_L1)       ? BUTTON_L1    : 0;
    *ctx += readHOMEfromI2C()            ? BUTTON_HOME  : 0;
    *ctx += readPOWfromI2C()             ? BUTTON_POWER : 0;
    *ctx += readZL()                     ? BUTTON_L2    : 0;
    *ctx += readZR()                     ? BUTTON_R2    : 0;
    
}

void read3DSliderfromI2C(u8* s3d) {
    i2cReadRegisterBuffer(I2C_DEV_MCU, 0x08, s3d, 1);
}

void readVolumeSliderfromI2C(u8* vol) {
    i2cReadRegisterBuffer(I2C_DEV_MCU, 0x09, vol, 1);
}

void readAnalog(analog *ctx) {
    memset(ctx, 0, sizeof(analog));

    CODEC_Get(ctx);

    read3DSliderfromI2C(&ctx->s3d);
    readVolumeSliderfromI2C(&ctx->vol);
}

/*
u16 withinDiff(s32 n1, s32 n2, s32 limit, int bit) {
    s32 diff = n1 - n2;
    return (diff > -limit && diff < limit ? 0 : 1) << bit;
}
*/

u16 cmpAnalog(analog* s1, analog* s2) {
    return withinDiff(s1->cpad_x, s2->cpad_x, CPAD_DIFF_LIMIT, 0) |
           withinDiff(s1->cpad_y, s2->cpad_y, CPAD_DIFF_LIMIT, 1) |
           withinDiff(s1->cstick_x, s2->cstick_x, CSTICK_DIFF_LIMIT, 2) |
           withinDiff(s1->cstick_y, s2->cstick_y, CSTICK_DIFF_LIMIT, 3) |
           withinDiff(s1->ts_x, s2->ts_x, TOUCH_DIFF_LIMIT, 4) |
           withinDiff(s1->ts_y, s2->ts_y, TOUCH_DIFF_LIMIT, 5) |
           withinDiff(s1->vol, s2->vol, SLIDER_DIFF_LIMIT, 6) |
           withinDiff(s1->s3d, s2->s3d, SLIDER_DIFF_LIMIT, 7);
}

void copyAnalog(analog* dest, analog* src) {
    memcpy(dest, src, sizeof(analog));
}

