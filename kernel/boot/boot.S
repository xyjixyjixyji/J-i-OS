[org 0x7c00] ; bootloader offset
    mov bp, 0x9000 ; set the stack
    mov sp, bp

    mov bx, MSG_REAL_MODE
    call print ; This will be written after the BIOS messages

    ; before we swtch to pm, we need to load another sector
    mov bx, 0x7E00
    mov dh, 1
    call disk_load

    call switch_to_pm
    jmp $ ; this will actually never be executed

%include "./boot_prt.S"
%include "./boot_lddsk.S"
%include "./prot/prot_swtch.S"

MSG_REAL_MODE db "Started in 16-bit real mode", 0
MSG_PROT_MODE db "Loaded 32-bit protected mode", 0

; bootsector
times 510-($-$$) db 0
dw 0xaa55

%include "./prot/prot_prt.S"
%include "./prot/gdt.S"
[bits 32]
BEGIN_PM: ; after the switch we will get here
    call clear_vga_pm

    mov ebx, MSG_PROT_MODE
    call print_string_pm ; Note that this will be written at the top left corner
    jmp $
