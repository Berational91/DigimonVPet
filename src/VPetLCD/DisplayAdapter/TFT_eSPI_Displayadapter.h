#include "AbstractDisplayadapter.h"
#include <TFT_eSPI.h>

class TFT_eSPI_DisplayAdapter : public AbstractDisplayAdapter {
private:
      TFT_eSprite* eSprite;

public:

      TFT_eSPI_DisplayAdapter(TFT_eSprite* eSprite, uint16_t resolutionX, uint16_t resolutionY):AbstractDisplayAdapter(resolutionX,resolutionY) { this->eSprite = eSprite; }

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
};