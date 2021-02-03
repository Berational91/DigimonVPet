/////////////////////////////////////////////////////////////////
/*
  Created by Berat Özdemir, January 24 , 2021.
*/
/////////////////////////////////////////////////////////////////

#include "DigimonWatchingScreen.h"
#include <Arduino.h>

V20::DigimonWatchingScreen::DigimonWatchingScreen(AbstractSpriteManager* _spriteManager, uint8_t _digimonSpritesIndex, int8_t _minX, int8_t _maxX, int8_t _minY, int8_t _maxY) {
  setXLimitations(_minX, _maxX); // -8 32
  setYLimitations(_minY, _maxY);
  digimonX = 8;
  digimonY = 0;
  looksLeft = false;
  looksUp = false;
  probabilityChangeDirection = 20;
  probabilityChangeWalkingSprite = 60;
  probabilityMoveVertical = 25;
  probabilityMakeAnotherMove = 5;
  spriteManager = _spriteManager;
  numberOfPoop = 0;
  poopAnimationCounter = 0;
  updateIntervallTime = 500;
  digimonSpritesIndex=_digimonSpritesIndex;
}


boolean V20::DigimonWatchingScreen::randomDecision(int percent) {
  return percent > random(0, 100);
}

void V20::DigimonWatchingScreen::loop(long delta) {

  if(isNextFrameTime(delta)){


    if(isFlushing){
      if(poopOffsetY<16+8){
        poopOffsetY++;
      }else{
        isFlushing = false;
        poopOffsetY=0;
        numberOfPoop=0;
        numberOfPoopWhileFlushing=0;
        setUpdateIntervallTime(updateIntervallTime*10);
      }
    }else{
    poopAnimationCounter++;
    poopAnimationCounter%=2;
    calculateWalking();
    }
  }

}


void V20::DigimonWatchingScreen::calculateWalking() {

  if (randomDecision(probabilityChangeDirection) || digimonX < minX || digimonX > maxX - numberOfPoop * poopWidth) {
    looksLeft = !looksLeft;
  }

  if (randomDecision(probabilityChangeDirection) || digimonY < minY || digimonY > maxY) {
    looksUp = !looksUp;
  }

  if (randomDecision(probabilityChangeWalkingSprite) || currentWalkSprite == 2) {
    //first two sprites are the walking animations
    currentWalkSprite++;
    currentWalkSprite %= 2;
  }

  if (randomDecision(probabilityMoveVertical)) {
    if (looksUp) {
      if (digimonY < maxY - 1) {
        digimonY++;
      }
      else {
        looksUp = !looksUp;
        if (digimonY > minY + 1)
          digimonY--;
      }
    }
    else {
      if (digimonY > minY + 1) {
        digimonY--;
      }
      else {
        looksUp = !looksUp;
        if (digimonY < maxY - 1)
          digimonY++;
      }
    }
  }

  if (looksLeft) {
    if (digimonX > minX + 1) {
      digimonX--;
    }
    else {
      looksLeft = !looksLeft;
      if (digimonX < maxX - 1 - numberOfPoop * poopWidth)
        digimonX++;
    }
  }
  else {
    if (digimonX < maxX - 1 - numberOfPoop * poopWidth) {
      digimonX++;
    }
    else {
      looksLeft = !looksLeft;
      if (digimonX > minX + 1)
        digimonX--;
    }
  }

  //with probability of 5% make some other moves
  if (randomDecision(probabilityMakeAnotherMove)) {
    currentWalkSprite = SPRITE_DIGIMON_HAPPY;
  }
}

/**
 * draws the poop
 * */
void V20::DigimonWatchingScreen::drawPoop(VPetLCD* lcd) {
  const byte* sprite = spriteManager->getSymbol(SYMBOL_POOP);
  const byte* flushSprite = spriteManager->getSymbol(SYMBOL_POOPWAVE);
  boolean mirrored = poopAnimationCounter == 1;
  uint8_t numPoop = max(numberOfPoopWhileFlushing, numberOfPoop); //numberOfPoop is 0 right before/after flush begun

  for (int i = 0; i < numPoop; i++) {

    if (i % 2 == 0) {
      if(isFlushing)
        lcd->drawByteArray(flushSprite, poopWidth, poopWidth, screenX + maxX - poopWidth - poopWidth * i / 2, screenY - poopWidth+poopOffsetY, mirrored, pixelColor);
      lcd->drawByteArray(sprite, poopWidth, poopWidth, screenX + maxX - poopWidth - poopWidth * i / 2, screenY + poopWidth+poopOffsetY, mirrored, pixelColor);
    }
    else {
      lcd->drawByteArray(sprite, poopWidth, poopWidth, screenX + maxX - poopWidth - poopWidth * (i - 1) / 2, screenY+poopOffsetY, mirrored, pixelColor);
    }
  }
}

void V20::DigimonWatchingScreen::flushPoop(){
  if(numberOfPoop > 0){
    numberOfPoopWhileFlushing=numberOfPoop;
    isFlushing = true;
    poopOffsetY=0;
    setUpdateIntervallTime(updateIntervallTime/10); // be careful of updateIntervalltimes which has 10 not as a factor
  }
}

/**
 * Draws the digimon Walking
 * */
void V20::DigimonWatchingScreen::drawWakedUp(VPetLCD* lcd) {
  const unsigned short* sprite = spriteManager->getDigimonSprite(digimonSpritesIndex, currentWalkSprite);
  lcd->draw16BitArray(sprite, screenX + digimonX, screenY + digimonY, !looksLeft, pixelColor);
}

/**
 * draws the screen
 * */
void V20::DigimonWatchingScreen::draw(VPetLCD* lcd) {
  drawPoop(lcd);
  drawWakedUp(lcd);
}

