#include "Arduino.h"
#include "Memory.h"

#include <EEPROM.h>

Memory::Memory(){}

byte Memory::updatePrice(byte position){
    position = 100 + position;
    byte current = EEPROM.read(position);
    if (current == 20){
        current = -1;
    }
    current += 1;
    EEPROM.write(position, current);
    return current;
}

byte Memory::essencePrice(byte position)
{
    return EEPROM.read(position+100);
}

boolean Memory::hasEssence(byte position)
{
    if(!position){
        for(byte i = 1; i <= 24; i++){
            if (EEPROM.read(i)){
                return 1;
            }
        }
        return 0;
    } else {
        if (!EEPROM.read(position)){
            return 0;
        } else {
            return 1;
        }
    }
}

byte Memory::subtract(byte position){
    byte current = EEPROM.read(position);
    if (current != 0){
        EEPROM.write(position, current-1);
    }
    return current;
}

byte Memory::update(byte position){
    byte current = EEPROM.read(position);
    if (current == 24){
        current = -1;
    }
    current += 1;
    EEPROM.write(position, current);
    return current;
}

