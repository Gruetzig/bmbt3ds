#include "types.h"
#include "draw.h"

#define CHAR_SPACING_Y 10
#define CHAR_SPACING_X 8

void drawCharacter(bool isTopScreen, u16 posX, u16 posY, u32 color, char character);
void drawString(bool isTopScreen, u16 posX, u16 posY, u32 color, const char* string, u8 maxlen);