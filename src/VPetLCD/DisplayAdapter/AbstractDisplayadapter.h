#pragma once
#include <Arduino.h>

class AbstractDisplayAdapter {

protected:
    uint16_t canvasWidth;
    uint16_t canvasHeight;
public:
    AbstractDisplayAdapter(uint16_t resolutionX, uint16_t resolutionY){canvasWidth=resolutionX; canvasHeight=resolutionY; }
    //Draws a filled colored rectangle on pos (x,y) with width w and height h 
    virtual void fillRect(int32_t x, int32_t y, int32_t w, int32_t h, uint32_t color);

    //draws a horizontal line starting at (x,y) with length w
    virtual void drawHLine(int32_t x, int32_t y, int32_t w, uint32_t color);

    //draws a vertical line starting at (x,y) with length h
    virtual void drawVLine(int32_t x, int32_t y, int32_t h, uint32_t color);


    //This method creates a Canvas on which could be drawn with the dimensions canvasWidth and canvasWidth
    virtual void createCanvas();


    //This method sets the colorDepth of the Canvas
    virtual void setColorDepth(int8_t b);

    //Fills the Canvas with the color
    virtual void fillCanvas(uint32_t color);

    //Pushes the content of the Canvas to the actual Display
    //transparent_color is the colorvalue which should be handled as transparent
    virtual void pushCanvas(int32_t x, int32_t y, uint16_t transparent_color);


    //deletes the current canvas in order to free space.
    virtual void deleteCanvas();


};