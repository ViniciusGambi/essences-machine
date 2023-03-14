#include "Arduino.h"
#include "Leds.h"
 
#include <Wire.h>
#include <Adafruit_MCP23017.h>

Leds::Leds(byte pins[]){   
   mcp = new Adafruit_MCP23017(); 
   _pins = pins;  
}

void Leds::begin(byte add){
    mcp->begin(add);
    for(int i = 0; i < 16; i++){
       mcp->pinMode(_pins[i], OUTPUT);
    }
}

void Leds::write(byte position, bool state){
    mcp->digitalWrite(_pins[position-1], state);
}

void Leds::turnOn(byte position){
   write(position, 1);
}

void Leds::turnOff(byte position){
  write(position, 0);
}

