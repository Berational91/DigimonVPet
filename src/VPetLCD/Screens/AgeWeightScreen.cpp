/////////////////////////////////////////////////////////////////
/*
  Created by Berat Özdemir, January 24 , 2021.
*/
/////////////////////////////////////////////////////////////////

#include "AgeWeightScreen.h"

/**
 * draws a Screen showing the weight and age of the digimon
 *
 */
void V20::AgeWeightScreen::draw(VPetLCD* lcd) {


  lcd->drawSymbol(SYMBOL_PET, screenX, screenY, false, pixelColor);
  lcd->drawSymbol(SYMBOL_SCALE, screenX, screenY + SPRITES_SYMBOL_RESOLUTION, false, pixelColor);

  lcd->drawSymbol(SYMBOL_AGE, screenX + 26, screenY, false, pixelColor);
  lcd->drawSymbol(SYMBOL_WEIGHT, screenX + 25, screenY + SPRITES_SYMBOL_RESOLUTION, false, pixelColor);

  int offsetX = 0;
  if (age < 10) {
    offsetX += SPRITES_DIGITS_WIDTH + 1;
  }



  lcd->drawIntegerOnLCD(age, screenX + 15 + offsetX, screenY, pixelColor);

  offsetX = 0;
  if (weight < 10) {
    offsetX += SPRITES_DIGITS_WIDTH + 1;
  }

  lcd->drawIntegerOnLCD(weight, screenX + 15 + offsetX, screenY + SPRITES_SYMBOL_RESOLUTION, pixelColor);


}
