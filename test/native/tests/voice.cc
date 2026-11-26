// Whole-synth rendering: notes in, audio and filter CVs out. Oscillators,
// envelope curves on the VCA, vintage drift (M3), filter-board CV paths.
#include "test.h"
#include "shruthi_env.h"

#include <stdio.h>
#include <string.h>

#include "shruthi/part.h"
#include "shruthi/system_settings.h"

using namespace shruthi;
using native_env::Cv;

namespace {

void NoteOn(uint8_t note, uint8_t velocity = 100) {
  native_env::MidiIn3(0x90, note, velocity);
}
void NoteOff(uint8_t note) { native_env::MidiIn3(0x80, note, 0); }

// A plain patch: one saw, no modulation into pitch/cutoff, so that the
// remaining variation comes from what the test sets.
void PlainPatch() {
  Patch* p = part.mutable_patch();
  p->osc[0].shape = WAVEFORM_POLYBLEP_SAW;
  p->osc[1].shape = WAVEFORM_NONE;
  p->mix_balance = 0;
  p->mix_sub_osc = 0;
  p->mix_noise = 0;
  p->filter_env = 0;
  p->filter_lfo = 0;
  for (uint8_t i = 0; i < kModulationMatrixSize; ++i) {
    p->modulation_matrix.modulation[i].amount = 0;
  }
  // The VCA follows envelope 2 through the fixed routing.
  p->modulation_matrix.modulation[1].source = MOD_SRC_ENV_2;
  p->modulation_matrix.modulation[1].destination = MOD_DST_VCA;
  p->modulation_matrix.modulation[1].amount = 63;
  part.Touch(false);
}

}  // namespace

TEST(VoiceNoteOnMakesSoundAndNoteOffStops) {
  native_env::Boot();
  part.mutable_system_settings()->midi_out_mode = MIDI_OUT_OFF;
  std::vector<uint8_t> audio;
  std::vector<Cv> cv;
  native_env::Render(20, &audio, &cv);
  CHECK(native_env::PeakToPeak(audio, 0, audio.size()) < 4);
  CHECK_EQ(cv.back().vca, 0);
  NoteOn(57);
  audio.clear();
  cv.clear();
  native_env::Render(300, &audio, &cv);
  CHECK(native_env::PeakToPeak(audio, audio.size() - 4000, 4000) > 40);
  CHECK(cv.back().vca > 100);
  NoteOff(57);
  audio.clear();
  cv.clear();
  native_env::Render(3000, &audio, &cv);
  CHECK_EQ(cv.back().vca, 0);
  CHECK(native_env::PeakToPeak(audio, audio.size() - 400, 400) < 4);
}

TEST(VoiceEveryOscillatorShapeRenders) {
  for (uint8_t shape = 0; shape < WAVEFORM_LAST; ++shape) {
    native_env::Boot();
    part.mutable_system_settings()->midi_out_mode = MIDI_OUT_OFF;
    PlainPatch();
    for (uint8_t prm = 0; prm < 128; prm += 63) {
      part.mutable_patch()->osc[0].shape = shape;
      part.mutable_patch()->osc[0].parameter = prm;
      NoteOn(48 + prm / 4);
      std::vector<uint8_t> audio;
      native_env::Render(150, &audio);
      int p2p = native_env::PeakToPeak(audio, audio.size() - 2000, 2000);
      if (shape == WAVEFORM_NONE) {
        CHECK_MSG(p2p < 8, "silence shape: p2p %d", p2p);
      } else {
        CHECK_MSG(p2p > 4, "shape %d (param %d) is silent", shape, prm);
      }
      NoteOff(48 + prm / 4);
      native_env::Render(5);
    }
  }
}

TEST(VoiceExtremeNotesAndBends) {
  native_env::Boot();
  part.mutable_system_settings()->midi_out_mode = MIDI_OUT_OFF;
  for (uint8_t shape = 1; shape < WAVEFORM_LAST; shape += 3) {
    part.mutable_patch()->osc[0].shape = shape;
    part.mutable_patch()->osc[1].shape = WAVEFORM_LAST - shape;
    part.mutable_patch()->osc[1].range = 24;
    NoteOn(127, 127);
    native_env::MidiIn3(0xe0, 0x7f, 0x7f);  // full bend up
    native_env::MidiIn3(0xd0, 127, 0);      // aftertouch
    native_env::Render(20);
    NoteOff(127);
    NoteOn(0, 1);
    native_env::MidiIn3(0xe0, 0, 0);
    native_env::Render(20);
    NoteOff(0);
  }
  native_env::MidiIn3(0xe0, 0, 0x40);
}

TEST(VoiceEnvelopeCurveShapesTheVca) {
  // A slow attack: the stock curve (fast start) spends the first part of
  // the attack well above the inverse-exponential preset (slow start),
  // and both reach full level at the same time.
  std::vector<Cv> cv[2];
  uint8_t curves[2] = { 0, 7 };
  for (int k = 0; k < 2; ++k) {
    native_env::Boot();
    part.mutable_system_settings()->midi_out_mode = MIDI_OUT_OFF;
    PlainPatch();
    native_env::Nrpn(0, PRM_ENV_ATTACK_2, 70);
    native_env::Nrpn(0, PRM_ENV_SUSTAIN_2, 127);
    native_env::Nrpn(0, PRM_ENV_CURVE_2, curves[k]);
    // The envelope reads its rates once per block, and a trigger latches
    // the attack rate (on hardware the NRPN alone takes ~4 blocks).
    native_env::Render(2);
    NoteOn(60);
    native_env::Render(3000, 0, &cv[k]);
  }
  uint8_t top = cv[1].back().vca;
  size_t end = 0;  // the inverse curve reaches the top only at the end
  while (end < cv[1].size() && cv[1][end].vca < top) ++end;
  CHECK(end > 100);
  CHECK(end < cv[1].size() - 1);
  CHECK_EQ(cv[0].back().vca, top);
  for (int q = 1; q <= 2; ++q) {
    size_t t = end * q / 4;
    CHECK_MSG(cv[0][t].vca > cv[1][t].vca + 40, "at %d/4: stock %d vs inverse %d",
              q, cv[0][t].vca, cv[1][t].vca);
  }
  CHECK_NEAR(cv[0][end + 2].vca, top, 3);
}

namespace {

// Rising crossings of mid-scale per window of |window| samples.
std::vector<int> CyclesPerWindow(const std::vector<uint8_t>& audio,
                                 size_t window) {
  std::vector<int> counts;
  int count = 0;
  for (size_t i = 1; i < audio.size(); ++i) {
    if (audio[i - 1] < 128 && audio[i] >= 128) ++count;
    if (i % window == 0) {
      counts.push_back(count);
      count = 0;
    }
  }
  return counts;
}

}  // namespace

TEST(VoiceVintageDriftsPitchWithinBounds) {
  // Note 96 (~2093 Hz), cycles counted per half second over 20 s. Without
  // drift the count is steady (+/-1 for window edges); at full drift it
  // wanders by up to +/-6 cents (+/-0.35%, ~3.6 cycles), never more than
  // twice that.
  for (int k = 0; k < 2; ++k) {
    native_env::Boot();
    part.mutable_system_settings()->midi_out_mode = MIDI_OUT_OFF;
    part.mutable_system_settings()->vintage = k ? 127 : 0;
    PlainPatch();
    NoteOn(96);
    native_env::Render(200);
    std::vector<uint8_t> audio;
    native_env::Render(20000, &audio);
    std::vector<int> c = CyclesPerWindow(audio, 19608);
    int lo = 1 << 30, hi = 0;
    for (size_t i = 0; i < c.size(); ++i) {
      if (c[i] < lo) lo = c[i];
      if (c[i] > hi) hi = c[i];
    }
    CHECK_NEAR(lo, 1046, 12);
    if (k == 0) {
      CHECK_MSG(hi - lo <= 1, "steady pitch wanders: %d..%d", lo, hi);
    } else {
      CHECK_MSG(hi - lo >= 2, "no pitch drift: %d..%d", lo, hi);
      CHECK_MSG(hi - lo <= 15, "pitch drift too wide: %d..%d", lo, hi);
    }
  }
}

TEST(VoiceVintageDriftsCutoffWithinBounds) {
  // With the cutoff unmodulated, any movement of the cutoff CV during a
  // held note is the drift: none when off, small and bounded when on.
  for (int k = 0; k < 2; ++k) {
    native_env::Boot();
    part.mutable_system_settings()->midi_out_mode = MIDI_OUT_OFF;
    part.mutable_system_settings()->vintage = k ? 127 : 0;
    PlainPatch();
    NoteOn(60);
    native_env::Render(400);
    std::vector<Cv> cv;
    native_env::Render(20000, 0, &cv);  // ~20 s
    int lo = 255, hi = 0;
    for (size_t i = 0; i < cv.size(); ++i) {
      if (cv[i].cutoff < lo) lo = cv[i].cutoff;
      if (cv[i].cutoff > hi) hi = cv[i].cutoff;
    }
    if (k == 0) {
      CHECK_EQ(hi - lo, 0);
    } else {
      CHECK_MSG(hi - lo >= 2, "no drift: %d..%d", lo, hi);
      CHECK_MSG(hi - lo <= 9, "drift too wide: %d..%d", lo, hi);
    }
  }
}

TEST(VoiceFilterBoardCvPathsRender) {
  // Every filter-board output path (resonance knees, SSM2164 table, DSP
  // UART stream) with resonance and cutoff at both ends.
  for (uint8_t board = 0; board < FILTER_BOARD_LAST; ++board) {
    native_env::Boot();
    part.mutable_system_settings()->midi_out_mode = MIDI_OUT_OFF;
    part.mutable_system_settings()->expansion_filter_board = board;
    for (uint8_t programmer = 0; programmer < 3; ++programmer) {
      part.mutable_system_settings()->programmer = programmer;
      for (int r = 0; r < 2; ++r) {
        part.mutable_patch()->filter_resonance = r ? 63 : 0;
        part.mutable_patch()->filter_cutoff = r ? 127 : 0;
        part.mutable_patch()->filter_1_mode_ = r ? 15 : 0;
        part.mutable_patch()->filter_2_mode_ = r ? 15 : 0;
        NoteOn(60);
        std::vector<Cv> cv;
        native_env::Render(30, 0, &cv);
        NoteOff(60);
        if (board == FILTER_BOARD_PVK && r) {
          CHECK(cv.back().resonance >= 190);
        }
      }
    }
    if (board == FILTER_BOARD_DSP) {
      CHECK(native_env::Uart1Out().size() > 100);
    }
  }
}

TEST(VoiceRoutingBytesForEveryFilterMode) {
  native_env::Boot();
  for (uint8_t m1 = 0; m1 < 16; ++m1) {
    for (uint8_t m2 = 0; m2 < 16; ++m2) {
      part.mutable_patch()->filter_1_mode_ = m1;
      part.mutable_patch()->filter_2_mode_ = m2;
      part.svf_routing_byte();
      part.pvk_routing_byte();
      part.sp_routing_byte();
      CHECK_EQ(part.fx_control_byte(), (m1 << 4) | m2);
    }
  }
}
