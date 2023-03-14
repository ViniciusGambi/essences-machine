#ifndef Buttons_H
#define Buttons_H

#include <Arduino.h>

#include <Wire.h>
#include <Adafruit_MCP23017.h>

class Buttons
{
public:
   Buttons(byte *pins);
   boolean readButton(byte position);
   void begin(byte add);
   int getButtonPressed();
 
private:
   byte *_pins;
   Adafruit_MCP23017 *mcp;
   int _buttonPressed = -1;
};

#endif
