#include "TFT_eSPI_Displayadapter.h"

//Draws a filled colored rectangle on pos (x,y) with width w and height h 
void TFT_eSPI_DisplayAdapter::fillRect(int32_t x, int32_t y, int32_t w, int32_t h, uint32_t color) {
    eSprite->fillRect(x, y, w, h, color);
}

//draws a horizontal line starting at (x,y) with length w
void TFT_eSPI_DisplayAdapter::drawHLine(int32_t x, int32_t y, int32_t w, uint32_t color) {
    eSprite->drawFastHLine(x, y, w, color);
}

//draws a vertical line starting at (x,y) with length h
void TFT_eSPI_DisplayAdapter::drawVLine(int32_t x, int32_t y, int32_t h, uint32_t color) {
    eSprite->drawFastVLine(x, y, h, color);
}


//This method creates a Canvas on which could be drawn
void TFT_eSPI_DisplayAdapter::createCanvas() {
    eSprite->createSprite(canvasWidth, canvasHeight);
}


//This method sets the colorDepth of the Canvas
void TFT_eSPI_DisplayAdapter::setColorDepth(int8_t b) {
    eSprite->setColorDepth(b);
}

//Fills the Canvas with the color
void TFT_eSPI_DisplayAdapter::fillCanvas(uint32_t color) {
    eSprite->fillSprite(color);
}

//Pushes the content of the Canvas to the actual Display
//transparent_color will not be rendered
void TFT_eSPI_DisplayAdapter::pushCanvas(int32_t x, int32_t y, uint16_t transparent_color) {
    eSprite->pushSprite(x, y, transparent_color);
}

//deletes the current canvas in order to free space.
void TFT_eSPI_DisplayAdapter::deleteCanvas() {
    eSprite->deleteSprite();
}