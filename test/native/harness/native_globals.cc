// Storage behind the avr-libc shims (registers, SREG, internal EEPROM),
// shared by the test runner and the tools.
#include <inttypes.h>
#include <avr/io.h>

volatile uint8_t native_sreg = 0x80;
volatile uint8_t native_sfr[0x200];
uint8_t native_eeprom[E2END + 1];
