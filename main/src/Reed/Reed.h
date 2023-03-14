#ifndef Reed_H
#define Reed_H

#include <Arduino.h>
#include "../DigitalSensor/DigitalSensor.h"

class Reed : public DigitalSensor
{
public:
   Reed(byte pin, Adafruit_MCP23017 *mcp) : DigitalSensor(pin, mcp){}
   Reed(byte pin, Adafruit_MCP23017 *mcp, boolean invert) : DigitalSensor(pin, mcp, invert){}
};

#endif
