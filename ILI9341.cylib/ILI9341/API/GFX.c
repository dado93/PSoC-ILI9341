/*

Adafruit GFX Library adapted for PSoC MCU
Author: Davide Marzorati
Date: July 27, 2018

This is the core graphics library for all Adafruit displays, providing a common
set of graphics primitives (points, lines, circles, etc.).  It needs to be
paired with a hardware-specific library for each Adafruit display device
(to handle the lower-level functions).

Adafruit invests time and resources providing this open source code, please
support Adafruit & open-source hardware by purchasing products from Adafruit!

Copyright (c) 2013 Adafruit Industries.  All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
- Redistributions of source code must retain the above copyright notice,
  this list of conditions and the following disclaimer.
- Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE.
 */

#include "`$INSTANCE_NAME`_GFX.h"
#include "`$INSTANCE_NAME`.h"
#include "`$INSTANCE_NAME`_glcdfont.c"
#include "string.h"

#ifndef min
    #define min(a,b) (((a) < (b)) ? (a) : (b))
#endif

#ifndef abs
    #define abs(a) ( ((a) >= 0) ? (a) : -(a))  
#endif

#ifndef _swap_int16_t
    #define _swap_int16_t(a, b) { int16_t t = a; a = b; b = t; }
#endif

#ifndef pgm_read_byte
    #define pgm_read_byte(addr) (*(const unsigned char *)(addr))
#endif
#ifndef pgm_read_word
    #define pgm_read_word(addr) (*(const unsigned short *)(addr))
#endif
#ifndef pgm_read_dword
    #define pgm_read_dword(addr) (*(const unsigned long *)(addr))
#endif

#if !defined(__INT_MAX__) || (__INT_MAX__ > 0xFFFF)
 #define pgm_read_pointer(addr) ((void *)pgm_read_dword(addr))
#else
 #define pgm_read_pointer(addr) ((void *)pgm_read_word(addr))
#endif


/**************************************************************************/
/*!
*   @brief    Write a line.  Bresenham's algorithm - thx wikpedia
*    @param    x0  Start point x coordinate
*    @param    y0  Start point y coordinate
*    @param    x1  End point x coordinate
*    @param    y1  End point y coordinate
*    @param    color 16-bit 5-6-5 Color to draw with
*/
/**************************************************************************/
void `$INSTANCE_NAME`_WriteLine(ILI9341 *ili9341, int16_t x0, int16_t y0,
        int16_t x1, int16_t y1, uint16_t color) {
    int16_t steep = abs(y1 - y0) > abs(x1 - x0);
    if (steep) {
        _swap_int16_t(x0, y0);
        _swap_int16_t(x1, y1);
    }

    if (x0 > x1) {
        _swap_int16_t(x0, x1);
        _swap_int16_t(y0, y1);
    }

    int16_t dx, dy;
    dx = x1 - x0;
    dy = abs(y1 - y0);

    int16_t err = dx / 2;
    int16_t ystep;

    if (y0 < y1) {
        ystep = 1;
    } else {
        ystep = -1;
    }

    for (; x0<=x1; x0++) {
        if (steep) {
            `$INSTANCE_NAME`_WritePixel(ili9341, y0, x0, color);
        } else {
            `$INSTANCE_NAME`_WritePixel(ili9341, x0, y0, color);
        }
        err -= dy;
        if (err < 0) {
            y0 += ystep;
            err += dx;
        }
    }
}
        
/**************************************************************************/
/*!
*   @brief    Draw a line
*    @param    x0  Start point x coordinate
*    @param    y0  Start point y coordinate
*    @param    x1  End point x coordinate
*    @param    y1  End point y coordinate
*    @param    color 16-bit 5-6-5 Color to draw with
*/
/**************************************************************************/
void `$INSTANCE_NAME`_DrawLine(ILI9341 *ili9341, int16_t x0, int16_t y0, int16_t x1, int16_t y1,
        uint16_t color) {
    // Update in subclasses if desired!
    if(x0 == x1){
        if(y0 > y1) _swap_int16_t(y0, y1);
        `$INSTANCE_NAME`_DrawFastVLine(ili9341, x0, y0, y1 - y0 + 1, color);
    } else if(y0 == y1){
        if(x0 > x1) _swap_int16_t(x0, x1);
        `$INSTANCE_NAME`_DrawFastHLine(ili9341, x0, y0, x1 - x0 + 1, color);
    } else {
        `$INSTANCE_NAME`_StartWrite();
        `$INSTANCE_NAME`_WriteLine(ili9341, x0, y0, x1, y1, color);
        `$INSTANCE_NAME`_EndWrite();
    }
}
        
/**************************************************************************/
/*!
*   @brief    Draw a circle outline
*    @param    x0   Center-point x coordinate
*    @param    y0   Center-point y coordinate
*    @param    r   Radius of circle
*    @param    color 16-bit 5-6-5 Color to draw with
*/
/**************************************************************************/
void `$INSTANCE_NAME`_DrawCircle(ILI9341 *ili9341, int16_t x0, int16_t y0, int16_t r,
        uint16_t color) {
    int16_t f = 1 - r;
    int16_t ddF_x = 1;
    int16_t ddF_y = -2 * r;
    int16_t x = 0;
    int16_t y = r;

    `$INSTANCE_NAME`_StartWrite();
    `$INSTANCE_NAME`_WritePixel(ili9341, x0  , y0+r, color);
    `$INSTANCE_NAME`_WritePixel(ili9341, x0  , y0-r, color);
    `$INSTANCE_NAME`_WritePixel(ili9341, x0+r, y0  , color);
    `$INSTANCE_NAME`_WritePixel(ili9341, x0-r, y0  , color);

    while (x<y) {
        if (f >= 0) {
            y--;
            ddF_y += 2;
            f += ddF_y;
        }
        x++;
        ddF_x += 2;
        f += ddF_x;

        `$INSTANCE_NAME`_WritePixel(ili9341, x0 + x, y0 + y, color);
        `$INSTANCE_NAME`_WritePixel(ili9341, x0 - x, y0 + y, color);
        `$INSTANCE_NAME`_WritePixel(ili9341, x0 + x, y0 - y, color);
        `$INSTANCE_NAME`_WritePixel(ili9341, x0 - x, y0 - y, color);
        `$INSTANCE_NAME`_WritePixel(ili9341, x0 + y, y0 + x, color);
        `$INSTANCE_NAME`_WritePixel(ili9341, x0 - y, y0 + x, color);
        `$INSTANCE_NAME`_WritePixel(ili9341, x0 + y, y0 - x, color);
        `$INSTANCE_NAME`_WritePixel(ili9341, x0 - y, y0 - x, color);
    }
    `$INSTANCE_NAME`_EndWrite();
}
        
/**************************************************************************/
/*!
*   @brief    Quarter-circle drawer, used to do circles and roundrects
*    @param    x0   Center-point x coordinate
*    @param    y0   Center-point y coordinate
*    @param    r   Radius of circle
*    @param    cornername  Mask bit #1 or bit #2 to indicate which quarters of the circle we're doing
*    @param    color 16-bit 5-6-5 Color to draw with
*/
/**************************************************************************/
void `$INSTANCE_NAME`_DrawCircleHelper(ILI9341 *ili9341, int16_t x0, int16_t y0,
        int16_t r, uint8_t cornername, uint16_t color) {
    int16_t f     = 1 - r;
    int16_t ddF_x = 1;
    int16_t ddF_y = -2 * r;
    int16_t x     = 0;
    int16_t y     = r;

    while (x<y) {
        if (f >= 0) {
            y--;
            ddF_y += 2;
            f     += ddF_y;
        }
        x++;
        ddF_x += 2;
        f     += ddF_x;
        if (cornername & 0x4) {
            `$INSTANCE_NAME`_WritePixel(ili9341, x0 + x, y0 + y, color);
            `$INSTANCE_NAME`_WritePixel(ili9341, x0 + y, y0 + x, color);
        }
        if (cornername & 0x2) {
            `$INSTANCE_NAME`_WritePixel(ili9341, x0 + x, y0 - y, color);
            `$INSTANCE_NAME`_WritePixel(ili9341, x0 + y, y0 - x, color);
        }
        if (cornername & 0x8) {
            `$INSTANCE_NAME`_WritePixel(ili9341, x0 - y, y0 + x, color);
            `$INSTANCE_NAME`_WritePixel(ili9341, x0 - x, y0 + y, color);
        }
        if (cornername & 0x1) {
            `$INSTANCE_NAME`_WritePixel(ili9341, x0 - y, y0 - x, color);
            `$INSTANCE_NAME`_WritePixel(ili9341, x0 - x, y0 - y, color);
        }
    }
}

/**************************************************************************/
/*!
*   @brief    Draw a circle with filled color
*    @param    x0   Center-point x coordinate
*    @param    y0   Center-point y coordinate
*    @param    r   Radius of circle
*    @param    color 16-bit 5-6-5 Color to fill with
*/
/**************************************************************************/
void `$INSTANCE_NAME`_FillCircle(ILI9341 *ili9341, int16_t x0, int16_t y0, int16_t r,
        uint16_t color) {
    `$INSTANCE_NAME`_StartWrite();
    `$INSTANCE_NAME`_WriteFastVLine(ili9341, x0, y0-r, 2*r+1, color);
    `$INSTANCE_NAME`_FillCircleHelper(ili9341, x0, y0, r, 3, 0, color);
    `$INSTANCE_NAME`_EndWrite();
}
        
/**************************************************************************/
/*!
   @brief    Quarter-circle drawer with fill, used to do circles and roundrects
    @param    x0   Center-point x coordinate
    @param    y0   Center-point y coordinate
    @param    r   Radius of circle
    @param    cornername  Mask bit #1 or bit #2 to indicate which quarters of the circle we're doing
    @param    delta  Offset from center-point, used for round-rects
    @param    color 16-bit 5-6-5 Color to fill with
*/
/**************************************************************************/
void `$INSTANCE_NAME`_FillCircleHelper(ILI9341 *ili9341, int16_t x0, int16_t y0, int16_t r,
        uint8_t cornername, int16_t delta, uint16_t color) {

    int16_t f     = 1 - r;
    int16_t ddF_x = 1;
    int16_t ddF_y = -2 * r;
    int16_t x     = 0;
    int16_t y     = r;

    while (x<y) {
        if (f >= 0) {
            y--;
            ddF_y += 2;
            f     += ddF_y;
        }
        x++;
        ddF_x += 2;
        f     += ddF_x;

        if (cornername & 0x1) {
            `$INSTANCE_NAME`_WriteFastVLine(ili9341, x0+x, y0-y, 2*y+1+delta, color);
            `$INSTANCE_NAME`_WriteFastVLine(ili9341, x0+y, y0-x, 2*x+1+delta, color);
        }
        if (cornername & 0x2) {
            `$INSTANCE_NAME`_WriteFastVLine(ili9341, x0-x, y0-y, 2*y+1+delta, color);
            `$INSTANCE_NAME`_WriteFastVLine(ili9341, x0-y, y0-x, 2*x+1+delta, color);
        }
    }
}
        
/**************************************************************************/
/*!
*   @brief   Draw a rectangle with no fill color
*    @param    ili9341 ILI9341 display struct
*    @param    x   Top left corner x coordinate
*    @param    y   Top left corner y coordinate
*    @param    w   Width in pixels
*    @param    h   Height in pixels
*    @param    color 16-bit 5-6-5 Color to draw with
*/
/**************************************************************************/
void `$INSTANCE_NAME`_DrawRect(ILI9341 *ili9341, int16_t x, int16_t y, int16_t w, int16_t h,
        uint16_t color) {
    `$INSTANCE_NAME`_StartWrite();
    `$INSTANCE_NAME`_WriteFastHLine(ili9341, x, y, w, color);
    `$INSTANCE_NAME`_WriteFastHLine(ili9341, x, y+h-1, w, color);
    `$INSTANCE_NAME`_WriteFastVLine(ili9341, x, y, h, color);
    `$INSTANCE_NAME`_WriteFastVLine(ili9341, x+w-1, y, h, color);
    `$INSTANCE_NAME`_EndWrite();
}
        
/**************************************************************************/
/*!
*   @brief   Draw a rounded rectangle with no fill color
*    @param    x   Top left corner x coordinate
*    @param    y   Top left corner y coordinate
*    @param    w   Width in pixels
*    @param    h   Height in pixels
*    @param    r   Radius of corner rounding
*    @param    color 16-bit 5-6-5 Color to draw with
*/
/**************************************************************************/
void `$INSTANCE_NAME`_DrawRoundRect(ILI9341 *ili9341, int16_t x, int16_t y, int16_t w,
        int16_t h, int16_t r, uint16_t color) {
    // smarter version
    `$INSTANCE_NAME`_StartWrite();
    `$INSTANCE_NAME`_WriteFastHLine(ili9341, x+r  , y    , w-2*r, color); // Top
    `$INSTANCE_NAME`_WriteFastHLine(ili9341, x+r  , y+h-1, w-2*r, color); // Bottom
    `$INSTANCE_NAME`_WriteFastVLine(ili9341, x    , y+r  , h-2*r, color); // Left
    `$INSTANCE_NAME`_WriteFastVLine(ili9341, x+w-1, y+r  , h-2*r, color); // Right
    // draw four corners
    `$INSTANCE_NAME`_DrawCircleHelper(ili9341, x+r    , y+r    , r, 1, color);
    `$INSTANCE_NAME`_DrawCircleHelper(ili9341, x+w-r-1, y+r    , r, 2, color);
    `$INSTANCE_NAME`_DrawCircleHelper(ili9341, x+w-r-1, y+h-r-1, r, 4, color);
    `$INSTANCE_NAME`_DrawCircleHelper(ili9341, x+r    , y+h-r-1, r, 8, color);
    `$INSTANCE_NAME`_EndWrite();
}

/**************************************************************************/
/*!
*   @brief   Draw a rounded rectangle with fill color
*    @param    x   Top left corner x coordinate
*    @param    y   Top left corner y coordinate
*    @param    w   Width in pixels
*    @param    h   Height in pixels
*    @param    r   Radius of corner rounding
*    @param    color 16-bit 5-6-5 Color to draw/fill with
*/
/**************************************************************************/
void `$INSTANCE_NAME`_FillRoundRect(ILI9341 *ili9341, int16_t x, int16_t y, int16_t w,
        int16_t h, int16_t r, uint16_t color) {
    // smarter version
    `$INSTANCE_NAME`_StartWrite();
    `$INSTANCE_NAME`_WriteFillRect(ili9341, x+r, y, w-2*r, h, color);

    // draw four corners
    `$INSTANCE_NAME`_FillCircleHelper(ili9341, x+w-r-1, y+r, r, 1, h-2*r-1, color);
    `$INSTANCE_NAME`_FillCircleHelper(ili9341, x+r    , y+r, r, 2, h-2*r-1, color);
    `$INSTANCE_NAME`_EndWrite();
}
        
/**************************************************************************/
/*!
*   @brief   Draw a triangle with no fill color
*    @param    x0  Vertex #0 x coordinate
*    @param    y0  Vertex #0 y coordinate
*    @param    x1  Vertex #1 x coordinate
*    @param    y1  Vertex #1 y coordinate
*    @param    x2  Vertex #2 x coordinate
*    @param    y2  Vertex #2 y coordinate
*    @param    color 16-bit 5-6-5 Color to draw with
*/
/**************************************************************************/
void `$INSTANCE_NAME`_DrawTriangle(ILI9341 *ili9341, int16_t x0, int16_t y0,
        int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color) {
    `$INSTANCE_NAME`_DrawLine(ili9341, x0, y0, x1, y1, color);
    `$INSTANCE_NAME`_DrawLine(ili9341, x1, y1, x2, y2, color);
    `$INSTANCE_NAME`_DrawLine(ili9341, x2, y2, x0, y0, color);
}

/**************************************************************************/
/*!
   @brief     Draw a triangle with color-fill
    @param    x0  Vertex #0 x coordinate
    @param    y0  Vertex #0 y coordinate
    @param    x1  Vertex #1 x coordinate
    @param    y1  Vertex #1 y coordinate
    @param    x2  Vertex #2 x coordinate
    @param    y2  Vertex #2 y coordinate
    @param    color 16-bit 5-6-5 Color to fill/draw with
*/
/**************************************************************************/
void `$INSTANCE_NAME`_FillTriangle(ILI9341 *ili9341, int16_t x0, int16_t y0,
        int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color) {

    int16_t a, b, y, last;

    // Sort coordinates by Y order (y2 >= y1 >= y0)
    if (y0 > y1) {
        _swap_int16_t(y0, y1); _swap_int16_t(x0, x1);
    }
    if (y1 > y2) {
        _swap_int16_t(y2, y1); _swap_int16_t(x2, x1);
    }
    if (y0 > y1) {
        _swap_int16_t(y0, y1); _swap_int16_t(x0, x1);
    }

    `$INSTANCE_NAME`_StartWrite();
    if(y0 == y2) { // Handle awkward all-on-same-line case as its own thing
        a = b = x0;
        if(x1 < a)      a = x1;
        else if(x1 > b) b = x1;
        if(x2 < a)      a = x2;
        else if(x2 > b) b = x2;
        `$INSTANCE_NAME`_WriteFastHLine(ili9341, a, y0, b-a+1, color);
        `$INSTANCE_NAME`_EndWrite();
        return;
    }

    int16_t
    dx01 = x1 - x0,
    dy01 = y1 - y0,
    dx02 = x2 - x0,
    dy02 = y2 - y0,
    dx12 = x2 - x1,
    dy12 = y2 - y1;
    int32_t
    sa   = 0,
    sb   = 0;

    // For upper part of triangle, find scanline crossings for segments
    // 0-1 and 0-2.  If y1=y2 (flat-bottomed triangle), the scanline y1
    // is included here (and second loop will be skipped, avoiding a /0
    // error there), otherwise scanline y1 is skipped here and handled
    // in the second loop...which also avoids a /0 error here if y0=y1
    // (flat-topped triangle).
    if(y1 == y2) last = y1;   // Include y1 scanline
    else         last = y1-1; // Skip it

    for(y=y0; y<=last; y++) {
        a   = x0 + sa / dy01;
        b   = x0 + sb / dy02;
        sa += dx01;
        sb += dx02;
        /* longhand:
        a = x0 + (x1 - x0) * (y - y0) / (y1 - y0);
        b = x0 + (x2 - x0) * (y - y0) / (y2 - y0);
        */
        if(a > b) _swap_int16_t(a,b);
        `$INSTANCE_NAME`_WriteFastHLine(ili9341, a, y, b-a+1, color);
    }

    // For lower part of triangle, find scanline crossings for segments
    // 0-2 and 1-2.  This loop is skipped if y1=y2.
    sa = dx12 * (y - y1);
    sb = dx02 * (y - y0);
    for(; y<=y2; y++) {
        a   = x1 + sa / dy12;
        b   = x0 + sb / dy02;
        sa += dx12;
        sb += dx02;
        /* longhand:
        a = x1 + (x2 - x1) * (y - y1) / (y2 - y1);
        b = x0 + (x2 - x0) * (y - y0) / (y2 - y0);
        */
        if(a > b) _swap_int16_t(a,b);
        `$INSTANCE_NAME`_WriteFastHLine(ili9341, a, y, b-a+1, color);
    }
    `$INSTANCE_NAME`_EndWrite();
}

// BITMAP / XBITMAP / GRAYSCALE / RGB BITMAP FUNCTIONS  -----------------
        
/**************************************************************************/
/*!
*   @brief     Draw a PROGMEM-resident 1-bit image at the specified (x,y) position
*     
*    Draw a PROGMEM-resident 1-bit image at the specified (x,y) position   
*    using the specified foreground color (unset bits are transparent).
*    @param    x   Top left corner x coordinate
*    @param    y   Top left corner y coordinate
*    @param    bitmap  byte array with monochrome bitmap
*    @param    w   Width of bitmap in pixels
*    @param    h   Hieght of bitmap in pixels
*    @param    color 16-bit 5-6-5 Color to draw with
*/
/**************************************************************************/
void `$INSTANCE_NAME`_DrawBitmapConstNoBg(ILI9341 *ili9341, int16_t x, int16_t y,
    const uint8_t bitmap[], int16_t w, int16_t h, uint16_t color) {

    int16_t byteWidth = (w + 7) / 8; // Bitmap scanline pad = whole byte
    uint8_t byte = 0;

    `$INSTANCE_NAME`_StartWrite();
    for(int16_t j=0; j<h; j++, y++) {
        for(int16_t i=0; i<w; i++) {
            if(i & 7) byte <<= 1;
            else      byte   = pgm_read_byte(&bitmap[j * byteWidth + i / 8]);
            if(byte & 0x80) `$INSTANCE_NAME`_WritePixel(ili9341, x+i, y, color);
        }
    }
    `$INSTANCE_NAME`_EndWrite();
} 
    
/**************************************************************************/
/*!
*   @brief      Draw a RAM-resident 1-bit image at the specified (x,y) position, using the specified foreground color (unset bits are transparent).
*    @param    x   Top left corner x coordinate
*    @param    y   Top left corner y coordinate
*    @param    bitmap  byte array with monochrome bitmap
*    @param    w   Width of bitmap in pixels
*    @param    h   Hieght of bitmap in pixels
*    @param    color 16-bit 5-6-5 Color to draw with
*/
/**************************************************************************/
void `$INSTANCE_NAME`_DrawBitmapNoBg(ILI9341 *ili9341, int16_t x, int16_t y,
  uint8_t *bitmap, int16_t w, int16_t h, uint16_t color) {

    int16_t byteWidth = (w + 7) / 8; // Bitmap scanline pad = whole byte
    uint8_t byte = 0;

    `$INSTANCE_NAME`_StartWrite();
    for(int16_t j=0; j<h; j++, y++) {
        for(int16_t i=0; i<w; i++ ) {
            if(i & 7) byte <<= 1;
            else      byte   = bitmap[j * byteWidth + i / 8];
            if(byte & 0x80) `$INSTANCE_NAME`_WritePixel(ili9341, x+i, y, color);
        }
    }
    `$INSTANCE_NAME`_EndWrite();
}

/**************************************************************************/
/*!
*   @brief      Draw a PROGMEM-resident 1-bit image at the specified (x,y) position, using the specified foreground (for set bits) and background (unset bits) colors.
*    @param    x   Top left corner x coordinate
*    @param    y   Top left corner y coordinate
*    @param    bitmap  byte array with monochrome bitmap
*    @param    w   Width of bitmap in pixels
*    @param    h   Hieght of bitmap in pixels
*    @param    color 16-bit 5-6-5 Color to draw pixels with
*    @param    bg 16-bit 5-6-5 Color to draw background with
*/
/**************************************************************************/
void `$INSTANCE_NAME`_DrawBitmapConstBg(ILI9341 *ili9341, int16_t x, int16_t y,
  const uint8_t bitmap[], int16_t w, int16_t h,
  uint16_t color, uint16_t bg) {

    int16_t byteWidth = (w + 7) / 8; // Bitmap scanline pad = whole byte
    uint8_t byte = 0;

    `$INSTANCE_NAME`_StartWrite();
    for(int16_t j=0; j<h; j++, y++) {
        for(int16_t i=0; i<w; i++ ) {
            if(i & 7) byte <<= 1;
            else      byte   = pgm_read_byte(&bitmap[j * byteWidth + i / 8]);
            `$INSTANCE_NAME`_WritePixel(ili9341, x+i, y, (byte & 0x80) ? color : bg);
        }
    }
    `$INSTANCE_NAME`_EndWrite();
}

/**************************************************************************/
/*!
   @brief      Draw a RAM-resident 1-bit image at the specified (x,y) position, using the specified foreground (for set bits) and background (unset bits) colors.
    @param    x   Top left corner x coordinate
    @param    y   Top left corner y coordinate
    @param    bitmap  byte array with monochrome bitmap
    @param    w   Width of bitmap in pixels
    @param    h   Hieght of bitmap in pixels
    @param    color 16-bit 5-6-5 Color to draw pixels with
    @param    bg 16-bit 5-6-5 Color to draw background with
*/
/**************************************************************************/
void `$INSTANCE_NAME`_DrawBitmapBg(ILI9341 *ili9341, int16_t x, int16_t y,
  uint8_t *bitmap, int16_t w, int16_t h, uint16_t color, uint16_t bg) {

    int16_t byteWidth = (w + 7) / 8; // Bitmap scanline pad = whole byte
    uint8_t byte = 0;

    `$INSTANCE_NAME`_StartWrite();
    for(int16_t j=0; j<h; j++, y++) {
        for(int16_t i=0; i<w; i++ ) {
            if(i & 7) byte <<= 1;
            else      byte   = bitmap[j * byteWidth + i / 8];
            `$INSTANCE_NAME`_WritePixel(ili9341, x+i, y, (byte & 0x80) ? color : bg);
        }
    }
    `$INSTANCE_NAME`_EndWrite();
}
 
/**************************************************************************/
/*!
*   @brief      Draw PROGMEM-resident XBitMap Files (*.xbm), exported from GIMP. 
*   Usage: Export from GIMP to *.xbm, rename *.xbm to *.c and open in editor.
*   C Array can be directly used with this function.
*   There is no RAM-resident version of this function; if generating bitmaps
*   in RAM, use the format defined by drawBitmap() and call that instead.
*    @param    x   Top left corner x coordinate
*    @param    y   Top left corner y coordinate
*    @param    bitmap  byte array with monochrome bitmap
*    @param    w   Width of bitmap in pixels
*    @param    h   Hieght of bitmap in pixels
*    @param    color 16-bit 5-6-5 Color to draw pixels with
*/
/**************************************************************************/
void `$INSTANCE_NAME`_DrawXBitmap(ILI9341 *ili9341, int16_t x, int16_t y,
  const uint8_t bitmap[], int16_t w, int16_t h, uint16_t color) {

    int16_t byteWidth = (w + 7) / 8; // Bitmap scanline pad = whole byte
    uint8_t byte = 0;

    `$INSTANCE_NAME`_StartWrite();
    for(int16_t j=0; j<h; j++, y++) {
        for(int16_t i=0; i<w; i++ ) {
            if(i & 7) byte >>= 1;
            else      byte   = pgm_read_byte(&bitmap[j * byteWidth + i / 8]);
            // Nearly identical to drawBitmap(), only the bit order
            // is reversed here (left-to-right = LSB to MSB):
            if(byte & 0x01) `$INSTANCE_NAME`_WritePixel(ili9341, x+i, y, color);
        }
    }
    `$INSTANCE_NAME`_EndWrite();
}

/**************************************************************************/
/*!
*   @brief   Draw a PROGMEM-resident 8-bit image (grayscale) at the specified (x,y) pos.  
*   Specifically for 8-bit display devices such as IS31FL3731; no color reduction/expansion is performed.
*    @param    x   Top left corner x coordinate
*    @param    y   Top left corner y coordinate
*    @param    bitmap  byte array with grayscale bitmap
*    @param    w   Width of bitmap in pixels
*    @param    h   Hieght of bitmap in pixels
*/
/**************************************************************************/
void `$INSTANCE_NAME`_DrawGrayscaleBitmapConstNoMask(ILI9341 *ili9341, int16_t x, int16_t y,
  const uint8_t bitmap[], int16_t w, int16_t h) {
    `$INSTANCE_NAME`_StartWrite();
    for(int16_t j=0; j<h; j++, y++) {
        for(int16_t i=0; i<w; i++ ) {
            `$INSTANCE_NAME`_WritePixel(ili9341, x+i, y, 
                (uint8_t)pgm_read_byte(&bitmap[j * w + i]));
        }
    }
    `$INSTANCE_NAME`_EndWrite();
}

/**************************************************************************/
/*!
   @brief   Draw a RAM-resident 8-bit image (grayscale) at the specified (x,y) pos.  
   Specifically for 8-bit display devices such as IS31FL3731; no color reduction/expansion is performed.
    @param    x   Top left corner x coordinate
    @param    y   Top left corner y coordinate
    @param    bitmap  byte array with grayscale bitmap
    @param    w   Width of bitmap in pixels
    @param    h   Hieght of bitmap in pixels
*/
/**************************************************************************/
void `$INSTANCE_NAME`_DrawGrayscaleBitmapNoMask(ILI9341 *ili9341, int16_t x, int16_t y,
  uint8_t *bitmap, int16_t w, int16_t h) {
    `$INSTANCE_NAME`_StartWrite();
    for(int16_t j=0; j<h; j++, y++) {
        for(int16_t i=0; i<w; i++ ) {
            `$INSTANCE_NAME`_WritePixel(ili9341, x+i, y, bitmap[j * w + i]);
        }
    }
    `$INSTANCE_NAME`_EndWrite();
}


/**************************************************************************/
/*!
   @brief   Draw a PROGMEM-resident 8-bit image (grayscale) with a 1-bit mask
   (set bits = opaque, unset bits = clear) at the specified (x,y) position.
   BOTH buffers (grayscale and mask) must be PROGMEM-resident.
   Specifically for 8-bit display devices such as IS31FL3731; no color reduction/expansion is performed.
    @param    x   Top left corner x coordinate
    @param    y   Top left corner y coordinate
    @param    bitmap  byte array with grayscale bitmap
    @param    mask  byte array with mask bitmap
    @param    w   Width of bitmap in pixels
    @param    h   Height of bitmap in pixels
*/
/**************************************************************************/
void `$INSTANCE_NAME`_DrawGrayscaleBitmapConstMask(ILI9341 *ili9341, int16_t x, int16_t y,
  const uint8_t bitmap[], const uint8_t mask[],
  int16_t w, int16_t h) {
    int16_t bw   = (w + 7) / 8; // Bitmask scanline pad = whole byte
    uint8_t byte = 0;
    `$INSTANCE_NAME`_StartWrite();
    for(int16_t j=0; j<h; j++, y++) {
        for(int16_t i=0; i<w; i++ ) {
            if(i & 7) byte <<= 1;
            else      byte   = pgm_read_byte(&mask[j * bw + i / 8]);
            if(byte & 0x80) {
                `$INSTANCE_NAME`_WritePixel(ili9341, x+i, y, (uint8_t)pgm_read_byte(&bitmap[j * w + i]));
            }
        }
    }
    `$INSTANCE_NAME`_EndWrite();
}

/**************************************************************************/
/*!
   @brief   Draw a RAM-resident 8-bit image (grayscale) with a 1-bit mask
   (set bits = opaque, unset bits = clear) at the specified (x,y) position.
   BOTH buffers (grayscale and mask) must be RAM-residentt, no mix-and-match
   Specifically for 8-bit display devices such as IS31FL3731; no color reduction/expansion is performed.
    @param    x   Top left corner x coordinate
    @param    y   Top left corner y coordinate
    @param    bitmap  byte array with grayscale bitmap
    @param    mask  byte array with mask bitmap
    @param    w   Width of bitmap in pixels
    @param    h   Height of bitmap in pixels
*/
/**************************************************************************/
void `$INSTANCE_NAME`_DrawGrayscaleBitmapMask(ILI9341 *ili9341, int16_t x, int16_t y,
  uint8_t *bitmap, uint8_t *mask, int16_t w, int16_t h) {
    int16_t bw   = (w + 7) / 8; // Bitmask scanline pad = whole byte
    uint8_t byte = 0;
    `$INSTANCE_NAME`_StartWrite();
    for(int16_t j=0; j<h; j++, y++) {
        for(int16_t i=0; i<w; i++ ) {
            if(i & 7) byte <<= 1;
            else      byte   = mask[j * bw + i / 8];
            if(byte & 0x80) {
                `$INSTANCE_NAME`_WritePixel(ili9341, x+i, y, bitmap[j * w + i]);
            }
        }
    }
    `$INSTANCE_NAME`_EndWrite();
}

// TEXT- AND CHARACTER-HANDLING FUNCTIONS ----------------------------------

// Draw a character
/**************************************************************************/
/*!
*   @brief   Draw a single character
*    @param    x   Bottom left corner x coordinate
*    @param    y   Bottom left corner y coordinate
*    @param    c   The 8-bit font-indexed character (likely ascii)
*    @param    color 16-bit 5-6-5 Color to draw chraracter with
*    @param    bg 16-bit 5-6-5 Color to fill background with (if same as color, no background)
*    @param    size  Font magnification level, 1 is 'original' size
*/
/**************************************************************************/
void `$INSTANCE_NAME`_DrawChar(ILI9341 *ili9341, int16_t x, int16_t y, unsigned char c,
  uint16_t color, uint16_t bg, uint8_t size) {

    if(!ili9341->gfxFont) { // 'Classic' built-in font

        if((x >= ili9341->width)            || // Clip right
           (y >= ili9341->height)           || // Clip bottom
           ((x + 6 * size - 1) < 0) || // Clip left
           ((y + 8 * size - 1) < 0))   // Clip top
            return;

        if(!ili9341->cp437 && (c >= 176)) c++; // Handle 'classic' charset behavior

        `$INSTANCE_NAME`_StartWrite();
        for(int8_t i=0; i<5; i++ ) { // Char bitmap = 5 columns
            uint8_t line = pgm_read_byte(&font[c * 5 + i]);
            for(int8_t j=0; j<8; j++, line >>= 1) {
                if(line & 1) {
                    if(size == 1)
                        `$INSTANCE_NAME`_WritePixel(ili9341, x+i, y+j, color);
                    else
                        `$INSTANCE_NAME`_WriteFillRect(ili9341, x+i*size, y+j*size, size, size, color);
                } else if(bg != color) {
                    if(size == 1)
                        `$INSTANCE_NAME`_WritePixel(ili9341, x+i, y+j, bg);
                    else
                        `$INSTANCE_NAME`_WriteFillRect(ili9341, x+i*size,
                            y+j*size, size, size, bg);
                }
            }
        }
        if(bg != color) { // If opaque, draw vertical line for last column
            if(size == 1) `$INSTANCE_NAME`_WriteFastVLine(ili9341, x+5, y, 8, bg);
            else          `$INSTANCE_NAME`_WriteFillRect(ili9341, x+5*size, y, size, 8*size, bg);
        }
        `$INSTANCE_NAME`_EndWrite();

    } else { // Custom font

        // Character is assumed previously filtered by write() to eliminate
        // newlines, returns, non-printable characters, etc.  Calling
        // drawChar() directly with 'bad' characters of font may cause mayhem!

        c -= (uint8_t)pgm_read_byte(&ili9341->gfxFont->first);
        GFXglyph *glyph  = &(((GFXglyph *)pgm_read_pointer(&ili9341->gfxFont->glyph))[c]);
        uint8_t  *bitmap = (uint8_t *)pgm_read_pointer(&ili9341->gfxFont->bitmap);

        uint16_t bo = pgm_read_word(&glyph->bitmapOffset);
        uint8_t  w  = pgm_read_byte(&glyph->width),
                 h  = pgm_read_byte(&glyph->height);
        int8_t   xo = pgm_read_byte(&glyph->xOffset),
                 yo = pgm_read_byte(&glyph->yOffset);
        uint8_t  xx, yy, bits = 0, bit = 0;
        int16_t  xo16 = 0, yo16 = 0;

        if(size > 1) {
            xo16 = xo;
            yo16 = yo;
        }

        // Todo: Add character clipping here

        // NOTE: THERE IS NO 'BACKGROUND' COLOR OPTION ON CUSTOM FONTS.
        // THIS IS ON PURPOSE AND BY DESIGN.  The background color feature
        // has typically been used with the 'classic' font to overwrite old
        // screen contents with new data.  This ONLY works because the
        // characters are a uniform size; it's not a sensible thing to do with
        // proportionally-spaced fonts with glyphs of varying sizes (and that
        // may overlap).  To replace previously-drawn text when using a custom
        // font, use the getTextBounds() function to determine the smallest
        // rectangle encompassing a string, erase the area with fillRect(),
        // then draw new text.  This WILL infortunately 'blink' the text, but
        // is unavoidable.  Drawing 'background' pixels will NOT fix this,
        // only creates a new set of problems.  Have an idea to work around
        // this (a canvas object type for MCUs that can afford the RAM and
        // displays supporting setAddrWindow() and pushColors()), but haven't
        // implemented this yet.

        `$INSTANCE_NAME`_StartWrite();
        for(yy=0; yy<h; yy++) {
            for(xx=0; xx<w; xx++) {
                if(!(bit++ & 7)) {
                    bits = pgm_read_byte(&bitmap[bo++]);
                }
                if(bits & 0x80) {
                    if(size == 1) {
                        `$INSTANCE_NAME`_WritePixel(ili9341, x+xo+xx, y+yo+yy, color);
                    } else {
                        `$INSTANCE_NAME`_WriteFillRect(ili9341, x+(xo16+xx)*size, y+(yo16+yy)*size,
                          size, size, color);
                    }
                }
                bits <<= 1;
            }
        }
        `$INSTANCE_NAME`_EndWrite();

    } // End classic vs custom font
}

/**************************************************************************/
/*!
    @brief  Print one byte/character of data, used to support print()
    @param  c  The 8-bit ascii character to write
*/
/**************************************************************************/
size_t `$INSTANCE_NAME`_Write(ILI9341 *ili9341, uint8_t c) {
    if(!ili9341->gfxFont) { // 'Classic' built-in font

        if(c == '\n') {                        // Newline?
            ili9341->cursor_x  = 0;                     // Reset x to zero,
            ili9341->cursor_y += ili9341->textsize * 8;          // advance y one line
        } else if(c != '\r') {                 // Ignore carriage returns
            if(ili9341->wrap && ((ili9341->cursor_x + ili9341->textsize * 6) 
            > ili9341->width)) { // Off right?
                ili9341->cursor_x  = 0;                 // Reset x to zero,
                ili9341->cursor_y += ili9341->textsize * 8;      // advance y one line
            }
            `$INSTANCE_NAME`_DrawChar(ili9341, ili9341->cursor_x, ili9341->cursor_y, c, 
                ili9341->textcolor, ili9341->textbgcolor, ili9341->textsize);
            ili9341->cursor_x += ili9341->textsize * 6;          // Advance x one char
        }

    } else { // Custom font

        if(c == '\n') {
            ili9341->cursor_x  = 0;
            ili9341->cursor_y += (int16_t)ili9341->textsize *
                        (uint8_t)pgm_read_byte(&ili9341->gfxFont->yAdvance);
        } else if(c != '\r') {
            uint8_t first = pgm_read_byte(&ili9341->gfxFont->first);
            if((c >= first) && (c <= (uint8_t)pgm_read_byte(&ili9341->gfxFont->last))) {
                GFXglyph *glyph = &(((GFXglyph *)pgm_read_pointer(
                  &ili9341->gfxFont->glyph))[c - first]);
                uint8_t   w     = pgm_read_byte(&glyph->width),
                          h     = pgm_read_byte(&glyph->height);
                if((w > 0) && (h > 0)) { // Is there an associated bitmap?
                    int16_t xo = (int8_t)pgm_read_byte(&glyph->xOffset); // sic
                    if(ili9341->wrap && ((ili9341->cursor_x + ili9341->textsize * (xo + w)) > ili9341->width)) {
                        ili9341->cursor_x  = 0;
                        ili9341->cursor_y += (int16_t)ili9341->textsize *
                          (uint8_t)pgm_read_byte(&ili9341->gfxFont->yAdvance);
                    }
                    `$INSTANCE_NAME`_DrawChar(ili9341,ili9341->cursor_x, ili9341->cursor_y,
                        c, ili9341->textcolor, ili9341->textbgcolor, ili9341->textsize);
                }
                ili9341->cursor_x += (uint8_t)pgm_read_byte(&glyph->xAdvance) * (int16_t)ili9341->textsize;
            }
        }
    }
    return 1;
}

size_t `$INSTANCE_NAME`_WriteString(ILI9341 *ili9341, const uint8_t *buffer, size_t size) {
    size_t n = 0;
    while (size--){
        size_t ret = `$INSTANCE_NAME`_Write(ili9341,*buffer++);
        if (ret == 0) {
            break;   
        }
        n += ret;
    }
    return n;
}

/**************************************************************************/
/*!
*    @brief  Print a string
*    @param  ili9341    ILI9341 struct
*    @param  str        string to be printed
*/
/**************************************************************************/
size_t `$INSTANCE_NAME`_Print(ILI9341 *ili9341, const char str[]) {
    return `$INSTANCE_NAME`_WriteString(ili9341, (const uint8_t *)str, strlen(str));
}

/**************************************************************************/
/*!
*    @brief  Print a string adding a new line char at the end
*    @param  ili9341    ILI9341 struct
*    @param  str        string to be printed
*/
/**************************************************************************/
size_t `$INSTANCE_NAME`_Println(ILI9341 *ili9341, const char str[]) {
     return `$INSTANCE_NAME`_Print(ili9341, str) +
                `$INSTANCE_NAME`_Print(ili9341, "\r\n");
}

/**************************************************************************/
/*!
*    @brief  Print single 
*    @param  ili9341    ILI9341 struct
*    @param  c          char to be printed
*/
/**************************************************************************/
size_t `$INSTANCE_NAME`_PrintChar(ILI9341 *ili9341, char c) {
    return `$INSTANCE_NAME`_Write(ili9341, c);   
}

/**************************************************************************/
/*!
*    @brief  Print single char adding a new line char
*    @param  ili9341    ILI9341 struct
*    @param  c          char to be printed
*/
/**************************************************************************/
size_t `$INSTANCE_NAME`_PrintlnChar(ILI9341 *ili9341, char c) {
    return `$INSTANCE_NAME`_Write(ili9341, c) +
            `$INSTANCE_NAME`_Print(ili9341, "\r\n");   
}

/**************************************************************************/
/*!
*    @brief  Set text cursor location
*    @param  x    X coordinate in pixels
*    @param  y    Y coordinate in pixels
*/
/**************************************************************************/
void `$INSTANCE_NAME`_SetCursor(ILI9341 *ili9341, int16_t x, int16_t y) {
    ili9341->cursor_x = x;
    ili9341->cursor_y = y;
}

/**************************************************************************/
/*!
*    @brief  Get text cursor X location
*    @returns    X coordinate in pixels
*/
/**************************************************************************/
int16_t `$INSTANCE_NAME`_GetCursorX(ILI9341 *ili9341) {
    return ili9341->cursor_x;
}

/**************************************************************************/
/*!
    @brief      Get text cursor Y location
    @returns    Y coordinate in pixels
*/
/**************************************************************************/
int16_t `$INSTANCE_NAME`_GetCursorY(ILI9341 *ili9341) {
    return ili9341->cursor_y;
}

/**************************************************************************/
/*!
*    @brief   Set text 'magnification' size. 
*
*    Each increase in s makes 1 pixel that much bigger.
*    @param  s  Desired text size. 1 is default 6x8, 2 is 12x16, 3 is 18x24, etc
*/
/**************************************************************************/
void `$INSTANCE_NAME`_SetTextSize(ILI9341 *ili9341, uint8_t s) {
    ili9341->textsize = (s > 0) ? s : 1;
}

/**************************************************************************/
/*!
*    @brief      Get rotation setting for display
*    @returns    0 thru 3 corresponding to 4 cardinal rotations
*/
/**************************************************************************/
uint8_t `$INSTANCE_NAME`_GetRotation(ILI9341 *ili9341) {
    return ili9341->rotation;
}

/**************************************************************************/
/*!
*    @brief Enable (or disable) Code Page 437-compatible charset.
*    There was an error in glcdfont.c for the longest time -- one character
*    (#176, the 'light shade' block) was missing -- this threw off the index
*    of every character that followed it.  But a TON of code has been written
*    with the erroneous character indices.  By default, the library uses the
*    original 'wrong' behavior and old sketches will still work.  Pass 'true'
*    to this function to use correct CP437 character values in your code.
*    @param  x  Whether to enable (True) or not (False)
*/
/**************************************************************************/
void `$INSTANCE_NAME`_Cp437(ILI9341 *ili9341, uint8_t x) {
    ili9341->cp437 = x;
}

/**************************************************************************/
/*!
*    @brief Set the font to display when print()ing, either custom or default
*    @param  f  The GFXfont object, if NULL use built in 6x8 font
*/
/**************************************************************************/
void `$INSTANCE_NAME`_SetFont(ILI9341 *ili9341, const GFXfont *f) {
    if(f) {            // Font struct pointer passed in?
        if(!ili9341->gfxFont) { // And no current font struct?
            // Switching from classic to new font behavior.
            // Move cursor pos down 6 pixels so it's on baseline.
            ili9341->cursor_y += 6;
        }
    } else if(ili9341->gfxFont) { // NULL passed.  Current font struct defined?
        // Switching from new to classic font behavior.
        // Move cursor pos up 6 pixels so it's at top-left of char.
        ili9341->cursor_y -= 6;
    }
    ili9341->gfxFont = (GFXfont *)f;
}

/**************************************************************************/
/*!
*    @brief    Helper to determine size of a character with current font/size.
*       Broke this out as it's used by both the PROGMEM- and RAM-resident getTextBounds() functions.
*    @param    c     The ascii character in question
*    @param    x     Pointer to x location of character
*    @param    y     Pointer to y location of character
*    @param    minx  Minimum clipping value for X
*    @param    miny  Minimum clipping value for Y
*    @param    maxx  Maximum clipping value for X
*    @param    maxy  Maximum clipping value for Y
*/
/**************************************************************************/
void `$INSTANCE_NAME`_CharBounds(ILI9341 *ili9341, char c, int16_t *x, int16_t *y,
  int16_t *minx, int16_t *miny, int16_t *maxx, int16_t *maxy) {

    if(ili9341->gfxFont) {

        if(c == '\n') { // Newline?
            *x  = 0;    // Reset x to zero, advance y by one line
            *y += ili9341->textsize * (uint8_t)pgm_read_byte(&ili9341->gfxFont->yAdvance);
        } else if(c != '\r') { // Not a carriage return; is normal char
            uint8_t first = pgm_read_byte(&ili9341->gfxFont->first),
                    last  = pgm_read_byte(&ili9341->gfxFont->last);
            if((c >= first) && (c <= last)) { // Char present in this font?
                GFXglyph *glyph = &(((GFXglyph *)pgm_read_pointer(
                  &ili9341->gfxFont->glyph))[c - first]);
                uint8_t gw = pgm_read_byte(&glyph->width),
                        gh = pgm_read_byte(&glyph->height),
                        xa = pgm_read_byte(&glyph->xAdvance);
                int8_t  xo = pgm_read_byte(&glyph->xOffset),
                        yo = pgm_read_byte(&glyph->yOffset);
                if(ili9341->wrap && ((*x+(((int16_t)xo+gw)*ili9341->textsize)) > ili9341->width)) {
                    *x  = 0; // Reset x to zero, advance y by one line
                    *y += ili9341->textsize * (uint8_t)pgm_read_byte(&ili9341->gfxFont->yAdvance);
                }
                int16_t ts = (int16_t)ili9341->textsize,
                        x1 = *x + xo * ts,
                        y1 = *y + yo * ts,
                        x2 = x1 + gw * ts - 1,
                        y2 = y1 + gh * ts - 1;
                if(x1 < *minx) *minx = x1;
                if(y1 < *miny) *miny = y1;
                if(x2 > *maxx) *maxx = x2;
                if(y2 > *maxy) *maxy = y2;
                *x += xa * ts;
            }
        }

    } else { // Default font

        if(c == '\n') {                     // Newline?
            *x  = 0;                        // Reset x to zero,
            *y += ili9341->textsize * 8;             // advance y one line
            // min/max x/y unchaged -- that waits for next 'normal' character
        } else if(c != '\r') {  // Normal char; ignore carriage returns
            if(ili9341->wrap && ((*x + ili9341->textsize * 6) > ili9341->width)) { // Off right?
                *x  = 0;                    // Reset x to zero,
                *y += ili9341->textsize * 8;         // advance y one line
            }
            int x2 = *x + ili9341->textsize * 6 - 1, // Lower-right pixel of char
                y2 = *y + ili9341->textsize * 8 - 1;
            if(x2 > *maxx) *maxx = x2;      // Track max x, y
            if(y2 > *maxy) *maxy = y2;
            if(*x < *minx) *minx = *x;      // Track min x, y
            if(*y < *miny) *miny = *y;
            *x += ili9341->textsize * 6;             // Advance x one char
        }
    }
}

/**************************************************************************/
/*!
*    @brief    Helper to determine size of a string with current font/size. Pass string and a cursor position, returns UL corner and W,H.
*    @param    str     The ascii string to measure
*    @param    x       The current cursor X
*    @param    y       The current cursor Y
*    @param    x1      The boundary X coordinate, set by function
*    @param    y1      The boundary Y coordinate, set by function
*    @param    w      The boundary width, set by function
*    @param    h      The boundary height, set by function
*/
/**************************************************************************/
void `$INSTANCE_NAME`_GetTextBounds(ILI9341 *ili9341, char *str, int16_t x, int16_t y,
        int16_t *x1, int16_t *y1, uint16_t *w, uint16_t *h) {
    uint8_t c; // Current character

    *x1 = x;
    *y1 = y;
    *w  = *h = 0;

    int16_t minx = ili9341->width, miny = ili9341->height, maxx = -1, maxy = -1;

    while((c = *str++))
        `$INSTANCE_NAME`_CharBounds(ili9341, c, &x, &y, &minx, &miny, &maxx, &maxy);

    if(maxx >= minx) {
        *x1 = minx;
        *w  = maxx - minx + 1;
    }
    if(maxy >= miny) {
        *y1 = miny;
        *h  = maxy - miny + 1;
    }
}


/* [] END OF FILE */
