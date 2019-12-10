#include "config/MyConfig.h"
#include "config/tftConfig.h"
#include "config/config.h"
#include <MySensors.h>
#include "tft.h"
#include "ui.h"
#include "InterruptManager.h"

Station *station;
TFT *tftDisplay;
bool *shouldRefresh;
UI *ui;
long *oldMillis;
InterruptManager *manager;

bool areEqual(float a, float b)
{
  return a + 0.05 > b && b > a - 0.05;
}

String addMissingZero(int n)
{
  if (n < 10)
    return "0" + String(n);
  return String(n);
}

String secondsToTimeHM(int seconds)
{
  return addMissingZero((seconds / 3600) % 24) + ":" + addMissingZero((seconds / 60) % 60);
}

void home(TFT *tft, Station *station, Station oldStation, bool isInit)
{
  Color timeBgColor = Color(169, 227, 187);
  Color tempBgColor = Color(247, 179, 43);
  Color humBgColor = Color(252, 246, 177);
  if (isInit)
  {
    tft->drawFillRect(0, 0, 128, 60, timeBgColor);
    tft->drawFillRect(0, 60, 128, 50, tempBgColor);
    tft->drawFillRect(0, 110, 128, 50, humBgColor);
    tft->drawText(0, 10, secondsToTimeHM(station->getTimeInSeconds()), 3, Color(0, 0, 0));
    tft->drawText(0, 70, String(station->getTemperature()) + String("*"), 3, Color(0, 0, 0));
    tft->drawText(0, 120, String(station->getHumadity()) + String("%"), 3, Color(0, 0, 0));
  }
  else
  {
    String oldTimeHM = secondsToTimeHM(oldStation.getTimeInSeconds());
    String timeHM = secondsToTimeHM(station->getTimeInSeconds());

    if (oldTimeHM != timeHM)
      tft->redrawText(0, 10, 3, timeHM, Color(0, 0, 0), oldTimeHM, timeBgColor);

    if (!areEqual(station->getTemperature(), oldStation.getTemperature()))
      tft->redrawText(0, 70, 3,
                      String(station->getTemperature()) + String("*"), Color(0, 0, 0),
                      String(oldStation.getTemperature()) + String("*"), tempBgColor);

    if (!areEqual(station->getHumadity(), oldStation.getHumadity()))
      tft->redrawText(0, 120, 3,
                      String(station->getHumadity()) + String("%"), Color(0, 0, 0),
                      String(oldStation.getHumadity()) + String("%"), humBgColor);
  }
}

void minimal(TFT *tft, Station *station, Station oldStation, bool isInit)
{
  Color bgColor = Color(0, 0, 0);
  Color textColor = Color(230, 230, 230);
  if (isInit){
    tft->drawFillRect(0, 0, 128, 160, bgColor);
    tft->drawText(0, 35, String(station->getTemperature()) + String("*"), 3, textColor);
    tft->drawText(0, 100, String((int)station->getAirPressure()) + String("hPa"), 1, textColor);
  }
    
  if (!areEqual(station->getTemperature(), oldStation.getTemperature()))
  {
    tft->drawText(0, 35, String(oldStation.getTemperature()) + String("*"), 3, bgColor);
    tft->drawText(0, 35, String(station->getTemperature()) + String("*"), 3, textColor);
  }
  if (!areEqual(station->getAirPressure(), oldStation.getAirPressure()))
  {
    tft->drawText(0, 100, String(oldStation.getAirPressure()) + String("hPa"), 2, bgColor);
    tft->drawText(0, 100, String(station->getAirPressure()) + String("hPa"), 2, textColor);
  }
}

void setupStation()
{
  station = new Station();
  station->setSleepModeObserver([](Station *station) {
    station->setBrigthness(station->isSleepMode() ? 30 : 100);
    ui->next();
    *shouldRefresh = true;
  });
  station->setMovementObserver([](Station *station) {
    if (station->movementDetected())
      station->turnOffSleepMode();
    else
      station->turnOnSleepMode();
  });
  station->turnOffSleepMode();
}

void setupUI()
{
  tftDisplay = new TFT(TFT_RST, TFT_A0, TFT_CS, TFT_SDA, TFT_SCK);
  shouldRefresh = new bool;
  *shouldRefresh = true;
  oldMillis = new long;
  *oldMillis = 0;

  const int numberOfScenes = 2;
  Scene *scenes = new Scene[numberOfScenes];
  scenes[1] = Scene(&home);
  scenes[0] = Scene(&minimal);

  ui = new UI(scenes, numberOfScenes, tftDisplay, station);
}

void setup()
{
  pinMode(PIN_NUMBER_BUTTON_NEXT, INPUT_PULLUP);
  pinMode(PIN_NUMBER_BUTTON_PREV, INPUT_PULLUP);
  pinMode(PIN_SLEEP_MODE, OUTPUT);
  pinMode(PIN_DISPLAY_BRIGTHNESS, OUTPUT);

  setupUI();
  setupStation();
}

void presentation()
{
  // Present locally attached sensors
}

void receive(const MyMessage &message)
{
  if ((message.type == V_TEMP))
  {
    station->setTemperature(message.getFloat());
    *shouldRefresh = true;
  }
  if ((message.type == V_HUM))
  {
    station->setHumadity(message.getFloat());
    *shouldRefresh = true;
  }
  if ((message.type == V_PRESSURE))
  {
    station->setAirPressure(message.getFloat());
    *shouldRefresh = true;
  }

  if ((message.type == V_TRIPPED))
  {
    station->setAirPressure(message.getFloat());
    *shouldRefresh = true;
  }
} // end: void receive()

void loop()
{
  if (millis() - *oldMillis > 10000)
  {
    int d = (millis() - *oldMillis) / 1000;
    station->setTimeInSeconds(station->getTimeInSeconds() + d);
    *shouldRefresh = true;
    *oldMillis = millis();
    if (station->movementDetected())
      station->detectedNoMovement();
    else
      station->detectedMovement();
  }
  if (*shouldRefresh)
  {
    analogWrite(PIN_DISPLAY_BRIGTHNESS, station->getBrigthness() * 255 / 100);
    ui->draw();
    Serial.print("Temp: ");
    Serial.print(station->getTemperature());
    Serial.print("\t\tHum: ");
    Serial.println(station->getHumadity());
    *shouldRefresh = false;
  }
  // manager->check();
  sleep(10);
}
