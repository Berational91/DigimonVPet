#include "SSD1306DisplayAdapter.h"

//Draws a filled colored rectangle on pos (x,y) with width w and height h 
void SSD1306DisplayAdapter::fillRect(int32_t x, int32_t y, int32_t w, int32_t h, uint32_t color) {
    display->fillRect(x, y, w, h, color);
}

//draws a horizontal line starting at (x,y) with length w
void SSD1306DisplayAdapter::drawHLine(int32_t x, int32_t y, int32_t w, uint32_t color) {
    display->drawFastHLine(x, y, w, color);
}

//draws a vertical line starting at (x,y) with length h
void SSD1306DisplayAdapter::drawVLine(int32_t x, int32_t y, int32_t h, uint32_t color) {
    display->drawFastVLine(x, y, h, color);
}


//This method creates a Canvas on which could be drawn
void SSD1306DisplayAdapter::createCanvas() {
   // display->createSprite(canvasWidth, canvasHeight);
}


//This method sets the colorDepth of the Canvas
void SSD1306DisplayAdapter::setColorDepth(int8_t b) {
    //display->setColorDepth(b);
   
}

//Fills the Canvas with the color
void SSD1306DisplayAdapter::fillCanvas(uint32_t color) {
    display->fillScreen(color);
}

//Pushes the content of the Canvas to the actual Display
//transparent_color will not be rendered
void SSD1306DisplayAdapter::pushCanvas(int32_t x, int32_t y, uint16_t transparent_color) {
    display->display();
}

//deletes the current canvas in order to free space.
void SSD1306DisplayAdapter::deleteCanvas() {
    display->clearDisplay();
}