print:
    pusha

start:
    mov al, [bx] ; base addr of string
    cmp al, 0
    je done
    mov ah, 0x0e
    int 0x10

    add bx, 1
    jmp start

done:
    popa
    ret

print_nl:
    pusha

    mov ah, 0x0e
    mov al, 0x0a ; newline
    int 0x10
    mov al, 0x0d ; carriage return
    int 0x10

    popa
    ret

print_hex:
    pusha

    mov cx, 0 ; index

hex_loop:
    cmp cx, 4 ; 4 digit hex
    je end

    mov ax, dx
    and ax, 0x000f ; 0x1234 -> 0x0004
    add al, 0x30
    cmp al, 0x39   ; > 9 -> A - F
    jle step2
    add al, 7      ; 'A': 65

step2:
    ; get the correct position of string to 
    ; place our ASCII char
    ; bx <- base + len - index
    mov bx, HEX_OUT + 5
    sub bx, cx
    mov [bx], al
    ror dx, 4

    add cx, 1
    jmp hex_loop

end:
    mov bx, HEX_OUT
    call print
    popa
    ret
    

HEX_OUT:
    db '0x0000', 0
