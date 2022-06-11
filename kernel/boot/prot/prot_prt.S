[bits 32] ; using 32-bit protected mode

; this is how constants are defined
VGA_BUFFER equ 0xb8000
VGA_SIZE   equ 25 * 80 * 2
COLOR_WB   equ 0x0f ; the color byte for each character

; char from ebx
print_string_pm:
    pushad
    mov edx, VGA_BUFFER

print_string_pm_loop:
    mov al, [ebx] ; [ebx] is the address of our character
    mov ah, COLOR_WB

    cmp al, 0 ; check if end of string
    je print_string_pm_done

    mov [edx], ax ; store character + attribute in video memory
    add ebx, 1 ; next char
    add edx, 2 ; next video memory position

    jmp print_string_pm_loop

print_string_pm_done:
    popad
    ret

; clear the vga_buffer
space equ ' '
clear_vga_pm:
    pushad
    mov ebx, VGA_BUFFER
    mov ecx, VGA_SIZE
    mov edx, 0

clear_vga_pm_loop:
    cmp edx, ebx
    je clear_vga_pm_done

    push edx

    mov al, space
    mov ah, COLOR_WB

    add edx, ebx ; index += offset
    mov [edx], ax

    pop edx
    add edx, 2

    jmp clear_vga_pm_loop

clear_vga_pm_done:
    popad
    ret