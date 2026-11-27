# SHOOZ

Firmware for the Mutable Instruments **Shruthi-1** hybrid monosynth, built on
top of [YAM](https://github.com/bjoeri/shruthi-1) ("Yet Another Mutation") by
bjoeri, itself based on the original firmware by Emilie Gillet.

SHOOZ is the Shruthi sibling of [BAMBI](https://github.com/armandhammer/BAMBI)
(Ambika) and shares its goals: sound and playability for a performance/sound
design synth, no groovebox features, and it has to work with any filter board
(SMR4, CS-80, IR3109, Polivoks, …).

> **Status:** wave 1 and the filter calibration page are implemented and
> build, with 276 B of flash free (YAM 0.05 had 960 B). They have **not been
> tested on hardware** yet. See [docs/PLAN.md](docs/PLAN.md) and the checklist in
> [docs/HARDWARE_TESTS.md](docs/HARDWARE_TESTS.md).

What SHOOZ adds to YAM 0.05:

- **Upstream 1.03 fixes:** the arpeggiator starts on the first key with an
  external clock, legato sequencer steps tie, Stop no longer cuts held notes
  in step mode, and release tails fade out fully.
- **Envelope curves:** each envelope gets a curve preset (0 = stock
  exponential, 4 = linear, 7 = inverse exponential), saved with the patch.
  They're on the new **env curves** page after LFO 2.
- **Vintage drift:** a global `vint` setting (system → MIDI page). The pitch,
  oscillator 2 against oscillator 1, and the cutoff wander slowly, like an
  old analog monosynth.
- **Filter calibration:** a 4th system page, **filter cal**, voices the
  analog filter board per unit: a profile (`cs80`, `ir31`, `pvk`, `smr4`)
  sets the resonance taper, level compensation and resonance → cutoff
  shift; `cofs` offsets the cutoff so patches match across units; `rmax`
  caps the resonance. `off` (the default) is stock.
- **Diagnostics for editors:** the SysEx version reply identifies SHOOZ and
  reports the worst-case free stack and audio glitch count
  (`utils/shooz_sysex.py`).

Patches that use envelope curves are saved with a new format marker that
stock YAM refuses cleanly (it keeps the current sound). Patches without
curves are identical to stock.

The original YAM readme is in [README](README).

## Building

Shruthi must be built with **avr-gcc 4.3.5 / avr-libc 1.6.8**: newer
compilers miscompile the oscillator code.

```sh
git clone --recursive https://github.com/armandhammer/SHOOZ.git
cd SHOOZ
docker build --platform linux/386 -t ambika-squeeze:4.3.5 \
  -f toolchain/Dockerfile.squeeze-i386 toolchain   # once, needs network
bash toolchain/avr-make.sh . shruthi/makefile syx  # build/shruthi1/shruthi1.syx
bash toolchain/size-report.sh .                    # flash/RAM + gates
```

Install the `.syx` with the Shruthi's MIDI firmware update procedure (see the
Shruthi-1 manual). CI builds every push (`.github/workflows/build.yml`).

## License

GPL-3.0, like the original firmware (see the source file headers). Hardware
files keep their original licenses.
