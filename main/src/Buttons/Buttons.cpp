#include "Arduino.h"
#include "Buttons.h"
 
Buttons::Buttons(byte pins[]){   
   mcp = new Adafruit_MCP23017(); 
   _pins = pins;  
}

void Buttons::begin(byte add){
    mcp->begin(add);
    for(int i = 0; i < 16; i++){
       mcp->pinMode(_pins[i], INPUT);
    }
}


boolean Buttons::readButton(byte position){
    return mcp->digitalRead(_pins[position-1]);
}

int Buttons::getButtonPressed(){
    int sum = 0;
    byte position;
    boolean state; 
    for(int i = 0; i < 16; i++){
        state = mcp->digitalRead(_pins[i]); 
        sum += state;
        if (state == 1){
            position = i+1;
        }
    }
    if (sum == 1){
        _buttonPressed = position;
        return -1;
    } else if (sum == 0 && _buttonPressed != -1){
        int ret = _buttonPressed;
        _buttonPressed = -1; 
        return ret;
    } else {
        return -1;
    }
    
    
}
