// Prints the SHOOZ parameter table, display labels and init data as JSON,
// straight from the firmware's own tables (PROGMEM structs, string table,
// init patch). SHED generates its Shruthi parameter map from this output:
//
//   make -f test/native/makefile export > shooz-params.json
#include <stdio.h>
#include <string.h>

#include "shruthi_env.h"

#include "shruthi/parameter.h"
#include "shruthi/part.h"
#include "shruthi/patch.h"
#include "shruthi/resources.h"
#include "shruthi/sequencer_settings.h"
#include "shruthi/storage.h"
#include "shruthi/system_settings.h"
#include "shruthi/diagnostics.h"

using namespace shruthi;

namespace {

const char* const kUnitNames[UNIT_LAST] = {
  "raw_uint8", "uint8", "int8", "boolean", "waveform", "sub_osc_waveform",
  "operator", "lfo_waveform", "lfo_rate", "index", "modulation_source",
  "modulation_destination", "arpeggio_direction", "raga",
  "tempo_with_external_clock", "midi_mode", "sequencer_mode",
  "sequencer_division", "groove_template", "arpeggio_pattern",
  "lfo_retrigger_mode", "start_page", "pause", "filter_board",
  "filter_1_mode", "filter_2_mode", "cv_operator", "fx_program",
  "filter_fx_mode", "filter_4p_mode", "filter_4p_flavour", "filter_sp_mode",
  "filter_profile",
};

void PrintJsonString(const char* s) {
  putchar('"');
  for (; *s; ++s) {
    unsigned char c = static_cast<unsigned char>(*s);
    if (c == '"' || c == '\\') {
      printf("\\%c", c);
    } else if (c < 0x20 || c >= 0x7f) {
      printf("\\u%04x", c);  // LCD glyphs (arrows, waveforms)
    } else {
      putchar(c);
    }
  }
  putchar('"');
}

void PrintString(ResourceId id) {
  char buffer[32];
  shruthi::ResourcesManager::LoadStringResource(id, buffer, sizeof(buffer) - 1);
  buffer[sizeof(buffer) - 1] = '\0';
  PrintJsonString(buffer);
}

void PrintBytes(const uint8_t* data, size_t size) {
  putchar('[');
  for (size_t i = 0; i < size; ++i) printf("%s%d", i ? "," : "", data[i]);
  putchar(']');
}

}  // namespace

int main() {
  native_env::Boot();
  printf("{\n  \"firmware\": {\"family\": %d, \"version\": %d, "
         "\"waveforms\": %d, \"patch_layout\": %d, \"rom_version\": [%d, %d]},\n",
         kShoozFamily, kShoozVersion, WAVEFORM_LAST, kPatchLayoutVersion,
         pgm_read_byte(wav_res_version), pgm_read_byte(wav_res_version + 1));
  printf("  \"sizes\": {\"patch\": %d, \"patch_ram\": %d, \"sequencer\": %d, "
         "\"sequence_dump\": %d, \"system\": %d},\n",
         static_cast<int>(StorageConfiguration<Patch>::size),
         static_cast<int>(sizeof(Patch)),
         static_cast<int>(sizeof(SequencerSettings)),
         static_cast<int>(StorageConfiguration<SequencerSettings>::size),
         static_cast<int>(sizeof(SystemSettings)));
  printf("  \"offsets\": {\"seq\": %d, \"sys\": %d, \"env_curve_1\": %d, "
         "\"env_curve_2\": %d, \"sys_vintage\": %d, "
         "\"filter_profile\": %d, \"filter_cutoff_offset\": %d, "
         "\"filter_resonance_max\": %d},\n",
         PRM_SEQ_MODE, PRM_SYS_OCTAVE, PRM_ENV_CURVE_1, PRM_ENV_CURVE_2,
         PRM_SYS_VINTAGE, PRM_FILTER_PROFILE, PRM_FILTER_CUTOFF_OFFSET,
         PRM_FILTER_RESONANCE_MAX);

  // The init patch as it goes on the wire (PrepareForWrite packs the
  // filter modes and operators into bytes 86-90).
  part.mutable_patch()->PrepareForWrite();
  printf("  \"init_patch\": ");
  PrintBytes(part.mutable_patch()->saved_data(), 92);
  printf(",\n  \"init_sequencer\": ");
  PrintBytes(reinterpret_cast<const uint8_t*>(&part.sequencer_settings()),
             sizeof(SequencerSettings));
  printf(",\n  \"init_system\": ");
  PrintBytes(reinterpret_cast<const uint8_t*>(&part.system_settings()),
             sizeof(SystemSettings));
  printf(",\n  \"parameters\": [\n");
  for (uint8_t i = 0; i < kNumParameters; ++i) {
    Parameter p = parameter_manager.parameter(i);
    bool is_signed = p.unit == UNIT_INT8;
    int min = is_signed ? static_cast<int8_t>(p.min_value) : p.min_value;
    int max = is_signed ? static_cast<int8_t>(p.max_value) : p.max_value;
    printf("    {\"index\": %d, \"offset\": %d, \"nrpn_owner\": %d, "
           "\"unit\": \"%s\", \"min\": %d, \"max\": %d, \"cc\": [%d, %d], "
           "\"short\": ",
           i, p.offset,
           parameter_manager.at_offset(p.offset) == i ? 1 : 0,
           kUnitNames[p.unit], min, max, p.midi_cc[0], p.midi_cc[1]);
    PrintString(p.short_name);
    printf(", \"long\": ");
    PrintString(p.long_name);
    // Display text for every value, as the LCD shows it (16 characters).
    printf(", \"labels\": [");
    for (int v = min; v <= max; ++v) {
      char buffer[17];
      memset(buffer, 0, sizeof(buffer));
      p.PrintValue(static_cast<uint8_t>(v), buffer, 16);
      // PrintValue right-aligns into |width|; trim.
      char* s = buffer;
      while (*s == ' ') ++s;
      size_t n = strlen(s);
      while (n && s[n - 1] == ' ') s[--n] = '\0';
      if (v != min) putchar(',');
      PrintJsonString(s);
    }
    printf("]}%s\n", i + 1 < kNumParameters ? "," : "");
  }
  printf("  ]\n}\n");
  return 0;
}
