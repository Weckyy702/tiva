ENTRY(_start)

MEMORY {
  ROM(rx): ORIGIN = 0x0,      LENGTH = 0x1000
}

SECTIONS {
  .text : {
    *(.text)
    *(.text.*)
  } >ROM
}
