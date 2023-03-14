#ifndef Relay_H
#define Relay_H

#include <Arduino.h>
#include "../DigitalEmitter/DigitalEmitter.h"

class Relay : public DigitalEmitter
{
public:
   Relay(byte pin, Adafruit_MCP23017 *mcp) : DigitalEmitter(pin, mcp){}
};

#endif
