#include "Arduino.h"
#include "Axis.h"

#include <avr/wdt.h>

Axis::Axis(Motor *motor, Reed *reed, Relay *piston, Inductive *inductive, LaserReceiver *receiver)
{
    _motor = motor;
    _reed = reed;
    _piston = piston;
    _inductive = inductive;
    _receiver = receiver;
}

void Axis::begin(){
    _motor->begin();
}

void Axis::setZero(){
    _currentPosition = 0;
}

boolean Axis::searchHome(){
    wdt_reset();
    if (!_reed->read()){
        while (_inductive->read() != 1){
            _motor->step(-1);
        }
        _motor->brake();
        _currentPosition = 0;
        delay(500);
        return true;
    } else{
        _piston->turnOff();
        delay(1000);
        return false;
    }
    
}

boolean Axis::goToPosition(byte position){
    wdt_reset();
    if (!_reed->read()){
        searchHome();
        _motor->step(_positions[position-1]-_currentPosition);
        _motor->brake();

        _currentPosition = _positions[position-1];
        return true;
    } else{
        _piston->turnOff();
        delay(1000);
        return false;
    }
}

boolean Axis::push(byte pressedEssence, byte attempts){
    byte count = 1;
    bool result = true;
    bool motorMoved = goToPosition(pressedEssence);
    delay(500);
    wdt_reset();
    if (motorMoved){      
      _piston->turnOn();
      float lastTime = millis();
      while(true){
        wdt_reset();
        if (_receiver->fell()){
          break;  
        }
        if (millis() - lastTime > 3000){
          if (count > attempts){
            result = false;
            break;
          }
          _piston->turnOff();
          delay(500);
          _piston->turnOn();
          lastTime = millis();
          count++;
        }
      }
      wdt_reset();
      delay(1000);
      _piston->turnOff();
      delay(1000);
      searchHome();
    } else {
      result = false;
    }
    return result;
}

