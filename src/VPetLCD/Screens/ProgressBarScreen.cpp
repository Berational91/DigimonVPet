/////////////////////////////////////////////////////////////////
/*
  Created by Berat Özdemir, January 24 , 2021.
*/
/////////////////////////////////////////////////////////////////

#include "ProgressBarScreen.h"


V20::ProgressBarScreen::ProgressBarScreen(char _text[], uint16_t _barLength, uint16_t _fillPercentage){

    int textlength = strlen(_text);
    char *buf = new char[textlength+1];
    strcpy(buf,_text);
    text=buf;

    barLength=_barLength;
    fillPercentage=_fillPercentage;
};


void V20::ProgressBarScreen::draw(VPetLCD *lcd){


  lcd->drawCharArrayOnLCD(text, screenX, 0, pixelColor);

  lcd->drawPixelOnLCD( screenX, screenY + SPRITES_UPPERCASE_ALPHABET_HEIGHT + 1, pixelColor);
  lcd->drawPixelOnLCD( screenX + barLength / 2 + 1, screenY + SPRITES_UPPERCASE_ALPHABET_HEIGHT + 1, pixelColor);
  lcd->drawPixelOnLCD( screenX + barLength + 1, screenY + SPRITES_UPPERCASE_ALPHABET_HEIGHT + 1, pixelColor);

  for (int i = 1; i <= barLength; i++) {
    lcd->drawPixelOnLCD(i + screenX, screenY + SPRITES_UPPERCASE_ALPHABET_HEIGHT + 2, pixelColor);
    lcd->drawPixelOnLCD(i + screenX, screenY + SPRITES_UPPERCASE_ALPHABET_HEIGHT + 2 + 5, pixelColor);
  }

  for (int i = 0; i < 4; i++) {
    lcd->drawPixelOnLCD( screenX, screenY + SPRITES_UPPERCASE_ALPHABET_HEIGHT + 3 + i, pixelColor);
    lcd->drawPixelOnLCD( screenX + barLength + 1, screenY + SPRITES_UPPERCASE_ALPHABET_HEIGHT + 3 + i, pixelColor);
  }

  uint16_t maxFill = barLength / 2;
  uint16_t percentageBars = fillPercentage * maxFill / 100;


  for (int i = 1; i <= percentageBars; i++) {
    lcd->drawPixelOnLCD( screenX + i * 2, screenY + SPRITES_UPPERCASE_ALPHABET_HEIGHT + 4, pixelColor);
    lcd->drawPixelOnLCD( screenX + i * 2, screenY + SPRITES_UPPERCASE_ALPHABET_HEIGHT + 5, pixelColor);
  }

}