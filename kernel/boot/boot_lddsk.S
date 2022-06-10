disk_load:
    pusha
    push dx

    mov ah, 0x02
    mov al, dh      ; expected to be loaded w/ the # of sectors to read
    mov cl, 0x02    ; first available sector, 1 is bootloader
    mov ch, 0x00    ; cylinder #
    mov dh, 0x00    ; head #
    int 0x13        ; caller setup buffer to [es:bx]
    jc ERR_DISK     ; CF=1 if error

    pop dx
    cmp al, dh      ; al=# of sectors read, sanity check
    jne ERR_SECTOR
    popa
    ret

ERR_DISK:
    mov bx, DISK_ERROR	; info
    call print
    call print_nl
    mov dh, ah		; error code
    call print_hex
    jmp loop

ERR_SECTOR:
    mov bx, SECTORS_ERROR
    call print

loop:
    jmp loop

DISK_ERROR: db "Disk read error", 0
SECTORS_ERROR: db "Incorrect number of sectors read", 0


