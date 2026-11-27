# SHOOZ Wave 1 — Implementation Plan

*Date: 2026-11-26. Companion to BAMBI's
[docs/AUDIT.md](https://github.com/armandhammer/BAMBI/blob/main/docs/AUDIT.md)
(section "Shruthi", items S1–S5) and its wave 1
[PLAN.md](https://github.com/armandhammer/BAMBI/blob/main/docs/PLAN.md).*

**Wave 1 scope:**
- **S1** upstream 1.03 sequencer/arpeggiator fixes
- **H8** capability bytes in the version reply, plus on-device diagnostics
  (stack high-water mark, audio glitch count)
- **S4** vintage drift
- **S5 (partial)** the tempo table is computed instead of stored. This removes
  no feature.
- **S2** envelope curves, per patch, 8 presets (decision §5.1: option A)

Deferred: **S3** filter-board profiles and the rest of **S5** (dropping the
user wavetable). **Update:** S3 is done after wave 1 as a per-unit
"filter cal" page that doesn't depend on the answer to §5.2 (see
DECISIONS.md, "S3 filter calibration", and HARDWARE_TESTS.md §S3). The
user wavetable stays.

## Status

All of wave 1 is implemented and builds. **Nothing has been verified on
hardware yet**: see [HARDWARE_TESTS.md](HARDWARE_TESTS.md).

| Milestone | Measured flash / static RAM | Free flash after | Notes |
|---|---|---|---|
| M0 baseline | 63,552 / 3,814 B | 960 B | YAM 0.05 unchanged; matches the shipped ELF to within 2 B |
| M1 S1 1.03 fixes | +72 / +0 | 888 B | Upstream `e0b5b62` applied cleanly |
| M2 H8 diagnostics + capabilities | +92 / +1 | 796 B | `0x1c` reply grows from 2 to 8 bytes |
| M3 S4 vintage drift | +284 / +7 | 512 B | Global setting `vint` on the system MIDI page |
| M4 S5 tempo table | **−806** / +0 | 1,318 B | `Clock::Update` multiplies instead of reading an 804 B table |
| M5 S2 envelope curves | +374 / +14 | **944 B** | New page "env curves"; patch format marker `'&'` |
| **Wave total** | **+16 / +22 B** | **944 B** ✅ (gate 256) | Static RAM 3,836 B, 260 B left for the stack |

The commits go in this order, so every commit passes the CI size gate (M5
before M4 would leave only 138 B free).

## 1. Constraints

- **Flash:** the bootloader sits at `0xFC00`. **Gate: ≥ 256 B free** at the
  end of the wave, so wave 2 has room for fixes.
- **RAM:** **Gate: measured stack high-water margin ≥ 96 B** (the M2 probe
  reads it). Static RAM grew 22 B. That's more than the 12 B first planned,
  because page definitions live in RAM (9 B for the new page).
- **Audio:** Shruthi renders audio in blocks from the main loop (~980 blocks/s),
  so new per-block work costs a little CPU and no ISR cycles. The M2 glitch
  counter catches any overrun.
- **Toolchain:** avr-gcc 4.3.5 / avr-libc 1.6.8 only. A lesson from M3:
  anything inlined into the huge `Voice::ProcessBlock` costs a lot of register
  spills (~300 B for a few lines), so new per-block work lives in out-of-line
  functions.

### Patch storage

The audit listed `extra_data_` as spare. It isn't: all 92 bytes of the stored
patch are in use, and patches are fixed 92-byte slots in EEPROM and on the
SysEx wire.

| Offset | Field | SHOOZ use |
|---|---|---|
| 76 | `extra_data_[0]` legato \| portamento | — (bit 7 is still free and ignored by stock) |
| 77 | `extra_data_[1]` seq mode (0–2) | **bits 2–4 env1 curve, bits 5–7 env2 curve** |
| 91 | `version_` | `'%'` as stock, **`'&'` when either curve is not 0** |

Stock YAM's `Patch::CheckBuffer` accepts only `'!'` and `'%'`. So it refuses
a SHOOZ patch that uses curves cleanly: the current sound stays and the name
shows `--------`. Patches with stock curves are byte-identical to stock.

The two live curve values sit right after `SystemSettings` in RAM
(`Part::env_curve_`, parameter offsets 157–158), so no existing parameter
offset or NRPN number moves.

## 2. Milestones

### M1 — S1 upstream 1.03 fixes

From `pichenettes/shruthi-1` `e0b5b62`:
- the arpeggiator re-clocks on the first key when it runs on external clock
  and no keys were held;
- legato steps extend the gate in sequencer mode (`NextStep()` now runs
  before the step is played, `arp_seq_step_` starts at `0xff`);
- Start/Stop leave notes alone in step mode, and Stop uses `AllSoundOff`;
- the VCA early-out checks `vca() == 0` instead of `< 2`, so quiet release
  tails are no longer cut off.

The 1.03 version string isn't taken.

### M2 — H8 diagnostics and capabilities

`shruthi/diagnostics.{h,cc}`:
- **Stack probe:** `.init3` paints the free RAM above `.bss` with `0xa5`;
  `FreeStack()` counts the bytes never touched since boot.
- **Glitch counter:** the main loop already shows `!` on an audio underrun;
  it now also adds the underruns to a total.

Both go into the reply to a version request (`0x1c`). Stock YAM sends 2 bytes
(ROM version). SHOOZ appends `family` (2), version (`0x01` = 0.1),
`WAVEFORM_LAST`, patch layout (1), free stack and glitch count. Editors that
read only the first 2 bytes keep working. Read it with
`python utils/shooz_sysex.py --in X --out Y version`.

### M3 — S4 vintage drift

A global system setting **`vint`** (0–127, 0 = off), in the stock `padding`
byte of `SystemSettings` (stock ignores it). It's on the system **MIDI** page
next to master tuning, in the 4th slot that stock filled with a duplicate of
`midi out`.

A slow random walk (new random targets every ~260 ms, smoothed over a similar
time) adds, at full amount:
- up to ±6 cents to both oscillators,
- up to ±6 cents to oscillator 2 against oscillator 1, so the beating drifts,
- up to ±4/256 to the cutoff.

It has its own 16-bit LFSR, so the shared `Random` state (noise, random
modulation source) is unchanged. It runs after the modulation matrix and adds
to its outputs. The rest of `ProcessBlock` is untouched.

### M4 — S5 tempo table

`lut_res_tempo_phase_increment` (201 × 32-bit, 804 B) held
`2^31 · 24 · bpm / (60 · control rate)`. `Clock::Update` now computes
`bpm × 876173`. The error is at most 78 in 35 million (~0.0001 BPM). The table
is removed from `resources/lookup_tables.py`.

### M5 — S2 envelope curves

Each envelope gets a curve preset 0–7:

| Preset | Shape (all segments) |
|---|---|
| 0 | exponential (stock) |
| 1–3 | toward linear |
| 4 | linear |
| 5–6 | toward inverse exponential |
| 7 | inverse exponential (slow start: swelling attacks, held decays) |

These are BAMBI's continuous curve values 0, 16, 32, 48, 64, 85, 106 and 127,
using the same maths (`Envelope::Shape`).

**UI:** a new page **"env curves"** (`crv1`, `crv2`). It's in the envelope/LFO
button cycle after LFO 2 (ENV1 → ENV2 → LFO1 → LFO2 → curves), and in the
encoder page order between LFO 2 and the mod matrix. Knobs 3–4 repeat `crv2`
and their columns stay blank, the same trick stock uses on the MIDI page.

**MIDI:** NRPN 157/158 (MSB 1, LSB 29/30). Front-panel edits aren't echoed
(stock never echoes offsets ≥ 128), and the curves travel in the patch SysEx
dump.

### M6 — release (not started)

Version string `SHOOZ v0.1` on the splash page, `SHOOZ.md` release notes,
tag `shooz-0.1` (pre-release) with the `.syx`.

## 3. Risks

| Risk | Mitigation |
|---|---|
| Stack overflow | M2 reads the real margin; gate ≥ 96 B before release |
| CPU overrun from per-block extras | Glitch counter in the version reply; the extras cost ~200 cycles per block, of ~20,000 |
| SHOOZ patches with curves on stock YAM | Refused cleanly by the `'&'` marker (name shows `--------`) |
| Other editors writing the patch's `extra_data_[1]` | Only the dump/receive path touches it; a stock editor that sends a stock patch just resets the curves to 0 |
| Can't test on hardware myself | One `.syx` plus [HARDWARE_TESTS.md](HARDWARE_TESTS.md); stock YAM `.syx` for rollback |

## 4. Not in wave 1

- **S3** filter-board profiles: done after wave 1 (+400 B flash, 276 B
  free; the version reply grows to 11 bytes).
- **S5 rest:** dropping the user wavetable (−1,033 B RAM). Needs §5.3.
- Front-panel echo of the curve edits (needs an NRPN MSB in `OnEdit`).
- SHED support for Shruthi/SHOOZ (protocol and parameter map).

## 5. Decisions

1. **Envelope curves storage:** decided 2026-11-26, **option A** (per patch,
   8 presets, `'&'` marker).
2. **Filter boards** (S3): which board setting do your CS-80 and IR3109
   boards run under now (LPF / SSM / 4PM / …)? No longer blocks S3: the
   profile is chosen separately from the board setting. Still useful to
   know (HARDWARE_TESTS.md §S3 asks).
3. **User wavetable:** is dropping it acceptable to free 1 KB of RAM? With
   944 B of flash free, this is now only needed if wave 2 runs short of RAM.
