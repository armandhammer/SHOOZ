// Copyright 2009 Olivier Gillet.
//
// Author: Olivier Gillet (ol.gillet@gmail.com)
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
// -----------------------------------------------------------------------------

#ifndef SHRUTHI_SYSTEM_SETTINGS_H_
#define SHRUTHI_SYSTEM_SETTINGS_H_

#include "avrlib/base.h"
#include "shruthi/patch.h"
#include "shruthi/sequencer_settings.h"

namespace shruthi {

class SystemSettings {
 public:
  int8_t octave;
  uint8_t raga;
  uint8_t portamento;
  uint8_t legato;

  int8_t master_tuning;
  uint8_t midi_channel;
  uint8_t midi_out_mode;
  
  uint8_t start_page;
  uint8_t display_delay;
  uint8_t expansion_filter_board;
  uint8_t programmer;
  uint8_t display_snap;

  uint16_t last_patch;
  // SHOOZ: vintage drift amount (0 = off). Stock YAM keeps this byte as
  // padding and ignores it.
  uint8_t vintage;
  
  void EepromSave() const;
  uint8_t EepromLoad();
// SHOOZ: packed so the host-native test build has the AVR's 15-byte layout
// (EEPROM image, SysEx 0x04 payload); a no-op on the AVR.
} __attribute__((packed));

enum FilterBoard {
  FILTER_BOARD_LPF,
  FILTER_BOARD_SSM,
  FILTER_BOARD_SVF,
  FILTER_BOARD_DSP,
  FILTER_BOARD_PVK,
  FILTER_BOARD_4PM,
  FILTER_BOARD_DLY,
  FILTER_BOARD_SP,
  FILTER_BOARD_LAST
};

enum ProgrammerMode {
  PROGRAMMER_NONE,
  PROGRAMMER_FCD,
  PROGRAMMER_XT
};

enum MidiOutMode {
  MIDI_OUT_OFF,
  MIDI_OUT_SOFT_THRU,
  MIDI_OUT_SEQUENCER,
  MIDI_OUT_CONTROLLER,
  MIDI_OUT_FULL,
  MIDI_OUT_1_0,
  MIDI_OUT_2_1,
  MIDI_OUT_3_4,
  MIDI_OUT_4_3,
  MIDI_OUT_5_4,
  MIDI_OUT_6_5,
  MIDI_OUT_7_6,
  MIDI_OUT_8_7,
};

enum START_PAGE {
  START_PAGE_SPLASH,
  START_PAGE_FILTER,
  START_PAGE_LAST_PATCH
};

enum SystemParameter {
  PRM_SYS_OCTAVE = sizeof(Patch) + sizeof(SequencerSettings),
  PRM_SYS_RAGA,
  PRM_SYS_PORTAMENTO,
  PRM_SYS_LEGATO,

  PRM_SYS_MASTER_TUNING,
  PRM_SYS_MIDI_CHANNEL,
  PRM_SYS_MIDI_OUT_MODE,

  PRM_SYS_START_PAGE,
  PRM_SYS_DISPLAY_DELAY,
  PRM_SYS_EXPANSION_FILTER_BOARD,
  PRM_SYS_PROGRAMMER,
  PRM_SYS_DISPLAY_SNAP,
  PRM_SYS_LAST_PATCH,
  PRM_SYS_VINTAGE = PRM_SYS_LAST_PATCH + 2,

  // SHOOZ: per-patch envelope curves, stored right after SystemSettings
  // (Part::env_curve_).
  PRM_ENV_CURVE_1,
  PRM_ENV_CURVE_2,

  // SHOOZ: filter calibration (FilterCalibration, below).
  PRM_FILTER_PROFILE,
  PRM_FILTER_CUTOFF_OFFSET,
  PRM_FILTER_RESONANCE_MAX,
  PRM_LAST
};

// SHOOZ: voicing of the analog filter board, per unit (not per patch).
// The board setting says how the board is wired (which CVs it reads); the
// profile says how it responds: resonance taper, passband level loss as the
// resonance rises, and the cutoff shift that comes with resonance. Profile
// 0 leaves the CVs exactly as stock.
enum FilterProfile {
  FILTER_PROFILE_OFF,
  FILTER_PROFILE_CS80,
  FILTER_PROFILE_IR3109,
  FILTER_PROFILE_POLIVOKS,
  FILTER_PROFILE_SMR4,
  FILTER_PROFILE_LAST
};

// Applied in FillAudioBuffer() (shruthi.cc), before the board-specific
// processing. Stored in the last 4 bytes of the internal EEPROM, which
// stock firmware never uses (patches and sequences end at byte 2000), so
// going back to stock YAM is safe. Not part of the 15-byte SystemSettings
// block (SysEx 0x04 stays stock); a full EEPROM backup (0x50) includes it.
// Saved by the system page save only (Editor::SaveSystemSettings).
class FilterCalibration {
 public:
  uint8_t magic;  // kFilterCalibrationMagic once saved
  // Parameters PRM_FILTER_PROFILE.. point here.
  uint8_t profile;
  int8_t cutoff_offset;  // -63..63, in 8-bit cutoff CV steps
  uint8_t resonance_max;  // 0..127, 127 = full range

  void EepromSave();
  void EepromLoad();
} __attribute__((packed));

static const uint16_t kFilterCalibrationEepromAddress = 2044;  // 2 KB - 4
static const uint8_t kFilterCalibrationMagic = 0xc5;

extern FilterCalibration filter_calibration;

}  // namespace shruthi

#endif // SHRUTHI_SYSTEM_SETTINGS_H_
