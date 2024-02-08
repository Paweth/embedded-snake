#pragma once
#include "GUI_Paint.h"
#include "LCD_1in3.h"

extern UWORD *BlackImage;

#define log(...) \
    { \
        Paint_Clear(WHITE); \
        char buffer[64]; \
        sprintf(buffer, __VA_ARGS__); \
        extern UWORD *BlackImage; \
        Paint_DrawString_EN(30, 30, buffer, &Font24, BLACK, WHITE); \
        LCD_1IN3_Display(BlackImage); \
    }
