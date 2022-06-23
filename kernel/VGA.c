#include "include/defs.h"
#include "include/VGA.h"
#include "include/types.h"

volatile vga_char *VGA_BUFFER = (vga_char*) VGA_START;

u8
VGA_color(const u8 fg, const u8 bg)
{
    return (bg << 4) | (fg & 0xF);
}

void
VGA_clear(const u8 fg, const u8 bg)
{
    int i;
    vga_char space;
    space.ch=' ';
    space.color=VGA_color(fg, bg);

    for(i = 0; i < VGA_SIZE; i++){
        VGA_BUFFER[i] = space;
    }
}

void
VGA_putc(const char ch, const u8 fg, const u8 bg)
{
    vga_char c;
    c.ch = ch;
    c.color = VGA_color(fg, bg);

    u16 cpos = get_cpos();
    if (ch == '\n') {
        set_cpos(0, (u8)(cpos / VGA_WIDTH + 1));
        return;
    }

    VGA_BUFFER[cpos] = c;
}

void
VGA_putstr(const char *str, const u8 fg, const u8 bg)
{
    while(*str) {
        VGA_putc(*str, fg, bg);
        str++;
        advance_cpos();
    }
}

void
VGA_putint(const int n, int radix)
{
    char str[32];
    itoa(n, str, radix);
    VGA_putstr(str, COLOR_RED, COLOR_BLK);
}

void
VGA_panic(const char* str)
{
    VGA_putstr(str, COLOR_RED, COLOR_BLK);
    while(1)
	;
}

u16
get_cpos()
{
    u16 cpos = 0;
    w_port(CURSOR_PORT_CMD, 0x0F);
    cpos |= r_port(CURSOR_PORT_DATA);

    w_port(CURSOR_PORT_CMD, 0x0E);
    cpos |= r_port(CURSOR_PORT_DATA) << 8;

    return cpos;
}

void advance_cpos()
{
    u16 cpos = get_cpos();
    cpos++;

    if (cpos >= VGA_SIZE) {
	    cpos = VGA_SIZE - 1;
    }

    w_port(CURSOR_PORT_CMD, 0x0F);
    w_port(CURSOR_PORT_DATA, (u8)(cpos & 0xFF)); // first byte
    w_port(CURSOR_PORT_CMD, 0x0E);
    w_port(CURSOR_PORT_DATA, (u8)((cpos >> 8) & 0xFF)); // second byte
}

void
set_cpos(u8 x, u8 y)
{
    u16 pos = (y * (u16)VGA_WIDTH) + x;
    if (pos >= VGA_SIZE) {
	    pos = VGA_SIZE - 1;
    }

    w_port(CURSOR_PORT_CMD, 0x0F);
    w_port(CURSOR_PORT_DATA, (u8)(pos & 0xFF)); // first byte
    w_port(CURSOR_PORT_CMD, 0x0E);
    w_port(CURSOR_PORT_DATA, (u8)((pos >> 8) & 0xFF)); // second byte
}

//
// we assume that cursor_start = cursor_end = 0
//
void
show_cursor()
{
    w_port(CURSOR_PORT_CMD, 0x0A);
    w_port(CURSOR_PORT_DATA, (r_port(CURSOR_PORT_DATA) & 0xC0) | 0);

    w_port(CURSOR_PORT_CMD, 0x0B);
    w_port(CURSOR_PORT_DATA, (r_port(CURSOR_PORT_DATA) & 0xE0) | 0);
}

void hide_cursor()
{
    w_port(CURSOR_PORT_CMD, 0x0A);
    w_port(CURSOR_PORT_DATA, 0x20);
}
