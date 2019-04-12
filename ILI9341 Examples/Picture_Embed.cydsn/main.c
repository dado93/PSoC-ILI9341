/**
* @brief Main program for ILI9341 graphics test.
* 
* @author Davide Marzorati
* @date April 12, 2019
*/
#include "project.h"
#include "dragon.h"

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    ILI9341 ili9341;
    SPIM_1_Start();
    UART_1_Start();
    UART_1_PutString("ILI9341 Test!\r\n");
    
    ILI9341_Start(&ili9341);
    ILI9341_SetRotation(&ili9341, 3);
 
    for(;;)
    {
        /* Place your application code here. */
        for(uint8_t r=0; r<4; r++) {
            ILI9341_SetRotation(&ili9341, r);
            ILI9341_FillScreen(&ili9341,ILI9341_BLACK);
            for(uint8_t j=1; j<20; j++) {
                ILI9341_DrawRGBBitmap(
                    &ili9341,
                    20 + j * (r + 3), // just some "randomness" - it will always be the same
                    40 + ( r + 2 ) * (j + 4), // just some "randomness" - it will always be the same
                    (uint16_t *)dragonBitmap,
                    DRAGON_WIDTH, DRAGON_HEIGHT);
                CyDelay(1); // Allow ESP8266 to handle watchdog & WiFi stuff
            }
            CyDelay(3000);
        }
    }
    
    for(;;)
    {
        /* Place your application code here. */
    }
}



/* [] END OF FILE */
