[bits 64]
[extern _start]

SECTION .text.prologue
GLOBAL _entry
[extern VGA_BUFFER]
_entry:
    call _start
    jmp $
