#include "MAX72XX_Display_Adapter.h"

//Draws a filled colored rectangle on pos (x,y) with width w and height h 
void MAX72XX_Display_Adapter::fillRect(int32_t x, int32_t y, int32_t w, int32_t h, uint32_t color) {
    for(int i =0; i< w;i++)
        for(int j =0; j< h;j++)
            drawPixel(x+i, y+j,color);
}

//draws a horizontal line starting at (x,y) with length w
void MAX72XX_Display_Adapter::drawHLine(int32_t x, int32_t y, int32_t w, uint32_t color) {
    for(int j =0; j< w;j++)
            drawPixel(x+j, y,color);
}

//draws a vertical line starting at (x,y) with length h
void MAX72XX_Display_Adapter::drawVLine(int32_t x, int32_t y, int32_t h, uint32_t color) {
   for(int j =0; j< h;j++)
            drawPixel(x, y+j,color);
}


//This method creates a Canvas on which could be drawn
void MAX72XX_Display_Adapter::createCanvas() {
   deleteCanvas();
}


//This method sets the colorDepth of the Canvas
void MAX72XX_Display_Adapter::setColorDepth(int8_t b) {
    //display->setColorDepth(b);
   
}

//Fills the Canvas with the color
void MAX72XX_Display_Adapter::fillCanvas(uint32_t color) {
    if(color == 0){
        for(int i = 0; i < 8; i++)
        for(int j = 0; j < 8; j++)
            canvas[i][j] = 0xFF;
    }else{
        deleteCanvas();
    }
}

//Pushes the content of the Canvas to the actual Display
//transparent_color will not be rendered
void MAX72XX_Display_Adapter::pushCanvas(int32_t x, int32_t y, uint16_t transparent_color) {
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            display->setRow(i,j, canvas[i][j]);
        }
    }
}

//deletes the current canvas in order to free space.
void MAX72XX_Display_Adapter::deleteCanvas() {
    for(int i = 0; i < 8; i++)
        for(int j = 0; j < 8; j++)
            canvas[i][j] = 0;
}

//draws pixel on the frame buffer;
void  MAX72XX_Display_Adapter::drawPixel(int32_t x, int32_t y,uint32_t color){


    if(x < 0 || x >=canvasWidth) return;
    if(y < 0 || y >=canvasHeight) return;

    uint8_t matrixIndex =  getLedMatrixIndex(x,y);
    uint8_t mask = getOrMask(x);
    uint8_t row = 7-y%8;
    canvas[matrixIndex][row] |= mask;

}