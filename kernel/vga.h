#ifndef vga_h
#define vga_h
#include "machine.h"

class VGA {
    public:

        // auto VGA_CTRL_REGISTER = 0x3D4;
        // auto VGA_DATA_REGISTER = 0x3D5;
        // auto VGA_CURSOR_LOCATION_HIGH = 14;
        // auto VGA_CURSOR_LOCATION_LOW = 15;
        // auto VGA_MEMORY = 0xB8000;
        // auto VGA_WIDTH = 80;
        
        void set_cursor_position(uint16_t position) {
            outb(0x3D4, 14); // Make sure that the outb function is properly defined and implemented to write to the specified port.
            outb(0x3D5, position >> 8);
            outb(0x3D4, 15); // Make sure that the outb function is properly defined and implemented to write to the specified port.
            outb(0x3D5, position);
        }

        // Print a string at the given VGA memory address
        void print_string(const char* str, uint16_t location) {
            // Set cursor position at start of the line
            set_cursor_position(location);

            // Loop through string and write characters to VGA memory
            for (size_t i = 0; str[i] != '\0'; i++) {
                uint16_t* location_ptr = reinterpret_cast<uint16_t*>(0xB8000 + location + i * 2); // Make sure that the location_ptr is pointing to the correct memory location in VGA_MEMORY.
                *location_ptr = static_cast<uint16_t>(str[i]) | 0x0700; // Make sure that the character is properly converted to uint16_t and combined with the attribute byte to display the correct color.
            }
        }
                // VGA initialization function
        void vga_init() {
            // Set VGA text mode
            outb(0x3C2, 0x0F);
            outb(0x3D4, 0x0A);
            outb(0x3D5, 0x20);
            outb(0x3D4, 0x0B);
            outb(0x3D5, 0x0);
            outb(0x3D4, 0x0C);
            outb(0x3D5, 0x0);
            outb(0x3D4, 0x0D);
            outb(0x3D5, 0x0E);

            // Clear screen
            for (uint16_t i = 0; i < 80; i++) {
                print_string(" ", i * 2); // Make sure that print_string is properly implemented to write spaces to VGA memory.
            }
        }
};
#endif