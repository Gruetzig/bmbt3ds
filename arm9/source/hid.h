#include "types.h"
#include "i2c.h"
#include "buttons.h"

typedef struct {
    bool a;
    bool b;
    bool x;
    bool y;
    bool ddown;
    bool dup;
    bool dleft;
    bool dright;
    bool start;
    bool select;
    bool home;
    bool l1;
    bool r1;
    bool l2;
    bool r2;
} HIDContext;

void readHID(HIDContext* ctx);