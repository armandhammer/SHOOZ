// Parameter table, NRPN/CC reception, and the tempo clock.
#include "test.h"
#include "shruthi_env.h"

#include "shruthi/clock.h"
#include "shruthi/parameter.h"
#include "shruthi/part.h"
#include "shruthi/system_settings.h"

using namespace shruthi;

namespace {

bool InRange(const Parameter& p, uint8_t v) {
  if (p.unit == UNIT_INT8) {
    return static_cast<int8_t>(v) >= static_cast<int8_t>(p.min_value) &&
           static_cast<int8_t>(v) <= static_cast<int8_t>(p.max_value);
  }
  return v >= p.min_value && v <= p.max_value;
}

// Offsets several filter boards share; their range depends on the board.
bool BoardSpecific(uint8_t offset) {
  return offset == PRM_FILTER_CUTOFF_2 || offset == PRM_FILTER_RESONANCE_2 ||
         offset == PRM_FILTER_MODE_1 || offset == PRM_FILTER_MODE_2;
}

}  // namespace

TEST(ParamTableRangesAreSane) {
  native_env::Boot();
  for (uint8_t i = 0; i < kNumParameters; ++i) {
    const Parameter& p = parameter_manager.parameter(i);
    CHECK_MSG(p.offset < kNumOffsets, "parameter %d: offset %d", i, p.offset);
    CHECK_MSG(p.unit < UNIT_LAST, "parameter %d: unit %d", i, p.unit);
    if (p.unit == UNIT_INT8) {
      CHECK_MSG(static_cast<int8_t>(p.min_value) <=
                static_cast<int8_t>(p.max_value), "parameter %d", i);
    } else {
      CHECK_MSG(p.min_value <= p.max_value, "parameter %d", i);
    }
  }
}

TEST(ParamOffsetLookupIsConsistent) {
  native_env::Boot();
  for (uint8_t i = 0; i < kNumParameters; ++i) {
    const Parameter& p = parameter_manager.parameter(i);
    uint8_t id = parameter_manager.at_offset(p.offset);
    CHECK_MSG(id != 0xff, "parameter %d (offset %d) unreachable", i,
              p.offset);
    if (!BoardSpecific(p.offset)) {
      CHECK_MSG(parameter_manager.parameter(id).offset == p.offset,
                "offset %d maps to parameter %d", p.offset, id);
    }
  }
  CHECK_EQ(parameter_manager.at_offset(kNumOffsets), 0xff);
  CHECK_EQ(parameter_manager.at_offset(255), 0xff);
  // Name, sequencer-only extra data, op_data: no parameter.
  for (uint8_t o = 68; o < 84; ++o) CHECK_EQ(parameter_manager.at_offset(o), 0xff);
}

TEST(ParamScaleAndIncrementStayInRange) {
  native_env::Boot();
  for (uint8_t i = 0; i < kNumParameters; ++i) {
    const Parameter& p = parameter_manager.parameter(i);
    if (p.unit == UNIT_RAW_UINT8) continue;
    for (uint8_t v = 0; v < 128; ++v) {
      CHECK_MSG(InRange(p, p.Scale(v)), "parameter %d: Scale(%d) = %d", i, v,
                p.Scale(v));
    }
    CHECK_EQ(p.Scale(0), p.min_value);
    // Ranges over 128 steps (LFO rate: 144) can't reach the top from a
    // 7-bit value: stock behaviour, the encoder still can.
    uint8_t range = p.max_value - p.min_value + 1;
    CHECK_MSG(p.Scale(127) == p.max_value ||
              (range == 0 || range > 128) && p.Scale(127) + 1 >= p.max_value ||
              p.unit == UNIT_TEMPO_WITH_EXTERNAL_CLOCK,
              "parameter %d: Scale(127) = %d, max %d", i, p.Scale(127),
              p.max_value);
    CHECK(InRange(p, p.Increment(p.max_value, 1)));
    CHECK(InRange(p, p.Increment(p.min_value, -1)));
    CHECK(InRange(p, p.Clamp(0x80)));
    CHECK(InRange(p, p.Clamp(0x7f)));
  }
}

TEST(ParamCcMapPointsBack) {
  native_env::Boot();
  for (uint8_t cc = 0; cc < 128; ++cc) {
    uint8_t id = parameter_manager.for_cc(cc);
    if (id == 0xff) continue;
    const Parameter& p = parameter_manager.parameter(id);
    CHECK_MSG(p.midi_cc[0] == cc || p.midi_cc[1] == cc, "cc %d", cc);
  }
}

TEST(ParamNrpnSetsEveryPatchAndSequencerParameter) {
  // Every non-system parameter accepts its min and max by NRPN, and
  // rejects a value one past each end.
  for (uint8_t i = 0; i < kNumParameters; ++i) {
    native_env::Boot();
    const Parameter& p0 = parameter_manager.parameter(i);
    Parameter p = p0;
    if (p.offset >= PRM_SYS_OCTAVE && p.offset < PRM_ENV_CURVE_1) continue;
    if (BoardSpecific(p.offset)) continue;
    // UI-only aliases (mod/op row selectors): their offset belongs to the
    // second row's first field.
    if (parameter_manager.at_offset(p.offset) != i) continue;
    native_env::Nrpn(0, p.offset, p.max_value);
    CHECK_MSG(part.GetParameter(p.offset) == p.max_value,
              "parameter %d (offset %d): max %d not set (%d)", i, p.offset,
              p.max_value, part.GetParameter(p.offset));
    native_env::Nrpn(0, p.offset, p.min_value);
    CHECK_MSG(part.GetParameter(p.offset) == p.min_value,
              "parameter %d (offset %d): min not set", i, p.offset);
    if (p.unit != UNIT_INT8 && p.max_value < 255) {
      native_env::Nrpn(0, p.offset, p.max_value + 1);
      CHECK_MSG(part.GetParameter(p.offset) == p.min_value,
                "parameter %d: max + 1 accepted", i);
    }
  }
}

TEST(ParamNrpnEnvelopeCurves) {
  native_env::Boot();
  native_env::Nrpn(0, PRM_ENV_CURVE_1, 5);
  native_env::Nrpn(0, PRM_ENV_CURVE_2, 7);
  CHECK_EQ(part.mutable_env_curve()[0], 5);
  CHECK_EQ(part.mutable_env_curve()[1], 7);
  native_env::Nrpn(0, PRM_ENV_CURVE_1, 8);  // out of range
  CHECK_EQ(part.mutable_env_curve()[0], 5);
  // The voice picks the curve up on the next block.
  native_env::Render(1);
  native_env::Nrpn(0, PRM_ENV_CURVE_2, 0);
  CHECK_EQ(part.mutable_env_curve()[1], 0);
}

TEST(ParamNrpnSignedValues) {
  native_env::Boot();
  // Oscillator 2 range is -24..24: send -12 (0xf4 = MSB 1, LSB 0x74).
  native_env::Nrpn(0, PRM_OSC_RANGE_2, 0xf4);
  CHECK_EQ(static_cast<int8_t>(part.patch().osc[1].range), -12);
  native_env::Nrpn(0, PRM_OSC_RANGE_2, 0xc0);  // -64: rejected
  CHECK_EQ(static_cast<int8_t>(part.patch().osc[1].range), -12);
}

TEST(ParamNrpnIgnoresUnmappedNumbers) {
  native_env::Boot();
  Patch before = part.patch();
  for (uint16_t n = 68; n < 84; ++n) native_env::Nrpn(0, n, 0x41);
  native_env::Nrpn(0, 200, 1);
  native_env::Nrpn(0, 0x3fff, 1);
  CHECK(memcmp(&before, &part.patch(), 92) == 0);
}

TEST(ParamCcScalesToRange) {
  native_env::Boot();
  for (uint8_t cc = 0; cc < 128; ++cc) {
    uint8_t id = parameter_manager.for_cc(cc);
    if (id == 0xff) continue;
    const Parameter& p0 = parameter_manager.parameter(id);
    Parameter p = p0;
    if (p.offset >= PRM_SYS_OCTAVE && p.offset < PRM_ENV_CURVE_1) continue;
    native_env::MidiIn3(0xb0, cc, 127);
    CHECK_MSG(InRange(p, part.GetParameter(p.offset)), "cc %d", cc);
    native_env::MidiIn3(0xb0, cc, 0);
    CHECK_MSG(InRange(p, part.GetParameter(p.offset)), "cc %d", cc);
  }
}

TEST(ClockTempoMatchesBpm) {
  // 24 clock ticks per beat at the control rate (sample rate / 40).
  const double control_rate = (20000000.0 / 510.0) / kAudioBlockSize;
  uint8_t bpms[] = { 40, 90, 120, 175, 240 };
  for (uint8_t k = 0; k < sizeof(bpms); ++k) {
    clock.Update(bpms[k]);
    clock.Reset();
    long ticks = static_cast<long>(control_rate * 60);  // one minute
    long wraps = 0;
    for (long t = 0; t < ticks; ++t) {
      clock.Tick();
      if (clock.Wrap(0)) ++wraps;
    }
    CHECK_NEAR(wraps, 24L * bpms[k], 1);
  }
  clock.Update(120);
}
