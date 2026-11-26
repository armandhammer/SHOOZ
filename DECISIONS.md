# Engineering decisions

Decisions taken without the owner during autonomous work, with the reason.
Newest last. Revisit any of them by opening an issue or reverting the commit.

## 2026-11-26 — native test harness and the fixes it found

- **Host-compiled firmware instead of simavr** (as in BAMBI). simavr isn't
  available; a host build runs the whole firmware under AddressSanitizer.
  AVR-only details (16-bit `int`, assembly `op.h`) are covered by the AVR
  build and size gates, not by these tests.
- **Parameters are addressed through `Part::parameter_address()`** instead
  of stock's `data_access_byte_[offset + 1]`, which only worked because
  avr-gcc 4.3.5 happened to place the patch, sequencer settings, system
  settings and the SHOOZ curves back to back. Costs 52 B of flash; no
  offset or NRPN number changes.
- **Everything loaded from SysEx or EEPROM is clamped to the parameter
  table** (`Part::SanitizeParameters()`): patches (0x01, program change,
  undo), sequences (0x02, 0x07), system settings (0x04, boot). A shape past
  the end jumped to a random address; modulation sources/destinations past
  the end read and wrote past the modulation arrays. Filter-board-specific
  bytes (cutoff 2, resonance 2, filter modes 1-2) are skipped: their range
  depends on the board, and they index no table. In-range data is never
  changed, so valid patches load exactly as before. Costs ~150 B.
- **A SysEx message for another device no longer re-runs the previous
  command.** Stock went to `RECEIVING_FOOTER` on a header mismatch and, if
  F7 came next, re-accepted the previous command (e.g. `F0 7D F7` after a
  randomize request randomized the patch again; after a dump request, it
  sent another dump). Same fix as BAMBI.
- **Patch/sequence write requests (0x21/0x22) refuse slots past the
  installed banks.** On a smaller EEPROM the address wrapped onto bank 0.
- **Wavequence position 127 plays wave 126.** The table holds 127 waves;
  stock read 129 bytes after it. Positions 0-126 are unchanged.
- **CSaw's PWM-edge polyBLEP index clamps to 127.** With a small or zero
  parameter the edge is detected a sample late and the index passed the
  128-byte table (the result is scaled by the parameter, so the audible
  effect was small, but it read whatever followed in flash).
- **Tempo from a pot/CC never reads 38.** Rounding gave 38, below the range
  minimum (39 = external clock); it is now 39. Same fix as BAMBI.
- **`ParameterManager::Init` cleared 192 bytes of a 160-byte table**
  (32 bytes of `cc_to_id_` beyond it, which was then re-initialized, so no
  symptom on the AVR). Now `sizeof`.
- **`TransientGenerator::Trigger()` returns `void`**, and
  `Editor::KnobIndexToParameterId` returns 0xff instead of falling off the
  end (unreachable with 4 knobs). No AVR code change of note.
- **`SystemSettings` is `__attribute__((packed))`**: a no-op on the AVR,
  and the host build gets the same 15-byte layout (EEPROM image, SysEx
  payload).
- **No LICENSE change.** SHOOZ stays GPLv3 like the upstream firmware.

Flash after these fixes: 676 B free (gate 256), static RAM 261 B free.
