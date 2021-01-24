/////////////////////////////////////////////////////////////////
/*
  Created by Berat Özdemir, January 24 , 2021.
*/
/////////////////////////////////////////////////////////////////

#include "PercentageScreen.h"



V20::PercentageScreen::PercentageScreen(char _text[],char _bottomChar, uint16_t _percentage){

    int textlength = strlen(_text);
    char *buf = new char[textlength+1];
    strcpy(buf,_text);
    text=buf;
    bottomChar=_bottomChar;
    percentage=_percentage;
};


void V20::PercentageScreen::draw(VPetLCD *lcd){
   

    int offset = 0;

    if (percentage < 10) {
        offset = 5;
    }
    if (percentage >= 100) {
        offset = -5;
    }

    lcd->drawCharArrayOnLCD(text, screenX + 8, 0, pixelColor);
    lcd->drawLetterOnLCD(bottomChar, screenX, screenY + SPRITES_UPPERCASE_ALPHABET_HEIGHT + 2, pixelColor);
    lcd->drawSymbol( SYMBOL_PERCENT, screenX + 26, screenY + SPRITES_UPPERCASE_ALPHABET_HEIGHT + 1, false, pixelColor);

    lcd->drawIntegerOnLCD(percentage, screenX + 16 + offset, screenY + SPRITES_UPPERCASE_ALPHABET_HEIGHT + 1, pixelColor);


}