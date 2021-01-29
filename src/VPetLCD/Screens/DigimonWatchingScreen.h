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

      boolean randomDecision(int percent);

    public:
      DigimonWatchingScreen(AbstractSpriteManager* _spriteManager,uint8_t digimonSpritesIndex, int8_t _minX, int8_t _maxX,int8_t _minY, int8_t _maxY);
      void draw(VPetLCD *lcd);
      void randomMoveDigimon(); 
      void setXLimitations(int8_t _minX, int8_t _maxX){minX = _minX; maxX = _maxX;};
      void setYLimitations(int8_t _minY, int8_t _maxY){minY = _minY; maxY = _maxY;};
    
  };

};