#ifndef INTERRUPT_MANAGER_H
#define INTERRUPT_MANAGER_H

class Interrupt
{
private:
    int pin = 0;
    void (*_run)();
    int oldState = LOW;
    int type;

public:
    Interrupt() {}
    Interrupt(int pin, void (*function)(), int type) : pin(pin), _run(function), type(type)
    {
        oldState = digitalRead(pin);
    }
    void run()
    {
        int currentState = digitalRead(pin);
        if (type == RISING && currentState == HIGH && oldState == LOW)
            this->_run();
        else if (type == HIGH && currentState == HIGH)
            this->_run();
        else if (type == LOW && currentState == LOW)
            this->_run();
        else if (type == FALLING && currentState == LOW && oldState == HIGH)
            this->_run();
        else if (type == CHANGE && currentState != oldState)
            this->_run();
        oldState = currentState;
    }
};

class InterruptManager
{
private:
    Interrupt *interrupts;
    int numberOfInterrupts;

public:
    InterruptManager(int numberOfInterrupts)
    {
        this->numberOfInterrupts = numberOfInterrupts;
        this->interrupts = new Interrupt[this->numberOfInterrupts];
    }

    void setInterrupt(int i, Interrupt interrupt)
    {
        if (i >= 0 && i < numberOfInterrupts)
            this->interrupts[i] = interrupt;
        else
            Serial.println("Wrong interrupt number");
    }

    void check()
    {
        for (int i = 0; i < numberOfInterrupts; i++)
            this->interrupts[i].run();
    }
};

#endif
