/////////////////////////////////////////////////////////////////
/*
  Created by Berat Özdemir, January 24 , 2021.
*/
/////////////////////////////////////////////////////////////////

#include "../VPetLCD.h"

#define MAX_OPTIONS 16
#define DEFAULT_SYMBOL_INDEX 0

namespace V20{
  /**
 *
 * Draws a Screen with a Selection Menu. Which can have up to 16 options. 
 * The Options can have an Icon and/or Text. Default Icon of an Option is Symbol with index 0.
 * */
  class SelectionScreen : public VPetLCD::Screen{
    private:
      char *selectionText[MAX_OPTIONS];
      uint8_t selectionIconIndex[MAX_OPTIONS];

        //the count of the Options 
      uint8_t nOptions;
      uint8_t currentSelection;

        
      boolean showIcons;
      boolean showText;


    public:
      SelectionScreen(boolean _showIcons);
      void setShowIcons(boolean b){showIcons=b;};
      void setShowText(boolean b){showText=b;};
      
      void addOption(char text[]);
      void addOption(char text[],uint8_t symbolIndex);

      void setIcon(uint8_t optionIndex, uint8_t symbolIndex);

      void setSelection(uint8_t _selection){currentSelection=_selection; };
      void nextSelection();
      uint8_t getSelection();
      void draw(VPetLCD *lcd);
  };

}