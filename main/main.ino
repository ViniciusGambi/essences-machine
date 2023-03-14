#include "constants.h"
#include "declarations.h"

byte machineMode = SALES;
bool firstTimeOnMode = true;
int balance = INITIAL_BALANCE;
int pressedEssence;

void setup()
{
  wdt_enable(WDTO_8S);
  Serial.begin(9600);
  initialize();
  topAxis.searchHome();
  bottomAxis.searchHome();
  compressor.turnOff();
}

void loop()
{
  Serial.println(pressure.read());
  
  //Watch Dog Reset
  wdt_reset();

  //Mode Selector
  if (modeButton.read()){
    if (machineMode == SALES) { 
      machineMode = INVENTORY;
      wdt_delay(100);
    } else if (machineMode == INVENTORY) { 
      machineMode = PRICE;
      wdt_delay(100);
    } else if (machineMode == PRICE) { 
      machineMode = PRESSURE;
      wdt_delay(100);
    } else {
      machineMode = SALES;
      wdt_delay(100);
    }
    firstTimeOnMode = true;
  }

  //Front Led Control
  for(int i = 1; i < 17; i++){
    leds.write(i, inventory.hasEssence(i));
  }

  //Pressure Control
  if (pressure.read() > 150){    
    ledStrip.turnOn();
    if (pressure.read() < 200){
      compressor.turnOn();
    } 
    if (pressure.read() > 400){
      compressor.turnOff();
    }
  } else {
    ledStrip.turnOff();
    compressor.turnOn();
    display.showScreen(display.DEFEITO_SCREEN);
    noteReader.inhibit(true);
  }

  //SALES MODE
  if (machineMode == SALES && pressure.read() > MINIMUM_PRESSURE_TO_OPERATE){
    if (inventory.hasEssence()){
      noteReader.inhibit(false);  
      if (balance == 0){
        display.showScreen(display.PASSO_A_PASSO_SCREEN, balance);
      }

      if (balance > 0){
        display.showScreen(display.ESCOLHA_SUA_ESSENCIA_SCREEN, balance);
      }
      
      if (noteReader.noteReaded() == noteReader.READING){
        display.showScreen(display.CONTA_DINHEIRO_SCREEN);
        while (noteReader.noteReaded() != noteReader.DONE){
          wdt_reset();  
        };
        balance += noteReader.getLastNote();
      }
  
      pressedEssence = buttons.getButtonPressed();
      if (pressedEssence > 0){
        noteReader.inhibit(true);
        if (balance >= inventory.essencePrice(pressedEssence)){
          if (inventory.hasEssence(pressedEssence)){
            display.showScreen(display.SEPARANDO_ESSENCIA_SCREEN);  
            if(dispenser.pushEssence(pressedEssence)){
              balance -= inventory.essencePrice(pressedEssence);
              inventory.subtract(pressedEssence);
              display.showScreen(display.RETIRE_SUA_ESSENCIA_SCREEN, balance);
              wdt_delay(3000);
              if (balance > 0){
                display.showScreen(display.ESCOLHA_SUA_ESSENCIA_SCREEN, balance);  
              }
            } else { 
              display.showScreen(display.DEFEITO_SCREEN); 
              wdt_delay(2000);
            }
          } else {
            display.showScreen(display.PRODUTO_EM_FALTA_SCREEN); 
            wdt_delay(2000);
          }
        } else {
          display.showScreen(display.SALDO_INSUFICIENTE_SCREEN);
          wdt_delay(3000);
        }
        noteReader.inhibit(false);   
      }
    } else {
      noteReader.inhibit(true);
      display.showScreen(display.MAQUINA_SEM_ESSENCIA_SCREEN);
    }
  }

  //INVENTORY MODE
  if (machineMode == INVENTORY){
    noteReader.inhibit(true);
    if (firstTimeOnMode){
        display.showScreen(display.ESTOQUE_SCREEN);
        firstTimeOnMode = false;
    }
    
    pressedEssence = buttons.getButtonPressed();
    if (pressedEssence > 0){
      display.showScreen(display.ESSENCIA_QUANTIDADE_SCREEN, pressedEssence, inventory.update(pressedEssence), true);
    }
  }

  //PRICE MODE
  if (machineMode == PRICE){
    noteReader.inhibit(true);
    if (firstTimeOnMode){
        display.showScreen(display.PRECO_SCREEN);
        firstTimeOnMode = false;
    }
    
    pressedEssence = buttons.getButtonPressed();
    if (pressedEssence > 0){
      display.showScreen(display.ESSENCIA_PRECO_SCREEN, pressedEssence, inventory.updatePrice(pressedEssence), true);
    }
  }

  //PRESSURE MODE
  if (machineMode == PRESSURE){
      int p = int(pressure.read());
      display.print(String(p));    
  }
}

void wdt_delay(unsigned long milliseconds){
  wdt_reset();
  delay(milliseconds);
  wdt_reset();
}
