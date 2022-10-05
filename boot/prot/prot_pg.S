; initialize paging in protected mode

;! the 4 level paging scheme is used in long mode
;
; 4 level pgtbl (each 2^12 = 4096B)
;
; PML4T -> 0x1000 (Page Map Level 4 Table)
; PDPT  -> 0x2000 (Page Directory Pointer Table)
; PDT   -> 0x3000 (Page Directory Table)
; PT    -> 0x4000 (Page table)

[bits 32]

init_pgtbl_prot:
    pushad

    ; we are not setting up 32bit paging, we are going straight to long mode
    ; clear 31st bit of cr0 to disable it
    ;
    ; NOTE: IT IS CRUTIAL TO DISABLE PAGING HERE

    ; Clear the mem area using rep stosd(repeating string command)
    ;
    ; rep stosd actually tells CPU to write a dword(4B) each repetition
    ; It also inc edi by 4
    ;
    ; eax: value to write
    ; edi: start addr
    ; ecx: # of repeatitions to perform
    mov edi, 0x1000 ; pgtbl from 0x1000 to 0x4FFF

    mov cr3, edi    ; put base to cr3(pgtbl reg, like satp in RISCV)

    xor eax, eax    ;

    mov ecx, 4096   ; Repeat 4096 times, each time 4 bytes => zero out all entries
                    ; of the 4 level pgtbl
    rep stosd

    mov edi, cr3    ; edi = PML4T[0]

    ; set up the first entry of each table
    ; flag bit 000..0011b, valid and R/W to OS
    ;
    ; 0 - 32 bits of PTE
    ; 31 - 12: bits 31-12 of the vaddr
    ; 11 - 8 : AVL (available)
    ; 7      : PS (4MB or 4KB aligned)
    ; 6      : AVL (available)
    ; 5      : A (accessed)
    ; 4      : PCD (cache disable bit)
    ; 3      : PWT (write-through bit) else write back
    ; 2      : U/S (user/supervisor) or supervisor
    ; 1      : R/W (read/write) or rdonly
    ; 0      : Present
    mov dword[edi], 0x00002003 ; lv4[0] = lv3

    add edi, 0x1000

    mov dword[edi], 0x00003003 ; lv3[0] = lv2

    add edi, 0x1000

    mov dword[edi], 0x00004003 ; lv2[0] = lv1

    add edi, 0x1000   ; edi = lv1

    ; set up the lv1 page table
    ; we make identity mapping in PT, we do this by using loop
    ; ecx is used as counter
    ;
    ; Lv1 tbl size should be less then 4KB, and each entry is 8B
    ; Therefore we can have at most 512 entries in one tbl
    mov ebx, 0x00000003 ; prot
    mov ecx, 512        ; 512 entries

    add_pte_to_lv1:
        mov dword[edi], ebx
        add ebx, 0x1000 ; 4KB * 512 = 2MB
        add edi, 8

        loop add_pte_to_lv1

    ; enable PAE paging
    ; PAE paging is a modern way of paging, by dividing 32 bit address into 4 parts
    ; 32 = 2 + 9 + 9 + 12
    ; 2    : first 2 bits to index in lv4
    ; 9, 9 : to index in lv3 and lv2
    ; 12   : index within lv1 page(actual page)
    mov eax, cr4
    or eax, 1 << 5
    mov cr4, eax

    popad
    ret
