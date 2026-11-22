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

#include "hid/drawhid.h"

typedef struct {
    int x, y, w;
    bool n3ds;
    u32 button;
    char* label;
    int offset;
    bool swap_xy;
} button_config;

static const button_config buttons[] = {
    { 370, 110, 20, 0, BUTTON_A,          "A",  7, 0 },
    { 340, 140, 20, 0, BUTTON_B,          "B",  7, 0 },
    { 340,  80, 20, 0, BUTTON_X,          "X",  7, 0 },
    { 310, 110, 20, 0, BUTTON_Y,          "Y",  7, 0 },
    {  40,  80, 20, 0, BUTTON_UP,         "<",  7, 1 },
    {  40, 140, 20, 0, BUTTON_DOWN,       ">",  7, 1 },
    {  10, 110, 20, 0, BUTTON_LEFT,       "<",  7, 0 },
    {  70, 110, 20, 0, BUTTON_RIGHT,      ">",  7, 0 },
    {  10, 210, 60, 0, BUTTON_SELECT,"SELECT",  7, 0 },
    { 330, 210, 60, 0, BUTTON_START,  "START", 11, 0 },
    { 170, 210, 60, 0, BUTTON_HOME,    "HOME", 15, 0 },
    { 370,  10, 20, 0, BUTTON_R1,         "R",  7, 0 },
    { 340,  10, 20, 1, BUTTON_R2,        "ZR",  3, 0 },
    {  10,  10, 20, 0, BUTTON_L1,         "L",  7, 0 },
    {  40,  10, 20, 1, BUTTON_L2,        "ZL",  3, 0 },
    {   0,   0,  0, 0, 0,                  "",  0, 0 } // END
};

void setupHIDBorders() {
    const button_config* btn = buttons;
    while (btn->button != 0) {
        if (!btn->n3ds || ((*(vu16*) 0x10140FFC) & 2) != 0) {
            DrawRecFull(btn->x - 1, btn->y - 1, btn->w + 2, 20+2, COLOR_WHITE, GetScreen(1));
        }

        btn++;
    }
}

void DrawHID(u32 *ctx, u32 *octx) {
    u32 diff = octx ? (*ctx ^ *octx) : *ctx;
    const button_config* btn = buttons;
    while (btn->button != 0) {
        if (diff & btn->button) {
            if (*ctx & btn->button) {
                DrawRecFull(btn->x, btn->y, btn->w, 20, COLOR_WHITE, GetScreen(1));
                if (!btn->n3ds || ((*(vu16*) 0x10140FFC) & 2) != 0) {
                    DrawText(btn->x + btn->offset, btn->y + 7, btn->label, COLOR_BLACK, btn->swap_xy, GetScreen(1));
                }
            } else {
                DrawRecFull(btn->x, btn->y, btn->w, 20, COLOR_BLACK, GetScreen(1));
                if (!btn->n3ds || ((*(vu16*) 0x10140FFC) & 2) != 0) {
                    DrawText(btn->x + btn->offset, btn->y + 7, btn->label, COLOR_WHITE, btn->swap_xy, GetScreen(1));
                }
            }
        }

        btn++;
    }
}

void setupAnalogLabels() {
    DrawText(132+1*8,  80,       "CPad:", COLOR_WHITE, 0, GetScreen(1));
    /*
    if (((*(vu16*) 0x10140FFC) & 2) != 0) {
        DrawText(132-8,    80+8,   "CStick:", COLOR_WHITE, 0, GetScreen(1));
    }
    */
    DrawText(132,      80+3*8,  "Touch:", COLOR_WHITE, 0, GetScreen(1));
    DrawText(132-8,    80+6*8, "Volume:", COLOR_WHITE, 0, GetScreen(1));
    DrawText(132+3*8,  80+7*8,     "3D:", COLOR_WHITE, 0, GetScreen(1));
}

// diff 0 also means all, convenient for force draw
void DrawAnalog(analog *ctx, u16 diff) {
    //DrawRecFull(132+7*8, 80, 11*8, 8*8, COLOR_BLACK, GetScreen(1));
    if (diff == 0) diff = 0xFFFF;

    if (diff & 0x3) {
        DrawRecFull(132+7*8, 80, 11*8, 8, COLOR_BLACK, GetScreen(1));
        DrawHex(132+7*8,  80,     ctx->cpad_x,   4, 1, COLOR_WHITE, GetScreen(1));
        DrawHex(132+13*8, 80,     ctx->cpad_y,   4, 1, COLOR_WHITE, GetScreen(1));
    }

    /*
    if (diff & 0xC) {
        if (((*(vu16*) 0x10140FFC) & 2) != 0) {
            DrawRecFull(132+7*8, 80+8, 11*8, 8, COLOR_BLACK, GetScreen(1));
            DrawHex(132+7*8,  80+8,   ctx->cstick_x, 4, 1, COLOR_WHITE, GetScreen(1));
            DrawHex(132+13*8, 80+8,   ctx->cstick_y, 4, 1, COLOR_WHITE, GetScreen(1));
        }
    }
    */

    if (diff & 0x30) {
        DrawRecFull(132+8*8, 80+3*8, 10*8, 8, COLOR_BLACK, GetScreen(1));
        DrawHex(132+8*8,  80+3*8, ctx->ts_x,     4, 0, COLOR_WHITE, GetScreen(1));
        DrawHex(132+14*8, 80+3*8, ctx->ts_y,     4, 0, COLOR_WHITE, GetScreen(1));
    }

    if (diff & 0x40) {
        DrawRecFull(132+12*8, 80+6*8, 2*8, 8, COLOR_BLACK, GetScreen(1));
        DrawHex(132+12*8, 80+6*8, ctx->vol,      2, 0, COLOR_WHITE, GetScreen(1));
    }

    if (diff & 0x80) {
        DrawRecFull(132+12*8, 80+7*8, 2*8, 8, COLOR_BLACK, GetScreen(1));
        DrawHex(132+12*8, 80+7*8, ctx->s3d,      2, 0, COLOR_WHITE, GetScreen(1));
    }
}

/*
look of the top screen, spaces 4, just a reference for me
L ZL-----------------------------ZR R

    DUP                       X
DLEFT DRIGHT                Y   A
   DDOWN                      B

---SELECT-------HOME-------START---


==== Analog Box ====
| CPad: -ABCD -ABCD|
CStick: -ABCD -ABCD|
|                  |
|Touch:  ABCD  ABCD|
|                  |
|                  |
Volume:      EF    |
|   3D:      EF    |
--------------------
*/
