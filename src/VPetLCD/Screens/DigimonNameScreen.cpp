/////////////////////////////////////////////////////////////////
/*
  Created by Berat Özdemir, January 24 , 2021.
*/
/////////////////////////////////////////////////////////////////

#include "DigimonNameScreen.h"

V20::DigimonNameScreen::DigimonNameScreen(AbstractSpriteManager* _spriteManager,char _digimonName[], uint16_t _digimonSpriteIndex, uint16_t _scrollBoxWidth) {

  int namelength = strlen(_digimonName);
  char* buf = new char[namelength + 1];
  strcpy(buf, _digimonName);
  digimonName = buf;

  digimonSpriteIndex = _digimonSpriteIndex;
  scrollBoxWidth = _scrollBoxWidth;
  spriteManager=_spriteManager;
  //initializing it with 20 because, if it's zero before displaying the first time
  //the text will be out of box at the first displaying
  textwidth = 20;
}


void V20::DigimonNameScreen::calculateTextWidth(VPetLCD* lcd) {
  textwidth = 0;
  int letters = strlen(digimonName);
  for (int i = 0; i < letters; i++) {
    char c = digimonName[i];

    textwidth += spriteManager->getSmallCapitalLetterWidth(c);
  }
}


void V20::DigimonNameScreen::draw(VPetLCD* lcd) {
  //calculating the width of the text
// void drawScrollBoxOnLCD(char text[], int16_t boxWidth, int16_t currentOffsetX, int16_t OnLcdX, int16_t OnLcdY, uint16_t color );
  const unsigned short *sprite = spriteManager->getDigimonSprite(digimonSpriteIndex,SPRITE_DIGIMON_WALK_0);
  
  lcd->draw16BitArray(sprite, screenX, screenY, false, pixelColor);
  drawScrollBoxOnLCD(lcd, digimonName, scrollBoxWidth, scrollOffsetX, screenX + SPRITES_DIGIMON_RESOLUTION, screenY + 8, pixelColor);
}


void V20::DigimonNameScreen::scrollText() {

  scrollOffsetX += 1;

  if (scrollOffsetX >= textwidth) {
    scrollOffsetX = -scrollBoxWidth + 1;
    // scrollOffsetX = -2*textwidth + scrollOffsetX;
  }

}


void V20::DigimonNameScreen::drawScrollBoxOnLCD(VPetLCD* lcd, char text[], int16_t boxWidth, int16_t currentOffsetX, int16_t OnLcdX, int16_t OnLcdY, uint16_t color) {

  //  drawNegatedLetterOnLCD(char c, OnLcdX, OnLcdX+boxWidth,  OnLcdX, OnLcdY, color);
  calculateTextWidth(lcd);
  int n_chars = strlen(text);

  int offsetX = -currentOffsetX;

  //filler for blank black box with no content of length boxwidth; 5 is the width of a black box drawn by drawNegatedLetterOnLCD with c= -1
  for (int i = 0; i < boxWidth / 5 + 1; i++) {
    offsetX -= 7; //5 is the width of a black box drawn by drawNegatedLetterOnLCD with c= -1
    drawNegatedLetterOnLCD(lcd, 0, OnLcdX, OnLcdX + boxWidth, OnLcdX + offsetX, OnLcdY, color);
  }

  offsetX = -currentOffsetX;

  for (int i = 0; i < n_chars; i++) {

    //current character
    char c = text[i];

    int spriteWidth = spriteManager->getSmallCapitalLetterWidth(c);
    drawNegatedLetterOnLCD(lcd, c, OnLcdX, OnLcdX + boxWidth, OnLcdX + offsetX, OnLcdY, color);

    offsetX += spriteWidth + 1; //plus 1 because there should be a space of 1 pixel between characters

  }

  //filler for blank black box with no content of length boxwidth; 5 is the width of a black box drawn by drawNegatedLetterOnLCD with c= -1
  for (int i = 0; i < boxWidth / 5 + 1; i++) {
    drawNegatedLetterOnLCD(lcd, 0, OnLcdX, OnLcdX + boxWidth, OnLcdX + offsetX, OnLcdY, color);
    offsetX += 5; //5 is the width of a black box drawn by drawNegatedLetterOnLCD with c= -1
  }
}


/**
 * Draws a character to the simulated LCD but negated in a black box
 *
 * @param c the character, that should be drawn (must be a letter)
 * @param OnLcdX x coordinate where the character should be drawn on the simulated LCD
 * @param OnLcdY y coordinate where the character should be drawn on the simulated LCD
 * @param color the color of the character
 *
 */
void V20::DigimonNameScreen::drawNegatedLetterOnLCD(VPetLCD* lcd, char c, int16_t minX, int16_t maxX, int16_t OnLcdX, int16_t OnLcdY, uint16_t color) {

  int spriteHeight = SPRITES_UPPERCASE_ALPHABET_HEIGHT;
  int spriteWidth = 4;
  const byte* sprite = spriteManager->getSmallCapitalLetter(c);
  //array for the negated character with one bottom line more and one top line more
  byte negatedChar[] = { 0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF };

  //draw black box for negative c
  if (c == 0) {
    spriteWidth = 6;
  }  
else {
    spriteWidth = spriteManager->getSmallCapitalLetterWidth(c);
    for (int i = 0; i < SPRITES_UPPERCASE_ALPHABET_HEIGHT; i++) {
      //shifting left 
      negatedChar[i + 1] = sprite[i];
      negatedChar[i + 1] = negatedChar[i + 1] >> 1;
      negatedChar[i + 1] = ~negatedChar[i + 1];
    }
  }
  // drawByteArray( capitalAlphabetSmall[arrayPos] , spriteWidth+1, spriteHeight+2, OnLcdX, OnLcdY, false, color);

  for (int currentY = 0; currentY < spriteHeight + 2; currentY++) {
    byte mask = 0b10000000;
    for (int currentX = 0; currentX < spriteWidth + 1; currentX++) {

      if ((negatedChar[currentY] & mask) && OnLcdX + currentX >= minX && OnLcdX + currentX < maxX) {
        lcd->drawPixelOnLCD(OnLcdX + currentX, OnLcdY + currentY, color);
      }
      mask = mask >> 1;
    }
  }

}


void V20::DigimonNameScreen::loop(unsigned long delta){
  if ( isNextFrameTime(delta) ){
    scrollText();
  }

}