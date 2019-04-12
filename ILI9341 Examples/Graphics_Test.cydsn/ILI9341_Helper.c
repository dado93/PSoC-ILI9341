
#include "ILI9341_Helper.h"

#ifndef min
    #define min(a,b) (((a) < (b)) ? (a) : (b))
#endif

void ILI9341_TestFillScreen(ILI9341 *ili9341) {
    // Fill screen with different colors
    ILI9341_FillScreen(ili9341, ILI9341_BLACK);
    ILI9341_FillScreen(ili9341, ILI9341_RED);
    ILI9341_FillScreen(ili9341, ILI9341_GREEN);
    ILI9341_FillScreen(ili9341, ILI9341_BLUE);
    ILI9341_FillScreen(ili9341, ILI9341_BLACK);
}

void ILI9341_TestLines(ILI9341 *ili9341, uint16_t color) {
    // Test line showing in normal mode
    int x1, y1, x2, y2;       // Coordinates
    int w = ili9341->width,   // Screen width
        h = ili9341->height;  // Screen height
    
    // fill screen with black
    ILI9341_FillScreen(ili9341, ILI9341_BLACK);
    
    // Draw lines 
    x1 = y1 = 0;
    y2 = h - 1;
    for(x2=0; x2<w; x2+=6)
        ILI9341_DrawLine(ili9341, x1, y1, x2, y2, color);
  
    x2 = w - 1;
    for(y2=0; y2<h; y2+=6)
        ILI9341_DrawLine(ili9341,x1, y1, x2, y2, color);
        
    // Fill screen again
    ILI9341_FillScreen(ili9341, ILI9341_BLACK);
    x1  = w - 1;
    y1  = 0;
    y2  = h - 1;

    // Draw lines
    for(x2=0; x2<w; x2+=6)
        ILI9341_DrawLine(ili9341, x1, y1, x2, y2, color);
    x2 = 0;
    for(y2=0; y2<h; y2+=6)
        ILI9341_DrawLine(ili9341, x1, y1, x2, y2, color);
    // Fill screen again
    ILI9341_FillScreen(ili9341,ILI9341_BLACK);
    
    // Reset coordinates
    x1    = 0;
    y1    = h - 1;
    y2    = 0;
    // Draw lines
    for(x2=0; x2<w; x2+=6) {
        ILI9341_DrawLine(ili9341,x1, y1, x2, y2, color);   
    }
    
    x2    = w - 1;
    for(y2=0; y2<h; y2+=6) {
        ILI9341_DrawLine(ili9341,x1, y1, x2, y2, color);
    }
    // Fill screen again
    ILI9341_FillScreen(ili9341,ILI9341_BLACK);

    x1    = w - 1;
    y1    = h - 1;
    y2    = 0;
    // Draw lines
    for(x2=0; x2<w; x2+=6) {
        ILI9341_DrawLine(ili9341,x1, y1, x2, y2, color);
    }
    x2    = 0;
    for(y2=0; y2<h; y2+=6) {
        ILI9341_DrawLine(ili9341,x1, y1, x2, y2, color);
    }
}

void ILI9341_TestFastLines(ILI9341 *ili9341, uint16_t color1, uint16_t color2) {
    // Test line drawing in fast mode
    int x, y, w = ili9341->width, h = ili9341->height;

    ILI9341_FillScreen(ili9341, ILI9341_BLACK);
    for(y=0; y<h; y+=5) 
        ILI9341_DrawFastHLine(ili9341, 0, y, w, color1);
    for(x=0; x<w; x+=5) 
        ILI9341_DrawFastVLine(ili9341, x, 0, h, color2);
}

void ILI9341_TestRects(ILI9341 *ili9341, uint16_t color) {
    // Test rectangles drawing
    int n, i, i2,
        cx = ili9341->width  / 2,
        cy = ili9341->height / 2;

    ILI9341_FillScreen(ili9341, ILI9341_BLACK);
    n = min(ili9341->width, ili9341->height);
    for(i=2; i<n; i+=6) {
        i2 = i / 2;
        ILI9341_DrawRect(ili9341, cx-i2, cy-i2, i, i, color);
    }
}

void ILI9341_TestFilledRects(ILI9341 *ili9341, uint16_t color1, uint16_t color2) {
    // Test filled rectangles drawing
    int n, i, i2,
        cx = ili9341->width  / 2 - 1,
        cy = ili9341->height / 2 - 1;

    ILI9341_FillScreen(ili9341, ILI9341_BLACK);
    n = min(ili9341->width , ili9341->height);
    for(i=n; i>0; i-=6) {
        i2    = i / 2;
        ILI9341_FillRect(ili9341,cx-i2, cy-i2, i, i, color1);
        ILI9341_DrawRect(ili9341,cx-i2, cy-i2, i, i, color2);
    }

}

void ILI9341_TestFilledCircles(ILI9341 *ili9341, uint8_t radius, uint16_t color) {
    // Test filled circles
    int x, y, w = ili9341->width, h = ili9341->height, r2 = radius * 2;

    ILI9341_FillScreen(ili9341, ILI9341_BLACK);
    for(x=radius; x<w; x+=r2) {
        for(y=radius; y<h; y+=r2) {
        ILI9341_FillCircle(ili9341, x, y, radius, color);
        }
    }
}

void ILI9341_TestCircles(ILI9341 *ili9341, uint8_t radius, uint16_t color) {
    // Test circles
    int x, y, r2 = radius * 2,
        w = ili9341->width  + radius,
        h = ili9341->height + radius;
    for(x=0; x<w; x+=r2) {
        for(y=0; y<h; y+=r2) {
        ILI9341_DrawCircle(ili9341, x, y, radius, color);
        }
    }
}

void ILI9341_TestTriangles(ILI9341 *ili9341) {
    // Test triangles
    int n, i, 
        cx = ili9341->width  / 2 - 1,
        cy = ili9341->height / 2 - 1;

    ILI9341_FillScreen(ili9341, ILI9341_BLACK);
    n = min(cx, cy);

    for(i=0; i<n; i+=5) {
        ILI9341_DrawTriangle(ili9341,
        cx    , cy - i, // peak
        cx - i, cy + i, // bottom left
        cx + i, cy + i, // bottom right
        ILI9341_Color565(i, i, i));
    }
}

void ILI9341_TestFilledTriangles(ILI9341 *ili9341) {
    // Test filled triangles
    int i,
        cx = ili9341->width  / 2 - 1,
        cy = ili9341->height / 2 - 1;

  ILI9341_FillScreen(ili9341, ILI9341_BLACK);
  for(i=min(cx,cy); i>10; i-=5) {
    ILI9341_FillTriangle(ili9341, cx, cy - i, cx - i, cy + i, cx + i, cy + i,
    ILI9341_Color565(0, i*10, i*10));
    ILI9341_DrawTriangle(ili9341, cx, cy - i, cx - i, cy + i, cx + i, cy + i,
    ILI9341_Color565(i*10, i*10, 0));
  }
}

void ILI9341_TestRoundRects(ILI9341 *ili9341) {
    // Test round rectangles
    int w, i, i2,
        cx = ili9341->width  / 2 - 1,
        cy = ili9341->height / 2 - 1;

    ILI9341_FillScreen(ili9341, ILI9341_BLACK);
    w = min(ili9341->width, ili9341->height);
    for(i=0; i<w; i+=6) {
        i2 = i / 2;
        ILI9341_DrawRoundRect(ili9341, cx-i2, cy-i2, i, i, i/8, ILI9341_Color565(i, 0, 0));
    }
}

void ILI9341_TestFilledRoundRects(ILI9341 *ili9341) {
    // Test filled round rectangles
    int i, i2,
        cx = ili9341->width  / 2 - 1,
        cy = ili9341->height / 2 - 1;

    ILI9341_FillScreen(ili9341, ILI9341_BLACK);

    for(i=min(ili9341->width, ili9341->height); i>20; i-=6) {
        i2 = i / 2;
        ILI9341_FillRoundRect(ili9341, cx-i2, cy-i2, i, i, i/8, ILI9341_Color565(0, i, 0));
    }
}

/* [] END OF FILE */
