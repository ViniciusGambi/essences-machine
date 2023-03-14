#include "Arduino.h"
#include "DigitalSensor.h"

#include <Wire.h>
#include <Adafruit_MCP23017.h>

DigitalSensor::DigitalSensor(byte pin, Adafruit_MCP23017 *mcp)
{
    _mcp = mcp;
    _pin = pin;
}

DigitalSensor::DigitalSensor(byte pin, Adafruit_MCP23017 *mcp, boolean invert)
{
    _invert = invert;
    _mcp = mcp;
    _pin = pin;
}

void DigitalSensor::begin(){
    _mcp->pinMode(_pin, INPUT);
}

boolean DigitalSensor::read()
{
    if (_invert){
        return !_mcp->digitalRead(_pin);
    } else {
        return _mcp->digitalRead(_pin);
    }
    
}

boolean DigitalSensor::fell(){
    bool value = read();
    if (_lastValue == 1 && value == 0){
        _lastValue = value;
        return true;
    } else {
        _lastValue = value;
        return false;
    }
}
