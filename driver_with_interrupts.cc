#include "kernel/machine.h"
#include "debug.h"
#include "stdint.h"
#include "kernel/vga.h"
#include "init.h"
#include "kernel/window.h"
#include "config.h"

/* INSTRUCTIONS 

USE VNC VIEWER TO SEE PROGRAM

KEY T - MOVE CLOUDS 
KEY U - MOVE COW
KEY Y - CHANGE COW COLOR
KEY S - SUNSET ANIMATION
CNTRL C - END PROGRAM
*/

struct Cloud {
    int offset_x;
    int offset_y;
    Cloud(int off_x, int off_y) : offset_x(off_x), offset_y(off_y) {}

    void createCloud(graphicsVGA * graphicVGA, int off_x, int off_y) {
           // clouds
        Window * cloudone = new Window();
        cloudone->fillCircle(60 + off_x, 50 + off_y, graphicVGA, 15, 0x3F);
        cloudone->fillCircle(70 + off_x, 55 + off_y, graphicVGA, 15, 0x3F);
        cloudone->fillCircle(80 + off_x, 50 + off_y, graphicVGA, 15, 0x3F);
        cloudone->fillCircle(90 + off_x, 55 + off_y, graphicVGA, 15, 0x3F);

        cloudone->fillCircle(150 + off_x, 30 + off_y, graphicVGA, 10, 0x3F);
        cloudone->fillCircle(160 + off_x, 33 + off_y, graphicVGA, 10, 0x3F);
        cloudone->fillCircle(170 + off_x, 30 + off_y, graphicVGA, 10, 0x3F);
        cloudone->fillCircle(180 + off_x, 33 + off_y, graphicVGA, 10, 0x3F);

        cloudone->fillCircle(250 + off_x, 70 + off_y, graphicVGA, 9, 0x3F);
        cloudone->fillCircle(260 + off_x, 75 + off_y, graphicVGA, 11, 0x3F);
        cloudone->fillCircle(265 + off_x, 70 + off_y, graphicVGA, 9, 0x3F);
        cloudone->fillCircle(275 + off_x, 75 + off_y, graphicVGA, 11, 0x3F);
    }
    void removeCloud(graphicsVGA * graphicVGA, int off_x, int off_y) {
         Window * cloudone = new Window();
        cloudone->fillCircle(60 + off_x, 50 + off_y, graphicVGA, 15, 0x11);
        cloudone->fillCircle(70 + off_x, 55 + off_y, graphicVGA, 15, 0x11);
        cloudone->fillCircle(80 + off_x, 50 + off_y, graphicVGA, 15, 0x11);
        cloudone->fillCircle(90 + off_x, 55 + off_y, graphicVGA, 15, 0x11);

        cloudone->fillCircle(150 + off_x, 30 + off_y, graphicVGA, 10, 0x11);
        cloudone->fillCircle(160 + off_x, 33 + off_y, graphicVGA, 10, 0x11);
        cloudone->fillCircle(170 + off_x, 30 + off_y, graphicVGA, 10, 0x11);
        cloudone->fillCircle(180 + off_x, 33 + off_y, graphicVGA, 10, 0x11);

        cloudone->fillCircle(250 + off_x, 70 + off_y, graphicVGA, 9, 0x11);
        cloudone->fillCircle(260 + off_x, 75 + off_y, graphicVGA, 11, 0x11);
        cloudone->fillCircle(265 + off_x, 70 + off_y, graphicVGA, 9, 0x11);
        cloudone->fillCircle(275 + off_x, 75 + off_y, graphicVGA, 11, 0x11);
    }
};

struct Cow {
    void createCow(graphicsVGA * graphicVGA, int off_x, int off_y, uint8_t cowColor) {
        Window * cow = new Window();
        cow -> fillRectangle(30 + off_x, 150 + off_y, graphicVGA, 45, 20, cowColor);
        cow -> fillRectangle(35 + off_x, 170 + off_y, graphicVGA, 10, 12, cowColor);
        cow -> fillRectangle(60 + off_x, 170 + off_y, graphicVGA, 10, 12, cowColor);
        cow -> fillCircle(27 + off_x, 147 + off_y, graphicVGA, 10, cowColor);
        cow -> drawOval(27 + off_x, 153 + off_y, graphicVGA, 15, 7, 0x3F);
        cow -> fillCircle(23 + off_x, 144 + off_y, graphicVGA, 1, 0x3F);
        cow -> fillCircle(31 + off_x, 144 + off_y, graphicVGA, 1, 0x3F);
        cow -> fillCircle(21 + off_x, 153 + off_y, graphicVGA, 1, cowColor);
        cow -> fillCircle(33 + off_x, 153 + off_y, graphicVGA, 1, cowColor);
        cow -> fillCircle(20 + off_x, 137 + off_y, graphicVGA, 2, cowColor);
        cow -> fillCircle(25 + off_x, 135 + off_y, graphicVGA, 2, 0x3F);
        cow -> fillCircle(29 + off_x, 135 + off_y, graphicVGA, 2, 0x3F);
        cow -> fillCircle(34 + off_x, 137 + off_y, graphicVGA, 2, cowColor);
        cow -> fillCircle(58 + off_x, 170 + off_y, graphicVGA, 5, 0x05);
        cow -> fillRectangle(75 + off_x, 150 + off_y, graphicVGA, 7, 3, cowColor);
        cow -> fillRectangle(79 + off_x, 150 + off_y, graphicVGA, 3, 10, cowColor); 
        cow -> fillCircle(80 + off_x, 160 + off_y, graphicVGA, 2, 0x3F);
    }
    void removeCow(graphicsVGA * graphicVGA, int off_x, int off_y) {
        Window * cow = new Window();
        cow -> fillRectangle(30 + off_x, 150 + off_y, graphicVGA, 45, 20, 0x11);
        cow -> fillRectangle(35 + off_x, 170 + off_y, graphicVGA, 10, 12, 0x11);
        cow -> fillRectangle(60 + off_x, 170 + off_y, graphicVGA, 10, 12,0x11);
        cow -> fillCircle(27 + off_x, 147 + off_y, graphicVGA, 10, 0x11);
        cow -> drawOval(27 + off_x, 153 + off_y, graphicVGA, 10, 7, 0x11);
        cow -> fillCircle(23 + off_x, 144 + off_y, graphicVGA, 1, 0x11);
        cow -> fillCircle(31 + off_x, 144 + off_y, graphicVGA, 1, 0x11);
        cow -> fillCircle(21 + off_x, 153 + off_y, graphicVGA, 1, 0x11);
        cow -> fillCircle(33 + off_x, 153 + off_y, graphicVGA, 1, 0x11);
        cow -> fillCircle(20 + off_x, 137 + off_y, graphicVGA, 2, 0x11);
        cow -> fillCircle(25 + off_x, 135 + off_y, graphicVGA, 2, 0x11);
        cow -> fillCircle(29 + off_x, 135 + off_y, graphicVGA, 2, 0x11);
        cow -> fillCircle(34 + off_x, 137 + off_y, graphicVGA, 2, 0x11);
        cow -> fillCircle(58 + off_x, 170 + off_y, graphicVGA, 6, 0x11);
        cow -> fillRectangle(75 + off_x, 150 + off_y, graphicVGA, 7, 3, 0x11);
        cow -> fillRectangle(79 + off_x, 150 + off_y, graphicVGA, 3, 10, 0x11); 
        cow -> fillCircle(80 + off_x, 160 + off_y, graphicVGA, 2, 0x11);
    }
};

void kernelMain() {

    // setting up APIC for interrupts
    // citations: https://web.archive.org/web/20140628205356/www.acm.uiuc.edu/sigops/roll_your_own/i386/irq.html

    // DISABLE PIC
    outb(0x64, 0xAD);
    while ((int)(inb(0x64) & 0x1) == 0x1) {
    }

    // REMAP PIC
    outb(0x20, 0x11); /* ICW1: Initialize PIC */
    outb(0xA0, 0x11);
    outb(0x21, 0x20); /* ICW2: IRQ 0-31 map to IDT vector 0x20-0x3F */
    outb(0xA1, 0x28);
    outb(0x21, 0x04); /* ICW3: Connect slave PIC to master PIC's IRQ2 */
    outb(0xA1, 0x02);
    outb(0x21, 0x05); /* ICW4: Master PIC is in 8086 mode */
    outb(0xA1, 0x01); /* Slave PIC is in 8086 mode */

    // MASK ALL IRQS
    outb(0x21, 0xff);
    outb(0xA1, 0xff);

    // -------------------------------------------------------------------

    inb(0x60); // FLUSH OUTPUT BUFFER
 
    // enable first port
    outb(0x64, 0xAE);
    int value_back = inb(0x64);
    if ((int)(value_back & 0x1) >= 1) {
        Debug::printf("enabled first port\n");
    }

    // enable second port
    outb(0x64, 0xA8);
    value_back = inb(0x64);
    if ((int)(value_back & 0x1) >= 1) {
        Debug::printf("enabled second port\n");
    }

    outb(0x64, 0xD4); // signal that we want to send a command to the second channel aka mouse
    int response = inb(0x60);
    while (response != 0xfa) { // WAIT FOR ACKNOWLEDGEMENT
        outb(0x60, 0xD4);
        response = inb(0x60);
        Debug::printf("sent 0xD4 recieved: %x\n", response);
    }

    // check for keyboard 
    outb(0x60, 0xF4); // enable data reporting
    response = inb(0x60);
    Debug::printf("sent 0xF4 recieved: %x\n", response);
    while (response != 0xfa) {
        response = inb(0x60);
        Debug::printf("sent 0xF4 recieved: %x\n", response);
    }

    outb(0x60, 0xF2); // get keyboard ID
    while(!(inb(0x64) & 1)) {} // wait until we can read
    Debug::printf("keyboard ID 0 : %x\n", inb(0x60));
    Debug::printf("keyboard ID 1 : %x\n", inb(0x60));
    Debug::printf("keyboard ID 2 : %x\n", inb(0x60));

    Debug::printf("keyboard returned controller\n");

  
    // GRAHPICS, SET UP PORTS
    Ports miscPort{0x3C2};
        Ports crtcIndexPort{0x3D4};
        Ports crtcDataPort{0x3D5};
        Ports seqIndexPort{0x3C4};
        Ports seqDataPort{0x3C5};
        Ports graphicsCtrlIndexPort{0x3CE};
        Ports graphicsCtrlDataPort{0x3CF};
        Ports attrbCtrlIndexPort{0x3C0};
        Ports attrbCtrlReadPort{0x3C1};
        Ports attrbCtrlWritePort{0x3C0};
        Ports attrbCtrlResetPort{0x3DA};

    graphicsVGA * graphicVGA = new graphicsVGA(miscPort, crtcIndexPort, crtcDataPort, 
    seqIndexPort, seqDataPort, graphicsCtrlIndexPort, graphicsCtrlDataPort,
    attrbCtrlIndexPort, attrbCtrlReadPort, attrbCtrlWritePort, attrbCtrlResetPort);
    graphicVGA -> setMode(320, 200, 8);

    //draw a rectangle on screen
    for(int32_t y = 0; y < 200; y++){
        for(int32_t x = 0; x < 320; x++){
            graphicVGA -> putPixel(x, y, 0x11, 0x00, 0x00);
        }
    }

    /*BACKGROUNDS */
    Window * background = new Window(); // vga, x, y
    /* BLUE BACKGROUND*/
    background -> fillRectangle(0, 0, graphicVGA, 320, 200, 0x11); 

    
    /* GRASS */
    Window * grass = new Window();
    grass -> fillRectangle(0, 180, graphicVGA, 320, 200, 0x02); // x, y, vga, width, height, colorindex

    /* SUN */
    Window * sun = new Window(); // vga, x, y
    // sun -> fillRectangle(15, 15, graphicVGA, 50, 50, 0x16); // width, height, colorindex
    sun->fillCircle(40, 40, graphicVGA, 25, 0x36);

    /* CLOUD */
    Cloud c{0, 0};
    c.createCloud(graphicVGA, 0, 0);

    /* COW */
    Cow cow{};
    int cowC = 0x3D;
    cow.createCow(graphicVGA, 0, 0, cowC);

    /* BARN */
    Window * barn = new Window();
    barn -> fillRectangle(130, 120, graphicVGA, 60, 60, 0x0C);
    barn -> fillTriangle(160, 90, graphicVGA, 60, 29, 0x0C);
    barn -> drawRectangle(140, 140, graphicVGA, 40, 40, 0x3F);
    barn -> drawDiagonalLines(140, 140, graphicVGA, 40, 40, 0x3F);
    barn -> drawRectangle(150, 115, graphicVGA, 20, 13, 0x3F);

    // waiting for input (polling)
    // FOLLOWS SCAN CODE 1 US QWERTY
    bool left_control_clicked = false;
    bool exit_terminal = false; // CONTROL C TERMINATES 
    int n = 1;
    int cloud_offset = 0;
    int cow_offset = 0;
    while (!exit_terminal) { 
        // while ((inb(0x64) & 0x1) == 0) {} NO MORE POLLING
        // GATHER PACKETS OF DATA
        int data = inb(0x60);
        int data_2 = inb(0x60);
        int data_3 = inb(0x60);
        int data_4 = inb(0x60);
        bool isMouse = false; 
        if (data != data_2 && data_3 != data_4) {
            isMouse = true;
        }
        if (!isMouse) {
            switch (data)
            {
            case 0x1e: {
                Debug::printf("a");
                break;
            }
            case 0x30: {
                Debug::printf("b");
                for(int32_t y = 0; y < 200; y++) {
                    for(int32_t x = 0; x < 320; x++){
                        graphicVGA -> putPixel(x, y, n, 0xC0, 0xCB);
                    }
                }
                if (n == 64) {
                    n = 0;
                }
                n++;
                break;
            }
            case 0x2e: {
                if (left_control_clicked) {
                    exit_terminal = true;
                    Debug::printf("C\n");
                } else {
                    Debug::printf("c");
                }
                break;
            }
            case 0x20: {
                Debug::printf("d");
                for(int32_t y = 0; y < 200; y++){
                    for(int32_t x = 0; x < 320; x++){
                        graphicVGA -> putPixel(x, y, 0x00, 0x00, 0xA8);
                    }
                }
                break;
            }
            case 0x12: {
                Debug::printf("e");
                break;
            }
            case 0x21: {
                Debug::printf("f");
                break;
            }
            case 0x22: {
                Debug::printf("g");
                break;
            }
            case 0x23: {
                Debug::printf("h");
                break;
            }
            case 0x17: {
                Debug::printf("i");
                break;
            }
            case 0x24: {
                Debug::printf("j");
                break;
            }
            case 0x25: {
                Debug::printf("k");
                break;
            }
            case 0x26: {
                Debug::printf("l");
                break;
            }
            case 0x32: {
                Debug::printf("m");
                break;
            }
            case 0x31 : {
            Debug::printf("n");
            break;
        }
        case 0x18 : {
            Debug::printf("o");
            break;
        }
        case 0x19 : {
            Debug::printf("p");
            break;
        }
        case 0x10 : {
            Debug::printf("q");
            break;
        }
        case 0x13 : {
            Debug::printf("r");
            break;
        }
        case 0x1f : {
            Debug::printf("s");
            int sunset_val = 0;
            switch(sunset_val) {
                case 0:  {
                    background -> fillRectangle(0, 0, graphicVGA, 320, 200, 0x14); 
                    barn -> fillRectangle(130, 120, graphicVGA, 60, 60, 0x0C);
                    barn -> fillTriangle(160, 90, graphicVGA, 60, 29, 0x0C);
                    barn -> drawRectangle(140, 140, graphicVGA, 40, 40, 0x3F);
                    barn -> drawDiagonalLines(140, 140, graphicVGA, 40, 40, 0x3F);
                    barn -> drawRectangle(150, 115, graphicVGA, 20, 13, 0x3F); 
                    sun->fillCircle(40, 55, graphicVGA, 25, 0x36);
                    c.createCloud(graphicVGA, cloud_offset, 0);
                    grass -> fillRectangle(0, 180, graphicVGA, 320, 200, 0x02);
                    barn -> fillRectangle(130, 120, graphicVGA, 60, 60, 0x0C);
                    barn -> fillTriangle(160, 90, graphicVGA, 60, 29, 0x0C);
                    barn -> drawRectangle(140, 140, graphicVGA, 40, 40, 0x3F);
                    barn -> drawDiagonalLines(140, 140, graphicVGA, 40, 40, 0x3F);
                    barn -> drawRectangle(150, 115, graphicVGA, 20, 13, 0x3F);
                    c.createCloud(graphicVGA, cloud_offset, 0);
                    grass -> fillRectangle(0, 180, graphicVGA, 320, 200, 0x02);
                    barn -> fillRectangle(130, 120, graphicVGA, 60, 60, 0x0C);
                    barn -> fillTriangle(160, 90, graphicVGA, 60, 29, 0x0C);
                    barn -> drawRectangle(140, 140, graphicVGA, 40, 40, 0x3F);
                    barn -> drawDiagonalLines(140, 140, graphicVGA, 40, 40, 0x3F);
                    barn -> drawRectangle(150, 115, graphicVGA, 20, 13, 0x3F);
                }
                case 1:  {
                    background -> fillRectangle(0, 0, graphicVGA, 320, 200, 0x15);
                    barn -> fillRectangle(130, 120, graphicVGA, 60, 60, 0x0C);
                    barn -> fillTriangle(160, 90, graphicVGA, 60, 29, 0x0C);
                    barn -> drawRectangle(140, 140, graphicVGA, 40, 40, 0x3F);
                    barn -> drawDiagonalLines(140, 140, graphicVGA, 40, 40, 0x3F);
                    barn -> drawRectangle(150, 115, graphicVGA, 20, 13, 0x3F); 
                    sun->fillCircle(40, 70, graphicVGA, 25, 0x36);
                    c.createCloud(graphicVGA, cloud_offset, 0);
                    grass -> fillRectangle(0, 180, graphicVGA, 320, 200, 0x02);
                    barn -> fillRectangle(130, 120, graphicVGA, 60, 60, 0x0C);
                    barn -> fillTriangle(160, 90, graphicVGA, 60, 29, 0x0C);
                    barn -> drawRectangle(140, 140, graphicVGA, 40, 40, 0x3F);
                    barn -> drawDiagonalLines(140, 140, graphicVGA, 40, 40, 0x3F);
                    barn -> drawRectangle(150, 115, graphicVGA, 20, 13, 0x3F);
                    c.createCloud(graphicVGA, cloud_offset, 0);
                    grass -> fillRectangle(0, 180, graphicVGA, 320, 200, 0x02);
                    barn -> fillRectangle(130, 120, graphicVGA, 60, 60, 0x0C);
                    barn -> fillTriangle(160, 90, graphicVGA, 60, 29, 0x0C);
                    barn -> drawRectangle(140, 140, graphicVGA, 40, 40, 0x3F);
                    barn -> drawDiagonalLines(140, 140, graphicVGA, 40, 40, 0x3F);
                    barn -> drawRectangle(150, 115, graphicVGA, 20, 13, 0x3F);
                }
                case 2:  {
                    background -> fillRectangle(0, 0, graphicVGA, 320, 200, 0x31);
                    barn -> fillRectangle(130, 120, graphicVGA, 60, 60, 0x0C);
                    barn -> fillTriangle(160, 90, graphicVGA, 60, 29, 0x0C);
                    barn -> drawRectangle(140, 140, graphicVGA, 40, 40, 0x3F);
                    barn -> drawDiagonalLines(140, 140, graphicVGA, 40, 40, 0x3F);
                    barn -> drawRectangle(150, 115, graphicVGA, 20, 13, 0x3F); 
                    sun->fillCircle(40, 85, graphicVGA, 25, 0x36);
                    c.createCloud(graphicVGA, cloud_offset, 0);
                    grass -> fillRectangle(0, 180, graphicVGA, 320, 200, 0x02);
                    barn -> fillRectangle(130, 120, graphicVGA, 60, 60, 0x0C);
                    barn -> fillTriangle(160, 90, graphicVGA, 60, 29, 0x0C);
                    barn -> drawRectangle(140, 140, graphicVGA, 40, 40, 0x3F);
                    barn -> drawDiagonalLines(140, 140, graphicVGA, 40, 40, 0x3F);
                    barn -> drawRectangle(150, 115, graphicVGA, 20, 13, 0x3F);
                    c.createCloud(graphicVGA, cloud_offset, 0);
                    grass -> fillRectangle(0, 180, graphicVGA, 320, 200, 0x02);
                    barn -> fillRectangle(130, 120, graphicVGA, 60, 60, 0x0C);
                    barn -> fillTriangle(160, 90, graphicVGA, 60, 29, 0x0C);
                    barn -> drawRectangle(140, 140, graphicVGA, 40, 40, 0x3F);
                    barn -> drawDiagonalLines(140, 140, graphicVGA, 40, 40, 0x3F);
                    barn -> drawRectangle(150, 115, graphicVGA, 20, 13, 0x3F);
                }
                case 3:  {
                    background -> fillRectangle(0, 0, graphicVGA, 320, 200, 0x11); 
                    barn -> fillRectangle(130, 120, graphicVGA, 60, 60, 0x0C);
                    barn -> fillTriangle(160, 90, graphicVGA, 60, 29, 0x0C);
                    barn -> drawRectangle(140, 140, graphicVGA, 40, 40, 0x3F);
                    barn -> drawDiagonalLines(140, 140, graphicVGA, 40, 40, 0x3F);
                    barn -> drawRectangle(150, 115, graphicVGA, 20, 13, 0x3F); 
                    sun->fillCircle(40, 100, graphicVGA, 25, 0x36);
                    c.createCloud(graphicVGA, cloud_offset, 0);
                    grass -> fillRectangle(0, 180, graphicVGA, 320, 200, 0x02);
                    c.createCloud(graphicVGA, cloud_offset, 0);
                    grass -> fillRectangle(0, 180, graphicVGA, 320, 200, 0x02);
                    barn -> fillRectangle(130, 120, graphicVGA, 60, 60, 0x0C);
                    barn -> fillTriangle(160, 90, graphicVGA, 60, 29, 0x0C);
                    barn -> drawRectangle(140, 140, graphicVGA, 40, 40, 0x3F);
                    barn -> drawDiagonalLines(140, 140, graphicVGA, 40, 40, 0x3F);
                    barn -> drawRectangle(150, 115, graphicVGA, 20, 13, 0x3F);
                    c.createCloud(graphicVGA, cloud_offset, 0);
                    barn -> fillRectangle(130, 120, graphicVGA, 60, 60, 0x0C);
                    barn -> fillTriangle(160, 90, graphicVGA, 60, 29, 0x0C);
                    barn -> drawRectangle(140, 140, graphicVGA, 40, 40, 0x3F);
                    barn -> drawDiagonalLines(140, 140, graphicVGA, 40, 40, 0x3F);
                    barn -> drawRectangle(150, 115, graphicVGA, 20, 13, 0x3F); 
                }
                case 4:  {
                    background -> fillRectangle(0, 0, graphicVGA, 320, 200, 0x00); 
                    barn -> fillRectangle(130, 120, graphicVGA, 60, 60, 0x0C);
                    barn -> fillTriangle(160, 90, graphicVGA, 60, 29, 0x0C);
                    barn -> drawRectangle(140, 140, graphicVGA, 40, 40, 0x3F);
                    barn -> drawDiagonalLines(140, 140, graphicVGA, 40, 40, 0x3F);
                    barn -> drawRectangle(150, 115, graphicVGA, 20, 13, 0x3F); 
                    sun->fillCircle(40, 115, graphicVGA, 25, 0x36);
                    c.createCloud(graphicVGA, cloud_offset, 0);
                    grass -> fillRectangle(0, 180, graphicVGA, 320, 200, 0x02);
                    barn -> fillRectangle(130, 120, graphicVGA, 60, 60, 0x0C);
                    barn -> fillTriangle(160, 90, graphicVGA, 60, 29, 0x0C);
                    barn -> drawRectangle(140, 140, graphicVGA, 40, 40, 0x3F);
                    barn -> drawDiagonalLines(140, 140, graphicVGA, 40, 40, 0x3F);
                    barn -> drawRectangle(150, 115, graphicVGA, 20, 13, 0x3F);
                    c.createCloud(graphicVGA, cloud_offset, 0);
                    grass -> fillRectangle(0, 180, graphicVGA, 320, 200, 0x02);
                    barn -> fillRectangle(130, 120, graphicVGA, 60, 60, 0x0C);
                    barn -> fillTriangle(160, 90, graphicVGA, 60, 29, 0x0C);
                    barn -> drawRectangle(140, 140, graphicVGA, 40, 40, 0x3F);
                    barn -> drawDiagonalLines(140, 140, graphicVGA, 40, 40, 0x3F);
                    barn -> drawRectangle(150, 115, graphicVGA, 20, 13, 0x3F);
                }
                case 5: background -> fillRectangle(0, 0, graphicVGA, 320, 200, 0x00); 
                case 6: {
                    /// ENDING SCREEN CODE ///
            /* BACKGROUND */
            Window * background = new Window(); // vga, x, y
            background -> fillRectangle(0, 0, graphicVGA, 320, 200, 0x00); // x, y, vga, width, height, colorindex

            // letter C
            Window * letterC = new Window();
            letterC -> fillRectangle(0, 30, graphicVGA, 30, 10, 0x0F); // x, y, vga, width, height, colorindex
            letterC -> fillRectangle(0, 30, graphicVGA, 10, 30, 0x0F); // x, y, vga, width, height, colorindex
            letterC -> fillRectangle(0, 60, graphicVGA, 30, 10, 0x0F); // x, y, vga, width, height, colorindex

            // letter O
            Window * letterO = new Window();
            letterO -> fillRectangle(40, 30, graphicVGA, 40, 40, 0x0F); // x, y, vga, width, height, colorindex
            letterO -> fillRectangle(48, 38, graphicVGA, 23, 23, 0x00); // x, y, vga, width, height, colorindex

            // letter N
            Window * letterN = new Window();
            letterN -> fillRectangle(90, 30, graphicVGA, 10, 40, 0x0F); // x, y, vga, width, height, colorindex
            letterN -> fillRectangle(100, 40, graphicVGA, 10, 10, 0x0F); // x, y, vga, width, height, colorindex
            letterN -> fillRectangle(110, 50, graphicVGA, 10, 10, 0x0F); // x, y, vga, width, height, colorindex
            letterN -> fillRectangle(120, 30, graphicVGA, 10, 40, 0x0F); // x, y, vga, width, height, colorindex

            // letter G
            Window * letterG = new Window();
            letterG -> fillRectangle(140, 30, graphicVGA, 30, 10, 0x0F); // x, y, vga, width, height, colorindex
            letterG -> fillRectangle(140, 30, graphicVGA, 10, 30, 0x0F); // x, y, vga, width, height, colorindex
            letterG -> fillRectangle(140, 60, graphicVGA, 30, 10, 0x0F); // x, y, vga, width, height, colorindex
            letterG -> fillRectangle(160, 50, graphicVGA, 10, 10, 0x0F); // x, y, vga, width, height, colorindex

            // letter R
            letterG -> fillRectangle(180, 30, graphicVGA, 10, 40, 0x0F); // x, y, vga, width, height, colorindex
            letterG -> fillRectangle(180, 30, graphicVGA, 30, 20, 0x0F); // x, y, vga, width, height, colorindex
            letterG -> fillRectangle(189, 38, graphicVGA, 10, 10, 0x00); // x, y, vga, width, height, colorindex
            letterG -> fillRectangle(190, 50, graphicVGA, 10, 10, 0x0F); // x, y, vga, width, height, colorindex
            letterG -> fillRectangle(200, 60, graphicVGA, 10, 10, 0x0F); // x, y, vga, width, height, colorindex

            // letter A
            letterG -> fillRectangle(220, 30, graphicVGA, 10, 40, 0x0F); // x, y, vga, width, height, colorindex
            letterG -> fillRectangle(240, 30, graphicVGA, 10, 40, 0x0F); // x, y, vga, width, height, colorindex
            letterG -> fillRectangle(220, 30, graphicVGA, 20, 10, 0x0F); // x, y, vga, width, height, colorindex
            letterG -> fillRectangle(220, 50, graphicVGA, 20, 10, 0x0F); // x, y, vga, width, height, colorindex

            // letter T
            letterG -> fillRectangle(260, 30, graphicVGA, 30, 10, 0x0F); // x, y, vga, width, height, colorindex
            letterG -> fillRectangle(270, 30, graphicVGA, 10, 40, 0x0F); // x, y, vga, width, height, colorindex

            // letter S
            letterG -> fillRectangle(295, 30, graphicVGA, 20, 40, 0x0F); // x, y, vga, width, height, colorindex
            letterG -> fillRectangle(305, 40, graphicVGA, 10, 10, 0x00); // x, y, vga, width, height, colorindex
            letterG -> fillRectangle(295, 50, graphicVGA, 10, 10, 0x00); // x, y, vga, width, height, colorindex

            // letter O
            letterO -> fillRectangle(20, 90, graphicVGA, 80, 80, 0x0F); // x, y, vga, width, height, colorindex
            letterO -> fillRectangle(35, 100, graphicVGA, 50, 50, 0x00); // x, y, vga, width, height, colorindex

            // letter S
            letterG -> fillRectangle(120, 90, graphicVGA, 80, 80, 0x0F); // x, y, vga, width, height, colorindex
            letterG -> fillRectangle(150, 110, graphicVGA, 50, 10, 0x00); // x, y, vga, width, height, colorindex
            letterG -> fillRectangle(120, 140, graphicVGA, 50, 10, 0x00); // x, y, vga, width, height, colorindex

            // check mark
            letterG -> fillRectangle(220, 90, graphicVGA, 80, 80, 0x12); // x, y, vga, width, height, colorindex
            letterG -> fillRectangle(220, 130, graphicVGA, 10, 10, 0x3F); 
            letterG -> fillRectangle(230, 140, graphicVGA, 10, 10, 0x3F); 
            letterG -> fillRectangle(240, 150, graphicVGA, 10, 10, 0x3F); 
            letterG -> fillRectangle(250, 140, graphicVGA, 10, 10, 0x3F);
            letterG -> fillRectangle(260, 130, graphicVGA, 10, 10, 0x3F);  
            letterG -> fillRectangle(270, 120, graphicVGA, 10, 10, 0x3F);  
            letterG -> fillRectangle(280, 110, graphicVGA, 10, 10, 0x3F);  
            letterG -> fillRectangle(290, 100, graphicVGA, 10, 10, 0x3F);
                }
                default: break;
            }
            break;
        }
        case 0x14 : {
            // Debug::printf("t");
            // create cloud
            c.removeCloud(graphicVGA, cloud_offset, 0);
            
        
            sun->fillCircle(40, 40, graphicVGA, 25, 0x36);
            
            cloud_offset+=3;
            c.createCloud(graphicVGA, cloud_offset, 0);
            
            break;
        }
        case 0x16 : {
            // Debug::printf("u");
            if (cow_offset == 152) {
                break;
            }
            ////////////////////////// DEMO ///////////////////////////////////
            cow.removeCow(graphicVGA, cow_offset, 0); 
            grass -> fillRectangle(0, 180, graphicVGA, 320, 200, 0x02);
            Debug::printf("cow: %d ", cow_offset);
            cow_offset-=4;
            if (cow_offset == -16) {
                cow_offset = 300;
            } else if (cow_offset == 152) {
                barn -> fillRectangle(130, 120, graphicVGA, 60, 60, 0x0C);
                // barn -> fillTriangle(160, 90, graphicVGA, 60, 29, 0x0C);
                // // Window * barnDoor = new Window();
                barn -> drawRectangle(140, 140, graphicVGA, 40, 40, 0x3F);
                barn -> drawDiagonalLines(140, 140, graphicVGA, 40, 40, 0x3F);
                barn -> drawRectangle(150, 115, graphicVGA, 20, 13, 0x3F);
                break;
            }
            Debug::printf("%d\n", cow_offset);
            cow.createCow(graphicVGA, cow_offset, 0, cowC);
            break;
        }
        case 0x2f : {
            Debug::printf("v");
            break;
        }
        case 0x11 : {
            Debug::printf("w");
            break;
        }
        case 0x2d : {
            Debug::printf("x");
            break;
        }
        case 0x15 : {
            Debug::printf("y");
            // CHANGE COW COLORS
            if (cowC != 0x14) {
                cowC = 0x14;
            } else {
                cowC= 0x3D;
            }
            
            cow.createCow(graphicVGA, cow_offset, 0, cowC);

            break;
        }
        case 0x2c : {
            Debug::printf("z");
            break;
        }
        case 0x0c : {
            Debug::printf("-");
            break;
        }
        case 0x04 : {
            Debug::printf("3");
            break;
        }
        case 0x08 : {
            // Debug::printf("CLICK UP\n");
            Debug::printf("7");
            break;
        }
        case 0x1c : {
            Debug::printf("\n");
            break;
        }
        case 0x28 : {
            Debug::printf("'");
            break;
        }
        case 0x34 : {
            Debug::printf(".");
            break;
        }
        case 0x38 : {
            Debug::printf("\nleft alt\n");
            break;
        }
        case 0x3c : {
            Debug::printf("\nf2\n");
            break;
        }
        case 0x40 : {
            Debug::printf("\nf6\n");
            break;
        }
        case 0x44 : {
            Debug::printf("\nf10\n");
            break;
        }
        case 0x48 : {
            Debug::printf("case 0x48");
            Debug::printf("8");
            break;
        }
        case 0x4c : {
            Debug::printf("5");
            break;
        }
        case 0x50 : {
            Debug::printf("2");
            break;
        }
        case 0x01 : {
            Debug::printf("\n espace\n");
            break;
        }
        case 0x05 : {
            Debug::printf("4");
            break;
        }
        case 0x09 : {
            // Debug::printf("\nCLICK DOWN\n");
            Debug::printf("8");
            break;
        }
        case 0x0D : {
            Debug::printf("=");
            break;
        }
        case 0x1D : {
            Debug::printf("^");
            left_control_clicked = true;
            break;
        }
        case 0x35 : {
            Debug::printf("/");
            break;
        }
        case 0x39 : {
            Debug::printf(" ");
            break;
        }
        case 0x3D : {
            Debug::printf("\nF3\n");
            break;
        }
        case 0x41 : {
            // Debug::printf("\nF7\n");
            break;
        }
        case 0x45 : {
            Debug::printf("\nnumber locked\n");
            break;
        }
        case 0x49 : {
            Debug::printf("9");
            break;
        }
        case 0x4D : {
            Debug::printf("6");
            break;
        }
        case 0x51 : {
            Debug::printf("4");
            break;
        }
        case 0x0B : {
            Debug::printf("0");
            break;
        }
        case 0x02 : {
            Debug::printf("1");
            break;
        }
        case 0x03 : {
            Debug::printf("2");
            break;
        }
        case 0x06 : {
            Debug::printf("5");
            break;
        }
        case 0x07 : {
            Debug::printf("6");
            break;
        }
        case 0x0A : {
            Debug::printf("case 0x0A");
            Debug::printf("9");
            break;
        }
        case 0x0E : {
            Debug::printf("backspace");
            break;
        }
        case 0x0F : {
            Debug::printf("tab");
            break;
        }
        case 0x1A : {
            Debug::printf("[");
            break;
        }
        case 0x1B : {
            Debug::printf("]");
            break;
        }
        case 0x27 : {
            Debug::printf(";");
            break;
        }
        case 0x2A : {
            Debug::printf("left shift");
            break;
        }
        case 0x2B : {
            Debug::printf("'\'");
            break;
        }
        case 0x33 : {
            Debug::printf(",");
            break;
        }
        case 0x36 : {
            Debug::printf("right shift");
            break;
        }
        case 0x3A : {
            Debug::printf("capslock");
            break;
        }
        case 0x3B : {
            Debug::printf("f1");
            break;
        }
        case 0x3E : {
            Debug::printf("f4");
            break;
        }
        case 0x3F : {
            Debug::printf("f5");
            break;
        }
        case 0x42 : {
            Debug::printf("f8");
            break;
        }
        case 0x43 : {
            Debug::printf("f9");
            break;
        }
        case 0x57 : {
            Debug::printf("f11");
            break;
        }

        default:
            // Debug::printf("recieved polling data: %x \n", data);
            break;
        }
    }
    else { // IDENTIFIED MOUSE
        
        // Debug::printf("MOUSE DATA\n");
         //Debug::printf("datas: %x %x %x %x\n", data, data_2, data_3, data_4);
            if (data_2 == 0xff && data_3 == 0x0) {
                Debug::printf("mouse moving left\n");
            } else if (data_2 == 0x01 && data_3 == 0x0) {
                Debug::printf("mouse moving right\n");
            } else if (data_2 == 0x0 && data_3 == 0x01) {
                Debug::printf("mouse moving up\n");
            } else if (data_2 == 0x0 && data_3 == 0xff) {
                Debug::printf("mouse moving down\n");
            } else if (data == 0x9) {
                Debug::printf("mouse left click down\n");
            } else if (data == 0xa) {
                Debug::printf("mouse right click down\n");
            }
        
        }
        outb(0x20, 0x20); // ACKNOWLEDGED INTERRUPT
    }
}