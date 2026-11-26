// Host shim for <avr/interrupt.h>.
#ifndef NATIVE_SHIM_AVR_INTERRUPT_H_
#define NATIVE_SHIM_AVR_INTERRUPT_H_
#include <avr/io.h>
#define cli() do { SREG &= 0x7f; } while (0)
#define sei() do { SREG |= 0x80; } while (0)
#define ISR(vector, ...) extern "C" void vector(void); void vector(void)
#define SIGNAL(vector) ISR(vector)
#define ISR_NOBLOCK
#define ISR_NAKED
#endif
