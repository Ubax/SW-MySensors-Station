#include "config/MyConfig.h"
#include "config/tftConfig.h"
#include "config/config.h"
#include <MySensors.h>
#include "tft.h"
#include "ui.h"

Station *station;
TFT *tftDisplay;
bool *shouldRefresh;
UI *ui;
long *oldMillis;

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
  Serial.println(isInit);
  if (isInit)
  {
    tft->drawFillRect(0, 0, 128, 60, Color(169, 227, 187));
    tft->drawFillRect(0, 60, 128, 50, Color(247, 179, 43));
    tft->drawFillRect(0, 110, 128, 50, Color(252, 246, 177));
    tft->drawText(0, 10, secondsToTimeHM(station->getTimeInSeconds()), 3, Color(0, 0, 0));
    tft->drawText(0, 70, String(station->getTemperature()) + String("*"), 3, Color(0, 0, 0));
    tft->drawText(0, 120, String(station->getHumadity()) + String("%"), 3, Color(0, 0, 0));
  }
  else
  {
    String oldTimeHM = secondsToTimeHM(oldStation.getTimeInSeconds());
    String timeHM = secondsToTimeHM(station->getTimeInSeconds());

    if (oldTimeHM != timeHM)
    {
      tft->drawText(0, 10, oldTimeHM, 3, Color(247, 179, 43));
      tft->drawText(0, 10, timeHM, 3, Color(0, 0, 0));
    }
    tft->drawText(0, 0, String(), 2, Color(0, 0, 0));
    if (!areEqual(station->getTemperature(), oldStation.getTemperature()))
    {
      tft->drawText(0, 70, String(oldStation.getTemperature()) + String("*"), 3, Color(247, 179, 43));
      tft->drawText(0, 70, String(station->getTemperature()) + String("*"), 3, Color(0, 0, 0));
    }
    if (!areEqual(station->getHumadity(), oldStation.getHumadity()))
    {
      tft->drawText(0, 120, String(oldStation.getHumadity()) + String("%"), 3, Color(252, 246, 177));
      tft->drawText(0, 120, String(station->getHumadity()) + String("%"), 3, Color(0, 0, 0));
    }
  }
}

void temp(TFT *tft, Station *station, Station oldStation, bool isInit)
{
  if (isInit)
    tft->drawFillRect(0, 0, 128, 160, Color(20, 20, 20));
  if (!areEqual(station->getTemperature(), oldStation.getTemperature()))
  {
    tft->drawText(0, 65, String(oldStation.getTemperature()) + String("*"), 3, Color(20, 20, 20));
    tft->drawText(0, 65, String(station->getTemperature()) + String("*"), 3, Color(200, 200, 200));
  }
}

void setup()
{
  pinMode(PIN_NUMBER_BUTTON_NEXT, INPUT_PULLUP);
  pinMode(PIN_NUMBER_BUTTON_PREV, INPUT_PULLUP);
  pinMode(PIN_SLEEP_MODE, OUTPUT);

  station = new Station();
  station->setSleepModeObserver([](Station *station) { digitalWrite(PIN_SLEEP_MODE, station->isSleepMode() ? LOW : HIGH); });
  station->turnOffSleepMode();
  tftDisplay = new TFT(TFT_RST, TFT_A0, TFT_CS, TFT_SDA, TFT_SCK);
  shouldRefresh = new bool;
  *shouldRefresh = true;
  oldMillis = new long;
  *oldMillis = 0;

  const int numberOfScenes = 2;
  Scene *scenes = new Scene[numberOfScenes];
  scenes[0] = Scene(&home, [](UI *ui) { ui->next(); }, [](UI *ui) { ui->prev(); }, [](UI *ui) { Serial.println("Enter"); }, [](UI *ui) { Serial.println("Back"); });
  scenes[1] = Scene(&temp, [](UI *ui) { ui->next(); }, [](UI *ui) { ui->prev(); }, [](UI *ui) { Serial.println("Enter"); }, [](UI *ui) { Serial.println("Back"); });
  ui = new UI(scenes, numberOfScenes, tftDisplay, station);

  attachInterrupt(digitalPinToInterrupt(PIN_NUMBER_BUTTON_NEXT), []() { ui->onNext(); }, RISING);
  attachInterrupt(digitalPinToInterrupt(PIN_NUMBER_BUTTON_PREV), []() { ui->onPrev(); }, RISING);
  attachInterrupt(digitalPinToInterrupt(PIN_NUMBER_BUTTON_ENTER), []() { ui->onEnter(); }, RISING);
  attachInterrupt(digitalPinToInterrupt(PIN_NUMBER_BUTTON_BACK), []() { ui->onBack(); }, RISING);
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
    //station->setHumadity(message.getFloat());
    station->setHumadity(30);
    *shouldRefresh = true;
  }

} // end: void receive()

void loop()
{
  if (millis() - *oldMillis > 3000)
  {
    Serial.print("Time update\t");
    int d = (millis() - *oldMillis) / 1000;
    Serial.print(d);
    Serial.print("\t");
    Serial.println(station->getTimeInSeconds());
    station->setTimeInSeconds(station->getTimeInSeconds() + d);
    *shouldRefresh = true;
    *oldMillis = millis();
  }
  if (*shouldRefresh)
  {
    ui->draw();
    /*Serial.print("Temp: ");
    Serial.print(station->getTemperature());
    Serial.print("\t\tHum: ");
    Serial.println(station->getHumadity());*/
    *shouldRefresh = false;
  }
  sleep(50);
}
