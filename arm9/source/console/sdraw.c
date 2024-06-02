#include "sdraw.h"
#include "font.h"

void drawCharacter(bool isTopScreen, u16 posX, u16 posY, u32 color, char character) { //taken from luma3ds
    u8 *select = isTopScreen ? GetScreen(1) : GetScreen(2);

    for(u32 y = 0; y < 8; y++)
    {
        char charPos = font[character * 8 + y];

        for(u32 x = 0; x < 8; x++)
            if(((charPos >> (7 - x)) & 1) == 1)
            {
                u32 screenPos = (posX * SCREEN_HEIGHT * 3 + (SCREEN_HEIGHT - y - posY - 1) * 3) + x * 3 * SCREEN_HEIGHT;

                select[screenPos] = color >> 16;
                select[screenPos + 1] = color >> 8;
                select[screenPos + 2] = color;
            }
    }
}

void drawString(bool isTopScreen, u16 posX, u16 posY, u32 color, const char* string, u8 maxlen) {
    u16 charposx = 0; 
    for (int i = 0;string[i] != '\0' || i < maxlen;i++) {
        drawCharacter(isTopScreen, (posX + charposx * CHAR_SPACING_X), posY, color, string[i]);
        charposx++;
    }
}