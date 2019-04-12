/** 
 * @file ILI9341_Helper.h
 * @brief File containing function declarations to test the ILI9341.
 * 
 * @author Davide Marzorati
*/

#ifndef __ILI9341_HELPER
    #define __ILI9341_HELPER
    
    #include "cytypes.h"
    #include "ILI9341.h"
    #include "ILI9341_GFX.h"
    
    /**
    * @brief Test fill screen on the display with several colors.
    * @param ili9341 ILI9341 object.
    */
    void ILI9341_TestFillScreen(ILI9341 *ili9341);
    
    /**
    * @brief Test lines on the display. Normal mode.
    * @param ili9341: ILI9341 object.
    * @param color: color of the lines
    */
    void ILI9341_TestLines(ILI9341 *ili9341,uint16_t color);
    
    /**
    * @brief Test lines on the display. Fast mode.
    * @param ili9341: ILI9341 object.
    * @param color1: color of first lines
    * @param color2: color of second lines
    */
    void ILI9341_TestFastLines(ILI9341 *ili9341,
                               uint16_t color1,
                               uint16_t color2);
    
    /**
    * @brief Test rectangles on the display.
    * @param ili9341: ILI9341 object.
    * @param color: color of the rectangles
    */
    void ILI9341_TestRects(ILI9341 *ili9341,uint16_t color);
    
    /**
    * @brief Test filled rectangles on the display.
    * @param ili9341: ILI9341 object.
    * @param color1: edge color
    * @param color2: fill color
    */
    void ILI9341_TestFilledRects(ILI9341 *ili9341,
                                 uint16_t color1,
                                 uint16_t color2);
    
    /**
    * @brief Test filled circles on the display.
    * @param ili9341: ILI9341 object.
    * @param radius: radius of the circles
    * @param color: color of the circles
    */
    void ILI9341_TestFilledCircles(ILI9341 *ili9341,
                                   uint8_t radius, 
                                   uint16_t color);
    
    /**
    * @brief Test cicles on the display.
    * @param ili9341: ILI9341 object.
    * @param radius: radius of the circles.
    * @param color: color of the circles
    */
    void ILI9341_TestCircles(ILI9341 *ili9341,
                             uint8_t radius, 
                             uint16_t color);
    
    /**
    * @brief Test triangles on the display.
    * @param ili9341: ILI9341 object.
    */
    void ILI9341_TestTriangles(ILI9341 *ili9341);
    
    /**
    * @brief Test filled triangles on the display.
    * @param ili9341: ILI9341 object.
    */
    void ILI9341_TestFilledTriangles(ILI9341 *ili9341);
    
    /**
    * @brief Test round rectangles on the display.
    * @param ili9341: ILI9341 object.
    */
    void ILI9341_TestRoundRects(ILI9341 *ili9341);
    
    /**
    * @brief Test filled round rectangles on the display.
    * @param ili9341: ILI9341 object.
    */
    void ILI9341_TestFilledRoundRects(ILI9341 *ili9341);

#endif

/* [] END OF FILE */
