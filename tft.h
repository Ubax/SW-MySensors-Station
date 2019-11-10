/**
 * @author Jakub Tkacz
 * 
 * The MIT License
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef SW_TFT_H
#define SW_TFT_H

#define TFT_WIDTH 128
#define TFT_HEIGHT 160

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>

class Color;
class TFT;

/**
 * Container for colors
 */
class Color
{
protected:
    int R, G, B;

public:
    Color(unsigned short R, unsigned short G, unsigned short B);
    unsigned short getRed();
    unsigned short getBlue();
    unsigned short getGreen();
    unsigned short get16Bit();
};

/**
 * Implements functions for drawing on tft display
 * 
 * All width and height prameters accept relative values.
 * The relative values are negative values in percentage format e.g. 25% = -25
 */

class TFT
{
protected:
    int RST, DC, CS;
    Adafruit_ST7735 tft;

public:
    /**
     * @brief Construct a new TFT object with default SPI values
     * 
     * @param RST 
     * @param DC 
     * @param CS 
     */
    TFT(int RST, int DC, int CS);

    /**
     * @brief Construct a new TFT object
     * 
     * @param RST 
     * @param DC 
     * @param CS 
     * @param MOSI 
     * @param CLK 
     */
    TFT(int RST, int DC, int CS, int MOSI, int CLK);

    void drawText(int x, int y, String text);
    void drawText(int x, int y, String text, unsigned short size, Color color);
    void drawRect(int x, int y, int width, int height, Color borderColor);
    void drawFillRect(int x, int y, int width, int height, Color fillColor);
    void fillScreen(Color borderColor);
};

#endif
