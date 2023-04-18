
#include "stdint.h"
#include "machine.h"
#include "ports.h"


class graphicsVGA {
        // Ports miscPort();
        // Ports crtcIndexPort();
        // Ports crtcDataPort();
        // Ports seqIndexPort();
        // Ports seqDataPort();
        // Ports graphicsCtrlIndexPort();
        // Ports graphicsCtrlDataPort();
        // Ports attrbCtrlIndexPort();
        // Ports attrbCtrlReadPort();
        // Ports attrbCtrlWritePort();
        // Ports attrbCtrlResetPort();
        Ports miscPort(0x3C2);
        Ports crtcIndexPort(0x3D4);
        Ports crtcDataPort(0x3D5);
        Ports seqIndexPort(0x3C4);
        Ports seqDataPort(0x3C5);
        Ports graphicsCtrlIndexPort(0x3CE);
        Ports graphicsCtrlDataPort(0x3CF);
        Ports attrbCtrlIndexPort(0x3C0);
        Ports attrbCtrlReadPort(0x3C1);
        Ports attrbCtrlWritePort(0x3C0);
        Ports attrbCtrlResetPort(0x3DA);

    void writeRegisters(uint8_t * registers) {
        miscPort.write(*(registers++));
    }
    uint8_t * GetFrameBufferSegment() {

    }
    void putPixel(uint32_t x, uint32_t y, uint8_t colorIndex) {

    }
    uint8_t getColorIndex(uint8_t r, uint8_t g, uint8_t b) {

    }

    public:
        graphicsVGA() {

        }
        ~graphicsVGA() {

        }

        //graphics mode: set video mode value to 0x13, 320x200 pixels with 256 colors
        bool supportsMode(uint32_t width, uint32_t height, uint32_t colorDepth) {
            return width == 320 && height == 200 && colorDepth = 8;
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




};


