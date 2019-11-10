# Configuration

Currently there are three configuration files

## config.h

In this file you can set pins for:

### Input

button|macro|default value
------|-----|-------------
next|PIN_NUMBER_BUTTON_NEXT|21
prev|PIN_NUMBER_BUTTON_PREV|20
enter|PIN_NUMBER_BUTTON_ENTER|18
back|PIN_NUMBER_BUTTON_BACK|19

### Output

name|macro|default value|description
----|-----|-------------|-----------
Sleep|PIN_SLEEP_MODE|2|This pin is in **HIGH** mode when sleep mode is **OFF**

## MyConfig.h

All macros for this file can be found on [MySensors website](https://mysensors.org)

## tftConfig.h

Pins setting for tft display

macro|default value
-----|-------------
TFT_CS|33
TFT_RST|6
TFT_DC|7
TFT_MOSI|31
TFT_SCK|32
