/////////////////////////////////////////////////////////////////
/*
  Created by Berat Özdemir, January 24 , 2021.
*/
/////////////////////////////////////////////////////////////////

#include "../VPetLCD.h"

namespace V20 {

  class DigimonNameScreen : public VPetLCD::Screen {

  private:
    AbstractSpriteManager* spriteManager;
    char* digimonName;
    uint16_t scrollBoxWidth;
    int scrollOffsetX;
    uint16_t textwidth;
    uint16_t digimonSpriteIndex;


    void calculateTextWidth(VPetLCD* lcd);
    void drawScrollBoxOnLCD(VPetLCD* lcd, char text[], int16_t boxWidth, int16_t currentOffsetX, int16_t OnLcdX, int16_t OnLcdY, uint16_t color);
    void drawNegatedLetterOnLCD(VPetLCD* lcd, char c, int16_t minX, int16_t maxX, int16_t OnLcdX, int16_t OnLcdY, uint16_t color);
    

  public:
  void scrollText();  
    void loop(unsigned long delta);
    DigimonNameScreen(AbstractSpriteManager* _spriteManager, char _digimonName[], uint16_t _digimonSpriteIndex, uint16_t _scrollBoxWidth);
    void draw(VPetLCD* lcd);
    void setDigimonSpriteIndex(uint16_t _digimonSpriteIndex) { digimonSpriteIndex = _digimonSpriteIndex; };


  };
}