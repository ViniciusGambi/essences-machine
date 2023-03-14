#ifndef Axis_H
#define Axis_H

#include <Arduino.h>

#include "../Motor/Motor.h"
#include "../Reed/Reed.h"
#include "../Relay/Relay.h"
#include "../Inductive/Inductive.h"
#include "../LaserReceiver/LaserReceiver.h"

class Axis
{
public:
   Axis(Motor *motor, Reed *reed, Relay *piston, Inductive *inductive, LaserReceiver *_receiver);
   void begin();
   void setZero();
   boolean goToPosition(byte position);
   boolean searchHome();
   boolean push(byte pressedEssence, byte attempts);
   
   
private:
   Motor *_motor;
   Reed *_reed;
   Relay *_piston;
   Inductive *_inductive;
   LaserReceiver *_receiver;
   int _positions[16] = {0, 375, 715, 1050, 1390, 1690, 2025, 2810, 0, 370, 670, 983, 1292, 1630, 1970, 2310 };
   int _currentPosition = 0;
};

#endif