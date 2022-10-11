#include "include/VGA.h"

#include "include/defs.h"
#include "include/types.h"

volatile vga_writer writer = {
    .pos_c = 0,
    .color = ((u8)COLOR_BLK << 4) | ((u8)COLOR_GREEN & 0xFF),
    .buf = (vga_char *)VGA_START,
};

static inline u8 vga_color(const u8 fg, const u8 bg) {
  return (bg << 4) | (fg & 0xF);
}

/*
 * change (r, c) to idx in VGA buffer
 */
static inline u64 rc2idx(const int r, const int c) { return r * VGA_WIDTH + c; }

static void vga_clearrow(u64 row) {
  vga_char blank = {
      .ch = ' ',
      .color = writer.color,
  };
  for (int i = 0; i < VGA_WIDTH; i++) {
    writer.buf[rc2idx(row, i)] = blank;
  }
}

void vga_clear() {
  for (int i = 0; i < VGA_HEIGHT; i++) {
    vga_clearrow(i);
  }
}

// erase last line, move every line upwards
static void vga_newline() {
  for (int i = 1; i < VGA_HEIGHT; i++) {
    for (int j = 0; j < VGA_WIDTH; j++) {
      writer.buf[rc2idx(i - 1, j)] = writer.buf[rc2idx(i, j)];
    }
  }
  vga_clearrow(VGA_HEIGHT - 1);
  writer.pos_c = 0;
}

static void vga_hidecursor() {
  w_port(CURSOR_PORT_CMD, 0x0A);
  w_port(CURSOR_PORT_DATA, 0x20);
}

void vga_init() {
  vga_clear();
  vga_hidecursor();
}

void vga_putc(const char ch) {
  switch (ch) {
    case '\n': {
      vga_newline();
      break;
    }
    case '\r': {
    }
    case '\b': {
    }
    case '\t': {
    }
    default: {
      if (writer.pos_c >= VGA_WIDTH) {
        vga_newline();
      }

      vga_char vc = {
          .ch = ch,
          .color = writer.color,
      };

      u64 row = VGA_HEIGHT - 1;
      u64 col = writer.pos_c;
      writer.buf[row * VGA_WIDTH + col] = vc;

      ++writer.pos_c;
    }
  }
}

void vga_putstr(const char *str) {
  while (*str) {
    vga_putc(*str);
    str++;
  }
}

void vga_putu64(const u64 val) {
  char buf[32];
  itoa(val, buf, 16);
  vga_putstr("0x");
  vga_putstr(buf);
}
