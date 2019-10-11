/*******************************************************************************
 * GCC linker script for STM32F100.
*******************************************************************************/

OUTPUT_FORMAT("elf32-littlearm", "elf32-bigarm", "elf32-littlearm")
OUTPUT_ARCH(arm)
ENTRY(Reset_Handler) /* Entry point. */

MEMORY {
    ROM (rx)  : ORIGIN = 0x08000000, LENGTH = 128K
    RAM (rwx) : ORIGIN = 0x20000000, LENGTH = 8K
}

/* Stack size used by the application. */
STACK_SIZE = 512;

/* Heap size used by the application. */
HEAP_SIZE = 0;

SECTIONS {

    .isr_vector : { /* Vector table goes first into ROM. */
        KEEP(*(.isr_vector)) /* Vector table. */
        . = ALIGN(4);
    } >ROM

    .text : { /* Code and constants. */
        . = ALIGN(4);
        *(.text)    /* .text  sections (code). */
        *(.text*)   /* .text* sections (code). */
        *(.rodata)  /* .rodata  sections (constants, strings, etc.). */
        *(.rodata*) /* .rodata* sections (constants, strings, etc.). */

        KEEP (*(.init))
        KEEP (*(.fini))

        . = ALIGN(4);
    } >ROM

    .preinit_array : {
        PROVIDE_HIDDEN (__preinit_array_start = .);
        KEEP (*(.preinit_array*))
        PROVIDE_HIDDEN (__preinit_array_end = .);
    } >ROM

    .init_array : {
        PROVIDE_HIDDEN (__init_array_start = .);
        KEEP (*(SORT(.init_array.*)))
        KEEP (*(.init_array*))
        PROVIDE_HIDDEN (__init_array_end = .);
    } >ROM

    .fini_array : {
        PROVIDE_HIDDEN (__fini_array_start = .);
        KEEP (*(.fini_array*))
        KEEP (*(SORT(.fini_array.*)))
        PROVIDE_HIDDEN (__fini_array_end = .);
    } >ROM

    _etext = .; /* Global sysmbols at end of code. */

    .stack : {
        __stack_start__ = .;
        . = . + STACK_SIZE;
        . = ALIGN(4);
        __stack_end__ = .;
    } >RAM

    .data : AT (_etext) {
        __data_load = LOADADDR (.data);
        __data_start = .;
        *(.data)           /* .data  sections. */
        *(.data*)          /* .data* sections. */
        . = ALIGN(4);
        __data_end__ = .;
        _edata = __data_end__;
    } >RAM

    .bss : {
        __bss_start__ = .;
        *(.bss)            /* .bss  sections. */
        *(.bss*)           /* .bss* sections. */
        *(COMMON)
        . = ALIGN(4);
        _ebss = .;         /* Define a global symbol at bss end. */
        __bss_end__ = .;
    } >RAM

    PROVIDE (end     = _ebss);
    PROVIDE (_end    = _ebss);
    PROVIDE (__end__ = _ebss);

    .heap : {
        __heap_start__ = .;
        . = . + HEAP_SIZE;
        . = ALIGN(4);
        __heap_end__ = .;
    } >RAM

    /DISCARD/ : {       /* Remove information from the standard libraries. */
        libc.a (*)
        libm.a (*)
        libgcc.a (*)
    }

}
