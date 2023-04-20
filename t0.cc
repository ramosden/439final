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

        /* BLUE BACKGROUND*/
        background -> fillRectangle(0, 0, graphicVGA, 320, 200, 0x19); 

        /* ORANGE BACKGROUND*/
        // background -> fillRectangle(0, 0, graphicVGA, 320, 200, 0x3D); 

    // /* GRASS */
    Window * grass = new Window();
    grass -> fillRectangle(0, 180, graphicVGA, 320, 200, 0x02); // x, y, vga, width, height, colorindex

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

    // COW
    
    Window * cowbody = new Window();
    cowbody -> fillRectangle(30, 150, graphicVGA, 45, 20, 0x3D);

    Window * cowlegone = new Window();
    cowlegone -> fillRectangle(35, 170, graphicVGA, 10, 12, 0x3D);

    Window * cowlegtwo = new Window();
    cowlegtwo -> fillRectangle(35, 170, graphicVGA, 10, 9, 0x3D);

    Window * cowlegthree = new Window();
    cowlegthree -> fillRectangle(60, 170, graphicVGA, 10, 12, 0x3D);

    Window * cowhead = new Window();
    cowhead -> fillCircle(27, 147, graphicVGA, 10, 0x3D);


    Window * cowmouth = new Window();
    cowmouth -> fillRectangle(15, 150, graphicVGA, 23, 5, 0x3F);
    

    Window * coweyeone = new Window();
    coweyeone -> fillCircle(23, 144, graphicVGA, 1, 0x00);

    Window * coweyetwo = new Window();
    coweyetwo -> fillCircle(31, 144, graphicVGA, 1, 0x00);


    Window * cownostrilone = new Window();
    cownostrilone -> fillCircle(18, 152, graphicVGA, 1, 0x00);

    Window * cownostriltwo = new Window();
    cownostriltwo -> fillCircle(34, 152, graphicVGA, 1, 0x00);
/*
    Window * cowhairone = new Window();
    cowhairone -> fillCircle(0, 0, graphicVGA, 2, 0x3F);

    Window * cowhairtwo = new Window();
    cowhairtwo -> fillCircle(0, 0, graphicVGA, 2, 0x3F);

    Window * cowhairthree = new Window();
    cowhairthree -> fillCircle(0, 0, graphicVGA, 2, 0x3F);

    Window * cowhairfour = new Window();
    cowhairfour -> fillCircle(0, 0, graphicVGA, 2, 0x3F);

    Window * cowutters = new Window();
    cowutters -> fillCircle();

    Window * cowtail = new Window();
    cowtail -> fillRectangle();
    
    Window * cowtailend = new Window();
    cowtailend -> fillCircle();


*/


    



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