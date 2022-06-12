disk_load:
   ; Save the registers
    push ax
    push bx
    push cx
    push dx

    ; Save the number of registers to load for later
    push cx

    ; For the ATA Read bios utility, the value of ah must be 0x02
    ; See the BIOS article from Chapter 1.2 for more info
    mov ah, 0x02

    ; The number of sectors to read must be in al, but our function
    ; takes it in cl
    mov al, cl

    ; The sector to read from must be in cl, but our function takes it
    mov cl, 0x02

    ; The destination address must be in bx, but our function takes it
    ; in dx
    mov bx, dx

    mov ch, 0x00        ; Cylinder goes in ch
    mov dh, 0x00        ; Cylinder head goes in dh

    ; Store boot drive in dl
    mov dl, byte[boot_drive]

    ; Perform the BIOS disk read
    int 0x13

    ; Check read error
    jc ERR_DISK

    ; Pop number of sectors to read
    ; Compare with sectors actually read
    pop bx
    cmp al, bl
    jne ERR_SECTOR

    ; Restore the registers
    pop dx
    pop cx
    pop bx
    pop ax

    ; Return
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


