#include "Arduino.h"
#include "Motor.h"

#include <Wire.h>

Motor::Motor(byte stepPin, byte dirPin)
{
    _stepPin = stepPin;
    _dirPin = dirPin;
}

void Motor::begin(){
    pinMode(_stepPin, OUTPUT);
    pinMode(_dirPin, OUTPUT);
}

void Motor::step(int steps){
    for(int i = 0; i < abs(steps); i++){
        if (steps > 0){
            digitalWrite(_dirPin, HIGH);
        } else {
            digitalWrite(_dirPin, LOW);
        }
        
        digitalWrite(_stepPin, HIGH);
        delayMicroseconds(_frequency);
        digitalWrite(_stepPin, LOW);
        delayMicroseconds(_frequency);
    }
}

void Motor::brake(){
    digitalWrite(_stepPin, HIGH);
    digitalWrite(_dirPin, HIGH);
}

void Motor::setFrequency(int frequency){
    _frequency = frequency;
}
