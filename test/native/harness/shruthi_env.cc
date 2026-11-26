#include "shruthi_env.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <avr/io.h>

#include "avrlib/base.h"
#include "avrlib/time.h"
#include "midi/midi.h"
#include "shruthi/audio_out.h"
#include "shruthi/diagnostics.h"
#include "shruthi/midi_dispatcher.h"
#include "shruthi/parameter.h"
#include "shruthi/part.h"
#include "shruthi/storage.h"

using namespace shruthi;

// Globals and functions defined in shruthi/shruthi.cc.
extern midi::MidiStreamParser<MidiDispatcher> midi_parser;
void FillAudioBuffer();

extern uint8_t native_eeprom[E2END + 1];
uint8_t native_external_eeprom[65536];

namespace shruthi {
// diagnostics.cc is not linked (it paints RAM up to RAMEND).
uint8_t Diagnostics::glitches_;
uint8_t Diagnostics::FreeStack() { return 200; }
}

namespace native_env {

static std::vector<uint8_t> midi_out;
static std::vector<uint8_t> uart1_out;
static unsigned long busy_waits_without_progress = 0;

static bool DrainMidiOut() {
  bool progress = false;
  while (midi_dispatcher.readable()) {
    midi_out.push_back(midi_dispatcher.ImmediateRead());
    progress = true;
  }
  return progress;
}

void Boot() {
  memset((void*)native_sfr, 0, sizeof(native_sfr));
  SREG = 0x80;
  UCSR0A |= _BV(UDRE0);
  UCSR1A |= _BV(UDRE1);
  memset(native_eeprom, 0xff, sizeof(native_eeprom));
  memset(native_external_eeprom, 0xff, sizeof(native_external_eeprom));
  DrainMidiOut();
  midi_out.clear();
  uart1_out.clear();
  busy_waits_without_progress = 0;
  // Leftover samples from a previous test.
  while (!audio_out.writable_block()) audio_out.EmitSample();
  // shruthi.cc Init(), minus the LCD/UI and the timers. The UI would call
  // editor.Init(), which builds the parameter lookup tables.
  parameter_manager.Init();
  Storage::Init();
  part.Init();
  // RAM is zero at power-on; here the voice keeps the previous test's
  // envelope levels (a new attack starts from the current level).
  part.mutable_voice()->Kill();
  Render(4);
  midi_out.clear();
}

void MidiIn(const uint8_t* data, size_t size) {
  for (size_t i = 0; i < size; ++i) {
    midi_parser.PushByte(data[i]);
  }
}

void MidiIn(const std::vector<uint8_t>& data) {
  if (!data.empty()) MidiIn(&data[0], data.size());
}

void MidiIn3(uint8_t status, uint8_t a, uint8_t b) {
  uint8_t m[3] = { status, a, b };
  MidiIn(m, 3);
}

void Nrpn(uint8_t channel, uint16_t address, uint16_t value) {
  uint8_t cc = 0xb0 | (channel & 0x0f);
  MidiIn3(cc, 99, (address >> 7) & 0x7f);
  MidiIn3(cc, 98, address & 0x7f);
  MidiIn3(cc, 6, (value >> 7) & 0x7f);
  MidiIn3(cc, 38, value & 0x7f);
}

void Render(int blocks, std::vector<uint8_t>* audio, std::vector<Cv>* cv) {
  for (int b = 0; b < blocks; ++b) {
    FillAudioBuffer();
    if (cv) {
      Cv c;
      c.cutoff = OCR2B;
      c.resonance = OCR2A;
      c.vca = OCR1AL;
      c.cv_1 = OCR0A;
      c.cv_2 = OCR0B;
      cv->push_back(c);
    }
    // The 40 kHz ISR plays the block.
    for (uint8_t i = 0; i < kAudioBlockSize; ++i) {
      audio_out.EmitSample();
      if (audio) audio->push_back(static_cast<uint8_t>(OCR1BL));
    }
    DrainMidiOut();
  }
}

const std::vector<uint8_t>& MidiOut() {
  DrainMidiOut();
  return midi_out;
}

void ClearMidiOut() {
  DrainMidiOut();
  midi_out.clear();
}

const std::vector<uint8_t>& Uart1Out() { return uart1_out; }

void LogUart(volatile uint8_t* data_register, uint8_t value) {
  if (data_register == &UDR0) {
    midi_out.push_back(value);
  } else if (data_register == &UDR1) {
    uart1_out.push_back(value);
  }
}

int PeakToPeak(const std::vector<uint8_t>& audio, size_t from, size_t size) {
  int lo = 255, hi = 0;
  for (size_t i = from; i < from + size && i < audio.size(); ++i) {
    if (audio[i] < lo) lo = audio[i];
    if (audio[i] > hi) hi = audio[i];
  }
  return hi >= lo ? hi - lo : 0;
}

static const uint8_t kHeader[] = { 0xf0, 0x00, 0x21, 0x02, 0x00, 0x02 };

std::vector<uint8_t> SysEx(uint8_t command, uint8_t argument,
                           const uint8_t* data, size_t size) {
  std::vector<uint8_t> m(kHeader, kHeader + sizeof(kHeader));
  m.push_back(command);
  m.push_back(argument);
  uint8_t checksum = 0;
  for (size_t i = 0; i < size; ++i) {
    m.push_back(data[i] >> 4);
    m.push_back(data[i] & 0x0f);
    checksum += data[i];
  }
  m.push_back(checksum >> 4);
  m.push_back(checksum & 0x0f);
  m.push_back(0xf7);
  return m;
}

std::vector<uint8_t> SysEx(uint8_t command, uint8_t argument) {
  return SysEx(command, argument, 0, 0);
}

std::vector<SysExReply> ParseSysEx(const std::vector<uint8_t>& bytes) {
  std::vector<SysExReply> replies;
  size_t i = 0;
  while (i < bytes.size()) {
    if (bytes[i] != 0xf0) {
      ++i;
      continue;
    }
    size_t end = i;
    while (end < bytes.size() && bytes[end] != 0xf7) ++end;
    if (end == bytes.size()) break;
    // Header (6) + command + argument + checksum (2) + F7.
    if (end - i >= 10 &&
        memcmp(&bytes[i], kHeader, sizeof(kHeader)) == 0 &&
        ((end - i) - 10) % 2 == 0) {
      SysExReply r;
      r.command = bytes[i + 6];
      r.argument = bytes[i + 7];
      uint8_t checksum = 0;
      for (size_t k = i + 8; k + 2 < end; k += 2) {
        uint8_t v = (bytes[k] << 4) | (bytes[k + 1] & 0x0f);
        r.data.push_back(v);
        checksum += v;
      }
      r.checksum_ok =
          checksum == ((bytes[end - 2] << 4) | (bytes[end - 1] & 0x0f));
      replies.push_back(r);
    }
    i = end + 1;
  }
  return replies;
}

bool Request(const std::vector<uint8_t>& request, uint8_t reply_command,
             SysExReply* reply) {
  ClearMidiOut();
  MidiIn(request);
  std::vector<SysExReply> replies = ParseSysEx(MidiOut());
  for (size_t i = 0; i < replies.size(); ++i) {
    if (replies[i].command == reply_command) {
      *reply = replies[i];
      return true;
    }
  }
  return false;
}

uint8_t SysExState() { return Storage::sysex_rx_state(); }

}  // namespace native_env

extern "C" void native_uart_tx(volatile uint8_t* data_register,
                               uint8_t value) {
  native_env::LogUart(data_register, value);
}

// Firmware is waiting for an interrupt to drain a buffer: be that interrupt.
extern "C" void native_busy_wait(void) {
  using namespace native_env;
  if (DrainMidiOut()) {
    busy_waits_without_progress = 0;
    return;
  }
  if (!audio_out.writable()) {
    audio_out.EmitSample();
    busy_waits_without_progress = 0;
    return;
  }
  // Delay() waits for the Timer 0 ISR to advance milliseconds().
  avrlib::TickSystemClock();
  if (++busy_waits_without_progress > 100000) {
    fprintf(stderr, "native_busy_wait: firmware is stuck in a busy-wait loop "
            "that no simulated interrupt can release\n");
    abort();
  }
}
