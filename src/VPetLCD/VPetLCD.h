/////////////////////////////////////////////////////////////////
/*
  VPetScreen.cpp - Arduino Library to Create a Digimon VPET
  like screen using the TFT_eSPI library
  Created by Berat Özdemir, January 16 , 2021.
*/
/////////////////////////////////////////////////////////////////
#pragma once

#ifndef VPetLCD_h
#define VPetLCD_h
////////////////////////////////////////////////////////////////
#include <TFT_eSPI.h>
#include "LettersAndDigits.h"
#include "Screens/SymbolData.h"


#define SPRITES_DIGIMON_RESOLUTION 16


class VPetLCD {


  private:

    TFT_eSprite *canvas;
    unsigned int menuItemSprites[N_SPRITES_MENU][SPRITES_MENU_RESOLUTION];
    byte symbols[N_SPRITES_SYMBOL][SPRITES_SYMBOL_RESOLUTION];


    uint16_t lcdWidth;
    uint16_t lcdHeight;
    uint16_t lcdX;
    uint16_t lcdY;
    uint16_t lcdScale;


    int16_t selectedMenuItem;



    uint16_t transparencyColor = 0;
    uint16_t backgroundColor = 0x86CE;
    uint16_t lcdInprintColor = 0x64EA;//0xAFF1;
    uint16_t lcdSelectionColor = 0x0001;

    void startRendering();
    void endRendering();

    
  public:

  // Lower level methods to Draw something on the Screen
    void drawPixelOnLCD(int16_t onLcdX, int16_t onLcdY, uint16_t color);
    void drawScaledGrid( uint16_t gwidth, uint16_t gheight);

    void drawMenuItem( uint16_t index, int16_t x, int16_t y, uint16_t scale, boolean mirror, uint16_t color);
    void drawMenu();

    void drawByteArray( const byte toDraw[], uint16_t spriteWidth, uint16_t spriteHeight, int16_t onLcdX, int16_t onLcdY, boolean mirror, uint16_t color);
    void draw16BitArray( const uint16_t toDraw[], int16_t onLcdX, int16_t onLcdY, boolean mirror, uint16_t color);
    
    void drawSymbol( uint16_t index, int16_t onLcdX, int16_t onLcdY, boolean mirror, uint16_t color);

    void drawLetterOnLCD(char c, int16_t onLcdX, int16_t onLcdY, uint16_t color);
    void drawCharArrayOnLCD(char charArr[], int16_t onLcdX, int16_t onLcdY, uint16_t color);

    void drawDigitOnLCD(int16_t digit, int16_t onLcdX, int16_t onLcdY, uint16_t color);
    void drawSmallDigitOnLCD(int16_t digit, int16_t onLcdX, int16_t onLcdY, uint16_t color);
    void drawIntegerOnLCD(int16_t integer, int16_t onLcdX, int16_t onLcdY, uint16_t color);
    void drawZeroPaddedIntegerOnLCD(int16_t integer, int16_t onLcdX, int16_t onLcdY, uint16_t color);
    
    void drawSmallIntegerOnLCD(int16_t digit, int16_t onLcdX, int16_t onLcdY, uint16_t color);
//----------------------------

    
    //Constructor
    VPetLCD(TFT_eSprite *eSprite, int lcdWidth, int lcdHeight);

    //sets the Position of the virtual LCD on the screen
    void setLCDPos(int x, int y){lcdX=x;lcdY=y; }

    //sets the Position of the virtual LCD on the screen
    void setLcdScale(int scale){lcdScale=scale; };

    void setSymbols(const byte sprite[][8]);
    void setMenuItems(const unsigned int sprite[][32]);


  // Abstract class for Screens. Every Screen must be an underclass of screen.
  // after implementing the draw(...) method, one can it with the renderScreen(...) Method
  // So you can easyli implement diffrent Screens with a huge variety in functionality
    class Screen{
      protected:
        uint16_t pixelColor = 0x0001;
        uint16_t screenX = 0;
        uint16_t screenY = 0;
      public:
        virtual void draw(VPetLCD *lcd) = 0;
        void setPixelColor(uint16_t color){pixelColor=color;};
        void setPos(uint16_t x, uint16_t y){screenX = x; screenY = y;};
    };

    //Renders the Content of the Virtual LCD according to the Screen Object
    void renderScreen(Screen *s){
        startRendering();
        s->draw(this);
        endRendering();
    }


    // Set the Selected Menu Item (The Menu will be separated into an own Class)
    void setSelectedMenuItemIndex(int16_t index) {
      selectedMenuItem = index;
    }


    uint16_t getLetterWidth(char c);
    byte getLetterSpriteLine(char c, uint16_t i);


};
#endif
