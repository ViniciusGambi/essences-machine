#ifndef Memory_H
#define Memory_H

#include <Arduino.h>

class Memory
{
public:
   Memory();
   boolean hasEssence(byte position = 0);
   byte essencePrice(byte position);
   byte subtract(byte position);
   byte update(byte position);
   byte updatePrice(byte position);

};


#endif
