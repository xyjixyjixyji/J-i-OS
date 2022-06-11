;
; From protected mode, to long mode
;

[bits 32]

; 1. Enable long mode
;       setting 8th bit of CORRECT register from
;       the model-specific registerS
;       To select, we put argument in ecx
;
; 2. Enable paging - set the 31th bit of cr0
;
; 3. Load 64b gdt to leave compatability mode
;
; 4. Clear pipeline - long jump

switch_to_lm:
    ; switch to lm
    mov ecx, 0xC0000080

    ; Reads the contents of a 64-bit model specific register
    ; (MSR) specified in the ECX register into registers
    ; EDX:EAX.
    rdmsr
    
    or eax, 1 << 8
    wrmsr

    ; enable paging
    mov eax, cr0
    or eax, 1 << 31
    mov cr0, eax

    ; leave compatability mode
    lgdt [gdt_64_descriptor]

    ; clear pipeline
    jmp CODE_SEG_64: init_lm

[bits 64]

init_lm:
    cli
    mov ax, DATA_SEG_64
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    jmp BEGIN_LONG_MODE