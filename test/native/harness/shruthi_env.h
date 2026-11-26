// Headless Shruthi: the real SHOOZ firmware linked natively. MIDI in/out are
// byte streams; audio and the filter-board CVs are read from the PWM
// compare registers, exactly as the hardware would output them.
//
//   native_env::Boot();                    // power-on, blank EEPROMs
//   native_env::MidiIn3(0x90, 60, 100);    // feed MIDI in
//   native_env::Render(100, &audio, &cv);  // 100 blocks of audio + CVs
#ifndef NATIVE_HARNESS_SHRUTHI_ENV_H_
#define NATIVE_HARNESS_SHRUTHI_ENV_H_

#include <inttypes.h>
#include <stddef.h>
#include <vector>

namespace native_env {

// One set of control outputs, sampled after each audio block.
struct Cv {
  uint8_t cutoff;     // VCF cutoff PWM (pin 14, OCR2B)
  uint8_t resonance;  // VCF resonance PWM (pin 15, OCR2A)
  uint8_t vca;        // VCA PWM (pin 13, OCR1A)
  uint8_t cv_1;       // CV 1 PWM (pin 3, OCR0A), filter-board specific
  uint8_t cv_2;       // CV 2 PWM (pin 4, OCR0B), filter-board specific
};

// Clears registers, both EEPROMs (0xff, like new chips) and the capture
// buffers, then runs the firmware's boot sequence minus the LCD.
void Boot();

void MidiIn(const uint8_t* data, size_t size);
void MidiIn(const std::vector<uint8_t>& data);
void MidiIn3(uint8_t status, uint8_t a, uint8_t b);
// NRPN write: CC 99/98, then 6/38 (data entry MSB/LSB).
void Nrpn(uint8_t channel, uint16_t address, uint16_t value);

// Renders |blocks| audio blocks (FillAudioBuffer + the sample ISR).
// Appends the 8-bit audio samples and the CVs after each block.
void Render(int blocks, std::vector<uint8_t>* audio = 0,
            std::vector<Cv>* cv = 0);

// Bytes the firmware sent to MIDI out since the last ClearMidiOut(), from
// the MIDI out buffer and from direct UART writes (SysEx dumps).
const std::vector<uint8_t>& MidiOut();
void ClearMidiOut();

// Bytes sent on UART 1 (the DSP filter board's control stream).
const std::vector<uint8_t>& Uart1Out();

int PeakToPeak(const std::vector<uint8_t>& audio, size_t from, size_t size);

// ---- SysEx (Mutable Instruments framing: F0 00 21 02 00 02 cmd arg
// <nibbles> <checksum nibbles> F7) ----

// Builds a Shruthi SysEx message. Each payload byte is sent as two nibbles,
// high first; the checksum is the 8-bit sum of the payload bytes.
std::vector<uint8_t> SysEx(uint8_t command, uint8_t argument,
                           const uint8_t* data, size_t size);
std::vector<uint8_t> SysEx(uint8_t command, uint8_t argument = 0);

struct SysExReply {
  uint8_t command;
  uint8_t argument;
  std::vector<uint8_t> data;  // Decoded payload.
  bool checksum_ok;
};

// Parses every Shruthi SysEx message in |bytes| (other bytes are skipped).
std::vector<SysExReply> ParseSysEx(const std::vector<uint8_t>& bytes);

// Sends |request| and returns the first SysEx reply with |reply_command|.
// Fails (returns false) if there is none.
bool Request(const std::vector<uint8_t>& request, uint8_t reply_command,
             SysExReply* reply);

// State of the firmware SysEx receiver after the last message.
uint8_t SysExState();

}  // namespace native_env

#endif  // NATIVE_HARNESS_SHRUTHI_ENV_H_
