#ifndef UI_CONTROLS_H
#define UI_CONTROLS_H

#include "tft.h"

class Style
{
protected:
    Color backgroundColor;
    Color textColor;

public:
    Style(Color backgroundColor, Color textColor) : backgroundColor(backgroundColor), textColor(textColor) {}

    Color getBackgroundColor() { return this->backgroundColor; }
    Color getTextColor() { return this->textColor; }
};

class Theme
{
protected:
    Style primary;
    Style secondary;

public:
    Theme(Style primary, Style secondary) : primary(primary), secondary(secondary) {}

    Style getPrimaryStyle() { return this->primary; }
    Style getSecondaryStyle() { return this->secondary; }
};

class UIControl
{
protected:
    Theme *theme;

public:
    UIControl(Theme *theme) : theme(theme) {}
    virtual void draw(TFT *tft, int x, int y);
};

class MenuItem : UIControl
{
protected:
    int width;
    int height;
    int textSize;
    String text;
    bool isActive;

public:
    /**
     * @brief Construct a new Menu Item object
     * 
     * **Shouldn't be used in code **
     */
    MenuItem() : UIControl(NULL){};
    /**
     * @brief Construct a new Menu Item object
     * 
     * @param text 
     * @param width - negative value (percentage of display)
     * @param height - negative value (percentage of display)
     */
    MenuItem(String text, Theme *theme, int width = -100, int height = 20) : UIControl(theme), text(text), width(width), height(height), isActive(false), textSize(height < 20 ? 2 : 3) {}

    void draw(TFT *tft, int x, int y);
    void activate();
    void deactivate();
};

class Menu : UIControl
{
protected:
    MenuItem *items;
    int numberOfItems;
    int width;
    int height;

public:
    Menu(String *items, int numberOfItems, Theme *theme, int width, int height);
    void draw(TFT *tft, int x, int y);
};

#endif