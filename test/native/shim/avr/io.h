// Host shim for <avr/io.h> (native test harness only).
//
// Every special function register lives in a plain byte array
// (native_sfr), so driver code compiles and runs on the host: writes go
// nowhere, reads return whatever a test put there. Register names and bit
// numbers come from avr-libc 1.6.8's own headers (test/native/shim/avr/libc,
// BSD licence), selected by the MCU macro the makefile passes:
// __AVR_ATmega644P__ for the Shruthi. Without an MCU macro only SREG and
// E2END are defined, which is enough for pure logic modules.
#ifndef _AVR_IO_H_
#define _AVR_IO_H_
#include <inttypes.h>

extern volatile uint8_t native_sfr[0x200];
extern volatile uint8_t native_sreg;

#define __SFR_OFFSET 0x20
#define _MMIO_BYTE(a) (native_sfr[(a)])
#define _MMIO_WORD(a) (*(volatile uint16_t*)(native_sfr + (a)))
#define _MMIO_DWORD(a) (*(volatile uint32_t*)(native_sfr + (a)))
#define _SFR_MEM8(a) _MMIO_BYTE(a)
#define _SFR_MEM16(a) _MMIO_WORD(a)
#define _SFR_MEM32(a) _MMIO_DWORD(a)
#define _SFR_IO8(a) _MMIO_BYTE((a) + __SFR_OFFSET)
#define _SFR_IO16(a) _MMIO_WORD((a) + __SFR_OFFSET)
#define _SFR_MEM_ADDR(sfr) \
  ((uint16_t)((const volatile uint8_t*)&(sfr) - native_sfr))
#define _SFR_IO_ADDR(sfr) (_SFR_MEM_ADDR(sfr) - __SFR_OFFSET)
#define _SFR_ADDR(sfr) _SFR_MEM_ADDR(sfr)
#define _SFR_BYTE(sfr) _MMIO_BYTE(_SFR_ADDR(sfr))
#define _SFR_WORD(sfr) _MMIO_WORD(_SFR_ADDR(sfr))
#define _BV(bit) (1 << (bit))
#define bit_is_set(sfr, bit) (_SFR_BYTE(sfr) & _BV(bit))
#define bit_is_clear(sfr, bit) (!(_SFR_BYTE(sfr) & _BV(bit)))
#define loop_until_bit_is_set(sfr, bit) do { } while (0)
#define loop_until_bit_is_clear(sfr, bit) do { } while (0)

#define SREG native_sreg
#define _VECTOR(N) __vector_ ## N

#if defined(__AVR_ATmega644P__)
#include "libc/iom644p.h"
#include "libc/portpins.h"
#elif defined(__AVR_ATmega328P__)
#include "libc/iom328p.h"
#include "libc/portpins.h"
#endif


#ifndef E2END
#define E2END 0x0FFF
#endif
#ifndef RAMEND
#define RAMEND 0x10FF
#endif

#endif  // _AVR_IO_H_
