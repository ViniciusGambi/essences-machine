#ifndef Button_H
#define Button_H

#include <Arduino.h>

class Button
{
public:
   Button(byte pin);
   boolean read();
   void begin();
   
private:
   byte _pin;
   bool _lastValue = 1;
   long _lastTime;
};


#endif
