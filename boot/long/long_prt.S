;
; Using VGA_BUFFER to print
;

[bits 64]

; rdi: color
; rsi: base addr of string
print_string_lm:
    push rax
    push rdx
    push rdi
    push rsi

    mov rdx, VGA_BUFFER
    shl rdi, 8  ; (color, char)

print_string_lm_loop:
    ; check if done
    cmp byte[rsi], 0
    je print_string_lm_done

    ; check if full
    cmp rdx, VGA_BUFFER + VGA_SIZE
    je print_string_lm_done

    mov rax, rdi
    mov al, byte[rsi]

    mov word[rdx], ax

    add rsi, 1
    add rdx, 2

    jmp print_string_lm_loop

print_string_lm_done:
    pop rsi
    pop rdi
    pop rdx
    pop rax
    ret

; rdi: color
clear_vga_lm:
    push rdi
    push rax
    push rcx

    shl rdi, 8
    mov rax, rdi

    mov al, space

    ; rep stosw write 1 word
    ;
    ; rax: value to write
    ; rdi: start addr
    ; rcx: # of repeatitions to perform

    mov rdi, VGA_BUFFER
    mov rcx, VGA_SIZE / 2
    
    rep stosw

    pop rcx
    pop rax
    pop rdi

    ret