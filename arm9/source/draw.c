#include "draw.h"
#include "console/font.h"

static u8 *top_screen0 = NULL;
static u8 *top_screen1 = NULL;
static u8 *bot_screen0 = NULL;
static u8 *bot_screen1 = NULL;

void InitScreenFbs(int argc, char *argv[]) //lel
{
	if (argc >= 2) {
		/* newer entrypoints */
		struct {
			u8 *top_left;
			u8 *top_right;
			u8 *bottom;
		} *fb = (void *)argv[1];
		top_screen0 = fb[0].top_left;
		top_screen1 = fb[1].top_left;
		bot_screen0 = fb[0].bottom;
		bot_screen1 = fb[1].bottom;
	} else {
		/* outdated entrypoints */
		top_screen0 = (u8 *)(*(u32 *)0x23FFFE00);
		top_screen1 = (u8 *)(*(u32 *)0x23FFFE00);
		bot_screen0 = (u8 *)(*(u32 *)0x23FFFE08);
		bot_screen1 = (u8 *)(*(u32 *)0x23FFFE08);
	}
}

void ClearScreen(u8 *screen, int width, int color) //stolen from firm_linux_loader
{
	if (color == COLOR_TRANSPARENT)
		color = COLOR_BLACK;

	for (int i = 0; i < (width * SCREEN_HEIGHT); i++) {
		*(screen++) = color >> 16;      // B
		*(screen++) = color >> 8;       // G
		*(screen++) = color & 0xFF;     // R
	}
}

void ClearScreenFull(bool clear_top, bool clear_bottom) //stolen from firm_linux_loader
{
	if (clear_top) {
		ClearScreen(top_screen0, SCREEN_WIDTH_TOP, COLOR_BLACK);
		ClearScreen(top_screen1, SCREEN_WIDTH_TOP, COLOR_BLACK);
	}
	if (clear_bottom) {
		ClearScreen(bot_screen0, SCREEN_WIDTH_BOT, COLOR_BLACK);
		ClearScreen(bot_screen1, SCREEN_WIDTH_BOT, COLOR_BLACK);
	}
}
u8* GetScreen(int screen) {
	if (screen == 1) return top_screen0; 
	if (screen == 2) return bot_screen0;
	if (screen == 3) return top_screen1;
	if (screen == 4) return bot_screen1;
	return 0;
}

void DrawPixel(int x, int y, int color, u8 *screen) { //stolen from GodMode9 :))
	int xDisplacement = (x * BYTES_PER_PIXEL * SCREEN_HEIGHT);
	int yDisplacement = ((SCREEN_HEIGHT - y - 1) * BYTES_PER_PIXEL);
	u8 *screenPos = screen + xDisplacement + yDisplacement;
	*(screenPos + 0) = color >> 16;         // B
	*(screenPos + 1) = color >> 8;          // G
	*(screenPos + 2) = color & 0xFF;        // R

}

void DrawRecFull(int x, int y, int w, int h, int color, u8 *screen) {
	int i;
	int j;
	for (i=x;i<x+w;i++) {
		for (j=y;j<y+h;j++) {
			DrawPixel(i, j, color, screen);
		}
	}
}

void DrawRecBordered(int x, int y, int w, int h, int color, u8 *screen) {
	int i;
	int j;
	for (i=x;i<x+w;i++) {
		for (j=y;j<y+h;j++) {
			DrawPixel(i, j, color, screen);
		}
	}
}

// ref to top left corner
void DrawChar(int x, int y, char chr, int color, bool swap_xy, u8 *screen) {
    int i;
    int j;
    for (i=0;i<8;i++) {
        for (j=0;j<8;j++) {
            bool set = 0;
            if (swap_xy) {
                if (font[((int)chr)*8+i] & (1 << (7-j))) set = 1;
            } else {
                if (font[((int)chr)*8+j] & (1 << (7-i))) set = 1;
            }
            if (set) DrawPixel(x+i, y+j, color, screen);
        }
    }
}

void DrawText(int x, int y, char* str, int color, bool swap_xy, u8 *screen) {
    while (*str > 0) {
        DrawChar(x, y, *str, color, swap_xy, screen);
        str++;
        x += 8;
    }
}

// will go wrong if ever draw u32... but we don't
// ndigit doesn't include negative sign
// maybe easier to just use snprintf...? meh
void DrawHex(int x, int y, s32 num, int ndigit, bool sign, int color, u8 *screen) {
    int i;
    bool negative = false;
    bool printed = false;

    if (num == 0) {
        x += 8 * (ndigit - 1) + (sign ? 8 : 0);
        DrawChar(x, y, '0', color, false, screen);
        return;
    }

    if (num < 0) {
        negative = true;
        num = -num;
    }
    // add space when negative and draw signed
    // otherwise, only draw negative sign right before printing first nibble
    if (sign && !negative) {
        x += 8;
    }
    for (i=0;i<ndigit;i++,x+=8) {
        s32 digit = (num >> (4*(ndigit-i-1))) & 0xF;
        if (digit == 0 && printed) {
            DrawChar(x, y, '0', color, false, screen);
        } else {
            if (sign && negative && !printed) {
                DrawChar(x, y, '-', color, false, screen);
                x += 8;
            }
            printed = true;
            if (digit < 0xA) {
                DrawChar(x, y, '0'+digit, color, false, screen);
            } else {
                DrawChar(x, y, 'A'+digit-0xA, color, false, screen);
            }
        }
    }
}
