#ifndef Led_h
#define Led_h

#include <Arduino.h>

class Led
{
    public:
        Led(int pin);
        void turnOn();
        void turnOff();
        void blink();
    private:
        int _pin;
};

#endif