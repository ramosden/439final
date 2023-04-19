#include "stdint.h"
#include "machine.h"
#include "ports.h"


class graphicsVGA {
    public:
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
        
        graphicsVGA(
        Ports miscPort, Ports crtcIndexPort, Ports crtcDataPort,  Ports seqIndexPort, Ports seqDataPort, Ports graphicsCtrlIndexPort, Ports graphicsCtrlDataPort, Ports attrbCtrlIndexPort, Ports attrbCtrlReadPort, Ports attrbCtrlWritePort, Ports attrbCtrlResetPort) : 
        miscPort(0x3C2),
        crtcIndexPort(0x3D4),
        crtcDataPort(0x3D5),
        seqIndexPort(0x3C4),
        seqDataPort(0x3C5),
        graphicsCtrlIndexPort(0x3CE),
        graphicsCtrlDataPort(0x3CF),
        attrbCtrlIndexPort(0x3C0),
        attrbCtrlReadPort(0x3C1),
        attrbCtrlWritePort(0x3C0),
        attrbCtrlResetPort(0x3DA) {}

        ~graphicsVGA() {}

    void writeRegisters(uint8_t * registers) {
        // misc regs
        miscPort.write(*(registers++));

        // sequencer regs
        for(uint8_t i = 0; i < 5; i++){
            seqIndexPort.write(i);
            seqDataPort.write(*(registers++));
        }

        // crtc registers
        crtcIndexPort.write(0x03); //lock and unlock reg
        crtcDataPort.write(crtcDataPort.read() | 0x80);
        crtcIndexPort.write(0x11);
        crtcDataPort.write(crtcDataPort.read() & ~0x80); //set 1st bit to 0

        registers[0x03] = registers[0x03] | 0x80;
        registers[0x11] = registers[0x11] & ~0x80;

        for (uint8_t i = 0; i < 25; i++) {
            crtcIndexPort.write(i);
            crtcDataPort.write(*(registers++));
        }

        // graphics controller
        for (uint8_t i = 0; i < 9; i++) {
            graphicsCtrlIndexPort.write(i);
            graphicsCtrlDataPort.write(*(registers++));
        }

        // attribute controllers
        for (uint8_t i = 0; i < 21; i++) {
            attrbCtrlResetPort.read();
            attrbCtrlIndexPort.write(i);
            attrbCtrlWritePort.write(*(registers++));
        }

        attrbCtrlResetPort.read();
        attrbCtrlIndexPort.write(0x20);
    }

    //graphics mode: set video mode value to 0x13, 320x200 pixels with 256 colors
    bool supportsMode(uint32_t width, uint32_t height, uint32_t colorDepth) {
        return width == 320 && height == 200 && colorDepth == 8;
    }

    bool setMode(uint32_t width, uint32_t height, uint32_t colorDepth) {

        if(supportsMode(width, height, colorDepth) == false) {
            return false;
        }
        unsigned char g_320x200x256[] =
            {
            /* MISC */
                0x63,
            /* SEQ */
                0x03, 0x01, 0x0F, 0x00, 0x0E,
            /* CRTC */
                0x5F, 0x4F, 0x50, 0x82, 0x54, 0x80, 0xBF, 0x1F,
                0x00, 0x41, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                0x9C, 0x0E, 0x8F, 0x28,	0x40, 0x96, 0xB9, 0xA3,
                0xFF,
            /* GC */
                0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x05, 0x0F,
                0xFF,
            /* AC */
                0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
                0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
                0x41, 0x00, 0x0F, 0x00,	0x00
            };

            writeRegisters(g_320x200x256);
            return true;
    }

    uint8_t * GetFrameBufferSegment() {
        graphicsCtrlIndexPort.write(0x06);
        uint8_t segmentNum = graphicsCtrlDataPort.read() & (3<<2);
        switch (segmentNum) {
            default:
            
            case 0<<2: return(uint8_t*)0x00000;
            case 1<<2: return(uint8_t*)0xA0000;
            case 2<<2: return(uint8_t*)0xB0000;
            case 3<<2: return(uint8_t*)0xB8000;
        }
    }
    void putPixelIndex(uint32_t x, uint32_t y, uint8_t colorIndex) {
        uint8_t* pixelAddr = GetFrameBufferSegment() + 320*y + x;
        *pixelAddr = colorIndex;
    }
    uint8_t getColorIndex(uint8_t r, uint8_t g, uint8_t b) {
        if(r == 0x00 && g == 0x00 && b == 0xA8){
            return 0x01; //blue
        } 
        
        else if(r == 0xFF && g == 0xFF && b == 0xFF){
            return 0x17; //white
        }
        return 0x00;
    }
    
    void putPixel(uint32_t x, uint32_t y, uint8_t r, uint8_t g, uint8_t b) {
        putPixelIndex(x, y, getColorIndex(r, g, b));
    }
};


