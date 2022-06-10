[org 0x7c00]
    mov bp, 0x8000	; stack base
    mov sp, bp

    mov bx, 0x9000	; buffer, [es:bx]
    mov dh, 2

    call disk_load

    mov dx, [0x9000]
    call print_hex

    call print_nl

    mov dx, [0x9000 + 512] ; first word from second sector
    call print_hex

    jmp $

%include "./boot_prt.S"
%include "./boot_lddsk.S"

times 510-($-$$) db 0
dw 0xaa55

times 256 dw 0xdada ; sec 2
times 256 dw 0xface ; sec 3
