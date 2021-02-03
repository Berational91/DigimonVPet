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

      uint8_t digimonSpritesIndex;
      int8_t digimonX;
      int8_t digimonY;
      boolean looksLeft;
      boolean looksUp;

    //those are the limits of the digimons movement
      int8_t maxX;
      int8_t minX;
      int8_t maxY;
      int8_t minY;

      uint8_t probabilityChangeDirection;
      uint8_t probabilityMoveVertical;
      uint8_t probabilityMakeAnotherMove;
      uint8_t probabilityChangeWalkingSprite;
      
      uint8_t currentWalkSprite;

      //Poop drawing stuff
      uint8_t numberOfPoop; //theAmount of poop on the screen; This will be set to 0 before/right after flushpoop(); is called 
      uint8_t numberOfPoopWhileFlushing; //theAmount of poop on the screen While Flushing Needed because read above
      uint8_t poopWidth = SPRITES_SYMBOL_RESOLUTION; //the width of poop in pixel
      uint8_t poopAnimationCounter;
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