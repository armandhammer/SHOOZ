// Host shim for <avr/eeprom.h>: a 4 KB in-memory EEPROM.
#ifndef NATIVE_SHIM_AVR_EEPROM_H_
#define NATIVE_SHIM_AVR_EEPROM_H_
#include <inttypes.h>
#include <string.h>
#include <avr/io.h>
extern uint8_t native_eeprom[E2END + 1];
#define EEMEM
static inline uint8_t eeprom_read_byte(const uint8_t* p) {
  return native_eeprom[reinterpret_cast<uintptr_t>(p) & E2END];
}
static inline void eeprom_write_byte(uint8_t* p, uint8_t v) {
  native_eeprom[reinterpret_cast<uintptr_t>(p) & E2END] = v;
}
static inline void eeprom_update_byte(uint8_t* p, uint8_t v) {
  eeprom_write_byte(p, v);
}
static inline uint16_t eeprom_read_word(const uint16_t* p) {
  uintptr_t a = reinterpret_cast<uintptr_t>(p);
  return native_eeprom[a & E2END] | (native_eeprom[(a + 1) & E2END] << 8);
}
static inline void eeprom_write_word(uint16_t* p, uint16_t v) {
  uintptr_t a = reinterpret_cast<uintptr_t>(p);
  native_eeprom[a & E2END] = v & 0xff;
  native_eeprom[(a + 1) & E2END] = v >> 8;
}
static inline void eeprom_read_block(void* d, const void* s, size_t n) {
  uintptr_t a = reinterpret_cast<uintptr_t>(s);
  for (size_t i = 0; i < n; ++i) {
    static_cast<uint8_t*>(d)[i] = native_eeprom[(a + i) & E2END];
  }
}
static inline void eeprom_write_block(const void* s, void* d, size_t n) {
  uintptr_t a = reinterpret_cast<uintptr_t>(d);
  for (size_t i = 0; i < n; ++i) {
    native_eeprom[(a + i) & E2END] = static_cast<const uint8_t*>(s)[i];
  }
}
#define eeprom_update_block eeprom_write_block
#define eeprom_busy_wait() do {} while (0)
#endif
