#include "src/Axis/Axis.h"
#include "src/Button/Button.h"
#include "src/Buttons/Buttons.h"
#include "src/Display/Display.h"
#include "src/Dispenser/Dispenser.h"
#include "src/Inductive/Inductive.h"
#include "src/LaserReceiver/LaserReceiver.h"
#include "src/Leds/Leds.h"
#include "src/Memory/Memory.h"
#include "src/Motor/Motor.h"
#include "src/NoteReader/NoteReader.h"
#include "src/Pressure/Pressure.h"
#include "src/Reed/Reed.h"
#include "src/Relay/Relay.h"

#include <avr/wdt.h>
#include <Wire.h>
#include <Adafruit_MCP23017.h>

Adafruit_MCP23017 mainMcp;

Memory inventory;

byte buttonsPins[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
byte ledsPins[]    = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};

Button modeButton(A2);

Buttons buttons(buttonsPins);
Leds leds(ledsPins);

Inductive topInductive(8, &mainMcp, true);
Inductive bottomInductive(7, &mainMcp, true);

LaserReceiver topReceiver(3, &mainMcp);
LaserReceiver bottomReceiver(2, &mainMcp);

Reed topReed(0, &mainMcp, true);
Reed bottomReed(1, &mainMcp, true);

Motor bottomMotor(3, 10);
Motor topMotor(5, 4);

Relay compressor(4, &mainMcp);
Relay ledStrip(10, &mainMcp);

Relay topPiston(6, &mainMcp);
Relay bottomPiston(5, &mainMcp);

Axis topAxis(&topMotor, &topReed, &topPiston, &topInductive, &topReceiver);
Axis bottomAxis(&bottomMotor, &bottomReed, &bottomPiston, &bottomInductive, &bottomReceiver);

Dispenser dispenser(&topAxis, &bottomAxis);

NoteReader noteReader(2, 9, &mainMcp);

Pressure pressure(A3);

Display display(7, 6, 9, 8);

void initialize(){
  mainMcp.begin(2);
  
  modeButton.begin();
  buttons.begin(1);
  ledStrip.begin();
  leds.begin(0);
  noteReader.begin();
  
  topInductive.begin();
  bottomInductive.begin();
  topReceiver.begin();
  bottomReceiver.begin();
  topReed.begin();
  bottomReed.begin();
  topPiston.begin();
  bottomPiston.begin();
  dispenser.begin();
  
  compressor.begin();
  pressure.begin();
}
