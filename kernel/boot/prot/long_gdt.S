;
; Global Descriptor Table in 64 bit long mode
;
; We are using this gdt because we need to LOAD it to LEAVE
; the compatability mode we used(32bit) previously when we 
; define a 32 bit gdt, where we have out 32BIT CODESEG and 
; 32BIT DATASEG
;
; We define this gdt simply for changing to Long mode completely
; This gdt will not be use for access control since pgtbl is used
;

gdt_64_start:

gdt_64_null:      ; first entry of gdt
    dd 0x0 ; 4B of zero
    dd 0x0 ; 4B of zero

gdt_64_code:      ; entry for code section
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
    ; 2nd Flags:        0b1010
    ;   Granularity:    1
    ;   32-bit Default: 0
    ;   64-bit Segment: 1
    ;   AVL:            0

    dw 0xffff           ; Limit (bits 0-15)
    dw 0x0              ; Base  (bits 0-15)
    db 0x0              ; Base  (bits 16-23)
    db 10011010b        ; 1st Flags, Type flags
    db 10101111b        ; 2nd Flags, Limit (bits 16-19)
    db 0x0              ; Base  (bits 24-31)

    ; Base:     0x00000
    ; Limit:    0x00000
    ; 1st Flags:        0b1001
    ;   Present:        1
    ;   Privelege:      00
    ;   Descriptor:     1
    ; Type Flags:       0b0010
    ;   Code:           0
    ;   Conforming:     0
    ;   Readable:       1
    ;   Accessed:       0
    ; 2nd Flags:        0b1010
    ;   Granularity:    1
    ;   32-bit Default: 0
    ;   64-bit Segment: 1
    ;   AVL:            0

gdt_64_data:
    dw 0x0
    dw 0x0
    db 0x0
    db 10010010b
    db 10101111b
    db 0x0

gdt_64_end:

gdt_64_descriptor:
    dw gdt_64_end - gdt_64_start - 1 ; size field: the size of table - 1
    dd gdt_64_start                  ; offset field

CODE_SEG_64 equ gdt_64_code - gdt_64_start
DATA_SEG_64 equ gdt_64_data - gdt_64_start