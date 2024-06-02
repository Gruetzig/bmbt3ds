#include "print.h"
#include "console.h"
#include "types.h"

#include <stdarg.h>


int pushDecimal(int decimal) {
    char buf[32]; // Assuming a maximum of 32 digits
    int i = 0;
    
    if (decimal == 0) {
        buf[i++] = '0';
    }
    else {
        while (decimal != 0 && i < 31) { 
            buf[i++] = '0' + (decimal % 10);
            decimal /= 10;
        }
    }
    
    // Reversing and pushing the characters onto some output
    for (int j = i - 1; j >= 0; j--) {
        pushCharacter(buf[j]);
    }
    
    pushString("", 0);
    
    return i;
}

//simple implementation of printf with %s and %d feature
int printf(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    int cnt = 0;
    for (int i = 0;i<strlen(fmt);i++) {
        switch(fmt[i]) {
            case '%':
                switch(fmt[i+1]) {
                    case '%':
                        pushCharacter('%');
                        i++;
                        cnt++;
                        break;
                    case 's':
                        char* str = va_arg(args, char*);
                        pushString(str, strlen(str));
                        cnt += strlen(str);
                        i++;
                        break;
                    case 'd':
                        cnt += pushDecimal(va_arg(args, int));
                        i++;
                        break;
                }
                break;
            default:
                pushCharacter(fmt[i]);
                cnt++;
        }
        
    }
    va_end(args);
    pushString("", 0);
    return cnt;
}