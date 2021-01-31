/////////////////////////////////////////////////////////////////
/*
  Created by Berat Özdemir, January 24 , 2021.
*/
/////////////////////////////////////////////////////////////////

#include "../VPetLCD.h"

namespace V20 {
  /**
 *
 * Renders a Screen showing a screen with a text above a percentage infomation.
 * (For example Displaying WIN Rate)
 *
 * */
  class ClockScreen : public VPetLCD::Screen {
  private:
    uint8_t hours;
    uint8_t minutes;
    uint8_t seconds;
    boolean showAMPM;
    boolean isSetMode;
    
    void incrementSeconds();

  public:
    ClockScreen(boolean _showAMPM);
    void loop(unsigned long delta);
    void setHours(uint8_t _hours) { hours = _hours; }
    void setMinutes(uint8_t _minutes) { minutes = _minutes; }
    void setSeconds(uint8_t _seconds) { seconds = _seconds; }

 

    void draw(VPetLCD* lcd);

  };

}