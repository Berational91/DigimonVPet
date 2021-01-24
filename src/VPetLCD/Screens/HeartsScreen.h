/////////////////////////////////////////////////////////////////
/*
  Created by Berat Özdemir, January 24 , 2021.
*/
/////////////////////////////////////////////////////////////////

#include "../VPetLCD.h"

namespace V20{



  class HeartsScreen : public VPetLCD::Screen{
    private:
      uint16_t maxHearts;
      uint16_t hearts;
      char* text;

    public:
      HeartsScreen(char _text[], uint16_t _hearts, uint16_t _maxHearts);
      void draw(VPetLCD *lcd);
      void setHearts(uint16_t _hearts){hearts=_hearts;};
      void setMaxHearts(uint16_t _maxHearts){maxHearts=_maxHearts;};
    
  };

};