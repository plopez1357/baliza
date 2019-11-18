#include "Arduino.h"
#include "Led.h"

Led::Led(int pin)
{
  pinMode(pin, OUTPUT);
  _pin = pin;
}

void Led::turnOn() 
{
  digitalWrite (_pin, HIGH);
}

void Led::turnOff() 
{
  digitalWrite (_pin, LOW);
}

void Led::blink() 
{
  digitalWrite (_pin, HIGH);
  delay(200);
  digitalWrite (_pin, LOW);
  delay(200);
  digitalWrite (_pin, HIGH);
  delay(200);
  digitalWrite (_pin, LOW);
  delay(200);
  digitalWrite (_pin, HIGH);
  delay(200);
  digitalWrite (_pin, LOW);
  delay(200);
  digitalWrite (_pin, HIGH);
  delay(200);
  digitalWrite (_pin, LOW);
  delay(200);
  digitalWrite (_pin, HIGH);
  delay(200);
  digitalWrite (_pin, LOW);
  delay(200);
}