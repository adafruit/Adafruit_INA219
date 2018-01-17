# Adafruit INA219 Library [![Build Status](https://travis-ci.org/adafruit/Adafruit_INA219.svg?branch=master)](https://travis-ci.org/adafruit/Adafruit_INA219)

<img src="https://cdn-shop.adafruit.com/970x728/904-00.jpg" height="300"/>

This is a library for the Adafruit INA219 high side DC current sensor boards:
  * https://www.adafruit.com/products/904
  * https://www.adafruit.com/product/3650
 
Check out the links above for our tutorials and wiring diagrams. This chip uses I2C to communicate

<!-- START COMPATIBILITY TABLE -->

## Compatibility

MCU                | Tested Works | Doesn't Work | Not Tested  | Notes
------------------ | :----------: | :----------: | :---------: | -----
Atmega328 @ 16MHz  |      X       |             |            | 
Atmega328 @ 12MHz  |      X       |             |            | 
Atmega32u4 @ 16MHz |      X       |             |            | 
Atmega32u4 @ 8MHz  |      X       |             |            | 
ESP8266            |      X       |             |            | 
Atmega2560 @ 16MHz |      X       |             |            | 
ATSAM3X8E          |      X       |             |            | Use D20/D21.
ATSAM21D           |      X       |             |            | 
ATtiny85 @ 16MHz   |      X       |             |            | Use SDA/SCL D0/D2
ATtiny85 @ 8MHz    |      X       |             |            | Use SDA/SCL D0/D2
Intel Curie @ 32MHz |             |             |     X       | 
STM32F2            |             |             |     X       | 

  * ATmega328 @ 16MHz : Arduino UNO, Adafruit Pro Trinket 5V, Adafruit Metro 328, Adafruit Metro Mini
  * ATmega328 @ 12MHz : Adafruit Pro Trinket 3V
  * ATmega32u4 @ 16MHz : Arduino Leonardo, Arduino Micro, Arduino Yun, Teensy 2.0
  * ATmega32u4 @ 8MHz : Adafruit Flora, Bluefruit Micro
  * ESP8266 : Adafruit Huzzah
  * ATmega2560 @ 16MHz : Arduino Mega
  * ATSAM3X8E : Arduino Due
  * ATSAM21D : Arduino Zero, M0 Pro
  * ATtiny85 @ 16MHz : Adafruit Trinket 5V
  * ATtiny85 @ 8MHz : Adafruit Gemma, Arduino Gemma, Adafruit Trinket 3V

<!-- END COMPATIBILITY TABLE -->

Adafruit invests time and resources providing this open source code, please support Adafruit and open-source hardware by purchasing products from Adafruit!

Written by Ktown for Adafruit Industries.
MIT license, all text above must be included in any redistribution
