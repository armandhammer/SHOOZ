# Native firmware tests

The SHOOZ firmware compiled for the host (x86-64 g++) and driven by unit
tests. No Shruthi and no AVR simulator needed.

```sh
test/native/run.sh                        # build + run (Docker gcc:14 off Linux)
test/native/run.sh SysEx                  # tests whose name contains "SysEx"
make -f test/native/makefile SANITIZE=1   # same, with AddressSanitizer (Linux)
```

CI runs the plain and the AddressSanitizer build on every push
(`.github/workflows/build.yml`, job `native-tests`).

## What runs

One binary, `shruthi_tests`, links every file in `shruthi/` and `avrlib/`
except `diagnostics.cc` (it paints RAM from `.init3`), the Wii nunchuk
driver, and `avrlib/time.cc` (a patched copy is used). `shruthi.cc` is
linked with `main` renamed, so `FillAudioBuffer()` and the filter-board CV
code are the real ones.

`harness/shruthi_env.*` is a headless Shruthi:

- MIDI bytes go into the real `MidiStreamParser`; MIDI out is collected
  from the dispatcher's buffer and from direct UART writes (SysEx dumps).
- `Render(n)` runs `FillAudioBuffer()` and the 40 kHz sample ISR for n
  blocks, capturing the 8-bit audio and the cutoff/resonance/VCA/CV1/CV2
  PWM values after each block. UART 1 (the DSP filter board stream) is
  captured too.
- `SysEx()`, `ParseSysEx()` and `Request()` build and decode Mutable
  Instruments SysEx (nibbles, checksum).
- Internal EEPROM is a 2 KB array, the I2C patch EEPROM a 64 KB array
  (`stubs/avrlib/devices/external_eeprom.h`).

| File | Covers |
|---|---|
| `tests/layout.cc` | parameter offsets → patch/sequencer/system/curve bytes |
| `tests/envelope.cc` | stages, the 8 SHOOZ curve presets (monotonic, ordered, same duration, linear, mirror) |
| `tests/parameters.cc` | parameter table ranges, offset/CC maps, Scale/Increment/Clamp, NRPN for every parameter, curves NRPN, tempo clock accuracy |
| `tests/sysex.cc` | version/bank replies, patch round trip, `'&'` curve marker, checksums, truncation, foreign messages, write/load slots, bulk blocks, sanitizing |
| `tests/voice.cc` | note on/off, every oscillator shape, extremes, curves on the VCA, vintage drift bounds (cutoff and pitch), every filter-board CV path |
| `tests/filter_cal.cc` | S3 filter calibration: stock CVs when off, every profile's taper/level/cutoff bounds, cutoff offset clipping, resonance max, NRPN ranges, EEPROM save/load/clamping, value labels and neighbouring string lists |
| `tests/fuzz.cc` | random channel messages, random NRPN/SysEx payloads, raw byte garbage |

## Parameter export for SHED

`make -f test/native/makefile export` builds `tools/export_params.cc`
against the same objects and prints the parameter table (offsets, units,
ranges, CCs, NRPN ownership), the LCD text for every value, the init
patch/sequencer/system data and the SHOOZ capability values as JSON. SHED's
Shruthi map (`src/model/params/shooz-params.json`) is this output; rerun it
whenever `parameter.cc`, the string table or the init patch change.

## How the firmware compiles on a PC

Same approach as BAMBI's harness:

- `shim/avr/*.h` replace avr-libc (registers in a byte array, PROGMEM as
  ordinary memory, EEPROM as an array).
- The makefile copies a few avrlib/firmware headers into
  `build/native/override/` with `sed` patches, so the avrlib submodule stays
  pristine; each patch is checked and the build fails if it stops applying:
  busy-wait loops call `AVRLIB_BUSY_WAIT()` (the harness plays the
  interrupts), UART writes are reported, missing `return` statements are
  added, `op.h` uses its C fallbacks, and `BufferedDisplay::Print` tests the
  row count before reading the next character.

## Things the native build is strict about

- **Non-void functions without `return`.** avr-gcc 4.3.5 returns whatever
  is in r24; modern g++ treats falling off the end as unreachable and drops
  the code after the call. `TransientGenerator::Trigger()` was one: under
  the native build, every note-on fell into an ASan report.
- **Memory layout.** Stock reached parameters through
  `data_access_byte_[offset + 1]`, which assumed the patch, sequencer and
  system settings sat back to back; SHOOZ uses `Part::parameter_address()`.
  `SystemSettings` is packed so the host has the AVR's 15-byte layout.
- **Host `int` is 32-bit**, so AVR 16-bit promotion bugs aren't reproduced.
  The AVR build and size gates still run in CI.
- **State survives `Boot()`** where real RAM wouldn't (oscillator phases,
  the RNG). Tests compare properties, not sample-exact renders across boots.
