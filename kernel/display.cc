#include "display.h"
#include "ports.h"
#include "machine.h"
#include "debug.h"

/*
#define VIDEO_ADDRESS 0xb8000
#define MAX_ROWS 25
#define MAX_COLS 80
#define WHITE_ON_BLACK 0x0f

Screen i/o ports 
// #define REG_SCRxpEEN_CTRL 0x3d4
// #define REG_SCREEN_DATA 0x3d5
*/

void set_cursor(int offset) {
    offset /= 2;
    outb(0x3d4, 14); 
    outb(0x3d5, (unsigned char) (offset >> 8));
    outb(0x3d4, 15);
    outb(0x3d5, (unsigned char) (offset & 0xff));
}

int get_cursor() {
    outb(0x3d4, 14);
    int offset = inb(0x3d5) << 8; /* High byte: << 8 */
    outb(0x3d4, 15);
    offset += inb(0x3d5);
    return offset * 2;
}

int get_offset(int col, int row) {
    return 2 * (row * 80 + col);
}

int get_row_from_offset(int offset) {
    return offset / (2 * 80);
}

int move_offset_to_new_line(int offset) {
    return get_offset(0, get_row_from_offset(offset) + 1);
}

void set_char_at_video_memory(char character, int offset) {
    unsigned char *vidmem = (unsigned char *) 0xb8000;
    vidmem[offset] = character;
    // vidmem[offset + 1] = 0x0f; //white on black
}

int scroll_ln(int offset) {
    //potentially fix memcpy parameters
    memcpy(
            (void *)((char *) (get_offset(0, 0) + 0xb8000)),
            (const void *)((char *) (get_offset(0, 1) + 0xb8000)),
            80 * (25 - 1) * 2 
    );

    for (int col = 0; col < 80; col++) {
        set_char_at_video_memory(' ', get_offset(col, 25 - 1));
    }

    return offset - 2 * 80;
}

/*
 * TODO:
 * - handle illegal offset (print error message somewhere)
 */
// void print_string(char *string) {
//     int offset = get_cursor();
//     int i = 0;
//     while (string[i] != 0) {
//         if (offset >= 25 * 80 * 2) {
//             offset = scroll_ln(offset);
//         }
//         if (string[i] == '\n') {
//             offset = move_offset_to_new_line(offset);
//         } else {
//             set_char_at_video_memory(string[i], offset);
//             offset += 2;
//         }
//         i++;
//     }
//     set_cursor(offset);
// }

void print_nl() {
    int newOffset = move_offset_to_new_line(get_cursor());
    if (newOffset >= 25 * 80 * 2) {
        newOffset = scroll_ln(newOffset);
    }
    set_cursor(newOffset);
}

void clear_screen() {
    int screen_size = 25 * 80;
    for (int i = 0; i < screen_size; ++i) {
        set_char_at_video_memory(' ', i * 2);
    }
    set_cursor(get_offset(0, 0));
}


//from util
char *int_to_string(int v, char *buff, int radix_base) {
    static char table[] = "0123456789abcdefghijklmnopqrstuvwxyz";
    char *p = buff;
    unsigned int n = (v < 0 && radix_base == 10) ? -v : (unsigned int) v;
    while (n >= (unsigned int)radix_base) {
        *p++ = table[n % radix_base];
        n /= radix_base;
    }
    *p++ = table[n];
    if (v < 0 && radix_base == 10) *p++ = '-';
    *p = '\0';
    return buff;
}


// void set_cursor(int offset) {
//     offset /= 2;
//     outb(0x3d4, 14); 
//     outb(0x3d5, (unsigned char) (offset >> 8));
//     outb(0x3d4, 15);
//     outb(0x3d5, (unsigned char) (offset & 0xff));
// }

// int get_cursor() {
//     outb(0x3d4, 14);
//     int offset = inb(0x3d5) << 8; /* High byte: << 8 */
//     outb(0x3d4, 15);
//     offset += inb(0x3d5);
//     return offset * 2;
// }

// int get_offset(int col, int row) {
//     return 2 * (row * 80 + col);
// }

// int get_row_from_offset(int offset) {
//     return offset / (2 * 80);
// }

// int move_offset_to_new_line(int offset) {
//     return get_offset(0, get_row_from_offset(offset) + 1);
// }

// void set_char_at_video_memory(char character, int offset) {
//     unsigned char *vidmem = (unsigned char *) 0xb8000;
//     vidmem[offset] = character;
//     vidmem[offset + 1] = 0x0f; //white on black
// }

// /*
//  * TODO:
//  * - handle illegal offset (print error message somewhere)
//  */
// void print_string(char *string) {
//     int offset = get_cursor();
//     int i = 0;
//     while (string[i] != 0) {
//         if (string[i] == '\n') {
//             offset = move_offset_to_new_line(offset);
//         } else {
//             set_char_at_video_memory(string[i], offset);
//             offset += 2;
//         }
//         i++;
//     }
//     set_cursor(offset);
// }

// void print_nl() {
//     int newOffset = move_offset_to_new_line(get_cursor());
//     set_cursor(newOffset);
// }

// void clear_screen() {
//     int screen_size = 25 * 80;
//     for (int i = 0; i < screen_size; ++i) {
//         set_char_at_video_memory(' ', i * 2);
//     }
//     set_cursor(get_offset(0, 0));
// }


// //from util
// char *int_to_string(int v, char *buff, int radix_base) {
//     static char table[] = "0123456789abcdefghijklmnopqrstuvwxyz";
//     char *p = buff;
//     unsigned int n = (v < 0 && radix_base == 10) ? -v : (unsigned int) v;
//     while (n >= (unsigned int)radix_base) {
//         *p++ = table[n % radix_base];
//         n /= radix_base;
//     }
//     *p++ = table[n];
//     if (v < 0 && radix_base == 10) *p++ = '-';
//     *p = '\0';
//     return buff;
// }