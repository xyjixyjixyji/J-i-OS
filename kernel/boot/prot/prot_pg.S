; initialize paging in protected mode

; 4 level pgtbl
;
; PML4T -> 0x1000 (Page Map Level 4 Table)
; PDPT  -> 0x2000 (Page Directory Pointer Table)
; PDT   -> 0x3000 (Page Directory Table)
; PT    -> 0x4000 (Page table)

[bits 32]

init_pgtbl_prot:
    pushad
