#include "debug.h"
#include "stdint.h"
#include "kernel/machine.h"

#include "debug.h"
#include "stdint.h"
#include "kernel/vga.h"
#include "init.h"
#include "kernel/graphicsvga.h"


void kernelMain() {
    // outb(0x64, 0xAD);
    // while ((int)(inb(0x64) & 0x1) == 0x1) {
    // }
    
    // Debug::printf("controller disabled\n");
    // while((inb(0x64) & 0x2) != 0) {}
    // outb(0x64, 0x20);
    // while ((inb(0x64) & 1) != 1) {} // bit 0 must be set before reading
    // int controller_config_byte = inb(0x60);
    // Debug::printf("config value: %x\n", controller_config_byte);
    // int val = inb(0x20);
    // clear bit 0, 1, 6
    // val = val & 0xFFFFFFFFFFFFFFBC;
    // bool has_dual_channel = false;
    // if ((int)(val & 0x20) > 0x0) {
        // has_dual_channel = true;
    // }
    // Debug::printf("%d\n", has_dual_channel);

    // outb(0x60, val);
    inb(0x60); // FLUSH OUTPUT BUFFER?

    // Debug::printf("did osdev flushing\n");
 
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
    // while (response != 0xfa) {
        // outb(0x60, 0xD4);
        // response = inb(0x60);
        Debug::printf("sent 0xD4 recieved: %x\n", response);
    // }
   

    // Debug::printf("PS/2 controller initialization complete\n");

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

    // while ((inb(0x64) & 0x2) != 0) {} // wait for cleared 1 bit
    // outb(0x60, 0xEB); // requesting for mouse packet
    // while ((inb(0x64) & 0x1) == 0) {} // wait for cleared 1 bit

    // // recieved ack
    // response = inb(0x60);
    // while (response != 0xfa) {
    //     response = inb(0x60);
    //     // Debug::printf("%x\n", response);
    // }
    // auto packet_1 = inb(0x60);
    // auto packet_2 = inb(0x60);
    // auto packet_3 = inb(0x60);
    // Debug::printf("packet 1: %x  packet 2: %x  packet 3: %x", packet_1, 
    //     packet_2, packet_3);
  
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
            graphicVGA -> putPixel(x, y, 0x00, 0x00, 0xA8);
        }
    }

    // waiting for input (polling)
    // FOLLOWS SCAN CODE 1 US QWERTY
    bool left_control_clicked = false;
    bool exit_terminal = false;
    int n = 1;
    while (!exit_terminal) {
        while ((inb(0x64) & 0x1) == 0) {}
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
            for(int32_t y = 0; y < 200; y++){
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
        break;
    }
    case 0x14 : {
        Debug::printf("t");
        break;
    }
    case 0x16 : {
        Debug::printf("u");
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
        Debug::printf("CLICK UP\n");
        // Debug::printf("7");
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
        Debug::printf("\nCLICK DOWN\n");
        // Debug::printf("8");
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
        Debug::printf("\nF7\n");
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
    else {
        // is mouse!
        // Debug::printf("MOUSE DATA\n");
         //Debug::printf("datas: %x %x %x %x\n", data, data_2, data_3, data_4);
            if (data == 0x18 && data_2 == 0xff && data_3 == 0x0 && data_4 == 0x41) {
                Debug::printf("mouse moving left\n");
            } else if (data == 0x08 && data_2 == 0x01 && data_3 == 0x0 && data_4 == 0x41) {
                Debug::printf("mouse moving right\n");
            } else if (data == 0x08 && data_2 == 0x0 && data_3 == 0x01 && data_4 == 0x41) {
                Debug::printf("mouse moving up\n");
            } else if (data == 0x28 && data_2 == 0x0 && data_3 == 0xff && data_4 == 0x41) {
                Debug::printf("mouse moving down\n");
            } else if (data == 0x9) {
                Debug::printf("mouse left click down\n");
            } else if (data == 0xa) {
                Debug::printf("mouse right click down\n");
            }
        
    }
    }
}
