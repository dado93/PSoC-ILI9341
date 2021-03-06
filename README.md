# PSoC ILI9341 Custom Component
This repository contains a PSoC Creator Library Project featuring a 
[ILI9341](https://www.adafruit.com/product/1770)
Custom Component. This work is based on the on the
[Adafruit ILI9341 library](https://github.com/adafruit/Adafruit_ILI9341) and on the [Adafruit GFX library](https://github.com/adafruit/Adafruit-GFX-Library). 

## Adafruit ILI9341
2.8" TFT LCD with Touchscreen Breakout Board w/MicroSD Socket - [ILI9341](https://www.adafruit.com/product/1770), This LCD display is 2.8" TFT display with resistive/capacitive touchscreen. The display has a resolution of 240x320 pixels with individual RGB pixel control.

## PSoC Custom Component
![alt text](https://i.imgur.com/PtuBFDf.png, "ILI9341 Custom Component")

The PSoC Custom component features all the useful methods to interface a PSoC board with a ILI9341 based TFT display. To date, 
the component was tested with a [PSoC 5LP Development Kit](http://www.cypress.com/documentation/development-kitsboards/cy8ckit-059-psoc-5lp-prototyping-kit-onboard-programmer-and). 
The component requires the presence, on the schematic, of an SPI Component to work.

## Setup
In order to be able to communicate with the display, it is necessary to connect the IM1, IM2, and IM3 pins of the display to 3.3 V. Do not connect them to 5V and remember not to connect IM0 pin.
