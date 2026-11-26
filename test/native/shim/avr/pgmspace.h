// Host shim for <avr/pgmspace.h> (native test harness only).
//
// Program memory is ordinary memory on the host. pgm_read_word is
// type-generic so tables of pointers (the resource string/LUT tables) keep
// their full host pointer width.

#ifndef NATIVE_SHIM_AVR_PGMSPACE_H_
#define NATIVE_SHIM_AVR_PGMSPACE_H_

#include <inttypes.h>
#include <string.h>
#include <avr/io.h>  // as in avr-libc

#define PROGMEM
#define PSTR(s) (s)
#define PGM_P const char*

typedef char prog_char;
typedef uint8_t prog_uchar;
typedef int8_t prog_int8_t;
typedef uint8_t prog_uint8_t;
typedef int16_t prog_int16_t;
typedef uint16_t prog_uint16_t;
typedef int32_t prog_int32_t;
typedef uint32_t prog_uint32_t;

#define pgm_read_byte(addr) (*reinterpret_cast<const uint8_t*>(addr))
#define pgm_read_byte_near(addr) pgm_read_byte(addr)

namespace native_shim {

template<typename T>
inline T pgm_read_word_impl(const T* p) { return *p; }

inline uint16_t pgm_read_word_bytes(const void* p) {
  const uint8_t* b = static_cast<const uint8_t*>(p);
  return static_cast<uint16_t>(b[0] | (b[1] << 8));
}
inline uint16_t pgm_read_word_impl(const void* p) {
  return pgm_read_word_bytes(p);
}
inline uint16_t pgm_read_word_impl(const char* p) {
  return pgm_read_word_bytes(p);
}
inline uint16_t pgm_read_word_impl(const uint8_t* p) {
  return pgm_read_word_bytes(p);
}
inline uint16_t pgm_read_word_impl(const int8_t* p) {
  return pgm_read_word_bytes(p);
}

}  // namespace native_shim

#define pgm_read_word(addr) (native_shim::pgm_read_word_impl(addr))
#define pgm_read_word_near(addr) pgm_read_word(addr)
#define pgm_read_dword(addr) (*reinterpret_cast<const uint32_t*>(addr))

#define memcpy_P memcpy
#define memcmp_P memcmp
#define strcpy_P strcpy
#define strncpy_P strncpy
#define strcat_P strcat
#define strlen_P strlen
#define strcmp_P strcmp
#define strncmp_P strncmp

#endif  // NATIVE_SHIM_AVR_PGMSPACE_H_
