#include "uiControls.h"

void MenuItem::draw(TFT *tft, int x, int y)
{
    Style style = this->isActive ? this->theme->getPrimaryStyle() : this->theme->getSecondaryStyle();
    tft->drawFillRect(x, y, width, height, style.getBackgroundColor());
    tft->drawText(x, y, this->text, this->textSize, style.getTextColor());
}

void MenuItem::activate()
{
    this->isActive = true;
}

void MenuItem::deactivate()
{
    this->isActive = false;
}

Menu::Menu(String *items, int numberOfItems, Theme *theme, int width = -100, int height = -100) : UIControl(theme), numberOfItems(numberOfItems), width(width), height(height)
{
    MenuItem *menuItems = new MenuItem[numberOfItems];
    for (int i = 0; i < numberOfItems; i++)
    {
        menuItems[i] = MenuItem(items[i], theme, width, height / numberOfItems);
    }
    this->items = menuItems;
}

void Menu::draw(TFT *tft, int x, int y)
{
    int heightOfOne = height / numberOfItems;
    for (int i = 0; i < numberOfItems; i++)
    {
        this->items[i].draw(tft, x, y + heightOfOne * i);
    }
}
