/////////////////////////////////////////////////////////////////
/*
  Created by Berat Özdemir, January 24 , 2021.
*/
/////////////////////////////////////////////////////////////////

#include "../VPetLCD.h"

namespace V20{



  class DigimonWatchingScreen : public VPetLCD::Screen{
    private:
      AbstractSpriteManager* spriteManager;

      uint8_t digimonSpritesIndex=0;
      int8_t digimonX=0;
      int8_t digimonY=0;
      boolean looksLeft;
      boolean looksUp;

    //those are the limits of the digimons movement
      int8_t maxX=0;
      int8_t minX=0;
      int8_t maxY=0;
      int8_t minY=0;

      uint8_t probabilityChangeDirection=0;
      uint8_t probabilityMoveVertical=0;
      uint8_t probabilityMakeAnotherMove=0;
      uint8_t probabilityChangeWalkingSprite=0;
      
      uint8_t currentWalkSprite=0;

      //Poop drawing stuff
      uint8_t numberOfPoop=0; //theAmount of poop on the screen; This will be set to 0 before/right after flushpoop(); is called 
      uint8_t numberOfPoopWhileFlushing=0; //theAmount of poop on the screen While Flushing Needed because read above
      uint8_t poopWidth = SPRITES_SYMBOL_RESOLUTION; //the width of poop in pixel
      uint8_t poopAnimationCounter=0;
      uint8_t poopOffsetY=0; // the offset when flushing
      boolean isFlushing=false;
      void drawPoop(VPetLCD* lcd);


      boolean randomDecision(int percent);

      void calculateWalking();
      

      void drawWakedUp(VPetLCD *lcd);
      void drawSleeping(VPetLCD *lcd, boolean inBed);

    public:
      DigimonWatchingScreen(AbstractSpriteManager* _spriteManager,uint8_t _digimonSpritesIndex, int8_t _minX, int8_t _maxX,int8_t _minY, int8_t _maxY);
      void draw(VPetLCD *lcd);
      void loop(long delta); 
      void setXLimitations(int8_t _minX, int8_t _maxX){minX = _minX; maxX = _maxX;};
      void setYLimitations(int8_t _minY, int8_t _maxY){minY = _minY; maxY = _maxY;};
      void setNumberOfPoop(uint8_t _numberOfPoop){numberOfPoop=_numberOfPoop;};
      void flushPoop();
    
  };

};