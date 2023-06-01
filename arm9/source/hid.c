#include "hid.h"

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

void readHID(HIDContext* ctx) {
    ctx->a = (HID_PAD & BUTTON_A);
    ctx->b = (HID_PAD & BUTTON_B);
    ctx->x = (HID_PAD & BUTTON_X);
    ctx->y = (HID_PAD & BUTTON_Y);
    ctx->ddown = (HID_PAD & BUTTON_DOWN);
    ctx->dup = (HID_PAD & BUTTON_UP);
    ctx->dleft = (HID_PAD & BUTTON_LEFT);
    ctx->dright = (HID_PAD & BUTTON_RIGHT);
    ctx->start = (HID_PAD & BUTTON_START);
    ctx->select = (HID_PAD & BUTTON_SELECT);
    ctx->r1 = (HID_PAD & BUTTON_R1);
    ctx->l1 = (HID_PAD & BUTTON_L1);
    readpowhomefromI2C();
    ctx->home = readHOMEfromI2C();
    ctx->power = readPOWfromI2C();
    readZLZR();
    ctx->l2 = readZL();
    ctx->r2 = readZR();
    
}