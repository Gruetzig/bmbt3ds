#include "hid/hid.h"

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

