/////////////////////////////////////////////////////////////////
/*
  Created by Berat Özdemir, January 24 , 2021.
*/
/////////////////////////////////////////////////////////////////

#include "HeartsScreen.h"


V20::HeartsScreen::HeartsScreen(char _text[], uint16_t _hearts, uint16_t _maxHearts){
  int textlength = strlen(_text);
  char *buf = new char[textlength+1];
  strcpy(buf,_text);
  text=buf;
  
  maxHearts=_maxHearts;
  hearts=_hearts;
}


/**
 * Renders a Screen showing a screen with hearts and a text above it. 
 * 
 * @param text the text that should be displayed above the hearts
 * @param hearts amount of filled hearts
 * @param maxHearts amount of the maximal amount of hearts (there will be maxhearts - hearts empty hearts)
 * @param lcdPosX the x position of the menu on the simulated LCD
 * @param lcdPosY the y position of the menu on the simulated LCD
 */
void V20::HeartsScreen::draw(VPetLCD *lcd) {

  
  lcd->drawCharArrayOnLCD(text, screenX, 0, pixelColor);
  for (int i = 0; i < hearts; i++) {
    lcd->drawSymbol( SYMBOL_HEART, screenX + i * SPRITES_SYMBOL_RESOLUTION, screenY + SPRITES_UPPERCASE_ALPHABET_HEIGHT, false, pixelColor);
  }

  for (int i = 0; i < maxHearts - hearts; i++) {
    lcd->drawSymbol( SYMBOL_HEARTEMPTY, screenX + (hearts + i)*SPRITES_SYMBOL_RESOLUTION, screenY + SPRITES_UPPERCASE_ALPHABET_HEIGHT, false, pixelColor);
  }

}
