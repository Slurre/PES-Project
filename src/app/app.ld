ENTRY(app_main)

MEMORY
{
    /* just a big address to trigger ld
        inserting veneer (absolute) function calls to base firmware */
    FLASH (rx) : ORIGIN = 0x10000000, LENGTH = 0x78000
    RAM (rwx) :  ORIGIN = 0x00000000, LENGTH = 64K
    FILE (rwx) : ORIGIN = 0x00000000, LENGTH = 1K
}

SECTIONS
{
    .header : {
        LONG(SIZEOF(.got))
        LONG(SIZEOF(.data))
        LONG(SIZEOF(.bss))
        LONG(SIZEOF(.text))
    } > FLASH AT> FILE

    .got : {
        *(.got)
    } > FLASH AT> FILE

    .data : {
        . = ALIGN(4);
        *(.data*)
        . = ALIGN(4);
    } > RAM AT> FILE

    .bss : {
        . = ALIGN(4);
        *(.bss*)
        . = ALIGN(4);
    } > RAM AT> FILE

    .text : {
        /* app_main has to be located at the beginning */
        *(.text.start)
        *(.text*)
    } > FLASH AT> FILE

    .discard : {
    /*/DISCARD/ : {*/
        *(.got.plt)
        *(.init)
        *(.fini)
    } > FLASH AT> FILE

    /*.bss :
    {
        . = ALIGN(4);
        __bss_start__ = .;
        *(.bss*)
        . = ALIGN(4);
        __bss_end__ = .;
    } > RAM

    .data :
    {
        . = ALIGN(4);
        __data_start__ = .;
        *(.data*)
        . = ALIGN(4);
        __data_end__ = .;

    } > RAM*/
}
