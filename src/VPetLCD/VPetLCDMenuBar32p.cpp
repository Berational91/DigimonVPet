#include "VPetLCDMenuBar32p.h"


        /**
         * Constructor - Creates a Menubar with _numberOfMenuItems menuItems. The bar
         * Shows _iconsPerPage icons at once and scrolls pagewise through all icons.
         * The BarWidth should be the length of your screen
         * */
        VPetLCDMenuBar32p::VPetLCDMenuBar32p( uint8_t _numberOfMenuItems, uint8_t _iconsPerPage, uint16_t _barWidth){
            numberOfMenuItems=_numberOfMenuItems;
            barWidth=_barWidth;
            barHeight=SPRITES_MENU_RESOLUTION;//standard is the height of the icons
            iconsPerPage=_iconsPerPage;


            iconColor=0x64EA;
            selectionColor=0x0001;

            iconIndices = new uint8_t[numberOfMenuItems];

            for(int i =0; i<numberOfMenuItems;i++){
                iconIndices[i]=0;
            }
        }

        /**
         *  Changes to the next Icon.
         * 
         * */
        void VPetLCDMenuBar32p::nextSelection(){
            currentSelection++;
            if(currentSelection == numberOfMenuItems){
                currentSelection =-1;
            }
        }


        /**
         * Sets the selections to the given index.
         * */
        void VPetLCDMenuBar32p::setSelection(uint8_t menuItemIndex){
            if(menuItemIndex >=0 && menuItemIndex < numberOfMenuItems){
                currentSelection = menuItemIndex;
            }
        }

        /**
         * Sets the icon for the menu entry. MenuItemIndex is the index of the menu entry, menuItemIconIndex is the  index of the symbol of the menu item in the HighResMenuitems.h 
         * */
        void VPetLCDMenuBar32p::setIconOnIndex(uint8_t menuItemIndex, uint8_t menuItemIconIndex){
                iconIndices[menuItemIndex] = menuItemIconIndex;
        }


        /**
         * Draws the Menu to the given Lcd
         * */
        void VPetLCDMenuBar32p::drawMenu(VPetLCD* lcd){
            uint8_t iconWidth = SPRITES_MENU_RESOLUTION;
            uint8_t numberOfGaps = iconsPerPage-1; //these are the gaps between the icons
            uint16_t gapSize = (barWidth - iconWidth*iconsPerPage)/numberOfGaps; //width of the gaps in pixel
            
            uint8_t page = currentSelection/iconsPerPage;
            uint8_t indexOnPage = currentSelection%iconsPerPage;


            for(int i=0; i < iconsPerPage; i++){
                uint8_t currentIndex = page*iconsPerPage+i;
                if(currentIndex < numberOfMenuItems)
                 lcd->drawMenuItem(iconIndices[currentIndex], i * iconWidth + gapSize * i, 0, 1, false, iconColor);
 
            }

            if (currentSelection > -1) {
                int offset = 2;
                lcd->drawMenuItem(iconIndices[currentSelection], indexOnPage * iconWidth + offset + gapSize * indexOnPage, offset, 1, false, selectionColor);
            }

        }