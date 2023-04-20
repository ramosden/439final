// #include "display.h"
#include "debug.h"
#include "stdint.h"
#include "vga.h"
#include "init.h"
// #include "graphicsvga.h"
#include "window.h"

void kernelMain() {
    
 
        // while(true){
        //     // newvga -> write_text();
            
        // }
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

    graphicVGA -> setMode(320, 200, 8); //0x13 graphics mode
    
    /*BACKGROUNDS */
        /* LILAC BACKGROUND */
        Window * background = new Window(); // vga, x, y
        background -> fillRectangle(0, 0, graphicVGA, 320, 200, 0x0F); 
        
        /* DARK PURPLE BACKGROUND*/
        background -> fillRectangle(0, 0, graphicVGA, 320, 200, 0x31); 

        /* MUTED PURPLE BACKGROUND*/
        background -> fillRectangle(0, 0, graphicVGA, 320, 200, 0x15); 
        
        /* DARK BLUE BACKGROUND*/
        background -> fillRectangle(0, 0, graphicVGA, 320, 200, 0x11); 

        /*  BACKGROUND*/
        background -> fillRectangle(0, 0, graphicVGA, 320, 200, 0x21); 

    // /* GRASS */
    Window * grass = new Window();
    grass -> fillRectangle(0, 180, graphicVGA, 320, 200, 0x10); // x, y, vga, width, height, colorindex

    // /* SUN */
    Window * sun = new Window(); // vga, x, y
    // sun -> fillRectangle(15, 15, graphicVGA, 50, 50, 0x16); // width, height, colorindex
    sun->fillCircle(40, 40, graphicVGA, 25, 0x36);

    // clouds
    Window * cloudone = new Window();
    cloudone->fillCircle(60, 50, graphicVGA, 15, 0x3F);
    cloudone->fillCircle(70, 55, graphicVGA, 15, 0x3F);
    cloudone->fillCircle(80, 50, graphicVGA, 15, 0x3F);
    cloudone->fillCircle(90, 55, graphicVGA, 15, 0x3F);

    cloudone->fillCircle(150, 30, graphicVGA, 10, 0x3F);
    cloudone->fillCircle(160, 33, graphicVGA, 10, 0x3F);
    cloudone->fillCircle(170, 30, graphicVGA, 10, 0x3F);
    cloudone->fillCircle(180, 33, graphicVGA, 10, 0x3F);

    cloudone->fillCircle(250, 70, graphicVGA, 9, 0x3F);
    cloudone->fillCircle(260, 75, graphicVGA, 11, 0x3F);
    cloudone->fillCircle(265, 70, graphicVGA, 9, 0x3F);
    cloudone->fillCircle(275, 75, graphicVGA, 11, 0x3F);

    // SHEEP!!!
    Window* sheep = new Window();
    sheep->fillCircle(250, 160, graphicVGA, 10, 0x0F);
    // sheep->fillCircle(260, 165, graphicVGA, 10, 0x31);
    // sheep->fillCircle(270, 160, graphicVGA, 10, 0x31);
    // sheep->fillCircle(280, 165, graphicVGA, 10, 0x31);

    // COW
    Window * cowbody = new Window();
    cowbody -> fillRectangle(30, 150, graphicVGA, 45, 20, 0x3D);

    Window * cowlegone = new Window();
    cowlegone -> fillRectangle(35, 170, graphicVGA, 10, 12, 0x3D);

    // Window * cowlegtwo = new Window();
    // cowlegtwo -> fillRectangle(35, 170, graphicVGA, 10, 9, 0x3D);

    Window * cowlegthree = new Window();
    cowlegthree -> fillRectangle(60, 170, graphicVGA, 10, 12, 0x3D);

    Window * cowhead = new Window();
    cowhead -> fillCircle(27, 147, graphicVGA, 10, 0x3D);


    Window * cowmouth = new Window();
    cowmouth -> fillRectangle(17, 150, graphicVGA, 20, 5, 0x3F);
        
    Window * coweyeone = new Window();
    coweyeone -> fillCircle(23, 144, graphicVGA, 1, 0x3F);

    Window * coweyetwo = new Window();
    coweyetwo -> fillCircle(31, 144, graphicVGA, 1, 0x3F);

    Window * cownostrilone = new Window();
    cownostrilone -> fillCircle(21, 152, graphicVGA, 1, 0x3D);

    Window * cownostriltwo = new Window();
    cownostriltwo -> fillCircle(33, 152, graphicVGA, 1, 0x3D);

    Window * cowhairone = new Window();
    cowhairone -> fillCircle(20, 137, graphicVGA, 2, 0x3F);

    Window * cowhairtwo = new Window();
    cowhairtwo -> fillCircle(25, 135, graphicVGA, 2, 0x3F);

    Window * cowhairthree = new Window();
    cowhairthree -> fillCircle(29, 135, graphicVGA, 2, 0x3F);

    Window * cowhairfour = new Window();
    cowhairfour -> fillCircle(34, 137, graphicVGA, 2, 0x3F);

    Window * cowudders = new Window();
    cowudders -> fillCircle(58, 170, graphicVGA, 6, 0x05);

    Window * cowtailpt1 = new Window();
    cowtailpt1 -> fillRectangle(75, 150, graphicVGA, 7, 3, 0x3D);
    
    Window * cowtailpt2 = new Window();
    cowtailpt2 -> fillRectangle(79, 150, graphicVGA, 3, 10, 0x3D);
    
    Window * cowtailend = new Window();
    cowtailend -> fillCircle(80, 160, graphicVGA, 2, 0x3F);

    Window * spots = new Window();
    spots -> fillCircle(40, 165, graphicVGA, 1, 0x3F);
    /*
    spots -> fillCircle();
    */

    /*
    
        Window * cow = new Window();
        cow -> fillRectangle(30 + off_x, 150 + off_y, graphicVGA, 45, 20, 0x3D);
        cow -> fillRectangle(35 + off_x, 170 + off_y, graphicVGA, 10, 12, 0x3D);

        // Window * cowlegtwo = new Window();
        // cowlegtwo -> fillRectangle(35, 170, graphicVGA, 10, 9, 0x3D);

        cow -> fillRectangle(60 + off_x, 170 + off_y, graphicVGA, 10, 12, 0x3D);
        cow -> fillCircle(27 + off_x, 147 + off_y, graphicVGA, 10, 0x3D);
        cow -> fillRectangle(15 + off_x, 150 + off_y, graphicVGA, 23, 5, 0x3F);
        cow -> fillCircle(23 + off_x, 144 + off_y, graphicVGA, 1, 0x00);
        cow -> fillCircle(31 + off_x, 144 + off_y, graphicVGA, 1, 0x00);
        cow -> fillCircle(18 + off_x, 152 + off_y, graphicVGA, 1, 0x00);
        cow -> fillCircle(34 + off_x, 152 + off_y, graphicVGA, 1, 0x00);
        cow -> fillCircle(20 + off_x, 137 + off_y, graphicVGA, 2, 0x3F);
        cow -> fillCircle(25 + off_x, 135 + off_y, graphicVGA, 2, 0x3F);
        cow -> fillCircle(29 + off_x, 135 + off_y, graphicVGA, 2, 0x3F);
        cow -> fillCircle(34 + off_x, 137 + off_y, graphicVGA, 2, 0x3F);
        cow -> fillCircle(58, 170, graphicVGA, 6, 0x05);
        cow -> fillRectangle(75, 150, graphicVGA, 7, 3, 0x3D);
        cow -> fillRectangle(79, 150, graphicVGA, 3, 10, 0x3D); 
        cow -> fillCircle(80, 160, graphicVGA, 2, 0x05);
    */

//barn
    Window * barn = new Window();
    barn -> fillRectangle(130, 120, graphicVGA, 60, 60, 0x0C);
    barn -> fillTriangle(160, 90, graphicVGA, 60, 29, 0x0C);
    // Window * barnDoor = new Window();
    barn -> drawRectangle(140, 140, graphicVGA, 40, 40, 0x3F);
    barn -> drawDiagonalLines(140, 140, graphicVGA, 40, 40, 0x3F);


    // CLEAR SCREEN
    // if (input) {
    //     // for(int32_t y = 0; y < 200; y++){
    //     //     for(int32_t x = 0; x < 320; x++){
    //     //         graphicVGA -> putPixelIndex(x, y, 0x01);
    //     //     }
    //     // }
    // }

       //the code below is for vga text mode!!!
        // auto newvga = new VGA();
        // newvga -> vga_init();
        // for (uint16_t i = 150; i < 210; i++) {
        //         newvga -> print_string(" hello from t0 ", i * 2); // Make sure that print_string is properly implemented to write spaces to VGA memory.
        // }

    while(1);

}