#include "graphicsvga.h"
#include "stdint.h"
#include "ports.h"

class Window {
public:

    uint32_t x;
    uint32_t y;
    uint32_t width;
    uint32_t height;
    uint8_t color;
    graphicsVGA* vga;
    
    Window() {
        // vga = vga_;
        // x = x_;
        // y = y_;
    }
    
    ~Window() {
        // delete vga;
    }

    // void draw_window() {
    //     // WINDOW BORDER
    //     // drawRectangle(x, y, width, height, 0xA7); // white color

    //     // TITLE BAR
    //     drawRectangle(x, y, width, 20, 0x0F); // blue color

    //     // TITLE TEXT
    //     // drawText(x+5, y+5, "My Window", 0xFFFFFF); // white color
        
    //     // INTERIOR CONTENT
    //     // drawRectangle(x+2, y+22, width-4, height-24, 0x17); // light gray color
    // }
    
    void drawRectangle(uint32_t x, uint32_t y, graphicsVGA* vga, uint32_t width, uint32_t height, uint8_t colorIndex) {
        // loop through each pixel in the rectangle
        for (uint32_t i = x; i < x + width; i++) {
            vga->putPixelIndex(i, y, colorIndex); // top horizontal line
            vga->putPixelIndex(i, y + height - 1, colorIndex); // bottom horizontal line
        }
        for (uint32_t j = y; j < y + height; j++) {
            vga->putPixelIndex(x, j, colorIndex); // left vertical line
            vga->putPixelIndex(x + width - 1, j, colorIndex); // right vertical line
        }
    }

    void drawDiagonalLines(uint32_t x, uint32_t y, graphicsVGA* vga, uint32_t width, uint32_t height, uint8_t colorIndex) {
         uint32_t minVal = 0;
         if(width < height){
             minVal = width;
         } else {
             minVal = height;
         }
        for (uint32_t i = 0; i < minVal; i++) {
            vga->putPixelIndex(x + i, y + i, colorIndex); // top-left to bottom-right diagonal
            vga->putPixelIndex(x + width - i - 1, y + i, colorIndex); // top-right to bottom-left diagonal
        }
    }
    
    void fillRectangle(uint32_t x, uint32_t y, graphicsVGA * vga, uint32_t width, uint32_t height, uint8_t colorIndex) {
        for(uint32_t h = y; h < height + y; h++){
            for(uint32_t w = x; w < width + x; w++){
                vga -> putPixelIndex(w, h, colorIndex);
            }
        }
    }

    void fillTriangle(uint32_t x, uint32_t y, graphicsVGA* vga, uint32_t width, uint32_t height, uint8_t colorIndex) {
        uint32_t halfWidth = width / 2;
        for (uint32_t h = 0; h <= height; h++) {
            uint32_t start = x - (halfWidth * h) / height;
            uint32_t end = x + (halfWidth * h) / height;
            for (uint32_t w = start; w <= end; w++) {
                vga->putPixelIndex(w, y + h, colorIndex);
            }
        }
    }


    void fillCircle(uint32_t centerX, uint32_t centerY, graphicsVGA *vga, uint32_t radius, uint8_t colorIndex) {
        uint32_t xMin = centerX - radius;
        uint32_t xMax = centerX + radius;
        uint32_t yMin = centerY - radius;
        uint32_t yMax = centerY + radius;

        for (uint32_t y = yMin; y <= yMax; y++) {
            for (uint32_t x = xMin; x <= xMax; x++) {
                uint32_t dx = x - centerX;
                uint32_t dy = y - centerY;
                if (dx * dx + dy * dy <= radius * radius) {
                    vga->putPixelIndex(x, y, colorIndex);
                }
            }
        }
    }




};