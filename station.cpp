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

#include "station.h"

float Station::getTemperature()
{
    return this->temperature;
}

float Station::getHumadity()
{
    return this->humadity;
}

float Station::getAirPressure()
{
    return this->airPressure;
}

int Station::getTimeInSeconds()
{
    return this->time;
}

bool Station::isSleepMode()
{
    return this->sleepMode;
}

void Station::setTemperature(float temperature)
{
    this->temperature = temperature;
}

void Station::setHumadity(float humadity)
{
    this->humadity = humadity;
}

void Station::setAirPressure(float airPressure)
{
    this->airPressure = airPressure;
}

void Station::setTimeInSeconds(int time)
{
    this->time = time;
}

void Station::turnOnSleepMode()
{
    this->sleepMode = true;
    this->sleepObserver(this);
}

void Station::turnOffSleepMode()
{
    this->sleepMode = false;
    this->sleepObserver(this);
}

void Station::setSleepModeObserver(void (*observer)(Station *))
{
    this->sleepObserver = observer;
}

void Station::setMovementObserver(void (*observer)(Station *))
{
    this->movementObserver = observer;
}

void Station::setBrigthness(int brigthness){
    if(brigthness<0)brigthness=0;
    if(brigthness>100)brigthness=100;
    this->brigthness=brigthness;
}

int Station::getBrigthness(){
    return this->brigthness;
}
bool Station::movementDetected(){
    return this->_movementDetected;
}
void Station::detectedMovement(){
    this->_movementDetected=true;
    this->movementObserver(this);
}
void Station::detectedNoMovement(){
    this->_movementDetected=false;
    this->movementObserver(this);
}

