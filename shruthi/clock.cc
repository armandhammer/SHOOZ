// Copyright 2011 Olivier Gillet.
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
//
// Global clock.

#include "shruthi/clock.h"

#include "shruthi/resources.h"

namespace shruthi {

Clock clock;

/* static */
uint16_t Clock::bpm_;

/* static */
uint32_t Clock::phase_;

/* static */
uint32_t Clock::phase_increment_;

/* static */
void Clock::Update(uint8_t bpm) {
  // SHOOZ: computed instead of read from the 804-byte table
  // lut_res_tempo_phase_increment (2^31 * 24 * bpm / (60 * control rate)).
  // The constant is truncated from 876173.33: the error is at most 78 in
  // 35 million (about 0.0001 BPM).
  phase_increment_ = static_cast<uint32_t>(bpm) * 876173UL;
}

}  // namespace shruthi
