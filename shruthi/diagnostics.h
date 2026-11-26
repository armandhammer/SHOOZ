// Copyright 2026 SHOOZ contributors.
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
//
// SHOOZ version constants and on-device diagnostics, reported in the reply to
// a version request (SysEx 0x1c).
//
// Stack probe: at reset, before .data/.bss are initialized, the RAM between
// the end of .bss (__heap_start; no heap is used) and RAMEND is filled with a
// known byte. FreeStack() counts how many of those bytes, from the bottom up,
// the stack has never overwritten since boot: the worst-case headroom.
//
// Glitch counter: total audio buffer underruns since boot (saturates at 255).

#ifndef SHRUTHI_DIAGNOSTICS_H_
#define SHRUTHI_DIAGNOSTICS_H_

#include "avrlib/base.h"

namespace shruthi {

// Firmware family reported in the version reply (BAMBI uses 1).
const uint8_t kShoozFamily = 2;
// SHOOZ version, 0xMm: 0x01 = 0.1.
const uint8_t kShoozVersion = 0x01;
// Patch layout: 0 = stock YAM, 1 = adds envelope curves.
const uint8_t kPatchLayoutVersion = 1;

class Diagnostics {
 public:
  // Worst-case free stack since boot, saturated to 255.
  static uint8_t FreeStack();

  static inline void AddGlitches(uint8_t n) {
    uint8_t total = glitches_ + n;
    glitches_ = total < glitches_ ? 255 : total;
  }
  static inline uint8_t glitches() { return glitches_; }

 private:
  static uint8_t glitches_;
};

}  // namespace shruthi

#endif  // SHRUTHI_DIAGNOSTICS_H_
