// Random MIDI streams into the whole firmware. Under SANITIZE=1 any
// out-of-bounds access fails the run; without it, a wild jump or a stuck
// busy-wait aborts.
#include "test.h"
#include "shruthi_env.h"

#include "shruthi/part.h"
#include "shruthi/system_settings.h"

using namespace shruthi;

namespace {

uint32_t rng = 0x12345678;
uint8_t Rand() {
  rng = rng * 1664525 + 1013904223;
  return rng >> 24;
}

}  // namespace

TEST(FuzzRandomChannelMessages) {
  native_env::Boot();
  for (int n = 0; n < 20000; ++n) {
    uint8_t status = 0x80 | (Rand() & 0x7f);
    if (status >= 0xf0) status = 0x90;  // SysEx/realtime: other tests
    native_env::MidiIn3(status & 0xf0, Rand() & 0x7f, Rand() & 0x7f);
    if ((n & 15) == 0) native_env::Render(1);
    // Keep listening on channel 1 / omni.
    if (part.system_settings().midi_channel > 1) {
      part.mutable_system_settings()->midi_channel = 0;
    }
  }
  native_env::MidiIn3(0xb0, 120, 0);  // all sound off
  native_env::Render(10);
}

TEST(FuzzRandomNrpnAndSysExPayloads) {
  native_env::Boot();
  for (int n = 0; n < 3000; ++n) {
    if (Rand() & 1) {
      native_env::Nrpn(0, Rand() | ((Rand() & 1) << 7), Rand());
    } else {
      // A well-formed Shruthi message (valid checksum) with random
      // content, for the transfer commands that carry data.
      static const uint8_t commands[] = { 0x01, 0x02, 0x04, 0x05, 0x06, 0x07 };
      static const uint8_t sizes[] = { 92, 32, 15, 2, 8, 0 };
      uint8_t k = Rand() % 6;
      uint8_t size = sizes[k] ? sizes[k] : sizeof(SequencerSettings);
      if (commands[k] == 0x04) size = sizeof(SystemSettings);
      std::vector<uint8_t> data(size);
      for (size_t i = 0; i < data.size(); ++i) data[i] = Rand();
      if (commands[k] == 0x01) {
        data[91] = (Rand() & 1) ? '%' : '&';
        for (int i = 8; i < 24; ++i) data[i] &= 0x7f;
      }
      if (commands[k] == 0x04) {
        data[PRM_SYS_MIDI_CHANNEL - PRM_SYS_OCTAVE] = 0;
        data[PRM_SYS_MIDI_OUT_MODE - PRM_SYS_OCTAVE] &= 3;
      }
      native_env::MidiIn(native_env::SysEx(commands[k], Rand() & 0x7f,
                                           &data[0], data.size()));
    }
    if (part.system_settings().midi_channel > 1) {
      part.mutable_system_settings()->midi_channel = 0;
    }
    if ((n & 7) == 0) {
      native_env::MidiIn3(0x90, 36 + (Rand() & 63), 100);
      native_env::Render(3);
    }
  }
  native_env::MidiIn3(0xb0, 120, 0);
  native_env::Render(10);
}

TEST(FuzzRandomBytes) {
  // Raw garbage, including stray status bytes, truncated SysEx and
  // realtime bytes in the middle of messages.
  native_env::Boot();
  for (int n = 0; n < 50000; ++n) {
    uint8_t b = Rand();
    // Avoid program changes and bulk/storage commands touching the EEPROM
    // at random: those are covered by the SysEx tests.
    if ((b & 0xf0) == 0xc0) b = 0xb0;
    native_env::MidiIn(&b, 1);
    if ((n & 63) == 0) native_env::Render(1);
    if (part.system_settings().midi_channel > 1) {
      part.mutable_system_settings()->midi_channel = 0;
    }
  }
  native_env::MidiIn3(0xb0, 120, 0);
  native_env::Render(10);
}
