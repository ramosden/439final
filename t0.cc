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
    


    Window * newWindow = new Window(graphicVGA, 0, 0, 320, 200);
    newWindow -> draw_window();
    newWindow -> fillRectangle(320, 200, graphicVGA, 0x01);

    // Window * newWindowtwo = new Window(graphicVGA, 0, 0, 320, 200);
    // newWindowtwo -> draw_window();
    // newWindowtwo -> fillRectangle(320, 200, graphicVGA, 0x00);

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