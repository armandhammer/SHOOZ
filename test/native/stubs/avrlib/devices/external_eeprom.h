// Native stub for avrlib/devices/external_eeprom.h: the Shruthi's I2C
// patch EEPROM (24LC512) as a 64 KB array. Same interface as the subset of
// the real class the firmware uses.
#ifndef AVRLIB_DEVICES_EXTERNAL_EEPROM_H_
#define AVRLIB_DEVICES_EXTERNAL_EEPROM_H_

#include <string.h>

#include "avrlib/base.h"

extern uint8_t native_external_eeprom[65536];

namespace avrlib {

template<uint16_t eeprom_size = 8192,
         typename Bus = void,
         uint8_t base_address = 0,
         bool auto_banking = false,
         uint8_t block_size = 32>
class ExternalEeprom {
 public:
  ExternalEeprom() { }
  static void Init() { }
  static void Done() { }
  static void set_bank(uint8_t bank) { }

  static uint16_t Write(uint16_t address, const uint8_t* data, uint16_t size) {
    for (uint16_t i = 0; i < size; ++i) {
      native_external_eeprom[static_cast<uint16_t>(address + i)] = data[i];
    }
    return size;
  }

  static uint16_t Read(uint16_t address, uint16_t size, uint8_t* data) {
    for (uint16_t i = 0; i < size; ++i) {
      data[i] = native_external_eeprom[static_cast<uint16_t>(address + i)];
    }
    return size;
  }

  static uint8_t Read(uint16_t address) {
    return native_external_eeprom[address];
  }
};

}  // namespace avrlib

#endif  // AVRLIB_DEVICES_EXTERNAL_EEPROM_H_
