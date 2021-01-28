/////////////////////////////////////////////////////////////////
/*
  Created by Berat Özdemir, January 24 , 2021.
*/
/////////////////////////////////////////////////////////////////

#include "SelectionScreen.h"


V20::SelectionScreen::SelectionScreen(boolean _showIcons){
     nOptions=0;
       currentSelection=0;

        
       showIcons=_showIcons;
       showText=true;

};
void V20::SelectionScreen::addOption(char text[]){
    int textlength = strlen(text);
    char *buf = new char[textlength+1];
    strcpy(buf,text);
    
    if(nOptions < MAX_OPTIONS){
        selectionText[nOptions] = buf;
        selectionIconIndex[nOptions] = DEFAULT_SYMBOL_INDEX;
        nOptions++;
    }else{

    }

}
void V20::SelectionScreen::addOption(char text[],uint8_t symbolIndex){
    addOption(text);
    selectionIconIndex[nOptions-1] = symbolIndex;
}

void V20::SelectionScreen::setIcon(uint8_t optionIndex, uint8_t symbolIndex){
    selectionIconIndex[optionIndex] = symbolIndex;

}

void V20::SelectionScreen::draw(VPetLCD *lcd){

    if(nOptions ==0){
        return;
    }

    int arrowY=0;

    //indices of the text and icons 
    uint8_t text1 =currentSelection;
    uint8_t icon1 =currentSelection;

    uint8_t text2=currentSelection+1;
    uint8_t icon2 =currentSelection+1;

  if(currentSelection % 2 == 1){
    arrowY=SPRITES_SYMBOL_RESOLUTION;
    //if the selection is odd, the arrow should be on the lower option
    text1--;
    icon1--;
    text2--;
    icon2--;
  }
  
  lcd->drawSymbol( SYMBOL_ARROW, screenX+1, screenY + arrowY, false, pixelColor);
  
 
  uint8_t offsetX =0;
  if(showIcons){
      offsetX = SPRITES_SYMBOL_RESOLUTION+1;
    lcd->drawSymbol( selectionIconIndex[icon1] , screenX + SPRITES_SYMBOL_RESOLUTION + 2, screenY, false, pixelColor);
    
    if(icon2 < nOptions)
        lcd->drawSymbol( selectionIconIndex[icon2] , screenX + SPRITES_SYMBOL_RESOLUTION + 2, screenY + SPRITES_SYMBOL_RESOLUTION , false, pixelColor);
  }

  if(showText){
    lcd->drawCharArrayOnLCD(selectionText[text1], screenX + SPRITES_SYMBOL_RESOLUTION + 2+offsetX, screenY+1, pixelColor);
    
    if(text2 < nOptions)
        lcd->drawCharArrayOnLCD(selectionText[text2], screenX + SPRITES_SYMBOL_RESOLUTION + 2+offsetX, screenY+SPRITES_SYMBOL_RESOLUTION+1, pixelColor);
  }
}

void V20::SelectionScreen::nextSelection(){
  currentSelection++;
  currentSelection %= nOptions;
}

uint8_t V20::SelectionScreen::getSelection(){
return currentSelection;
}