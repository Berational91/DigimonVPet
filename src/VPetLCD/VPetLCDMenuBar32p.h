
#include "VPetLCD.h"


/**
 * A customizable Menubar. The bar shows n icons at once and scrolls pagewise through all icons.
 * The BarWidth should be the length of your screen
 * */
class VPetLCDMenuBar32p{

    private:
        uint8_t numberOfMenuItems; // number of the items in the menu
        int8_t currentSelection; // index of the current selection

        uint16_t iconColor; //the color of the icons
        uint16_t selectionColor; //the color of the selection

        uint16_t barWidth; //width of the menu bar
        uint16_t barHeight;
        uint8_t iconsPerPage; //how many items should be shown at once

        uint8_t* iconIndices; //the indices of the symbols of the menu items in the HighResMenuitems.h



    public:
        VPetLCDMenuBar32p( uint8_t _numberOfMenuItems, uint8_t _iconsPerPage, uint16_t _barWidth);
        void nextSelection();
        void setSelection(uint8_t menuItemIndex);
        void setIconOnIndex(uint8_t menuItemIndex, uint8_t menuItemIconIndex);
        void drawMenu(VPetLCD* lcd);

        //getter and setter defined in header
        int16_t getSelection(){return currentSelection;};

        void setBarHeight(uint16_t _barHeight){barHeight=_barHeight;};
        void setBarWidth(uint16_t _barWidth){barWidth=_barWidth;};
        uint16_t getBarHeight(){return barHeight;};
        uint16_t getBarWidth(){return barWidth;};
        uint16_t getIconColor(){return iconColor;};
        uint16_t getSelectionColor(){return selectionColor;};
        void setIconColor(uint16_t _iconColor){iconColor=_iconColor;};
        void setSelectionColor(uint16_t _selectionColor){ selectionColor = _selectionColor;};

};
