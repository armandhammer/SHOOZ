// Force-included into every native translation unit (see test/native/makefile).
//
// Firmware busy-waits on buffers that interrupts drain on the real hardware.
// The makefile generates copies of those headers in which each wait loop
// calls AVRLIB_BUSY_WAIT(); the harness uses it to run the simulated
// interrupt work (MIDI out drain, audio samples, the millisecond clock) and
// to fail fast on a real deadlock. native_uart_tx() sees every byte written
// to a UART data register.
#ifndef NATIVE_HARNESS_NATIVE_HOOKS_H_
#define NATIVE_HARNESS_NATIVE_HOOKS_H_
#include <inttypes.h>
#ifdef __cplusplus
extern "C" {
#endif
void native_busy_wait(void);
void native_uart_tx(volatile uint8_t* data_register, uint8_t value);
#ifdef __cplusplus
}
#endif
#define AVRLIB_BUSY_WAIT() native_busy_wait()
#endif
