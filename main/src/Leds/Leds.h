#ifndef Leds_H
#define Leds_H

#include <Arduino.h>

#include <Wire.h>
#include <Adafruit_MCP23017.h>

class Leds
{
public:
   Leds(byte *pins);
   void begin(byte add);
   void write(byte position, bool state);
   void turnOn(byte position);
   void turnOff(byte position);
 
private:
   byte *_pins;
   Adafruit_MCP23017 *mcp;
};


#endif
