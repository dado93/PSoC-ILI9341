# PSoC ILI9341 Custom Component
This repository contains a PSoC Creator Library Project featuring a 
[ILI9341](https://www.adafruit.com/product/1770)
Custom Component. This work is based on the on the
[Adafruit ILI9341 library](https://github.com/adafruit/Adafruit_ILI9341) and on the [Adafruit GFX library](https://github.com/adafruit/Adafruit-GFX-Library). 

## Adafruit ILI9341
The Sensirion SHT7x sensors is a temperature and humidity sensor. According to Sensirion description, the SHTx sensor is
*a digital pin-type relative humidity sensor for easy replaceability in a wide range of applications. 
The series consists of a standard version, SHT71, which convinces with its attractive price-performance ratio, 
and a high-end version, SHT75.*

## PSoC Custom Component
![alt text](https://i.imgur.com/PtuBFDf.png, "ILI9341 Custom Component")

The PSoC Custom component features all the useful methods to interface a PSoC board with a ILI9341 based TFT display. To date, 
the component was tested with a [PSoC 5LP Development Kit](http://www.cypress.com/documentation/development-kitsboards/cy8ckit-059-psoc-5lp-prototyping-kit-onboard-programmer-and). 
The component requires the presence, on the schematic, of an SPI Component to work.
