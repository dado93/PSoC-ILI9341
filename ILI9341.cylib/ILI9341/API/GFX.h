/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#ifndef _`$INSTANCE_NAME`_GFX_H
#define _`$INSTANCE_NAME`_GFX_H
    
#include "cytypes.h"
#include "`$INSTANCE_NAME`.h"
#include "`$INSTANCE_NAME`_gfxfont.h"
#include "stdlib.h" // size_t data type   
        
// TRANSACTION API / CORE DRAW API
void    `$INSTANCE_NAME`_WriteLine(ILI9341 *ili9341, int16_t x0, int16_t y0,
            int16_t x1, int16_t y1, uint16_t color);
void    `$INSTANCE_NAME`_DrawLine(ILI9341 *ili9341, int16_t x0, int16_t y0, int16_t x1, int16_t y1,
            uint16_t color);

void    `$INSTANCE_NAME`_DrawCircle(ILI9341 *ili9341, int16_t x0, int16_t y0,
            int16_t r, uint16_t color);
void    `$INSTANCE_NAME`_DrawCircleHelper(ILI9341 *ili9341, int16_t x0, int16_t y0,
            int16_t r, uint8_t cornername, uint16_t color);
void    `$INSTANCE_NAME`_FillCircle(ILI9341 *ili9341, int16_t x0, int16_t y0, int16_t r,
            uint16_t color);
void    `$INSTANCE_NAME`_FillCircleHelper(ILI9341 *ili9341, int16_t x0, int16_t y0, int16_t r,
            uint8_t cornername, int16_t delta, uint16_t color);

void    `$INSTANCE_NAME`_DrawRect(ILI9341 *ili9341, int16_t x, int16_t y, int16_t w, int16_t h,
            uint16_t color);
void    `$INSTANCE_NAME`_DrawRoundRect(ILI9341 *ili9341, int16_t x, int16_t y, int16_t w,
            int16_t h, int16_t r, uint16_t color);
void    `$INSTANCE_NAME`_FillRoundRect(ILI9341 *ili9341, int16_t x, int16_t y, int16_t w,
            int16_t h, int16_t r, uint16_t color);

void    `$INSTANCE_NAME`_DrawTriangle(ILI9341 *ili9341, int16_t x0, int16_t y0,
            int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color);
void    `$INSTANCE_NAME`_FillTriangle(ILI9341 *ili9341, int16_t x0, int16_t y0,
            int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color);

void    `$INSTANCE_NAME`_DrawBitmapConstNoBg(ILI9341 *ili9341, int16_t x, int16_t y,
            const uint8_t bitmap[], int16_t w, int16_t h, uint16_t color);
void    `$INSTANCE_NAME`_DrawBitmapNoBg(ILI9341 *ili9341, int16_t x, int16_t y,
            uint8_t bitmap[], int16_t w, int16_t h, uint16_t color);
void    `$INSTANCE_NAME`_DrawBitmapConstBg(ILI9341 *ili9341, int16_t x, int16_t y,
            const uint8_t bitmap[], int16_t w, int16_t h, uint16_t color, uint16_t bg);
void    `$INSTANCE_NAME`_DrawBitmapBg(ILI9341 *ili9341, int16_t x, int16_t y,
            uint8_t *bitmap, int16_t w, int16_t h, uint16_t color, uint16_t bg);

void    `$INSTANCE_NAME`_DrawXBitmap(ILI9341 *ili9341, int16_t x, int16_t y,
            const uint8_t bitmap[], int16_t w, int16_t h, uint16_t color);

void    `$INSTANCE_NAME`_DrawGrayscaleBitmapConstNoMask(ILI9341 *ili9341, int16_t x, int16_t y,
            const uint8_t bitmap[], int16_t w, int16_t h);
void    `$INSTANCE_NAME`_DrawGrayscaleBitmapNoMask(ILI9341 *ili9341, int16_t x, int16_t y,
            uint8_t *bitmap, int16_t w, int16_t h);
void    `$INSTANCE_NAME`_DrawGrayscaleBitmapConstMask(ILI9341 *ili9341, int16_t x, int16_t y,
            const uint8_t bitmap[], const uint8_t mask[],
            int16_t w, int16_t h);
void    `$INSTANCE_NAME`_DrawGrayscaleBitmapMask(ILI9341 *ili9341, int16_t x, int16_t y,
            uint8_t *bitmap, uint8_t *mask, int16_t w, int16_t h);

void    `$INSTANCE_NAME`_DrawChar(ILI9341 *ili9341, int16_t x, int16_t y, unsigned char c,
            uint16_t color, uint16_t bg, uint8_t size);
size_t  `$INSTANCE_NAME`_Write(ILI9341 *ili9341, uint8_t c);
void    `$INSTANCE_NAME`_SetCursor(ILI9341 *ili9341, int16_t x, int16_t y);
int16_t `$INSTANCE_NAME`_GetCursorX(ILI9341 *ili9341);
int16_t `$INSTANCE_NAME`_GetCursorY(ILI9341 *ili9341);
void    `$INSTANCE_NAME`_SetTextSize(ILI9341 *ili9341, uint8_t s);
uint8_t `$INSTANCE_NAME`_GetRotation(ILI9341 *ili9341);
void    `$INSTANCE_NAME`_Cp437(ILI9341 *ili9341, uint8_t x);
void    `$INSTANCE_NAME`_SetFont(ILI9341 *ili9341, const GFXfont *f);
void    `$INSTANCE_NAME`_CharBounds(ILI9341 *ili9341, char c, int16_t *x, int16_t *y,
            int16_t *minx, int16_t *miny, int16_t *maxx, int16_t *maxy);
void    `$INSTANCE_NAME`_GetTextBounds(ILI9341 *ili9341, char *str, int16_t x, int16_t y,
            int16_t *x1, int16_t *y1, uint16_t *w, uint16_t *h);

size_t `$INSTANCE_NAME`_WriteString(ILI9341 *ili9341, const uint8_t *buffer, size_t size);

size_t `$INSTANCE_NAME`_Print(ILI9341 *ili9341, const char[]);
size_t `$INSTANCE_NAME`_PrintChar(ILI9341 *ili9341, char);

size_t `$INSTANCE_NAME`_Println(ILI9341 *ili9341, const char[]);
size_t `$INSTANCE_NAME`_PrintlnChar(ILI9341 *ili9341, char);

#endif

/* [] END OF FILE */
