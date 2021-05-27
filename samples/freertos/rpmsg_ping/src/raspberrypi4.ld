ENTRY(_boot)

CODE_BASE = 0x20000000;
DATA_BASE = 0x20200000;
STACK_TOP = 0x20600000;
OAMP_SHM  = 0x20600000;
PT_BASE   = 0x20800000;
 
SECTIONS
{
    /* Starts at 0x20000000 (assuming ends at 0x207FFFFF, 8MB). */
    . = CODE_BASE;
    __start = .;
    __text_start = .;
    .text :
    {
        KEEP(*(.vectors))
        KEEP(*(.text.boot))
        *(.text)
    }
    __text_end = .;
 
    . = ALIGN(4096); /* Align to 4K */
    . = DATA_BASE;
    __data_start = .;
    .data :
    {
        *(.data)
    }
    . = ALIGN(4096); /* Align to 4K */
    __data_end = .;
 
    __bss_start = .;
    __bss_start__ = .;
    .bss :
    {
        bss = .;
        *(.bss)
    }
    . = ALIGN(4096); /* Align to 4K */
    __bss_end = .;
    __bss_end__ = .;
    end = .;
    __end = .;
    __end__ = .;

    . = STACK_TOP ; /* Stack memory */
    stack_top = .;

    . = ALIGN(4096); /* Align to 4K */
    . = OAMP_SHM ; /* Shared memory for OpenAMP */
    .oamp :
    {
        *(.resource_table)
        *(.oamp)
    }

    . = ALIGN(4096); /* Align to 4K */
    . = PT_BASE ; /* Page table */
    .pt :
    {
        *(.pt)
    }
}
__bss_size = (__bss_end - __bss_start)>>3;
