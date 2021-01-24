/////////////////////////////////////////////////////////////////
/*
  Created by Berat Özdemir, January 24 , 2021.
*/
/////////////////////////////////////////////////////////////////

#include "../VPetLCD.h"

namespace V20{
  /**
 *
 * Renders a Screen showing a screen with a text above a percentage infomation. 
 * (For example Displaying WIN Rate)
 * 
 * */
  class PercentageScreen : public VPetLCD::Screen{
    private:
      char* text;
      char bottomChar;
      uint16_t percentage;

    public:
      PercentageScreen(char _text[], char _bottomChar, uint16_t _percentage);
      void draw(VPetLCD *lcd);
      void setPercentage(uint16_t _percentage){percentage=_percentage;};

  };

}