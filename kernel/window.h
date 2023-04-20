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
    
    // void drawRectangle(uint32_t x, uint32_t y, uint32_t width, uint32_t height, uint8_t colorIndex) {
    //     // loop through each pixel in the rectangle
    //     for (uint32_t i = x; i < x + width; i++) {
    //         vga->putPixelIndex(i, y, colorIndex); // top horizontal line
    //         vga->putPixelIndex(i, y + height - 1, color); // bottom horizontal line
    //     }
    //     for (uint32_t j = y; j < y + height; j++) {
    //         vga->putPixelIndex(x, j, colorIndex); // left vertical line
    //         vga->putPixelIndex(x + width - 1, j, color); // right vertical line
    //     }
    // }
    
    void fillRectangle(uint32_t x, uint32_t y, graphicsVGA * vga, uint32_t width, uint32_t height, uint8_t colorIndex) {
        for(uint32_t h = y; h < height + y; h++){
            for(uint32_t w = x; w < width + x; w++){
                vga -> putPixelIndex(w, h, colorIndex);
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

    void fillOval(uint32_t centerX, uint32_t centerY, graphicsVGA *vga, uint32_t radiusX, uint32_t radiusY, uint8_t colorIndex) {
        uint32_t xMin = centerX - radiusX;
        uint32_t xMax = centerX + radiusX;
        uint32_t yMin = centerY - radiusY;
        uint32_t yMax = centerY + radiusY;

        for (uint32_t y = yMin; y <= yMax; y++) {
            for (uint32_t x = xMin; x <= xMax; x++) {
                uint32_t dx = x - centerX;
                uint32_t dy = y - centerY;
                if ((dx*dx)/(radiusX*radiusX) + (dy*dy)/(radiusY*radiusY) <= 1) {
                    vga->putPixelIndex(x, y, colorIndex);
                }
            }
        }
    }

    void drawCow(graphicsVGA *vga) {
        // Draw head
        fillOval(160, 70, vga, 30, 20, 1); // Head
        fillCircle(145, 63, vga, 5, 0); // Eye
        fillCircle(145, 63, vga, 2, 1); // Pupil

        // Draw body
        fillOval(120, 110, vga, 40, 20, 1); // Upper body
        fillOval(100, 120, vga, 40, 20, 1); // Lower body
        fillRectangle(100, 110, vga, 20, 30, 0); // Left leg
        fillRectangle(120, 110, vga, 20, 30, 0); // Right leg

        // Draw spots
        fillCircle(135, 100, vga, 6, 0); // Spot on head
        fillCircle(112, 115, vga, 5, 0); // Spot on upper body
        fillCircle(130, 130, vga, 7, 0); // Spot on lower body
        fillCircle(150, 130, vga, 7, 0); // Spot on lower body
    }

};