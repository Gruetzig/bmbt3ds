#include "drawhid.h"

/*void DrawHID(HIDContext *ctx) {
    if (ctx->a) {
        DrawRecFull(370, 110, 20, 20, COLOR_WHITE, GetScreen(1));
    }
    if (ctx->b) {
        DrawRecFull(340, 140, 20, 20, COLOR_WHITE, GetScreen(1));
    }
    if (ctx->x) {
        DrawRecFull(340, 80, 20, 20, COLOR_WHITE, GetScreen(1));
    }
    if (ctx->y) {
        DrawRecFull(310, 110, 20, 20, COLOR_WHITE, GetScreen(1));
    }
    if (ctx->dup) {
        DrawRecFull(40, 80, 20, 20, COLOR_WHITE, GetScreen(1));
    }
    if (ctx->ddown) {
        DrawRecFull(40, 140, 20, 20, COLOR_WHITE, GetScreen(1));
    }
    if (ctx->dleft) {
        DrawRecFull(10, 110, 20, 20, COLOR_WHITE, GetScreen(1));
    }
    if (ctx->dright) {
        DrawRecFull(70, 110, 20, 20, COLOR_WHITE, GetScreen(1));
    }
    if (ctx->select) {
        DrawRecFull(350, 210, 40, 20, COLOR_WHITE, GetScreen(1));
    }
    if (ctx->start) {
        DrawRecFull(10, 210, 40, 20, COLOR_WHITE, GetScreen(1));
    }
    if (ctx->home) {
        DrawRecFull(180, 210, 40, 20, COLOR_WHITE, GetScreen(1));
    }
    if (ctx->r1) {
        DrawRecFull(370, 10, 20, 20, COLOR_WHITE, GetScreen(1));
    }
    if (ctx->r2) {
        DrawRecFull(340, 10, 20, 20, COLOR_WHITE, GetScreen(1));
    }
    if (ctx->l1) {
        DrawRecFull(10, 10, 20, 20, COLOR_WHITE, GetScreen(1));
    }
    if (ctx->l2) {
        DrawRecFull(40, 10, 20, 20, COLOR_WHITE, GetScreen(1));
    }
}*/

void DrawHID(HIDContext *ctx) {
    if (ctx->a) {
        DrawRecFull(370, 110, 20, 20, COLOR_WHITE, GetScreen(1));
    } else {
        DrawRecFull(370, 110, 20, 20, COLOR_BLACK, GetScreen(1));
    }
    
    if (ctx->b) {
        DrawRecFull(340, 140, 20, 20, COLOR_WHITE, GetScreen(1));
    } else {
        DrawRecFull(340, 140, 20, 20, COLOR_BLACK, GetScreen(1));
    }
    
    if (ctx->x) {
        DrawRecFull(340, 80, 20, 20, COLOR_WHITE, GetScreen(1));
    } else {
        DrawRecFull(340, 80, 20, 20, COLOR_BLACK, GetScreen(1));
    }
    
    if (ctx->y) {
        DrawRecFull(310, 110, 20, 20, COLOR_WHITE, GetScreen(1));
    } else {
        DrawRecFull(310, 110, 20, 20, COLOR_BLACK, GetScreen(1));
    }
    
    if (ctx->dup) {
        DrawRecFull(40, 80, 20, 20, COLOR_WHITE, GetScreen(1));
    } else {
        DrawRecFull(40, 80, 20, 20, COLOR_BLACK, GetScreen(1));
    }
    
    if (ctx->ddown) {
        DrawRecFull(40, 140, 20, 20, COLOR_WHITE, GetScreen(1));
    } else {
        DrawRecFull(40, 140, 20, 20, COLOR_BLACK, GetScreen(1));
    }
    
    if (ctx->dleft) {
        DrawRecFull(10, 110, 20, 20, COLOR_WHITE, GetScreen(1));
    } else {
        DrawRecFull(10, 110, 20, 20, COLOR_BLACK, GetScreen(1));
    }
    
    if (ctx->dright) {
        DrawRecFull(70, 110, 20, 20, COLOR_WHITE, GetScreen(1));
    } else {
        DrawRecFull(70, 110, 20, 20, COLOR_BLACK, GetScreen(1));
    }
    
    if (ctx->select) {
        DrawRecFull(350, 210, 40, 20, COLOR_WHITE, GetScreen(1));
    } else {
        DrawRecFull(350, 210, 40, 20, COLOR_BLACK, GetScreen(1));
    }
    
    if (ctx->start) {
        DrawRecFull(10, 210, 40, 20, COLOR_WHITE, GetScreen(1));
    } else {
        DrawRecFull(10, 210, 40, 20, COLOR_BLACK, GetScreen(1));
    }
    
    if (ctx->home) {
        DrawRecFull(180, 210, 40, 20, COLOR_WHITE, GetScreen(1));
    } else {
        DrawRecFull(180, 210, 40, 20, COLOR_BLACK, GetScreen(1));
    }
    
    if (ctx->r1) {
        DrawRecFull(370, 10, 20, 20, COLOR_WHITE, GetScreen(1));
    } else {
        DrawRecFull(370, 10, 20, 20, COLOR_BLACK, GetScreen(1));
    }
    
    if (ctx->r2) {
        DrawRecFull(340, 10, 20, 20, COLOR_WHITE, GetScreen(1));
    } else {
        DrawRecFull(340, 10, 20, 20, COLOR_BLACK, GetScreen(1));
    }
    
    if (ctx->l1) {
        DrawRecFull(10, 10, 20, 20, COLOR_WHITE, GetScreen(1));
    } else {
        DrawRecFull(10, 10, 20, 20, COLOR_BLACK, GetScreen(1));
    }
    
    if (ctx->l2) {
        DrawRecFull(40, 10, 20, 20, COLOR_WHITE, GetScreen(1));
    } else {
        DrawRecFull(40, 10, 20, 20, COLOR_BLACK, GetScreen(1));
    }
}

/*
look of the top screen, spaces 4, just a reference for me
L ZL-----------------------------ZR R

    DUP                       X
DLEFT DRIGHT                Y   A
   DDOWN                      B

---SELECT-------HOME-------START---
*/