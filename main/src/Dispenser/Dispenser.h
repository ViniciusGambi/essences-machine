#ifndef Dispenser_H
#define Dispenser_H

#include <Arduino.h>

#include "../Axis/Axis.h"

class Dispenser
{
public:
   Dispenser(Axis *topAxis, Axis *bottomAxis);
   void begin();
   boolean pushEssence(byte pressedEssence);
   
private:
   Axis *_topAxis;
   Axis *_bottomAxis;
};

#endif