#include "Arduino.h"
#include "DigitalEmitter.h"

#include <Wire.h>
#include <Adafruit_MCP23017.h>

DigitalEmitter::DigitalEmitter(byte pin, Adafruit_MCP23017 *mcp)
{
    _mcp = mcp;
    _pin = pin;
}

void DigitalEmitter::begin(){
    _mcp->pinMode(_pin, OUTPUT);
    _state = false;
    turnOff();
}

void DigitalEmitter::turnOn(){
    if(!_state){
        _mcp->digitalWrite(_pin, HIGH);
        _state = true;
    }
}

void DigitalEmitter::turnOff(){
    if(_state){
        _mcp->digitalWrite(_pin, LOW);
        _state = false;
    }
}