ENTRY(app_main)

SECTIONS
{
    /* just a big address to trigger ld
       inserting veneer (absolute) function calls to base firmware */
    . = 0xffffffff;
    .text : {
        /* app_main has to be located at the beginning */
        *(.text.start)
        *(.text)
    }
}
