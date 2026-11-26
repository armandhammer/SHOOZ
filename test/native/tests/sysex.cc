// SysEx protocol: requests and replies, patch round trips (including the
// SHOOZ '&' curve marker), checksums, foreign/malformed messages, storage
// writes, and sanitizing of out-of-range data.
#include "test.h"
#include "shruthi_env.h"

#include <string.h>

#include "shruthi/diagnostics.h"
#include "shruthi/parameter.h"
#include "shruthi/part.h"
#include "shruthi/storage.h"
#include "shruthi/system_settings.h"

using namespace shruthi;
using native_env::SysEx;
using native_env::SysExReply;

extern uint8_t native_eeprom[];
extern uint8_t native_external_eeprom[65536];

namespace {

bool DumpPatch(std::vector<uint8_t>* data) {
  SysExReply r;
  if (!native_env::Request(SysEx(0x11), 0x01, &r)) return false;
  if (!r.checksum_ok || r.data.size() != 92) return false;
  *data = r.data;
  return true;
}

std::vector<uint8_t> InitPatchBytes() {
  native_env::Boot();
  std::vector<uint8_t> d;
  DumpPatch(&d);
  return d;
}

void SendPatch(const std::vector<uint8_t>& data) {
  native_env::MidiIn(SysEx(0x01, 0, &data[0], data.size()));
}

const uint8_t kIdentityRequest[] = { 0xf0, 0x7e, 0x7f, 0x06, 0x01, 0xf7 };
// Stock replayed the previous command when the byte that broke the header
// match was directly followed by F7: a minimal non-commercial message, and
// a message for another Mutable Instruments product (cut short).
const uint8_t kShortForeign[] = { 0xf0, 0x7d, 0xf7 };
const uint8_t kOtherProduct[] = { 0xf0, 0x00, 0x21, 0x02, 0x00, 0x04, 0xf7 };
const uint8_t kRolandMessage[] = {
  0xf0, 0x41, 0x10, 0x42, 0x12, 0x40, 0x00, 0x7f, 0x00, 0x41, 0xf7 };

}  // namespace

TEST(SysExVersionReply) {
  native_env::Boot();
  SysExReply r;
  CHECK(native_env::Request(SysEx(0x1c), 0x0c, &r));
  CHECK(r.checksum_ok);
  CHECK_EQ(r.data.size(), 8);
  CHECK_EQ(r.data[2], kShoozFamily);
  CHECK_EQ(r.data[3], kShoozVersion);
  CHECK_EQ(r.data[4], WAVEFORM_LAST);
  CHECK_EQ(r.data[5], kPatchLayoutVersion);
}

TEST(SysExNumBanksReply) {
  native_env::Boot();
  SysExReply r;
  CHECK(native_env::Request(SysEx(0x1b), 0x0b, &r));
  CHECK_EQ(r.argument, Storage::num_accessible_banks());
  CHECK_EQ(r.data.size(), 0);
}

TEST(SysExPatchDumpRoundTrip) {
  native_env::Boot();
  native_env::Nrpn(0, PRM_FILTER_CUTOFF, 77);
  native_env::Nrpn(0, PRM_OSC_SHAPE_2, 9);
  native_env::Nrpn(0, PRM_MOD_SOURCE + 3 * 5 + 2, 0xfb);  // row 6: -5
  std::vector<uint8_t> a;
  CHECK(DumpPatch(&a));
  CHECK_EQ(a[91], '%');
  CHECK_EQ(a[12], 77);
  native_env::Boot();
  CHECK(part.patch().filter_cutoff != 77);
  SendPatch(a);
  CHECK_EQ(native_env::SysExState(), RECEPTION_OK);
  CHECK_EQ(part.patch().filter_cutoff, 77);
  CHECK_EQ(part.patch().osc[1].shape, 9);
  CHECK_EQ(part.patch().modulation_matrix.modulation[5].amount, -5);
  std::vector<uint8_t> b;
  CHECK(DumpPatch(&b));
  CHECK(a == b);
}

TEST(SysExCurvesTravelWithShoozMarker) {
  native_env::Boot();
  native_env::Nrpn(0, PRM_ENV_CURVE_1, 3);
  native_env::Nrpn(0, PRM_ENV_CURVE_2, 6);
  std::vector<uint8_t> d;
  CHECK(DumpPatch(&d));
  CHECK_EQ(d[91], '&');
  CHECK_EQ((d[77] >> 2) & 7, 3);
  CHECK_EQ(d[77] >> 5, 6);
  CHECK_EQ(d[77] & 3, part.sequencer_settings().seq_mode);
  native_env::Boot();
  CHECK_EQ(part.mutable_env_curve()[0], 0);
  SendPatch(d);
  CHECK_EQ(part.mutable_env_curve()[0], 3);
  CHECK_EQ(part.mutable_env_curve()[1], 6);
  // The sequencer mode survives the shared byte.
  CHECK_EQ(part.sequencer_settings().seq_mode, d[77] & 3);
}

TEST(SysExStockCurvesStayStockFormat) {
  std::vector<uint8_t> d = InitPatchBytes();
  CHECK_EQ(d[91], '%');
  CHECK_EQ(d[77] & 0xfc, 0);
}

TEST(SysExStockPatchIgnoresSpareBits) {
  // A stock ('%') patch never carries curves, whatever the spare bits say.
  std::vector<uint8_t> d = InitPatchBytes();
  d[77] |= 0xfc;
  native_env::Nrpn(0, PRM_ENV_CURVE_1, 4);
  SendPatch(d);
  CHECK_EQ(native_env::SysExState(), RECEPTION_OK);
  CHECK_EQ(part.mutable_env_curve()[0], 0);
  CHECK_EQ(part.mutable_env_curve()[1], 0);
}

TEST(SysExRejectsBadChecksum) {
  std::vector<uint8_t> d = InitPatchBytes();
  d[12] = 5;
  std::vector<uint8_t> m = SysEx(0x01, 0, &d[0], d.size());
  m[m.size() - 2] ^= 1;
  uint8_t before = part.patch().filter_cutoff;
  native_env::MidiIn(m);
  CHECK_EQ(native_env::SysExState(), RECEPTION_ERROR);
  CHECK_EQ(part.patch().filter_cutoff, before);
}

TEST(SysExRejectsBadVersionAndName) {
  std::vector<uint8_t> d = InitPatchBytes();
  d[12] = 5;
  d[91] = 'Z';
  SendPatch(d);
  CHECK(part.patch().filter_cutoff != 5);
  d[91] = '%';
  d[10] = 0x80;  // patch bytes 8-23 must be 7-bit
  SendPatch(d);
  CHECK(part.patch().filter_cutoff != 5);
}

TEST(SysExRejectsTruncatedMessage) {
  std::vector<uint8_t> d = InitPatchBytes();
  d[12] = 5;
  std::vector<uint8_t> m = SysEx(0x01, 0, &d[0], d.size());
  m.erase(m.begin() + 40, m.begin() + 42);
  native_env::MidiIn(m);
  CHECK(part.patch().filter_cutoff != 5);
  CHECK(native_env::SysExState() != RECEPTION_OK);
}

TEST(SysExAcceptsOldManufacturerId) {
  std::vector<uint8_t> d = InitPatchBytes();
  d[12] = 5;
  std::vector<uint8_t> m = SysEx(0x01, 0, &d[0], d.size());
  m[2] = 0x20;
  m[3] = 0x77;
  native_env::MidiIn(m);
  CHECK_EQ(native_env::SysExState(), RECEPTION_OK);
  CHECK_EQ(part.patch().filter_cutoff, 5);
}

TEST(SysExIgnoresForeignMessages) {
  native_env::Boot();
  // The default MIDI out mode is soft thru, which would echo the input.
  part.mutable_system_settings()->midi_out_mode = MIDI_OUT_OFF;
  Patch before = part.patch();
  native_env::ClearMidiOut();
  native_env::MidiIn(kIdentityRequest, sizeof(kIdentityRequest));
  native_env::MidiIn(kRolandMessage, sizeof(kRolandMessage));
  CHECK(native_env::MidiOut().empty());
  CHECK(memcmp(&before, &part.patch(), sizeof(Patch)) == 0);
}

TEST(SysExForeignMessageDoesNotReplayRequest) {
  // A message for another device must not re-run the previous command.
  native_env::Boot();
  part.mutable_system_settings()->midi_out_mode = MIDI_OUT_OFF;
  SysExReply r;
  CHECK(native_env::Request(SysEx(0x11), 0x01, &r));
  native_env::ClearMidiOut();
  native_env::MidiIn(kIdentityRequest, sizeof(kIdentityRequest));
  native_env::MidiIn(kShortForeign, sizeof(kShortForeign));
  native_env::MidiIn(kOtherProduct, sizeof(kOtherProduct));
  CHECK_EQ(native_env::ParseSysEx(native_env::MidiOut()).size(), 0);
  // Same for an unknown Shruthi command.
  native_env::MidiIn(SysEx(0x1c));
  native_env::ClearMidiOut();
  native_env::MidiIn(SysEx(0x7f));
  CHECK_EQ(native_env::ParseSysEx(native_env::MidiOut()).size(), 0);
  CHECK(native_env::SysExState() != RECEPTION_OK);
}

TEST(SysExForeignMessageDoesNotReplayRandomize) {
  native_env::Boot();
  native_env::MidiIn(SysEx(0x31));  // randomize patch
  CHECK_EQ(native_env::SysExState(), RECEPTION_OK);
  Patch randomized = part.patch();
  native_env::MidiIn(kRolandMessage, sizeof(kRolandMessage));
  native_env::MidiIn(kShortForeign, sizeof(kShortForeign));
  CHECK(memcmp(&randomized, &part.patch(), 92) == 0);
}

TEST(SysExRandomizedPatchIsInRange) {
  native_env::Boot();
  for (int n = 0; n < 50; ++n) {
    native_env::MidiIn(SysEx(0x31));
    for (uint8_t o = 0; o < sizeof(Patch); ++o) {
      uint8_t id = parameter_manager.at_offset(o);
      if (id == 0xff || o == PRM_FILTER_CUTOFF_2 ||
          o == PRM_FILTER_RESONANCE_2 || o == PRM_FILTER_MODE_1 ||
          o == PRM_FILTER_MODE_2) continue;
      const Parameter& p0 = parameter_manager.parameter(id);
      Parameter p = p0;
      uint8_t v = part.GetParameter(o);
      CHECK_MSG(p.Clamp(v) == v, "offset %d = %d out of range", o, v);
    }
    native_env::Render(2);
  }
}

TEST(SysExNameTransferAndRequest) {
  native_env::Boot();
  const uint8_t name[8] = { 'S', 'H', 'O', 'O', 'Z', ' ', ' ', '1' };
  native_env::MidiIn(SysEx(0x06, 0, name, 8));
  CHECK(memcmp(part.patch().name, name, 8) == 0);
  SysExReply r;
  CHECK(native_env::Request(SysEx(0x16), 0x06, &r));
  CHECK_EQ(r.data.size(), 8);
  CHECK(memcmp(&r.data[0], name, 8) == 0);
}

TEST(SysExStepTransferAndRequest) {
  native_env::Boot();
  const uint8_t step[2] = { 0x80 | 64, 0x75 };
  native_env::MidiIn(SysEx(0x05, 3, step, 2));
  CHECK_EQ(part.sequencer_settings().steps[3].data_[0], step[0]);
  CHECK_EQ(part.sequencer_settings().steps[3].data_[1], step[1]);
  SysExReply r;
  // Argument 0x13: the step index is masked to 0-15.
  CHECK(native_env::Request(SysEx(0x15, 0x13), 0x05, &r));
  CHECK_EQ(r.argument, 3);
  CHECK_EQ(r.data.size(), 2);
  CHECK_EQ(r.data[0], step[0]);
}

TEST(SysExPatchWriteAndProgramChange) {
  native_env::Boot();
  uint16_t slots[] = { 0, 15, 16, 200, Storage::size<Patch>() - 1 };
  for (uint8_t k = 0; k < 5; ++k) {
    native_env::Nrpn(0, PRM_FILTER_CUTOFF, 10 + k);
    uint8_t slot[2] = { static_cast<uint8_t>(slots[k] >> 8),
                        static_cast<uint8_t>(slots[k] & 0xff) };
    native_env::MidiIn(SysEx(0x21, 0, slot, 2));
    CHECK_EQ(native_env::SysExState(), RECEPTION_OK);
  }
  for (uint8_t k = 0; k < 5; ++k) {
    native_env::MidiIn3(0xb0, 0, slots[k] >> 7);
    uint8_t program_change[2] = { 0xc0, static_cast<uint8_t>(slots[k] & 0x7f) };
    native_env::MidiIn(program_change, 2);
    CHECK_MSG(part.patch().filter_cutoff == 10 + k, "slot %d: cutoff %d",
              slots[k], part.patch().filter_cutoff);
  }
}

TEST(SysExPatchWriteRejectsMissingSlot) {
  // Slots past the installed EEPROM banks would wrap onto bank 0 of a
  // smaller chip.
  native_env::Boot();
  static uint8_t external[65536];
  static uint8_t internal[E2END + 1];
  memcpy(external, native_external_eeprom, sizeof(external));
  memcpy(internal, native_eeprom, sizeof(internal));
  uint16_t bad[] = { Storage::size<Patch>(), 0x7fff, 0xffff };
  for (uint8_t k = 0; k < 3; ++k) {
    uint8_t slot[2] = { static_cast<uint8_t>(bad[k] >> 8),
                        static_cast<uint8_t>(bad[k] & 0xff) };
    native_env::MidiIn(SysEx(0x21, 0, slot, 2));
    CHECK_EQ(native_env::SysExState(), RECEPTION_ERROR);
    native_env::MidiIn(SysEx(0x22, 0, slot, 2));
    CHECK_EQ(native_env::SysExState(), RECEPTION_ERROR);
  }
  CHECK(memcmp(external, native_external_eeprom, sizeof(external)) == 0);
  CHECK(memcmp(internal, native_eeprom, sizeof(internal)) == 0);
}

TEST(SysExSanitizesOutOfRangePatch) {
  // An oscillator shape past the end indexes past the render function
  // table (a jump to a random address on the AVR); a modulation
  // destination past the end writes past the modulation arrays.
  std::vector<uint8_t> d = InitPatchBytes();
  d[PRM_OSC_SHAPE_1] = 0x7f;
  d[PRM_OSC_SHAPE_2] = 200;
  d[PRM_MIX_SUB_OSC_SHAPE] = 99;
  d[PRM_LFO_WAVE_1] = 120;
  d[PRM_LFO_RETRIGGER_2] = 50;
  d[PRM_MOD_SOURCE + 3 * 4] = 100;       // row 5 source
  d[PRM_MOD_DESTINATION + 3 * 11] = 250;  // row 12 destination
  d[87] = 0xff;  // op_data_[1]: operator 7, operand 31
  d[89] = 0xff;
  SendPatch(d);
  CHECK_EQ(native_env::SysExState(), RECEPTION_OK);
  for (uint8_t o = 0; o < sizeof(Patch); ++o) {
    uint8_t id = parameter_manager.at_offset(o);
    if (id == 0xff || o == PRM_FILTER_CUTOFF_2 || o == PRM_FILTER_RESONANCE_2 ||
        o == PRM_FILTER_MODE_1 || o == PRM_FILTER_MODE_2) continue;
    const Parameter& p0 = parameter_manager.parameter(id);
    Parameter p = p0;
    uint8_t v = part.GetParameter(o);
    CHECK_MSG(p.Clamp(v) == v, "offset %d = %d out of range", o, v);
  }
  native_env::MidiIn3(0x90, 60, 100);
  native_env::Render(50);
  native_env::MidiIn3(0x80, 60, 0);
  native_env::Render(10);
}

TEST(SysExSanitizesSequencerAndSystemSettings) {
  native_env::Boot();
  // Full sequencer state (0x07) with every byte at 0x7f-ish garbage.
  std::vector<uint8_t> seq(sizeof(SequencerSettings), 0xee);
  native_env::MidiIn(SysEx(0x07, 0, &seq[0], seq.size()));
  // System settings (0x04).
  std::vector<uint8_t> sys(sizeof(SystemSettings), 0xee);
  sys[PRM_SYS_MIDI_CHANNEL - PRM_SYS_OCTAVE] = 0;  // keep listening (omni)
  native_env::MidiIn(SysEx(0x04, 0, &sys[0], sys.size()));
  for (uint8_t o = PRM_SEQ_MODE; o < PRM_ENV_CURVE_1; ++o) {
    uint8_t id = parameter_manager.at_offset(o);
    if (id == 0xff) continue;
    const Parameter& p0 = parameter_manager.parameter(id);
    Parameter p = p0;
    uint8_t v = part.GetParameter(o);
    CHECK_MSG(p.Clamp(v) == v, "offset %d = %d out of range", o, v);
  }
  // Run the sequencer/arpeggiator on that state.
  native_env::MidiIn3(0x90, 60, 100);
  native_env::MidiIn3(0x90, 64, 100);
  native_env::Render(400);
  native_env::MidiIn3(0x80, 60, 0);
  native_env::MidiIn3(0x80, 64, 0);
  native_env::Render(10);
}

TEST(SysExBulkBlocks) {
  native_env::Boot();
  std::vector<uint8_t> block(128);
  for (int i = 0; i < 128; ++i) block[i] = i ^ 0x55;
  native_env::MidiIn(SysEx(0x40, 3, &block[0], 128));  // internal EEPROM
  CHECK_EQ(native_env::SysExState(), RECEPTION_OK);
  CHECK(memcmp(native_eeprom + 3 * 128, &block[0], 128) == 0);
  native_env::MidiIn(SysEx(0x41, 0, &block[0], 128));  // external, 16 KB in
  CHECK_EQ(native_env::SysExState(), RECEPTION_OK);
  CHECK(memcmp(native_external_eeprom + 16384 - 2048, &block[0], 128) == 0);
  // Past the addressable space (2 KB + 7 x 8 KB = 58 KB).
  native_env::MidiIn(SysEx(0x43, 127, &block[0], 128));
  CHECK_EQ(native_env::SysExState(), RECEPTION_ERROR);
}

TEST(SysExFullModeEchoesSysEx) {
  native_env::Boot();
  part.mutable_system_settings()->midi_out_mode = MIDI_OUT_FULL;
  native_env::ClearMidiOut();
  std::vector<uint8_t> m = SysEx(0x1b);
  native_env::MidiIn(m);
  std::vector<uint8_t> out = native_env::MidiOut();
  // The echo of the request comes first, then the reply.
  CHECK(out.size() >= m.size());
  CHECK(std::equal(m.begin(), m.end(), out.begin()));
}
