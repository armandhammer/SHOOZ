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

#include "shruthi/diagnostics.h"

#include <avr/io.h>

// End of .bss/.noinit, provided by the avr-libc linker script.
extern uint8_t __heap_start;

static const uint8_t kStackPaint = 0xa5;

// Runs from .init3: the stack pointer is set (.init2) but nothing has been
// pushed yet, and .data/.bss are initialized afterwards (.init4), so it is
// safe to overwrite everything from __heap_start to RAMEND. Naked and without
// a return: execution falls through into the next init section.
extern "C" void DiagnosticsPaintStack(void)
    __attribute__((naked, used, section(".init3")));

extern "C" void DiagnosticsPaintStack(void) {
  uint8_t* p = &__heap_start;
  while (p <= reinterpret_cast<uint8_t*>(RAMEND)) {
    *p++ = kStackPaint;
  }
}

namespace shruthi {

/* static */
uint8_t Diagnostics::glitches_;

/* static */
uint8_t Diagnostics::FreeStack() {
  const uint8_t* p = &__heap_start;
  uint8_t n = 0;
  while (n != 255 && p <= reinterpret_cast<const uint8_t*>(RAMEND) &&
         *p == kStackPaint) {
    ++p;
    ++n;
  }
  return n;
}

}  // namespace shruthi
