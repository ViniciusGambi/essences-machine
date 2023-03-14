#ifndef Motor_H
#define Motor_H

#include <Arduino.h>

#include <Wire.h>

class Motor
{
public:
   Motor(byte stepPin, byte dirPin);
   void begin();
   void step(int steps);
   void setFrequency(int frequency);
   void brake();

   
private:
   byte _stepPin;
   byte _dirPin;
   int _frequency = 500;
};


#endif
