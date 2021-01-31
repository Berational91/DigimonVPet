/////////////////////////////////////////////////////////////////
/*
  VPetLCD.cpp - Arduino Library to Create a Digimon VPET
  like screen using the TFT_eSPI library
  Created by Berat Özdemir, January 16 , 2021.
*/
/////////////////////////////////////////////////////////////////
#include "VPetLCD.h"
#include "VPetLCDMenuBar32p.h"

/**
   This Function draws the Menu icon selected by the index on the actual screen (not the simulated LCD)

   @param index the index of the sprite menu icon from menuItemSprites
   @param x x coordinate where the icon should be drawn
   @param y y coordinate where the icon should be drawn
   @param scale the icon will be scaled by this factor
   @param mirror if true, the icon will be drawn mirrored
   @param color the color of the icon

*/
void VPetLCD::drawMenuItem(uint16_t index, int16_t x, int16_t y, uint16_t scale, boolean mirror, uint16_t color) {

  //Since the icons are monochrome, and stored with one bit per pixel. The images
  //are stored with one integer per row.
  //Thee image is restored by reading it bit-wise. This happens with a mask
  //which has one 1 entry, which is shifted every iteration until the whole
  // image is restored

  const uint32_t* sprite = spriteManager->getHighResMenuItem(index);

  for (int currentY = 0; currentY < SPRITES_MENU_RESOLUTION; currentY++) {
    //initializing mask to read pixel out of the integer
    unsigned int mask = 0b10000000000000000000000000000000;

    //if mirror read from left to right
    if (mirror)
      mask = 0b00000000000000000000000000000001;

    for (int currentX = 0; currentX < SPRITES_MENU_RESOLUTION; currentX++) {

      if (sprite[currentY] & mask) {
        canvas->fillRect((x + currentX) * scale, (y + currentY) * scale, scale, scale, color);
      }

      //if mirror read from left to right
      if (mirror)
        mask = mask << 1;
      else
        mask = mask >> 1;
    }
  }
}

/**
   This Function draws the byte array given by toDraw[] to the simulated LCD.

   @param toDraw[] the monochrome Sprite to be drawn, where one byte represents one line of the sprite
   @param spriteWidth width of the sprite
   @param spriteHeight height of the sprite
   @param onLcdX x coordinate where the icon should be drawn on the simulated LCD
   @param onLcdY y coordinate where the icon should be drawn on the simulated LCD
   @param mirror if true, the icon will be drawn mirrored
   @param color the color of the icon

*/
void VPetLCD::drawByteArray(const byte toDraw[], uint16_t spriteWidth, uint16_t spriteHeight, int16_t onLcdX, int16_t onLcdY, boolean mirror, uint16_t color) {

  //look in drawMenuItem(...) for explaination

  for (int currentY = 0; currentY < spriteHeight; currentY++) {

    byte mask = 0b10000000;
    if (mirror)
      mask = 0b00000001;

    for (int currentX = 0; currentX < spriteWidth; currentX++) {

      if (toDraw[currentY] & mask) {
        drawPixelOnLCD(onLcdX + currentX, onLcdY + currentY, color);
      }

      if (mirror)
        mask = mask << 1;
      else
        mask = mask >> 1;
    }
  }
}

/**
 * This function draws the Top/Bottom Menu of the VPET LCD
 */
void VPetLCD::drawMenu() {
  if (menuBar != NULL) {
    menuBar->drawMenu(this);
  }
}

/**
 * Draws the simulated LCD-Dotmatrix to the screen.
 *
 * @param resolutionX the x resolution of the simulated LCD-Dotmatrix
 * @param resolutionY the x resolution of the simulated LCD-Dotmatrix
 *
 */
void VPetLCD::drawScaledGrid(uint16_t resolutionX, uint16_t resolutionY) {

  for (int currentY = 0; currentY < resolutionY; currentY++) {
    for (int currentX = 0; currentX < resolutionX; currentX++) {
      //creating grid by drawing hollow rectangles which is not verry efficient..
      canvas->fillRect(lcdX + currentX * lcdScale, lcdY + currentY * lcdScale, lcdScale, lcdScale, lcdInprintColor);
      canvas->fillRect(lcdX + currentX * lcdScale + 1, lcdY + currentY * lcdScale + 1, lcdScale - 2, lcdScale - 2, backgroundColor);
    }
  }

  /*
   *
   * This is a alternative (more efficient, on the ESP32 2-3 FPS faster) way to draw a grid, but the above one looks better
   */
   /*

     canvas->fillRect(lcdX , lcdY, lcdScale*resolutionX, lcdScale*resolutionY, lcdInprintColor);
     for (int currentY = 0; currentY < resolutionY+1; currentY++)
     {
       canvas->drawFastHLine(lcdX, lcdY + currentY*lcdScale, resolutionX*(lcdScale),backgroundColor);
     }

     for (int currentX = 0; currentX < resolutionX+1; currentX++)
     {
       canvas->drawFastVLine(lcdX+currentX*lcdScale, lcdY , resolutionY*(lcdScale),backgroundColor);
     }*/
}

/**
 * Draws the sprite of the Digimon to the simulated LCD
 *
 * @param index the index of the sprite of the digimon
 * @param onLcdX x coordinate where the digimon should be drawn on the simulated LCD
 * @param onLcdY y coordinate where the digimon should be drawn on the simulated LCD
 * @param mirror if true, the digimon will be drawn mirrored
 * @param color the color of the digimon
 *
 */
void VPetLCD::draw16BitArray(const uint16_t toDraw[], int16_t onLcdX, int16_t onLcdY, boolean mirror, uint16_t color) {

  int spriteWidth = SPRITES_DIGIMON_RESOLUTION;
  int spriteHeight = SPRITES_DIGIMON_RESOLUTION;

  for (int currentY = 0; currentY < spriteHeight; currentY++) {

    unsigned short mask = 0b1000000000000000;
    if (mirror)
      mask = 0b0000000000000001;

    for (int currentX = 0; currentX < spriteWidth; currentX++) {

      if (toDraw[currentY] & mask) {
        drawPixelOnLCD(onLcdX + currentX, onLcdY + currentY, color);
      }

      if (mirror)
        mask = mask << 1;
      else
        mask = mask >> 1;
    }
  }
}

/**
 * Draws the symbol on given index to the simulated LCD
 *
 * @param index the index of the symbol
 * @param onLcdX x coordinate where the symbol should be drawn on the simulated LCD
 * @param onLcdY y coordinate where the symbol should be drawn on the simulated LCD
 * @param mirror if true, the symbol will be drawn mirrored
 * @param color the color of the symbol
 *
 */
void VPetLCD::drawSymbol(uint16_t index, int16_t onLcdX, int16_t onLcdY, boolean mirror, uint16_t color) {

  int spriteWidth = SPRITES_SYMBOL_RESOLUTION;
  int spriteHeight = SPRITES_SYMBOL_RESOLUTION;
  const byte* sprite = spriteManager->getSymbol(index);
  drawByteArray(sprite, spriteWidth, spriteHeight, onLcdX, onLcdY, mirror, color);
}

/**
 * Draws a Pixel the simulated LCD
 *
 * @param onLcdX x coordinate where the pixel should be drawn on the simulated LCD
 * @param onLcdY y coordinate where the pixel should be drawn on the simulated LCD
 * @param color the color of the pixel
 *
 */
void VPetLCD::drawPixelOnLCD(int16_t onLcdX, int16_t onLcdY, uint16_t color) {

  //do nothin if pixel is out of lcd
  if (onLcdX < 0 || onLcdY < 0 || onLcdX >= lcdWidth || onLcdY >= lcdHeight) {
    return;
  }
  canvas->fillRect(lcdX + onLcdX * lcdScale, lcdY + onLcdY * lcdScale, lcdScale, lcdScale, color);
}

/**
 * Draws a character to the simulated LDC
 *
 * @param c the character, that should be drawn (must be a letter)
 * @param onLcdX x coordinate where the character should be drawn on the simulated LCD
 * @param onLcdY y coordinate where the character should be drawn on the simulated LCD
 * @param color the color of the character
 *
 */
void VPetLCD::drawLetterOnLCD(char c, int16_t onLcdX, int16_t onLcdY, uint16_t color) {

  int spriteHeight = SPRITES_UPPERCASE_ALPHABET_HEIGHT;
  int spriteWidth = 4;


  spriteWidth = spriteManager->getSmallCapitalLetterWidth(c);
  const byte* sprite = spriteManager->getSmallCapitalLetter(c);

  drawByteArray(sprite, spriteWidth, spriteHeight, onLcdX, onLcdY, false, color);
}

/**
 * Draws an array of characters (String) to the simulated LCD
 *
 * @param charArr[] the character array that should be drawn (must consist only letters)
 * @param onLcdX x coordinate where the character array should be drawn on the simulated LCD
 * @param onLcdY y coordinate where the character array should be drawn on the simulated LCD
 * @param color the color of the character array
 *
 */
void VPetLCD::drawCharArrayOnLCD(char charArr[], int16_t onLcdX, int16_t onLcdY, uint16_t color) {

  int n_chars = strlen(charArr);

  int offsetX = 0;

  for (int i = 0; i < n_chars; i++) {

    //current character
    char c = charArr[i];

    int spriteWidth = spriteManager->getSmallCapitalLetterWidth(c);

    drawLetterOnLCD(c, onLcdX + offsetX, onLcdY, color);

    offsetX += spriteWidth + 1; //plus 1 because there should be a space of 1 pixel between characters
  }
}

/**
 * Draws a digit to the simulated LDC
 *
 * @param digit an integer in the interaval [0,9]
 * @param onLcdX x coordinate where the digit should be drawn on the simulated LCD
 * @param onLcdY y coordinate where the digit should be drawn on the simulated LCD
 * @param color the color of the character
 *
 */
void VPetLCD::drawDigitOnLCD(int16_t digit, int16_t onLcdX, int16_t onLcdY, uint16_t color) {
  int spriteHeight = SPRITES_DIGITS_HEIGHT;
  int spriteWidth = SPRITES_DIGITS_WIDTH;
  const byte* sprite = spriteManager->getDigitSprite(digit);

  drawByteArray(sprite, spriteWidth, spriteHeight, onLcdX, onLcdY, false, color);
}

/**
 * Draws a small digit to the simulated LDC
 *
 * @param digit an integer in the interaval [0,9]
 * @param onLcdX x coordinate where the digit should be drawn on the simulated LCD
 * @param onLcdY y coordinate where the digit should be drawn on the simulated LCD
 * @param color the color of the character
 *
 */
void VPetLCD::drawSmallDigitOnLCD(int16_t digit, int16_t onLcdX, int16_t onLcdY, uint16_t color) {
  int spriteHeight = SPRITES_SMALL_DIGITS_HEIGHT;
  int spriteWidth = SPRITES_SMALL_DIGITS_WIDTH;
  const byte* sprite = spriteManager->getSmallDigitsSprite(digit / 2);
  byte mask = 0b01000000;

  //since the small digits are compressed (2 digits in one sprite), determine if the sprite is left (even) or right (odd)
  if (digit % 2 == 1) {
    //set mask properly to sample from the right sprite
    mask = 0b00000100;
  }

  for (int currentY = 0; currentY < spriteHeight; currentY++) {
    if (digit % 2 == 1) {
      mask = 0b00000100;
    }
    else {
      mask = 0b01000000;
    }
    for (int currentX = 0; currentX < spriteWidth; currentX++) {

      //the digit/2 is in order to get the correct index of the sprite, since there are 2 digits together in the smallsprites
      if (sprite[currentY] & mask) {
        drawPixelOnLCD(onLcdX + currentX, onLcdY + currentY, color);
      }
      mask = mask >> 1;
    }
  }
}

/**
 * Draws an integer to the simulated LDC
 *
 * @param integer draws an (at the moment positive) integer to the simulated LCD
 * @param onLcdX x coordinate where the digit should be drawn on the simulated LCD
 * @param onLcdY y coordinate where the digit should be drawn on the simulated LCD
 * @param color the color of the character
 *
 */
void VPetLCD::drawIntegerOnLCD(int16_t integer, int16_t onLcdX, int16_t onLcdY, uint16_t color) {

  int16_t spriteWidth = SPRITES_DIGITS_WIDTH;

  //if there is just one digit, then just draw it
  if (integer >= 0 && integer < 10) {
    drawDigitOnLCD(integer, onLcdX, onLcdY, color);
    return;
  }

  //we need to determine how many digits the integer has in order to calculate the width(offset)
  //because, we will get the last digit first in the second while loop.
  int copy = integer;
  int16_t offset = 0;

  while (copy != 0) {
    offset += spriteWidth + 1;
    copy /= 10;
  }

  while (integer != 0) {
    offset -= spriteWidth + 1;
    drawDigitOnLCD(integer % 10, onLcdX + offset, onLcdY, color);
    integer /= 10;
  }
}

/**
 * Draws an integer to the simulated LCD, but with zero pad
 *
 * @param integer draws an (at the moment positive) integer to the simulated LCD
 * @param onLcdX x coordinate where the digit should be drawn on the simulated LCD
 * @param onLcdY y coordinate where the digit should be drawn on the simulated LCD
 * @param color the color of the character
 *
 */
void VPetLCD::drawZeroPaddedIntegerOnLCD(int16_t integer, int16_t onLcdX, int16_t onLcdY, uint16_t color)
{

  //if there is just one digit, then just draw it
  if (integer >= 0 && integer < 10) {
    drawDigitOnLCD(0, onLcdX, onLcdY, color);
    drawIntegerOnLCD(integer, onLcdX + SPRITES_DIGITS_WIDTH + 1, onLcdY, color);
    return;
  }

  drawIntegerOnLCD(integer, onLcdX, onLcdY, color);
}

/**
 * Draws an small integer to the simulated LCD, which is zero padded up to 2 digits
 *
 * @param integer draws an (at the moment positive) integer to the simulated LCD
 * @param onLcdX x coordinate where the digit should be drawn on the simulated LCD
 * @param onLcdY y coordinate where the digit should be drawn on the simulated LCD
 * @param color the color of the character
 *
 */
void VPetLCD::drawSmallIntegerOnLCD(int16_t integer, int16_t onLcdX, int16_t onLcdY, uint16_t color)
{

  int16_t spriteWidth = SPRITES_SMALL_DIGITS_WIDTH;

  //if there is just one digit, then just draw it
  if (integer >= 0 && integer < 10) {
    drawSmallDigitOnLCD(0, onLcdX, onLcdY, color);
    drawSmallDigitOnLCD(integer, onLcdX + SPRITES_SMALL_DIGITS_WIDTH + 1, onLcdY, color);
    return;
  }

  //we need to determine how many digits the integer has in order to calculate the width(offset)
  //because, we will get the last digit first in the second while loop.
  int copy = integer;
  int16_t offset = 0;

  while (copy != 0) {
    offset += spriteWidth + 1;
    copy /= 10;
  }

  while (integer != 0) {
    offset -= spriteWidth + 1;
    drawSmallDigitOnLCD(integer % 10, onLcdX + offset, onLcdY, color);
    integer /= 10;
  }
}

/**
 * This method has to be called in every method that renders something to the TFT_eSprite canvas attribute bevor drawing something
*/
void VPetLCD::startRendering() {

  canvas->fillCanvas(backgroundColor);
  drawScaledGrid(lcdWidth, lcdHeight);
}

/**
 * This method has to be called in every method that renders something to the TFT_eSprite canvas attribute after drawing something
 */
void VPetLCD::endRendering() {
  drawMenu();
  // Push sprite to TFT screen CGRAM at coordinate x,y (top left corner)
  // Specify what colour is to be treated as transparent (black in this example)
  canvas->pushCanvas(0, 0, transparencyColor);
  // Delete Sprite to free memory, creating and deleting takes very little time.
}

//////////////////////Constructor/////////////////////////////

/**
   This is the Constructor.

   @param tft Pointer to TFT_eSPrite object, which should be the output
   @param lcdWidth determines the width in Pixels of the virtual VPET-LCD (32  for VPet 20th)
   @param lcdHeight determines the width in Pixels of the virtual VPET-LCD (16  for VPet 20th)
*/
VPetLCD::VPetLCD(AbstractDisplayAdapter* displayAdapter, AbstractSpriteManager* _spriteManager, int lcdWidth, int lcdHeight) {

  this->canvas = displayAdapter;
  this->lcdHeight = lcdHeight;
  this->lcdWidth = lcdWidth;
  spriteManager = _spriteManager;
  this->lcdX = 0;
  this->lcdY = 0;

  this->lcdScale = 6;

  canvas->createCanvas();
  canvas->setColorDepth(16);
}


void VPetLCD::setMenuBar(VPetLCDMenuBar32p* _menuBar) {
  menuBar = _menuBar;
  this->lcdY = menuBar->getBarHeight();
};


/**
 * adds delta to timeSincelastupdate and returns true if updateIntervallTime is exceeded
 *@returns true if the last frame is updateIntervallTime ms ago, false if not. 
 * */
boolean VPetLCD::Screen::isNextFrameTime(long delta) {

  timeSinceLastUpdate += delta;
  if (timeSinceLastUpdate > updateIntervallTime)
  {
    timeSinceLastUpdate %= updateIntervallTime;
    return true;
  }
  return false;

}
