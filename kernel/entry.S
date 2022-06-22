[bits 64]
[extern _start]

SECTION .text.prologue
GLOBAL _entry
_entry:
    call _start
    jmp $
