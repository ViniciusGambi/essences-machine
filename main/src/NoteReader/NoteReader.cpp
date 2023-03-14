#include "Arduino.h"
#include "NoteReader.h"
 
#include <Wire.h>
#include <Adafruit_MCP23017.h>

unsigned long count = 0;
unsigned long lastChange = millis();
byte pin;
bool lastState=1;

void pulseCounter()//ISR
{
  bool currentState = digitalRead(pin);
  if(!lastState){
    if(currentState){
        if (millis() - lastChange > 95 && millis() - lastChange < 105){
          count++;
        }
    }
  }

  lastState = currentState;
  lastChange = millis();
}

NoteReader::NoteReader(byte signalPin, byte inibPin, Adafruit_MCP23017 *mcp)
{
    _mcp = mcp;
    _signalPin = signalPin;
    _inibPin = inibPin;
    pin = signalPin;
}

void NoteReader::begin(){
   _mcp->pinMode(_inibPin, OUTPUT);
   pinMode(_signalPin, INPUT);
   attachInterrupt(digitalPinToInterrupt(_signalPin), pulseCounter, CHANGE);
}

int NoteReader::getLastNote(){
   return _lastNote;
}

byte NoteReader::test(){
  
  return 0;
}

byte NoteReader::noteReaded(){
   long interval = millis() - lastChange;
   if (interval < 105 && count > 0){
      return 2;
   } else {
      if (count > 0){
         _lastNote = count;
         count = 0;
         return 1;
      } else {
         return 0;
      }
   }
}

void NoteReader::inhibit(boolean inhibit){
   if (inhibit){
      _mcp->digitalWrite(_inibPin, HIGH);
      detachInterrupt(digitalPinToInterrupt(_signalPin));
      _inhibited = true;
   } else {
      _mcp->digitalWrite(_inibPin, LOW);
      attachInterrupt(digitalPinToInterrupt(_signalPin), pulseCounter, CHANGE);
      _inhibited = false;
   }
}

bool NoteReader::isInhibited(){
  return _inhibited;
}