ENTRY( _start )

SECTIONS
{
    . = 0x8200;

    .text : {
        *(.text.prologue); /* this is for setting everything after _entry */
        *(.text .text.*)
        . = ALIGN(0x1000);
        PROVIDE(end_of_text = .);
    }

    .rodata : {
        . = ALIGN(16);
        *(.srodata .srodata.*)
        . = ALIGN(16);
        *(.rodata .rodata.*)
    }

    .data : {
        . = ALIGN(16);
        *(.sdata .sdata.*)
        . = ALIGN(16);
        *(.data .data.*)
    }

    .bss : {
        . = ALIGN(16);
        *(.sbss .sbss.*)
        . = ALIGN(16);
        *(.bss .bss.*)
    }

    PROVIDE(end = .);
}
