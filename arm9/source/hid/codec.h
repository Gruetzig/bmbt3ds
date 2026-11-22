/*
 *   This file is originally part of GodMode9
 *   Copyright (C) 2017 Sergi Granell, Paul LaMendola
 *   Copyright (C) 2019 Wolfvak
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 2 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include "types.h"
#include "hid/buttons.h"

void CODEC_Init(void);

void CODEC_GetRawData(u32 *buffer);
void CODEC_Get(analog *input);
