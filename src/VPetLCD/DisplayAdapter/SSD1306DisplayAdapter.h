#include "AbstractDisplayadapter.h"
#include <Adafruit_SSD1306.h>

class SSD1306DisplayAdapter : public AbstractDisplayAdapter {
private:
      Adafruit_SSD1306* display;

public:

      SSD1306DisplayAdapter(Adafruit_SSD1306* _display, uint16_t resolutionX, uint16_t resolutionY):AbstractDisplayAdapter(resolutionX,resolutionY) { this->display = _display; }

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