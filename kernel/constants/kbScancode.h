/**
 * 
 * @file kbScancode.c
 * @brief translate bytestream from kb to ascii code
 * 
 */

#include "../include/types.h"

// globally accessible
// FIXME: may change the semantic of enter
// ....., see https://wiki.osdev.org/PS/2_Keyboard
u8 kbsc[] = {
    0,
    0, /* Escape */
    '1', '2', '3', '4', '5', '6', '7',
    '8', '9', '0', '-', '=', '\b', '\t', 'q',
    'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p',
    '[', ']',
    '\n', /* enter */
    0, /* left control */
    'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l',
    ';', '\'', '`',
    0 /* left shift */,
    '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',',
    '.', '/',
    0 /* right shift */,
    0 /* keypad * */,
    0 /* lalt */,
    ' ',
    0 /* caps */,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /* F1-F10 */
    0 /* number lock */,
    0 /* scroll lock */,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0,
    /* release sequences below, not handled now */
    0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, /* here is the end of F12 released line */
};