// #include "display.h"
#include "debug.h"
#include "stdint.h"
#include "vga.h"
#include "init.h"
// #include "graphicsvga.h"
#include "window.h"

void kernelMain() {
    
    //the code below is for vga text mode!!!
        // auto newvga = new VGA();
        // newvga -> vga_init();
        // for (uint16_t i = 150; i < 210; i++) {
        //         newvga -> print_string(" hello from t0 ", i * 2); // Make sure that print_string is properly implemented to write spaces to VGA memory.
        // }
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
    
    //draw a rectangle on screen
    for(int32_t y = 0; y < 200; y++){
        for(int32_t x = 0; x < 320; x++){
            graphicVGA -> putPixel(x, y, 0x00, 0x00, 0xA8);
        }
    }

    Window * newWindow = new Window(graphicVGA, 0, 0, 320, 200);
    newWindow -> draw_window();
    // for (size_t i = 0; str[i] != '\0'; i++) {
    //             uint16_t* location_ptr = reinterpret_cast<uint16_t*>(0xB8000 + location + i * 2); // Make sure that the location_ptr is pointing to the correct memory location in VGA_MEMORY.
    //             *location_ptr = static_cast<uint16_t>(str[i]) | 0x0700; // Make sure that the character is properly converted to uint16_t and combined with the attribute byte to display the correct color.
    //         }
    while(1);

}