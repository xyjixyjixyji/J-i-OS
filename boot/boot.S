;
; =====================================
; |       REAL MODE SECTOR(boot)      |  
; =====================================
;
[org 0x7c00] ; bootloader offset

[bits 16]

    mov bp, 0x0500 ; set the stack
    mov sp, bp

    mov byte[boot_drive], dl

    mov bx, MSG_REAL_MODE
    call print ; This will be written after the BIOS messages

    ; before we swtch to pm, we need to load another sector
    mov dx, 0
    mov es, dx

    ; es:dx = dest paddr
    mov dx, 0x7E00

    mov cx, 20

    call disk_load

    call switch_to_pm
    jmp $ ; this will actually never be executed

MSG_REAL_MODE db "Started in 16-bit real mode", 0
boot_drive    db 0x00

%include "./real/boot_prt.S"
%include "./real/boot_lddsk.S"
%include "./real/boot_swtch.S"
%include "./real/prot_gdt.S"

; bootsector
times 510-($-$$) db 0
dw 0xaa55


;
; ====================================
; |       PROTECTED MODE SECTOR      |  
; ====================================
;

[bits 32]

PROT_MODE_START:

[bits 32]
BEGIN_PM: ; after the switch we will get here
    call clear_vga_pm
    call detect_lm_prot

    call init_pgtbl_prot

    call switch_to_lm

    jmp $

%include "./prot/prot_prt.S"
%include "./prot/prot_lm.S"
%include "./prot/prot_pg.S"
%include "./prot/prot_swtch.S"
%include "./prot/long_gdt.S"

MSG_PROT_MODE db "Loaded 32-bit protected mode", 0
MSG_LM_SUPPORTED db "64-bit long mode supported", 0
VGA_BUFFER equ 0xb8000
VGA_SIZE   equ 25 * 80 * 2
COLOR_WB   equ 0x0f ; the color byte for each character

times 512-($-PROT_MODE_START) db 0

;
; ====================================
; |         LONG MODE SECTOR         |  
; ====================================
;

[bits 64]

; 0x7C00 -> 0x7E00 sec1 (real mode code)
; 0x7E00 -> 0x8000 sec2 (prot mode code)
; 0x8000 -> 0x8200 sec3 (long mode code)
; 0x8200 (our C kernel, use ld to load to that area)

BEGIN_LONG_MODE:
    mov rdi, COLOR_WHITE_BLUE
    call clear_vga_lm

    mov rdi, COLOR_WHITE_BLUE
    mov rsi, MSG_LM_OK
    call print_string_lm

    call kernel_start

    jmp $

%include "./long/long_prt.S"

kernel_start     equ 0x8200
MSG_LM_OK        db "Running in long mode, paging enabled...", 0
COLOR_WHITE_BLUE equ 0x1F

times 512-($-BEGIN_LONG_MODE) db 0
