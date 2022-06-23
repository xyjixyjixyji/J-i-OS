#ifndef __VGA_H
#define __VGA_H

#include "types.h"

#define VGA_START  0xb8000
#define VGA_WIDTH  80
#define VGA_HEIGHT 25
#define VGA_SIZE   VGA_WIDTH * VGA_HEIGHT

#define COLOR_BLK       0
#define COLOR_BLUE      1
#define COLOR_GREEN     2
#define COLOR_CYAN      3
#define COLOR_RED       4
#define COLOR_PURPLE    5
#define COLOR_BROWN     6
#define COLOR_GRAY      7
#define COLOR_DK_GRAY   COLOR_BLK       & 0xF
#define COLOR_LT_BLUE   COLOR_BLUE      & 0xF
#define COLOR_LT_GREEN  COLOR_GREEN     & 0xF
#define COLOR_LT_RED    COLOR_RED       & 0xF
#define COLOR_LT_PURPLE COLOR_PURPLE    & 0xF
#define COLOR_YELLOW    COLOR_BROWN     & 0xF
#define COLOR_WHITE     COLOR_GRAY      & 0xF

#define CURSOR_PORT_CMD  (u16) 0x3D4
#define CURSOR_PORT_DATA (u16) 0x3D5

typedef struct __attribute__((packed)) {
    char ch;
    char color;
} vga_char;

#endif
