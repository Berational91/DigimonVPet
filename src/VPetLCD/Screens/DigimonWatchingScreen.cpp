/////////////////////////////////////////////////////////////////
/*
  Created by Berat Özdemir, January 24 , 2021.
*/
/////////////////////////////////////////////////////////////////

#include "DigimonWatchingScreen.h"
#include <Arduino.h>

V20::DigimonWatchingScreen::DigimonWatchingScreen(uint8_t digimonSpritesIndex, int8_t _minX, int8_t _maxX,int8_t _minY, int8_t _maxY){
      setXLimitations(_minX,_maxX); // -8 32
      setYLimitations(_minY,_maxY);
      digimonX=8;
      digimonY=0;
      looksLeft=false;
      looksUp=false;
      probabilityChangeDirection=20;
      probabilityChangeWalkingSprite=60;
      probabilityMoveVertical=25;
      probabilityMakeAnotherMove=5;

}


boolean V20::DigimonWatchingScreen::randomDecision(int percent) {
  return percent > random(0, 100);
}

void V20::DigimonWatchingScreen::randomMoveDigimon(){
    //those magic numbers -8 32 and 40 are the displays borders
    // the 
    if (randomDecision(probabilityChangeDirection) || digimonX < minX || digimonX > maxX) {
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

    if(randomDecision(probabilityMoveVertical)){
        if(looksUp){
            digimonY++;
        }else{
            digimonY--;
        }
    }

    if (looksLeft) {
      digimonX--;
    } else {
      digimonX++;
    }

    //with probability of 5% make some other moves
    if (randomDecision(probabilityMakeAnotherMove)) {
      currentWalkSprite = SPRITE_DIGIMON_MOVE;
    }

    
}

void V20::DigimonWatchingScreen::draw(VPetLCD *lcd){
    lcd->draw16BitArray(DIGIMON[digimonSpritesIndex][currentWalkSprite],digimonX,digimonY,!looksLeft,pixelColor);
}
      
