ENTRY(app_main)

SECTIONS
{
    . = 0x30000;
    .text : {
          *(.text)
    }
}
