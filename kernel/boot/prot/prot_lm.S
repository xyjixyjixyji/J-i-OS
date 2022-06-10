;
; prot_lm.S
;
; detect if we can enter long mode
;

[bits 32]

detect_lm_prot:
    pushad

    ; 1. Check for CPUID (built-in cmd)
    ; 2. Check for CPUID extended functions
    ; 3. Check for long mode support

    ; Check CPUID
    ; Flag bit 21 tells us whether CPUID is supported
    ; 
    ; If flag bit 21 can be changed, CPUID can be supported
    ; If bit 21 is unchanged after we flipped it, not supported 

    pushfd
    pop eax         ; flag to eax
    mov ecx, eax    ; save to ecx

    xor eax, 1 << 21

    push eax
    popfd           ; if CPUID is supported, flag should be flipped

    pushfd
    pop eax

    push ecx        ; restore flag
    popfd

    cmp ecx, eax
    je cpuid_not_supported

    ; Check CPUID extended functions
    ;
    ; CPUID function takes argument from eax, return value to eax
    ; set eax, call it and see the value is bigger than original
    mov eax, 0x80000000
    cpuid ; return the highest calling parameters (from wiki)
    cmp eax, 0x80000001 ; should be at least 0x80000001
    jb cpuid_no_ext

    ; Check for long mode
    ;
    ; If long mode is supported, then cpuid will set the 29th bit of 
    ; edx, argument should be 0x80000001
    mov eax, 0x80000001
    cpuid
    test edx, 1 << 29
    jz lm_not_supported

    popad
    ret

cpuid_not_supported:
    call clear_vga_pm
    mov ebx, ERR_CPUID_NOTSUPPORTED
    call print_string_pm
    jmp $ ; panic

cpuid_no_ext:
    call clear_vga_pm
    mov ebx, ERR_CPUID_NO_EXT
    call print_string_pm
    jmp $

lm_not_supported:
    call clear_vga_pm
    mov ebx, ERR_LM_NOTFOUND
    call print_string_pm
    jmp $

ERR_CPUID_NOTSUPPORTED db "CPUID not supported", 0
ERR_CPUID_NO_EXT db "CPUID without extended functions", 0
ERR_LM_NOTFOUND db "Long mode not supported", 0