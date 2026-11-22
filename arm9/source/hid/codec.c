// Somewhat based on xerpi's CODEC driver for Linux
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

#include "types.h"

#include "hid/codec.h"
#include "hid/spi.h"

/* SPI stuff */
static void CODEC_WriteRead(u32 *txb, u8 txl, u32 *rxb, u8 rxl)
{
	SPI_XferInfo xfers[2];

	xfers[0].buf = txb;
	xfers[0].len = txl;
	xfers[0].read = false;

	xfers[1].buf = rxb;
	xfers[1].len = rxl;
	xfers[1].read = true;

	SPI_DoXfer(SPI_DEV_CODEC, xfers, 2, true);
}

static void CODEC_RegSelect(u8 reg)
{
	SPI_XferInfo xfer;
	u32 cmd;

	cmd = reg << 8;

	xfer.buf = &cmd;
	xfer.len = 2;
	xfer.read = false;

	SPI_DoXfer(SPI_DEV_CODEC, &xfer, 1, true);
}

static u8 CODEC_RegRead(u8 reg)
{
	u32 cmd, ret;
	cmd = (reg << 1) | 1;
	CODEC_WriteRead(&cmd, 1, &ret, 1);
	return ret;
}

static void CODEC_RegReadBuf(u8 reg, u32 *out, u8 size)
{
	u32 cmd = (reg << 1) | 1;
	CODEC_WriteRead(&cmd, 1, out, size);
}

static void CODEC_RegWrite(u8 reg, u8 val)
{
	SPI_XferInfo xfer;
	u32 cmd;

	cmd = (val << 8) | (reg << 1);

	xfer.buf = &cmd;
	xfer.len = 2;
	xfer.read = false;

	SPI_DoXfer(SPI_DEV_CODEC, &xfer, 1, true);
}

static void CODEC_RegMask(u8 reg, u8 mask0, u8 mask1)
{
	CODEC_RegWrite(reg, (CODEC_RegRead(reg) & ~mask1) | (mask0 & mask1));
}

// elder god magic
void CODEC_Init(void)
{
	CODEC_RegSelect(0x67);
	CODEC_RegWrite(0x24, 0x98);
	CODEC_RegWrite(0x26, 0x00);
	CODEC_RegWrite(0x25, 0x43);
	CODEC_RegWrite(0x24, 0x18);
	CODEC_RegWrite(0x17, 0x43);
	CODEC_RegWrite(0x19, 0x69);
	CODEC_RegWrite(0x1B, 0x80);
	CODEC_RegWrite(0x27, 0x11);
	CODEC_RegWrite(0x26, 0xEC);
	CODEC_RegWrite(0x24, 0x18);
	CODEC_RegWrite(0x25, 0x53);

	CODEC_RegMask(0x26, 0x80, 0x80);
	CODEC_RegMask(0x24, 0x00, 0x80);
	CODEC_RegMask(0x25, 0x10, 0x3C);
}

void CODEC_GetRawData(u32 *buffer)
{
	CODEC_RegSelect(0xFB);
	CODEC_RegReadBuf(1, buffer, 0x34);
}

void CODEC_Get(analog *input)
{
	u32 raw_data_buf[0x34 / 4];
	u8 *raw_data = (u8*)raw_data_buf;
	bool ts_pressed;

	CODEC_GetRawData(raw_data_buf);

	// X axis is inverted
	input->cpad_x = -(((raw_data[0x24] << 8 | raw_data[0x25]) & 0xFFF) - 2048);
	input->cpad_y =   ((raw_data[0x14] << 8 | raw_data[0x15]) & 0xFFF) - 2048;

	ts_pressed = !(raw_data[0] & BIT(4));
	if (ts_pressed) {
		input->ts_x = (raw_data[0] << 8) | raw_data[1];
		input->ts_y = (raw_data[10] << 8) | raw_data[11];
	}
}
