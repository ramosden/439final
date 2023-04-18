// #include "display.h"
#include "debug.h"
#include "stdint.h"
#include "vga.h"
#include "init.h"
#include "graphicsvga.h"

// // VGA text mode constants
// auto VGA_CTRL_REGISTER = 0x3D4;
// auto VGA_DATA_REGISTER = 0x3D5;
// auto VGA_CURSOR_LOCATION_HIGH = 14;
// auto VGA_CURSOR_LOCATION_LOW = 15;
// auto VGA_MEMORY = 0xB8000;
// auto VGA_WIDTH = 80;

// // Helper function to write to VGA register
// // void write_vga_register(uint8_t index, uint8_t value) {
// //     __asm__ volatile("outb %0, %1" : : "a"(value), "Nd"(index));
// // }

// // Set cursor position on screen
// void set_cursor_position(uint16_t position) {
//     outb(VGA_CTRL_REGISTER, VGA_CURSOR_LOCATION_HIGH);
//     // write_vga_register(VGA_CTRL_REGISTER, VGA_CURSOR_LOCATION_HIGH);
//     outb(VGA_DATA_REGISTER, position >> 8);
//     outb(VGA_CTRL_REGISTER, VGA_CURSOR_LOCATION_LOW);
//     outb(VGA_DATA_REGISTER, position);
// }

// // Print a string at the given VGA memory address
// void print_string(const char* str, uint16_t location) {
//     // Set cursor position at start of the line
//     set_cursor_position(location);

//     // Loop through string and write characters to VGA memory
//     for (size_t i = 0; str[i] != '\0'; i++) {
//         uint16_t* location_ptr = reinterpret_cast<uint16_t*>(VGA_MEMORY + location + i * 2);
//         *location_ptr = static_cast<uint16_t>(str[i]) | 0x0700;
//     }
// }

// // VGA initialization function
// void vga_init() {
//     // Set VGA text mode
//     outb(0x3C2, 0x0F);
//     outb(0x3D4, 0x0A);
//     outb(0x3D5, 0x20);
//     outb(0x3D4, 0x0B);
//     outb(0x3D5, 0x0);
//     outb(0x3D4, 0x0C);
//     outb(0x3D5, 0x0);
//     outb(0x3D4, 0x0D);
//     outb(0x3D5, 0x0E);

//     // Clear screen
//     for (uint16_t i = 0; i < VGA_WIDTH; i++) {
//         print_string(" ", i * 2);
//     }
// }

// void kernelMain() {
//     vga_init();
//     print_string("Hello, world!", VGA_MEMORY);
// }



// auto VGA_CTRL_REGISTER = 0x3D4;
// auto VGA_DATA_REGISTER = 0x3D5;
// auto VGA_CURSOR_LOCATION_HIGH = 14;
// auto VGA_CURSOR_LOCATION_LOW = 15;
// auto VGA_MEMORY = 0xB8000;
// auto VGA_WIDTH = 80;

// Helper function to write to VGA register
// void write_vga_register(uint8_t index, uint8_t value) {
//     __asm__ volatile("outb %0, %1" : : "a"(value), "Nd"(index));
// }

// Set cursor position on screen
// void set_cursor_position(uint16_t position) {
//     outb(VGA_CTRL_REGISTER, VGA_CURSOR_LOCATION_HIGH); // Make sure that the outb function is properly defined and implemented to write to the specified port.
//     outb(VGA_DATA_REGISTER, position >> 8);
//     outb(VGA_CTRL_REGISTER, VGA_CURSOR_LOCATION_LOW); // Make sure that the outb function is properly defined and implemented to write to the specified port.
//     outb(VGA_DATA_REGISTER, position);
// }

// Print a string at the given VGA memory address
// void print_string(const char* str, uint16_t location) {
//     // Set cursor position at start of the line
//     set_cursor_position(location);

//     // Loop through string and write characters to VGA memory
//     for (size_t i = 0; str[i] != '\0'; i++) {
//         uint16_t* location_ptr = reinterpret_cast<uint16_t*>(VGA_MEMORY + location + i * 2); // Make sure that the location_ptr is pointing to the correct memory location in VGA_MEMORY.
//         *location_ptr = static_cast<uint16_t>(str[i]) | 0x0700; // Make sure that the character is properly converted to uint16_t and combined with the attribute byte to display the correct color.
//     }
// }

// // VGA initialization function
// void vga_init() {
//     // Set VGA text mode
//     outb(0x3C2, 0x0F);
//     outb(0x3D4, 0x0A);
//     outb(0x3D5, 0x20);
//     outb(0x3D4, 0x0B);
//     outb(0x3D5, 0x0);
//     outb(0x3D4, 0x0C);
//     outb(0x3D5, 0x0);
//     outb(0x3D4, 0x0D);
//     outb(0x3D5, 0x0E);

//     // Clear screen
//     for (uint16_t i = 0; i < VGA_WIDTH; i++) {
//         print_string(" ", i * 2); // Make sure that print_string is properly implemented to write spaces to VGA memory.
//     }
// }

// void print_string_two(const char* str, uint16_t location) {
//     // Set cursor position at start of the line
//     set_cursor_position(location);

//     // Loop through string and write characters to VGA memory
//     for (size_t i = 0; str[i] != '\0'; i++) {
//         uint16_t* location_ptr = reinterpret_cast<uint16_t*>(0xB8000 + location + i * 2);
//         uint16_t value = static_cast<uint16_t>(str[i]) | 0x0700;
//         *location_ptr = value;
//         Debug::printf("VGA memory at location %x: %04x\n", location + i * 2, value);
//     }
// }

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
    graphicVGA -> setMode(320, 200, 8);
    //draw a rectangle on screen
    for(int32_t y = 0; y < 200; y++){
        for(int32_t x = 0; x < 320; x++){
            graphicVGA -> putPixel(x, y, 0x00, 0x00, 0xA8);
        }
    }
    // for (size_t i = 0; str[i] != '\0'; i++) {
    //             uint16_t* location_ptr = reinterpret_cast<uint16_t*>(0xB8000 + location + i * 2); // Make sure that the location_ptr is pointing to the correct memory location in VGA_MEMORY.
    //             *location_ptr = static_cast<uint16_t>(str[i]) | 0x0700; // Make sure that the character is properly converted to uint16_t and combined with the attribute byte to display the correct color.
    //         }
    while(1);

}