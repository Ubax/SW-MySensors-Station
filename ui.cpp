
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

#include "ui.h"

Scene::Scene()
{
    this->_draw = NULL;
}
Scene::Scene(void (*_draw)(TFT *, Station *, Station, bool), void (*_onNext)(UI *), void (*_onPrev)(UI *), void (*_onEnter)(UI *), void (*_onBack)(UI *))
{
    this->_draw = _draw;
    this->_onNext = _onNext;
    this->_onPrev = _onPrev;
    this->_onEnter = _onEnter;
    this->_onBack = _onBack;
}
void Scene::draw(TFT *tft, Station *station, bool isInit)
{
    Station _station = Station();
    _station = *station;
    if (this->_draw != NULL)
        this->_draw(tft, &_station, this->oldStation, isInit);
    this->oldStation = *station;
    *station = _station;
}
void Scene::onNext(UI *ui)
{
    this->_onNext(ui);
}
void Scene::onPrev(UI *ui)
{
    this->_onPrev(ui);
}
void Scene::onEnter(UI *ui)
{
    this->_onEnter(ui);
}
void Scene::onBack(UI *ui)
{
    this->_onBack(ui);
}

UI::UI(Scene *scenes, int numberOfScenes, TFT *tft, Station *station)
{
    this->scenes = new Scene[numberOfScenes];
    for (int i = 0; i < numberOfScenes; i++)
    {
        this->scenes[i] = scenes[i];
    }
    this->numberOfScenes = numberOfScenes;
    this->tft = tft;
    this->currentSceneId = 0;
    this->station = station;
    this->isInit = new bool;
    *this->isInit = true;
}
void UI::next()
{
    *this->isInit = true;
    if (!this->refreshed)
        return;
    if (this->currentSceneId < numberOfScenes - 1)
        this->currentSceneId++;
    else
        this->currentSceneId = 0;
    this->refreshed = false;
}
void UI::prev()
{
    *this->isInit = true;
    if (!this->refreshed)
        return;
    if (this->currentSceneId > 0)
        this->currentSceneId--;
    else
        this->currentSceneId = numberOfScenes - 1;
    this->refreshed = false;
}
void UI::draw()
{
    this->scenes[this->currentSceneId].draw(this->tft, this->station, *this->isInit);
    this->refreshed = true;
    *this->isInit = false;
}
void UI::onNext()
{
    this->scenes[this->currentSceneId].onNext(this);
}
void UI::onPrev()
{
    this->scenes[this->currentSceneId].onPrev(this);
}
void UI::onEnter()
{
    this->scenes[this->currentSceneId].onEnter(this);
}
void UI::onBack()
{
    this->scenes[this->currentSceneId].onBack(this);
}