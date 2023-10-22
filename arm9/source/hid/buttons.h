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

#pragma once

#include "types.h"

#define HID_PAD                (*(vu32 *)0x10146000 ^ 0xFFF)

#define _BUTTON_R1              (1 << 8)
#define _BUTTON_L1              (1 << 9)
#define _BUTTON_A               (1 << 0)
#define _BUTTON_B               (1 << 1)
#define _BUTTON_X               (1 << 10)
#define _BUTTON_Y               (1 << 11)
#define _BUTTON_SELECT          (1 << 2)
#define _BUTTON_START           (1 << 3)
#define _BUTTON_RIGHT           (1 << 4)
#define _BUTTON_LEFT            (1 << 5)
#define _BUTTON_UP              (1 << 6)
#define _BUTTON_DOWN            (1 << 7)

#define BUTTON_A (1 << 0)
#define BUTTON_B (1 << 1)
#define BUTTON_X (1 << 2)
#define BUTTON_Y (1 << 3)
#define BUTTON_DOWN (1 << 4)
#define BUTTON_UP (1 << 5)
#define BUTTON_LEFT (1 << 6)
#define BUTTON_RIGHT (1 << 7)
#define BUTTON_START (1 << 8)
#define BUTTON_SELECT (1 << 9)
#define BUTTON_R1 (1 << 10)
#define BUTTON_L1 (1 << 11)
#define BUTTON_R2 (1 << 12)
#define BUTTON_L2 (1 << 13)
#define BUTTON_HOME (1 << 14)
#define BUTTON_POWER (1 << 15)