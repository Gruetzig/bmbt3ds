#include "sdraw.h"
#include "types.h"

#define PRINTBUFMAX 8192

s32 strlen(const char* string);
void pushCharacter(char character);
void pushString(char* string, s32 len);
void drawConsole();