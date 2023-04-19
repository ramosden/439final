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
    uint32_t * buffer; //store pixel data for image
    
    Window(graphicsVGA* vga_, uint32_t x_, uint32_t y_, uint32_t width_, uint32_t height_) {
        vga = vga_;
        x = x_;
        y = y_;
        width = width_;
        height = height_;
        buffer = new uint32_t[width_ * height_];
    }
    
    ~Window() {
        delete[] buffer;
        // delete vga;
    }

    void draw_window() {
        // WINDOW BORDER
        // drawRectangle(x, y, width, height, 0xA7); // white color

        // TITLE BAR
        drawRectangle(x, y, width, 20, 0x01); // blue color

        // TITLE TEXT
        // drawText(x+5, y+5, "My Window", 0xFFFFFF); // white color
        
        // INTERIOR CONTENT
        // drawRectangle(x+2, y+22, width-4, height-24, 0x17); // light gray color
    }
    
    void drawRectangle(uint32_t x, uint32_t y, uint32_t width, uint32_t height, uint8_t colorIndex) {
        // loop through each pixel in the rectangle
        for (uint32_t i = x; i < x + width; i++) {
            vga->putPixelIndex(i, y, colorIndex); // top horizontal line
            vga->putPixelIndex(i, y + height - 1, color); // bottom horizontal line
        }
        for (uint32_t j = y; j < y + height; j++) {
            vga->putPixelIndex(x, j, colorIndex); // left vertical line
            vga->putPixelIndex(x + width - 1, j, color); // right vertical line
        }
    }
    
    void fillRectangle(uint32_t width, uint32_t height, graphicsVGA* graphicVGA, uint8_t colorIndex) {
            // INTERIOR green bg
        for(uint32_t y = 0; y < height; y++){
            for(uint32_t x = 0; x < width; x++){
                graphicVGA -> putPixelIndex(x, y, colorIndex);
            }
        }
    }

};