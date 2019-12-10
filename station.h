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

#ifndef SW_MY_STATION
#define SW_MY_STATION

/**
 * Model for all data sent to the station
 * 
 * Currently consists of:
 * * temperature
 * * humadity
 * * time
 * * sleep mode with observer functionality
 */

class Station
{
protected:
    float temperature;
    float humadity;
    int time;
    bool sleepMode;
    bool _movementDetected;
    int brigthness=100;
    float airPressure=0.0;
    void (*sleepObserver)(Station *);
    void (*movementObserver)(Station *);

public:
    float getTemperature();
    float getHumadity();
    float getAirPressure();
    int getTimeInSeconds();
    bool isSleepMode();
    bool movementDetected();
    int getBrigthness();
    void setTemperature(float temperature);
    void setHumadity(float humadity);
    void setAirPressure(float airPressure);
    void setTimeInSeconds(int time);
    void turnOnSleepMode();
    void turnOffSleepMode();
    void setSleepModeObserver(void (*observer)(Station *));
    void setMovementObserver(void (*observer)(Station *));
    void setBrigthness(int brigthness);
    void detectedMovement();
    void detectedNoMovement();
};

#endif
