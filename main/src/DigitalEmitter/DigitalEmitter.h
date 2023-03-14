#ifndef DigitalEmitter_H
#define DigitalEmitter_H

#include <Arduino.h>

#include <Wire.h>
#include <Adafruit_MCP23017.h>

class DigitalEmitter
{
public:
   DigitalEmitter(byte pin, Adafruit_MCP23017 *mcp);
   void turnOn();
   void turnOff();
   void begin();

   
private:
   byte _pin;
   Adafruit_MCP23017 *_mcp;
   bool _state = false;
};


#endif
