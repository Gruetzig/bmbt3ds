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

void setupHIDBorders() {
    DrawRecFull(370-1, 110-1, 20+2, 20+2, COLOR_WHITE, GetScreen(1));
    DrawRecFull(340-1, 140-1, 20+2, 20+2, COLOR_WHITE, GetScreen(1));
    DrawRecFull(340-1, 80-1, 20+2, 20+2, COLOR_WHITE, GetScreen(1));
    DrawRecFull(310-1, 110-1, 20+2, 20+2, COLOR_WHITE, GetScreen(1));
    DrawRecFull(40-1, 80-1, 20+2, 20+2, COLOR_WHITE, GetScreen(1));
    DrawRecFull(40-1, 140-1, 20+2, 20+2, COLOR_WHITE, GetScreen(1));
    DrawRecFull(10-1, 110-1, 20+2, 20+2, COLOR_WHITE, GetScreen(1));
    DrawRecFull(70-1, 110-1, 20+2, 20+2, COLOR_WHITE, GetScreen(1));
    DrawRecFull(10-1, 210-1, 40+2, 20+2, COLOR_WHITE, GetScreen(1));
    DrawRecFull(350-1, 210-1, 40+2, 20+2, COLOR_WHITE, GetScreen(1));
    DrawRecFull(180-1, 210-1, 40+2, 20+2, COLOR_WHITE, GetScreen(1));
    DrawRecFull(370-1, 10-1, 20+2, 20+2, COLOR_WHITE, GetScreen(1));
    DrawRecFull(340-1, 10-1, 20+2, 20+2, COLOR_WHITE, GetScreen(1));
    DrawRecFull(10-1, 10-1, 20+2, 20+2, COLOR_WHITE, GetScreen(1));
    DrawRecFull(40-1, 10-1, 20+2, 20+2, COLOR_WHITE, GetScreen(1));
}

void DrawHID(u32 *ctx) {
    if (*ctx & BUTTON_A) {
        DrawRecFull(370, 110, 20, 20, COLOR_WHITE, GetScreen(1));
    } else {
        DrawRecFull(370, 110, 20, 20, COLOR_BLACK, GetScreen(1));
    }
    
    if (*ctx & BUTTON_B) {
        DrawRecFull(340, 140, 20, 20, COLOR_WHITE, GetScreen(1));
    } else {
        DrawRecFull(340, 140, 20, 20, COLOR_BLACK, GetScreen(1));
    }
    
    if (*ctx & BUTTON_X) {
        DrawRecFull(340, 80, 20, 20, COLOR_WHITE, GetScreen(1));
    } else {
        DrawRecFull(340, 80, 20, 20, COLOR_BLACK, GetScreen(1));
    }
    
    if (*ctx & BUTTON_Y) {
        DrawRecFull(310, 110, 20, 20, COLOR_WHITE, GetScreen(1));
    } else {
        DrawRecFull(310, 110, 20, 20, COLOR_BLACK, GetScreen(1));
    }
    
    if (*ctx & BUTTON_UP) {
        DrawRecFull(40, 80, 20, 20, COLOR_WHITE, GetScreen(1));
    } else {
        DrawRecFull(40, 80, 20, 20, COLOR_BLACK, GetScreen(1));
    }
    
    if (*ctx & BUTTON_DOWN) {
        DrawRecFull(40, 140, 20, 20, COLOR_WHITE, GetScreen(1));
    } else {
        DrawRecFull(40, 140, 20, 20, COLOR_BLACK, GetScreen(1));
    }
    
    if (*ctx & BUTTON_LEFT) {
        DrawRecFull(10, 110, 20, 20, COLOR_WHITE, GetScreen(1));
    } else {
        DrawRecFull(10, 110, 20, 20, COLOR_BLACK, GetScreen(1));
    }
    
    if (*ctx & BUTTON_RIGHT) {
        DrawRecFull(70, 110, 20, 20, COLOR_WHITE, GetScreen(1));
    } else {
        DrawRecFull(70, 110, 20, 20, COLOR_BLACK, GetScreen(1));
    }
    
    if (*ctx & BUTTON_SELECT) {
        DrawRecFull(10, 210, 40, 20, COLOR_WHITE, GetScreen(1));
    } else {
        DrawRecFull(10, 210, 40, 20, COLOR_BLACK, GetScreen(1));
    }
    
    if (*ctx & BUTTON_START) {
        DrawRecFull(350, 210, 40, 20, COLOR_WHITE, GetScreen(1));
    } else {
        DrawRecFull(350, 210, 40, 20, COLOR_BLACK, GetScreen(1));
    }
    
    if (*ctx & BUTTON_HOME) {
        DrawRecFull(180, 210, 40, 20, COLOR_WHITE, GetScreen(1));
    } else {
        DrawRecFull(180, 210, 40, 20, COLOR_BLACK, GetScreen(1));
    }
    
    if (*ctx & BUTTON_R1) {
        DrawRecFull(370, 10, 20, 20, COLOR_WHITE, GetScreen(1));
    } else {
        DrawRecFull(370, 10, 20, 20, COLOR_BLACK, GetScreen(1));
    }
    
    if (*ctx & BUTTON_R2) {
        DrawRecFull(340, 10, 20, 20, COLOR_WHITE, GetScreen(1));
    } else {
        DrawRecFull(340, 10, 20, 20, COLOR_BLACK, GetScreen(1));
    }
    
    if (*ctx & BUTTON_L1) {
        DrawRecFull(10, 10, 20, 20, COLOR_WHITE, GetScreen(1));
    } else {
        DrawRecFull(10, 10, 20, 20, COLOR_BLACK, GetScreen(1));
    }
    
    if (*ctx & BUTTON_L2) {
        DrawRecFull(40, 10, 20, 20, COLOR_WHITE, GetScreen(1));
    } else {
        DrawRecFull(40, 10, 20, 20, COLOR_BLACK, GetScreen(1));
    }
}

/*
look of the top screen, spaces 4, just a reference for me
L ZL-----------------------------ZR R

    DUP                       X
DLEFT DRIGHT                Y   A
   DDOWN                      B

---SELECT-------HOME-------START---
*/