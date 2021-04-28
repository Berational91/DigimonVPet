#include "AbstractDisplayadapter.h"
#include <LedControl.h>

class MAX72XX_Display_Adapter : public AbstractDisplayAdapter {
private:
      LedControl* display;
      byte canvas[8][8]; // 8 rows per led-matrix: first 4 elemens are the top led matrices, last 4 are the bottom matrices

      //returns the index of the byte array in canvas 
      uint8_t getLedMatrixIndex(int32_t x, int32_t y){
            uint8_t index = 0;
            index += x/8;

            if(y > 7){
                  index +=4;
            }
            return index;
      }

      //returns the index of the byte array in canvas 
      uint8_t getOrMask(int8_t x){
             
            return 0b00000001 << x%8;
      }

public:

      MAX72XX_Display_Adapter(LedControl* _display):AbstractDisplayAdapter(32,16) { this->display = _display; }

      //Draws a filled colored rectangle on pos (x,y) with width w and height h 
      void fillRect(int32_t x, int32_t y, int32_t w, int32_t h, uint32_t color);

      //draws a horizontal line starting at (x,y) with length w
      void drawHLine(int32_t x, int32_t y, int32_t w, uint32_t color);

      //draws a vertical line starting at (x,y) with length h
      void drawVLine(int32_t x, int32_t y, int32_t h, uint32_t color);



      //This method creates a Canvas on which could be drawn
      void createCanvas();

      //This method sets the colorDepth of the Canvas
      void setColorDepth(int8_t b);

      //Fills the Canvas with the color

      void fillCanvas(uint32_t color);

      //Pushes the content of the Canvas to the actual Display
      void pushCanvas(int32_t x, int32_t y, uint16_t transparent_color);

      //deletes the current canvas in order to free space.
      void deleteCanvas();

      void drawPixel(int32_t x, int32_t y,uint32_t color);

      
};