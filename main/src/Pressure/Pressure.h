#ifndef Pressure_H
#define Pressure_H

#include <Arduino.h>

class Pressure
{
public:
   Pressure(byte pin);
   float read();
   void begin();
   
private:
   byte _pin;
};


#endif
