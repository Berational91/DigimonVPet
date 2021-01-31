#pragma once
#include "ImageData/SymbolData.h"
#include "ImageData/DigimonSprites.h"
#include "ImageData/LettersAndDigits.h"
#include "ImageData/HighResMenuItems.h"
#include <Arduino.h>



/**
 * The Realization of this class provides all other Classes the sprites
 * Since the access to the progmem is on different platforms different,
 * there must be an implementation for every platform of this class
 * 
 * */
class AbstractSpriteManager{

    public:
        virtual const unsigned short* getDigimonSprite(uint16_t digimonIndex, uint16_t spriteIndex)=0;

        //the small digits array has stored 2 digits in one sprite => 01 on index 0; 23 on index 1 etc.
        //therefore the index is 0-4
        virtual const byte* getSmallDigitsSprite(uint8_t index)=0;
        virtual const byte* getDigitSprite(uint8_t digit)=0;
        virtual const byte* getSmallCapitalLetter(char c)=0;
        virtual const uint8_t getSmallCapitalLetterWidth(char c)=0;
        virtual const byte* getSymbol(uint16_t symbolIndex)=0;
        virtual const uint32_t* getHighResMenuItem(uint16_t menuItemIndex)=0;
        virtual ~AbstractSpriteManager(){};
};



