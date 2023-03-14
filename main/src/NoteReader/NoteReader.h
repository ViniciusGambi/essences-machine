#ifndef NoteReader_H
#define NoteReader_H

#include <Arduino.h>

#include <Wire.h>
#include <Adafruit_MCP23017.h>

class NoteReader
{
public:
   NoteReader(byte signalPin, byte inibPin, Adafruit_MCP23017 *mcp);
   void begin();
   int getLastNote();
   byte noteReaded();
   byte test();
   void inhibit(boolean inhibit);
   bool isInhibited();

   const byte WAITING = 0;
   const byte DONE = 1;
   const byte READING = 2;
   
private:
   byte _signalPin;
   byte _inibPin;
   Adafruit_MCP23017 *_mcp;
   float _lastTime;
   int _lastCount = 0;
   int _lastNote = 0;
   boolean _inhibited;
};


#endif
