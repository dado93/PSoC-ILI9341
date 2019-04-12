/**
* @brief Main program for ILI9341 graphics test.
* 
* @author Davide Marzorati
* @date April 12, 2019
*/
#include "project.h"
#include "ILI9341_Helper.h"


int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    ILI9341 ili9341;
    // Start the SPI Master component
    SPIM_1_Start();
    CyDelay(500);
    
    // Start the display and change default orientation
    ILI9341_Start(&ili9341);
    ILI9341_SetRotation(&ili9341, 3);

    // Test fill screen
    ILI9341_TestFillScreen(&ili9341);
    CyDelay(500);
    
    // Test lines
    ILI9341_TestLines(&ili9341,ILI9341_CYAN);
    CyDelay(500);
    
    // Test lines - fast mode
    ILI9341_TestFastLines(&ili9341, ILI9341_RED, ILI9341_BLUE);
    CyDelay(500);
    
    // Test rectangles
    ILI9341_TestRects(&ili9341, ILI9341_GREEN);
    CyDelay(500);
    
    // Test filled rectangles
    ILI9341_TestFilledRects(&ili9341, ILI9341_YELLOW, ILI9341_MAGENTA);
    CyDelay(500);
    
    // Test filled circles
    ILI9341_TestFilledCircles(&ili9341, 10, ILI9341_MAGENTA);
    CyDelay(500);
    
    // Test circles
    ILI9341_TestCircles(&ili9341, 10, ILI9341_WHITE);
    CyDelay(500);
    
    // Test triangles
    ILI9341_TestTriangles(&ili9341);
    CyDelay(500);
    
    // Test filled triangles
    ILI9341_TestFilledTriangles(&ili9341);
    CyDelay(500);
    
    // Test rounded rects
    ILI9341_TestRoundRects(&ili9341);
    CyDelay(500);
    
    // Test filled round rects
    ILI9341_TestFilledRoundRects(&ili9341);
    CyDelay(500);
    
    for(;;)
    {
        /* Place your application code here. */
    }
}



/* [] END OF FILE */
