#include "Arduino.h"
#include "Button.h"

Button::Button(byte pin)
{
    _pin = pin;
}

void Button::begin(){
    pinMode(_pin, INPUT);
}

boolean Button::read()
{
    bool value = digitalRead(_pin);
    
    if (_lastValue == 1 && value == 0){

        _lastTime = millis();
    }

    if (_lastValue == 0 && value == 1){
        _lastValue = value;
        if (millis()-_lastTime > 20 && millis()-_lastTime < 10000){
            return true;
        } else {
            return false;
        }
    } else {
        _lastValue = value;
        return false;
    }
 
}
