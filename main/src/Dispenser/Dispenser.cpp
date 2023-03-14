#include "Arduino.h"
#include "Dispenser.h"

#include <avr/wdt.h>

Dispenser::Dispenser(Axis *topAxis, Axis *bottomAxis)
{
    _topAxis = topAxis;
    _bottomAxis = bottomAxis;
}

void Dispenser::begin(){
    _topAxis->begin();
    _bottomAxis->begin();
}

boolean Dispenser::pushEssence(byte pressedEssence){
  bool result = true;
  if (pressedEssence < 9){
    if (!_bottomAxis->push(pressedEssence, 0)){
      result = _bottomAxis->push(pressedEssence, 1);
    }
  } else {
    if (!_topAxis->push(pressedEssence, 0)){
      result = _topAxis->push(pressedEssence, 1);
    }
  }
  return result;
}
