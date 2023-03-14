#ifndef LaserReceiver_H
#define LaserReceiver_H

#include <Arduino.h>
#include "../DigitalSensor/DigitalSensor.h"

class LaserReceiver : public DigitalSensor
{
public:
   LaserReceiver(byte pin, Adafruit_MCP23017 *mcp) : DigitalSensor(pin, mcp){}
   LaserReceiver(byte pin, Adafruit_MCP23017 *mcp, boolean invert) : DigitalSensor(pin, mcp, invert){}
};

#endif
