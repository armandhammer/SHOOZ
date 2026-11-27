// SHOOZ filter calibration (system page "filter cal"): profile, cutoff
// offset and resonance max, applied to the filter CVs in FillAudioBuffer(),
// stored in the last 4 bytes of the internal EEPROM.
#include "test.h"
#include "shruthi_env.h"

#include <string.h>

#include <string>

#include <avr/eeprom.h>

#include "shruthi/parameter.h"
#include "shruthi/part.h"
#include "shruthi/system_settings.h"

using namespace shruthi;
using native_env::Cv;

extern uint8_t native_eeprom[E2END + 1];

namespace {

// One block with the current patch, resonance 0..63 and cutoff 0..127 (the
// patch ranges); returns the CVs written after it.
Cv RenderWith(uint8_t resonance, uint8_t cutoff) {
  part.mutable_patch()->filter_resonance = resonance;
  part.mutable_patch()->filter_cutoff = cutoff;
  std::vector<Cv> cv;
  native_env::Render(2, 0, &cv);
  return cv.back();
}

void BootHeld() {
  native_env::Boot();
  Patch* p = part.mutable_patch();
  p->filter_env = 0;
  p->filter_lfo = 0;
  for (uint8_t i = 0; i < kModulationMatrixSize; ++i) {
    p->modulation_matrix.modulation[i].amount = 0;
  }
  // Duo mode: the cutoff doesn't track the note, so it is the knob value.
  p->osc[0].option = OP_DUO;
  part.Touch(false);
  native_env::MidiIn3(0x90, 60, 127);
  native_env::Render(200);  // envelope at sustain
}

void SetCalibration(uint8_t profile, int8_t offset, uint8_t resonance_max) {
  filter_calibration.profile = profile;
  filter_calibration.cutoff_offset = offset;
  filter_calibration.resonance_max = resonance_max;
}

}  // namespace

TEST(FilterCalLayoutAndDefaults) {
  native_env::Boot();
  CHECK(part.parameter_address(PRM_FILTER_PROFILE) ==
        &filter_calibration.profile);
  CHECK(part.parameter_address(PRM_FILTER_CUTOFF_OFFSET) ==
        (uint8_t*)&filter_calibration.cutoff_offset);
  CHECK(part.parameter_address(PRM_FILTER_RESONANCE_MAX) ==
        &filter_calibration.resonance_max);
  CHECK_EQ(PRM_FILTER_PROFILE, 159);
  // Blank EEPROM: off.
  CHECK_EQ(filter_calibration.profile, FILTER_PROFILE_OFF);
  CHECK_EQ(filter_calibration.cutoff_offset, 0);
  CHECK_EQ(filter_calibration.resonance_max, 127);
  // Stock data stops well before the calibration bytes.
  CHECK(16 + 16 * PATCH_SIZE + 16 * 32 <= kFilterCalibrationEepromAddress);
  CHECK_EQ(kFilterCalibrationEepromAddress + 4, E2END + 1);
}

TEST(FilterCalOffSendsStockCvs) {
  // Profile off, offset 0, max 127: CVs equal the voice's values.
  BootHeld();
  for (uint8_t board = 0; board < FILTER_BOARD_LAST; ++board) {
    if (board == FILTER_BOARD_PVK || board == FILTER_BOARD_DLY ||
        board == FILTER_BOARD_4PM) {
      continue;  // These reshape resonance/VCA themselves.
    }
    part.mutable_system_settings()->expansion_filter_board = board;
    for (uint8_t r = 0; r < 64; r += 7) {
      for (uint8_t c = 0; c < 128; c += 9) {
        Cv cv = RenderWith(r, c);
        CHECK_EQ(cv.cutoff, part.voice().cutoff());
        CHECK_EQ(cv.resonance, part.voice().resonance());
        CHECK_EQ(cv.vca, part.voice().vca());
      }
    }
  }
}

TEST(FilterCalProfilesShapeResonanceAndLevel) {
  BootHeld();
  for (uint8_t profile = 0; profile < FILTER_PROFILE_LAST; ++profile) {
    SetCalibration(profile, 0, 127);
    int previous_resonance = -1;
    int previous_cutoff = -1;
    for (uint8_t r = 0; r < 64; ++r) {
      Cv cv = RenderWith(r, 64);
      uint8_t raw = part.voice().resonance();
      // The taper only lifts the curve and keeps it monotonic.
      CHECK_MSG(cv.resonance >= raw, "profile %d r %d: %d < %d", profile, r,
                cv.resonance, raw);
      CHECK(static_cast<int>(cv.resonance) >= previous_resonance);
      previous_resonance = cv.resonance;
      // Resonance -> cutoff only raises the cutoff, monotonically.
      CHECK(cv.cutoff >= part.voice().cutoff());
      CHECK(static_cast<int>(cv.cutoff) >= previous_cutoff);
      previous_cutoff = cv.cutoff;
      // Level compensation only ever lowers the VCA, by at most half.
      CHECK(cv.vca <= part.voice().vca());
      CHECK(cv.vca >= part.voice().vca() / 2);
    }
    // Full scale stays full scale.
    CHECK(RenderWith(63, 64).resonance >= 250);
  }
}

TEST(FilterCalLadderProfilesEvenOutTheLevel) {
  // IR3109 and SMR4 hold the level back at low resonance and give it back
  // at full resonance; Polivoks pulls it down at full resonance.
  BootHeld();
  uint8_t ladders[] = { FILTER_PROFILE_IR3109, FILTER_PROFILE_SMR4 };
  for (int i = 0; i < 2; ++i) {
    SetCalibration(ladders[i], 0, 127);
    Cv low = RenderWith(0, 64);
    uint8_t vca = part.voice().vca();
    CHECK_MSG(low.vca < vca * 7 / 10, "profile %d: %d of %d", ladders[i],
              low.vca, vca);
    Cv high = RenderWith(63, 64);
    CHECK(high.vca >= part.voice().vca() - 2);
  }
  SetCalibration(FILTER_PROFILE_POLIVOKS, 0, 127);
  CHECK_EQ(RenderWith(0, 64).vca, part.voice().vca());
  CHECK(RenderWith(63, 64).vca < part.voice().vca() * 8 / 10);
  // IR3109: the steepest taper; half the knob (128) gives 128 + 39.
  SetCalibration(FILTER_PROFILE_IR3109, 0, 127);
  CHECK_NEAR(RenderWith(32, 64).resonance, 167, 2);
}

TEST(FilterCalCutoffOffsetClipsAtBothEnds) {
  BootHeld();
  SetCalibration(FILTER_PROFILE_OFF, 63, 127);
  CHECK_EQ(RenderWith(0, 127).cutoff, 255);
  Cv mid = RenderWith(0, 40);
  CHECK_EQ(mid.cutoff, part.voice().cutoff() + 63);
  SetCalibration(FILTER_PROFILE_OFF, -63, 127);
  CHECK_EQ(RenderWith(0, 0).cutoff, 0);
  mid = RenderWith(0, 100);
  CHECK_EQ(mid.cutoff, part.voice().cutoff() - 63);
  // With the IR3109 resonance shift on top, still no wrap-around.
  SetCalibration(FILTER_PROFILE_IR3109, 63, 127);
  CHECK_EQ(RenderWith(63, 127).cutoff, 255);
}

TEST(FilterCalResonanceMax) {
  BootHeld();
  SetCalibration(FILTER_PROFILE_OFF, 0, 0);
  CHECK(RenderWith(63, 64).resonance <= 2);
  SetCalibration(FILTER_PROFILE_OFF, 0, 64);
  Cv half = RenderWith(63, 64);
  CHECK_NEAR(half.resonance, part.voice().resonance() / 2, 3);
  // Still applied after the taper.
  SetCalibration(FILTER_PROFILE_IR3109, 0, 64);
  CHECK(RenderWith(63, 64).resonance <= 130);
}

TEST(FilterCalNrpnAndRanges) {
  native_env::Boot();
  native_env::Nrpn(0, PRM_FILTER_PROFILE, FILTER_PROFILE_SMR4);
  CHECK_EQ(filter_calibration.profile, FILTER_PROFILE_SMR4);
  native_env::Nrpn(0, PRM_FILTER_PROFILE, FILTER_PROFILE_LAST);  // rejected
  CHECK_EQ(filter_calibration.profile, FILTER_PROFILE_SMR4);
  native_env::Nrpn(0, PRM_FILTER_CUTOFF_OFFSET, 0xc1);  // -63
  CHECK_EQ(filter_calibration.cutoff_offset, -63);
  native_env::Nrpn(0, PRM_FILTER_CUTOFF_OFFSET, 0xc0);  // -64: rejected
  CHECK_EQ(filter_calibration.cutoff_offset, -63);
  native_env::Nrpn(0, PRM_FILTER_CUTOFF_OFFSET, 64);  // rejected
  CHECK_EQ(filter_calibration.cutoff_offset, -63);
  native_env::Nrpn(0, PRM_FILTER_RESONANCE_MAX, 100);
  CHECK_EQ(filter_calibration.resonance_max, 100);
  native_env::Nrpn(0, PRM_FILTER_RESONANCE_MAX, 128);  // rejected
  CHECK_EQ(filter_calibration.resonance_max, 100);
  // Not part of the patch.
  Patch before = part.patch();
  native_env::Nrpn(0, PRM_FILTER_PROFILE, FILTER_PROFILE_CS80);
  CHECK(memcmp(&before, &part.patch(), sizeof(Patch)) == 0);
}

TEST(FilterCalSavedOnlyBySystemSave) {
  native_env::Boot();
  SetCalibration(FILTER_PROFILE_IR3109, -20, 90);
  // A SystemSettings save on its own (e.g. the last patch number on each
  // patch load) leaves the calibration bytes alone.
  part.system_settings().EepromSave();
  CHECK_EQ(native_eeprom[kFilterCalibrationEepromAddress], 0xff);
  // Editor::SaveSystemSettings() (private) adds this call.
  filter_calibration.EepromSave();
  CHECK_EQ(native_eeprom[kFilterCalibrationEepromAddress],
           kFilterCalibrationMagic);
  // Power cycle: RAM cleared, EEPROM kept.
  SetCalibration(0, 0, 0);
  part.Init();
  CHECK_EQ(filter_calibration.profile, FILTER_PROFILE_IR3109);
  CHECK_EQ(filter_calibration.cutoff_offset, -20);
  CHECK_EQ(filter_calibration.resonance_max, 90);
  // The 15-byte SysEx 0x04 payload doesn't carry it (stock layout).
  CHECK_EQ(sizeof(SystemSettings), 15u);
}

TEST(FilterCalCorruptEepromIsClamped) {
  native_env::Boot();
  uint8_t* e = native_eeprom + kFilterCalibrationEepromAddress;
  e[0] = kFilterCalibrationMagic;
  e[1] = 200;
  e[2] = 100;
  e[3] = 255;
  part.Init();
  CHECK_EQ(filter_calibration.profile, FILTER_PROFILE_LAST - 1);
  CHECK_EQ(filter_calibration.cutoff_offset, 63);
  CHECK_EQ(filter_calibration.resonance_max, 127);
  e[2] = 0x80;  // -128
  part.Init();
  CHECK_EQ(filter_calibration.cutoff_offset, -63);
  // Wrong magic: defaults, whatever the bytes say.
  e[0] = 0;
  e[1] = 2;
  part.Init();
  CHECK_EQ(filter_calibration.profile, FILTER_PROFILE_OFF);
  CHECK_EQ(filter_calibration.resonance_max, 127);
  // Rendering with what is loaded never indexes past the profile table.
  native_env::Render(4);
}

namespace {

std::string Label(uint8_t parameter_index, uint8_t value) {
  char buffer[17];
  memset(buffer, 0, sizeof(buffer));
  parameter_manager.parameter(parameter_index).PrintValue(value, buffer, 16);
  std::string s(buffer);
  s.erase(0, s.find_first_not_of(' '));
  s.erase(s.find_last_not_of(' ') + 1);
  return s;
}

}  // namespace

TEST(FilterCalLabelsAndNeighbouringStrings) {
  // The profile names sit in the string table between the start page names
  // and the raga names; units index their strings by value, so a misplaced
  // string shifts a whole list.
  native_env::Boot();
  const char* profiles[] = { "off", "cs80", "ir31", "pvk", "smr4" };
  uint8_t prof = parameter_manager.at_offset(PRM_FILTER_PROFILE);
  for (uint8_t i = 0; i < FILTER_PROFILE_LAST; ++i) {
    CHECK(Label(prof, i) == profiles[i]);
  }
  uint8_t raga = parameter_manager.at_offset(PRM_SYS_RAGA);
  CHECK(Label(raga, 0) == "equal");
  CHECK(Label(raga, 32) == "rasia");
  uint8_t start_page = parameter_manager.at_offset(PRM_SYS_START_PAGE);
  CHECK(Label(start_page, 2) == "preset");
  uint8_t offset = parameter_manager.at_offset(PRM_FILTER_CUTOFF_OFFSET);
  CHECK(Label(offset, static_cast<uint8_t>(-63)) == "-63");
}
