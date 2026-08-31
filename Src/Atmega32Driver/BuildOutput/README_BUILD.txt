This folder contains a verified build of the complete project, produced
with avr-gcc 7.3.0 targeting -mmcu=atmega32, exactly as EmbeddedBuilder's
avr8-gnu-toolchain will build it.

smarthome.elf - full debug binary (symbols included)
smarthome.hex - Intel HEX file, ready to load directly into SimulIDE

Build result: 0 errors, 0 real warnings.
Flash usage: 8618 / 32768 bytes (26%)
SRAM usage: 490 / 2048 bytes (24%)

To rebuild yourself in EmbeddedBuilder: import this whole folder as the
project source tree, main.c is the entry point, and it should build
without any changes needed.
