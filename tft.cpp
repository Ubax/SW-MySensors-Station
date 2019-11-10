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

#include "tft.h"

Color::Color(unsigned short R, unsigned short G, unsigned short B)
{
    this->R = R % 256;
    this->G = G % 256;
    this->B = B % 256;
}
unsigned short Color::getRed() { return R; }
unsigned short Color::getBlue() { return B; }
unsigned short Color::getGreen() { return G; }
unsigned short Color::get16Bit()
{
    return ((R >> 3) << 11) + ((G >> 2) << 5) + (B >> 3);
}

TFT::TFT(int RST, int DC, int CS) : RST(RST), DC(DC), CS(CS), tft(CS, DC, RST)
{
    tft.initR(INITR_BLACKTAB);
    tft.fillScreen(ST7735_BLACK);
    tft.setRotation(2);
}

TFT::TFT(int RST, int DC, int CS, int MOSI, int CLK) : RST(RST), DC(DC), CS(CS), tft(CS, DC, MOSI, CLK, RST)
{
    tft.initR(INITR_BLACKTAB);
    tft.fillScreen(ST7735_BLACK);
    tft.setRotation(2);
}

void TFT::drawText(int x, int y, String text)
{
    drawText(x, y, text, 1, Color(255, 255, 255));
}

void TFT::drawText(int x, int y, String text, unsigned short size, Color color)
{
    tft.setTextSize(size);
    tft.setTextColor(color.get16Bit());
    tft.setCursor(x, y);
    tft.print(text);
}

int recalcWidth(int width)
{
    return (width < 0) ? TFT_WIDTH * ((-width) / 100.0) : width;
}

int recalcHeight(int height)
{
    return (height < 0) ? TFT_HEIGHT * ((-height) / 100.0) : height;
}

void TFT::drawRect(int x, int y, int width, int height, Color borderColor)
{
    width = recalcWidth(width);
    height = recalcHeight(height);
    tft.drawRect(x, y, width, height, borderColor.get16Bit());
}
void TFT::drawFillRect(int x, int y, int width, int height, Color fillColor)
{
    width = recalcWidth(width);
    height = recalcHeight(height);
    tft.fillRect(x, y, width, height, fillColor.get16Bit());
}

void TFT::fillScreen(Color fillColor)
{
    tft.fillScreen(fillColor.get16Bit());
}
