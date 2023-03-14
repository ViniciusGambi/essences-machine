#include "Arduino.h"
#include "Display.h"

#include "U8glib.h"

Display::Display(byte pinEnable, byte pinRw, byte pinRs, byte pinReset)
{
    u8g = new U8GLIB_ST7920_128X64_1X(pinEnable, pinRw, pinRs, pinReset); // Enable, RW, RS, RESET

    pinMode(pinReset, OUTPUT);
}

void Display::print(String text)
{
    u8g->firstPage();
    do
    {
        u8g->setFont(u8g_font_unifont);
        u8g->drawStr(0, 22, text.c_str());
    } while (u8g->nextPage());
}

void Display::prepare()
{
    u8g->setFont(u8g_font_6x10);
    u8g->setFontRefHeightExtendedText();
    u8g->setDefaultForegroundColor();
    u8g->setFontPosTop();
    u8g->firstPage();
}

void Display::printBalance(int balance)
{
    if (balance == 0)
    {
        u8g->setPrintPos(76, 61);
    }
    else if (balance < 100)
    {
        u8g->setPrintPos(68, 61);
    }
    else
    {
        u8g->setPrintPos(60, 61);
    }
    u8g->print(balance);
}

void Display::mainScreen(int pressure, int balance)
{
    prepare();
    do
    {
        u8g->setFont(u8g_font_ncenB10);
        u8g->drawStr(1, 45, "PRESSÃO:");
        u8g->setPrintPos(85, 45);
        u8g->print(pressure);
        u8g->drawStr(1, 61, "SALDO:      ,00 R$");
        printBalance(balance);
    }

    while (u8g->nextPage());
    setScreen(70);
}

void Display::showScreen(byte screen, int balance, boolean force)
{
    if (getScreen() != screen)
    {
        prepare();
        do
        {
            if (screen == PASSO_A_PASSO_SCREEN)
            {
                u8g->setFont(u8g_font_helvB08);
                u8g->drawStr(1, 13, "1-INSIRA O DINHEIRO");
                u8g->drawStr(1, 29, "2-ESCOLHA O PRODUTO");
                u8g->drawStr(1, 45, "3-RETIRE SEU PRODUTO");
                u8g->setFont(u8g_font_ncenB10);
                u8g->drawStr(1, 61, "SALDO:      ,00 R$");
                printBalance(balance);
            } 
            else if (screen == ESCOLHA_SUA_ESSENCIA_SCREEN)
            {
                u8g->setFont(u8g_font_ncenB10);
                u8g->drawStr(28, 13, "ESCOLHA");
                u8g->drawStr(48, 29, "SUA");
                u8g->drawStr(24, 45, "ESSENCIA");
                u8g->drawStr(1, 61, "SALDO:      ,00 R$");
                printBalance(balance);
            } 
            else if (screen == SEPARANDO_ESSENCIA_SCREEN)
            {
                u8g->setFont(u8g_font_ncenB10);
                u8g->drawStr(2, 22, "      AGUARDE");
                u8g->setFont(u8g_font_helvB08);
                u8g->drawStr(2, 45, "SEPARANDO ESSENCIA");
            } 
            else if (screen == DEFEITO_SCREEN)
            {
                u8g->setFont(u8g_font_ncenB10);
                u8g->drawStr(25, 17, "DEFEITO");
                u8g->drawStr(7, 35, "CONTATE-NOS");
                u8g->drawStr(15, 57, "43 9 9985 2791");
            } 
            else if (screen == SALDO_INSUFICIENTE_SCREEN)
            {
                u8g->setFont(u8g_font_ncenB10);
                u8g->drawStr(35, 22, "SALDO");
                u8g->drawStr(5, 50, "INSUFICIENTE");
            } 
            else if (screen == PRODUTO_EM_FALTA_SCREEN)
            {
                u8g->setFont(u8g_font_ncenB10);
                u8g->drawStr(27, 15, "PRODUTO");
                u8g->drawStr(55, 29, "EM");
                u8g->drawStr(37, 45, "FALTA");
                u8g->setFont(u8g_font_ncenB10);
                u8g->drawStr(10, 60, "Escolha outro");
            } 
            else if (screen == SALDO_INSUFICIENTE_PRODUTO_EM_FALTA_SCREEN)
            {
                u8g->setFont(u8g_font_ncenB10);
                u8g->drawStr(35, 17, "SALDO");
                u8g->drawStr(5, 35, "INSUFICIENTE");
                u8g->drawStr(1, 50, "Produto em falta");
            } 
            else if (screen == MAQUINA_SEM_ESSENCIA_SCREEN)
            {
                u8g->setFont(u8g_font_ncenB10);
                u8g->drawStr(25, 18, "MAQUINA");
                u8g->drawStr(45, 36, "SEM");
                u8g->drawStr(24, 54, "ESSENCIA");
            } 
            else if (screen == RETIRE_SUA_ESSENCIA_SCREEN)
            {
                u8g->setFont(u8g_font_ncenB10);
                u8g->drawStr(1, 61, "SALDO:      ,00 R$");
                printBalance(balance);
                u8g->drawStr(30, 15, "RETIRE");
                u8g->drawStr(45, 30, "SUA");
                u8g->drawStr(20, 45, "ESSENCIA");
            } 
            else if (screen == CONTA_DINHEIRO_SCREEN)
            {
                u8g->setFont(u8g_font_ncenB10);
                u8g->drawStr(24, 15, "AGUARDE");
                u8g->drawStr(20, 30, "CONTANDO");
                u8g->drawStr(24, 45, "DINHEIRO");
            } 
            else if (screen == ESTOQUE_SCREEN)
            {
                u8g->setFont(u8g_font_ncenB10);
                u8g->drawStr(39, 15, "ESTOQUE");
            } 
            else if (screen == PRECO_SCREEN)
            {
                u8g->setFont(u8g_font_ncenB10);
                u8g->drawStr(39, 15, "PRECO");
            } 
            else
            {
                print("!!");
            }

        }

        while (u8g->nextPage());
        setScreen(screen);
    }
}

void Display::showScreen(byte screen, byte essencia, byte qtd, boolean force)
{
    if (getScreen() != screen || force == true)
    {
        prepare();
        do
        {
            if (screen == ESSENCIA_QUANTIDADE_SCREEN)
            {
                u8g->setFont(u8g_font_helvB08);
                u8g->drawStr(10, 25, "ESSENCIA      :");
                u8g->setPrintPos(90, 25);
                u8g->print(essencia);
                u8g->drawStr(10, 45, "QUANTIDADE :");
                u8g->setPrintPos(90, 45);
                u8g->print(qtd);
            }
            else if (screen == ESSENCIA_PRECO_SCREEN)
            {
                u8g->setFont(u8g_font_helvB08);
                u8g->drawStr(10, 25, "ESSENCIA      :");
                u8g->setPrintPos(90, 25);
                u8g->print(essencia);
                u8g->drawStr(10, 45, "PRECO :");
                u8g->setPrintPos(90, 45);
                u8g->print(qtd);
            }
            else {
                print("!!");
            }
        }
        while (u8g->nextPage());
        setScreen(screen);
    }
}

void Display::setScreen(byte screen)
{
    _currentScreen = screen;
}

byte Display::getScreen()
{
    return _currentScreen;
}