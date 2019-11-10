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

#ifndef SW_UI
#define SW_UI

#include "station.h"
#include "tft.h"

class UI;
class Scene;

class Scene
{
protected:
  void (*_draw)(TFT *, Station *, Station, bool);
  void (*_onEnter)(UI *);
  void (*_onBack)(UI *);
  void (*_onNext)(UI *);
  void (*_onPrev)(UI *);
  Station oldStation;

public:
  /**
   * @brief Construct a new Scene object
   * 
   * Empty constructor that shouldn't be used in code
   */
  Scene();
  /**
   * @brief Construct a new Scene object
   * 
   * @param _draw - function which will draw scene. Draw function should take four arguments: pointer to display, pointer to current station, old station, is scene in init mode
   * @param _onNext - function which will be fired when next button is pressed
   * @param _onPrev - function which will be fired when prev button is pressed
   * @param _onEnter - function which will be fired when enter button is pressed
   * @param _onBack - function which will be fired when back button is pressed
   */
  Scene(void (*_draw)(TFT *, Station *, Station, bool), void (*_onNext)(UI *), void (*_onPrev)(UI *), void (*_onEnter)(UI *), void (*_onBack)(UI *));

  /**
   * @brief Function drawing scene
   * 
   * @param tft
   * @param station 
   * @param isInit 
   */
  void draw(TFT *tft, Station *station, bool isInit);

  /**
   * @brief Function informing scene that next button is pressed
   * 
   * @param ui - UI which informs scene of that event
   */
  void onNext(UI *ui);

  /**
   * @brief Function informing scene that prev button is pressed
   * 
   * @param ui - UI which informs scene of that event
   */
  void onPrev(UI *ui);

  /**
   * @brief Function informing scene that enter button is pressed
   * 
   * @param ui - UI which informs scene of that event
   */
  void onEnter(UI *ui);

  /**
   * @brief Function informing scene that back button is pressed
   * 
   * @param ui - UI which informs scene of that event
   */
  void onBack(UI *ui);
};

class UI
{
protected:
  Scene *scenes;
  int numberOfScenes;
  TFT *tft;
  int currentSceneId;
  Station *station;
  bool refreshed = false;
  bool *isInit;

public:
  /**
   * @brief Construct a new UI object
   * 
   * @param scenes - array of scenes
   * @param numberOfScenes 
   * @param tft 
   * @param station 
   */
  UI(Scene *scenes, int numberOfScenes, TFT *tft, Station *station);

  /**
   * @brief Go to next scene
   * 
   */
  void next();

  /**
   * @brief Go to previous scene
   * 
   */
  void prev();

  /**
   * @brief Draw current scene
   * 
   */
  void draw();

  /**
   * @brief Inform UI that next button is pressed
   * 
   */
  void onNext();

  /**
   * @brief Inform UI that prev button is pressed
   * 
   */
  void onPrev();

  /**
   * @brief Inform UI that enter button is pressed
   * 
   */
  void onEnter();

  /**
   * @brief Inform UI that back button is pressed
   * 
   */
  void onBack();
};

#endif
