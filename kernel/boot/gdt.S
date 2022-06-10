;
; Global Descriptor Table in 32 bit protected mode
;   we need gdt before enabling paging
;

gdt_start:

gdt_null:      ; first entry of gdt
    dd 0x0 ; 4B of zero
    dd 0x0 ; 4B of zero

gdt_code:      ; entry for code section
    ; Base:     0x00000
    ; Limit:    0xFFFFF
    ; 1st Flags:        0b1001
    ;   Present:        1
    ;   Privelege:      00
    ;   Descriptor:     1
    ; Type Flags:       0b1010
    ;   Code:           1
    ;   Conforming:     0
    ;   Readable:       1
    ;   Accessed:       0
    ; 2nd Flags:        0b1100
    ;   Granularity:    1
    ;   32-bit Default: 1
    ;   64-bit Segment: 0
    ;   AVL:            0

    dw 0xffff           ; Limit (bits 0-15)
    dw 0x0              ; Base  (bits 0-15)
    db 0x0              ; Base  (bits 16-23)
    db 10011010b        ; 1st Flags, Type flags
    db 11001111b        ; 2nd Flags, Limit (bits 16-19)
    db 0x0              ; Base  (bits 24-31)

gdt_data:
    dw 0xFFFF
    dw 0x0
    db 0x0
    db 10010010b
    db 11001111b
    db 0x0

gdt_end:

gdt_descriptor:
    dw gdt_end - gdt_start - 1 ; size field: the size of table - 1
    dd gdt_start               ; offset field

CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start
