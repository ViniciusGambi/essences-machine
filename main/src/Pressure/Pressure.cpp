#include "Arduino.h"
#include "Pressure.h"

Pressure::Pressure(byte pin)
{
    _pin = pin;
}

void Pressure::begin(){
    pinMode(_pin, INPUT);
}

float Pressure::read()
{
    return analogRead(_pin)*0.64;
}