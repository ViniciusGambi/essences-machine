#ifndef DigitalSensor_H
#define DigitalSensor_H

#include <Arduino.h>

#include <Wire.h>
#include <Adafruit_MCP23017.h>

class DigitalSensor
{
public:
   DigitalSensor(byte pin, Adafruit_MCP23017 *mcp);
   DigitalSensor(byte pin, Adafruit_MCP23017 *mcp, boolean invert);
   boolean read();
   boolean fell();
   void begin();
   
private:
   boolean _lastValue;
   boolean _invert = false;
   byte _pin;
   Adafruit_MCP23017 *_mcp;
};


#endif
