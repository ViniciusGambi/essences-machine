#ifndef Display_H
#define Display_H

#include <Arduino.h>
#include "U8glib.h"

class Display
{
public:
   Display(byte pinEnable, byte pinRw, byte pinRs, byte pinReset);
   void prepare();
   void print(String text);
   void mainScreen(int pressure, int balance);
   void showScreen(byte screen, int balance = -1, boolean force = false);
   void showScreen(byte screen, byte essencia, byte qtd, boolean force = false);
   void setScreen(byte screen);
   byte getScreen();
   void printBalance(int balance);

   const byte PASSO_A_PASSO_SCREEN = 1;
   const byte ESCOLHA_SUA_ESSENCIA_SCREEN = 2;
   const byte SEPARANDO_ESSENCIA_SCREEN = 3;
   const byte DEFEITO_SCREEN = 4;
   const byte SALDO_INSUFICIENTE_SCREEN = 5;
   const byte PRODUTO_EM_FALTA_SCREEN = 6;
   const byte ESSENCIA_QUANTIDADE_SCREEN = 7;
   const byte SALDO_INSUFICIENTE_PRODUTO_EM_FALTA_SCREEN = 8;
   const byte MAQUINA_SEM_ESSENCIA_SCREEN = 9;
   const byte RETIRE_SUA_ESSENCIA_SCREEN = 10;
   const byte CONTA_DINHEIRO_SCREEN = 11;
   const byte ESTOQUE_SCREEN = 12;
   const byte PRECO_SCREEN = 13;
   const byte ESSENCIA_PRECO_SCREEN = 14;

private:
   byte _currentScreen;
   U8GLIB_ST7920_128X64_1X *u8g;
};
#endif
