#ifndef Inductive_H
#define Inductive_H

#include <Arduino.h>
#include "../DigitalSensor/DigitalSensor.h"

class Inductive : public DigitalSensor
{
public:
   Inductive(byte pin, Adafruit_MCP23017 *mcp) : DigitalSensor(pin, mcp){}
   Inductive(byte pin, Adafruit_MCP23017 *mcp, boolean invert) : DigitalSensor(pin, mcp, invert){}
};

#endif
