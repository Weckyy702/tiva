ENTRY(reset_handler)

__stack_top = 0x20000000 + 0x8000;

MEMORY {
  ROM(rx): org = 0x0,          len = 0x40000
  RAM(rwx): org = 0x20000000, len = 0x8000
}

SECTIONS {
  .vector : {
    KEEP(*(.vector))
  } >ROM

  .text : {
    . = ALIGN(4);
    *(.text)
    *(.text.*)

    . = ALIGN(4);
    __etext = .;
  } >ROM

  /DISCARD/ : {

  }

}

