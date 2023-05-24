#include "hid.h"

u8 buttonbyte;

void readZLZR() {
    
}

bool readHOMEfromI2C() {
    u8 sussy = i2cReadRegister(I2C_DEV_MCU, 0x18);
    return (bool)( (sussy >> 3) & 0x01);
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
    ctx->home = readHOMEfromI2C();
    
}