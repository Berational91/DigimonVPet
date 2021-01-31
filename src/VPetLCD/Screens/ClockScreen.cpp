/////////////////////////////////////////////////////////////////
/*
  Created by Berat Özdemir, January 24 , 2021.
*/
/////////////////////////////////////////////////////////////////

#include "ClockScreen.h"



V20::ClockScreen::ClockScreen(boolean _showAMPM) {
  showAMPM = _showAMPM;
  isSetMode = false;
  setUpdateIntervallTime(1000);
}

void V20::ClockScreen::loop(unsigned long delta ){
  if (isNextFrameTime(delta)){
    incrementSeconds();
  }
}

void V20::ClockScreen::incrementSeconds() {

  seconds++;
  if (seconds == 60) {
    seconds = 0;
    minutes++;
  }

  if (minutes == 60) {
    minutes = 0;
    hours++;
  }

  if (hours == 24) {
    hours = 0;
  }

}

void V20::ClockScreen::draw(VPetLCD* lcd) {
  boolean isAM = hours < 12;

  if (showAMPM) {

    if (hours >= 13) {
      hours -= 12;
    }
    if (hours == 0) {
      hours = 12;
    }

    if (isAM) {
      lcd->drawSymbol(SYMBOL_AM, screenX, screenY + SPRITES_UPPERCASE_ALPHABET_HEIGHT + 2, false, pixelColor);
    }    
else {
      lcd->drawSymbol(SYMBOL_PM, screenX, screenY + SPRITES_UPPERCASE_ALPHABET_HEIGHT + 2, false, pixelColor);
    }

  }

  lcd->drawZeroPaddedIntegerOnLCD(hours, screenX, screenY, pixelColor);
  lcd->drawPixelOnLCD(screenX + 2 * (SPRITES_DIGITS_WIDTH + 1), screenY + 1, pixelColor);
  lcd->drawPixelOnLCD(screenX + 2 * (SPRITES_DIGITS_WIDTH + 1), screenY + 5, pixelColor);
  lcd->drawZeroPaddedIntegerOnLCD(minutes, screenX + 2 * (SPRITES_DIGITS_WIDTH + 1) + 2, screenY, pixelColor);
  lcd->drawSmallIntegerOnLCD(seconds, screenX + 4 * (SPRITES_DIGITS_WIDTH + 1) + 2, screenY + 2, pixelColor);


  //draw the triangles representing the seconds
  int triangleY = screenY + SPRITES_UPPERCASE_ALPHABET_HEIGHT + 2 + 3;
  for (int i = 0; i < 5; i++) {
    lcd->drawSymbol(SYMBOL_EMPTY_TRIANGLE, screenX + 14 + (i * 3), triangleY, false, pixelColor);
  }

  if (seconds % 10 <= 5) {
    for (int i = 0; i < seconds % 10; i++) {
      lcd->drawSymbol(SYMBOL_TRIANGLE, screenX + 14 + (i * 3), triangleY, false, pixelColor);
    }

  }
  if (seconds % 10 > 5) {
    int darkTriangles = 10 - seconds % 10;
    for (int i = 0; i < darkTriangles; i++) {
      lcd->drawSymbol(SYMBOL_TRIANGLE, screenX + 14 + 4 * 3 - (i * 3), triangleY, false, pixelColor);
    }
  }


}