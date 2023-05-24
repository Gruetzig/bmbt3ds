#include "types.h"

#define RGB(r,g,b) (r<<24|b<<16|g<<8|r)
#define COLOR_BLACK         RGB(0x00, 0x00, 0x00)
#define COLOR_WHITE         RGB(0xFF, 0xFF, 0xFF)
#define COLOR_BLACK         RGB(0x00, 0x00, 0x00)
#define COLOR_WHITE         RGB(0xFF, 0xFF, 0xFF)
#define COLOR_RED           RGB(0xFF, 0x00, 0x00)
#define COLOR_GREEN         RGB(0x00, 0xFF, 0x00)
#define COLOR_BLUE          RGB(0x00, 0x00, 0xFF)
#define COLOR_CYAN          RGB(0x00, 0xFF, 0xFF)
#define COLOR_MAGENTA       RGB(0xFF, 0x00, 0xFF)
#define COLOR_YELLOW        RGB(0xFF, 0xFF, 0x00)
#define COLOR_GREY          RGB(0x77, 0x77, 0x77)
#define COLOR_TRANSPARENT   RGB(0xFF, 0x00, 0xEF)

#define BYTES_PER_PIXEL 3
#define SCREEN_HEIGHT 240
#define SCREEN_WIDTH_TOP 400
#define SCREEN_WIDTH_BOT 320




void InitScreenFbs(int argc, char *argv[]);
void ClearScreen(u8 *screen, int width, int color);
void ClearScreenFull(bool clear_top, bool clear_bottom);
u8* GetScreen(int screen);
void DrawPixel(int x, int y, int color, u8 *screen);
void DrawRecFull(int x, int y, int w, int h, int color, u8 *screen);