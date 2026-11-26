// Every parameter is addressed by a byte offset (PatchParameter,
// SequencerParameter, SystemParameter). Stock YAM added the offset to a
// dummy byte placed before the patch, which assumed the compiler laid the
// patch, sequencer and system settings out back to back (true for
// avr-gcc 4.3.5, false for host g++). SHOOZ resolves the offset explicitly
// (Part::parameter_address); these tests pin the mapping.
#include "test.h"
#include "shruthi_env.h"

#include "shruthi/part.h"
#include "shruthi/system_settings.h"

using namespace shruthi;

TEST(LayoutStructSizes) {
  CHECK_EQ(sizeof(Patch), 100);
  CHECK_EQ(PRM_SYS_OCTAVE, sizeof(Patch) + sizeof(SequencerSettings));
  // 15 bytes, as on the AVR (the struct is packed for the host build).
  CHECK_EQ(sizeof(SystemSettings), 15);
  CHECK_EQ(PRM_ENV_CURVE_1 - PRM_SYS_OCTAVE, 15);
  // Offsets above 159 are not reachable by NRPN (ParameterManager).
  CHECK(PRM_ENV_CURVE_2 < 160);
}

TEST(LayoutPatchOffsets) {
  native_env::Boot();
  Patch* p = part.mutable_patch();
  p->osc[1].shape = 7;
  p->filter_cutoff = 42;
  p->modulation_matrix.modulation[11].amount = -3;
  p->filter_2_mode_ = 2;
  p->ops_[1].op = 5;
  CHECK_EQ(part.GetParameter(PRM_OSC_SHAPE_2), 7);
  CHECK_EQ(part.GetParameter(PRM_FILTER_CUTOFF), 42);
  CHECK_EQ(static_cast<int8_t>(part.GetParameter(PRM_MOD_SOURCE + 11 * 3 + 2)),
           -3);
  CHECK_EQ(part.GetParameter(PRM_FILTER_MODE_2), 2);
  CHECK_EQ(part.GetParameter(PRM_OP_OPERATOR + 3), 5);
}

TEST(LayoutSequencerAndSystemOffsets) {
  native_env::Boot();
  part.mutable_sequencer_settings()->seq_tempo = 133;
  part.mutable_system_settings()->midi_channel = 9;
  part.mutable_system_settings()->vintage = 77;
  part.mutable_env_curve()[0] = 3;
  part.mutable_env_curve()[1] = 6;
  CHECK_EQ(part.GetParameter(PRM_SEQ_TEMPO), 133);
  CHECK_EQ(part.GetParameter(PRM_SYS_MIDI_CHANNEL), 9);
  CHECK_EQ(part.GetParameter(PRM_SYS_VINTAGE), 77);
  CHECK_EQ(part.GetParameter(PRM_ENV_CURVE_1), 3);
  CHECK_EQ(part.GetParameter(PRM_ENV_CURVE_2), 6);
}
