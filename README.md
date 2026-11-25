# SHOOZ

Firmware for the Mutable Instruments **Shruthi-1** hybrid monosynth, built on
top of [YAM](https://github.com/bjoeri/shruthi-1) ("Yet Another Mutation") by
bjoeri, itself based on the original firmware by Emilie Gillet.

SHOOZ is the Shruthi sibling of [BAMBI](https://github.com/armandhammer/BAMBI)
(Ambika) and shares its goals: sound and playability for a performance/sound
design synth, no groovebox features, and it has to work with any filter board
(SMR4, CS-80, IR3109, Polivoks, …).

> **Status:** setup only. This branch builds YAM 0.05 unchanged with the
> pinned toolchain. Planned first changes (see BAMBI
> [docs/AUDIT.md](https://github.com/armandhammer/BAMBI/blob/main/docs/AUDIT.md),
> "Shruthi"): upstream 1.03 sequencer/arpeggiator fixes, envelope curves
> shared with BAMBI, filter-board profiles, vintage drift. Shruthi has only
> ~960 B of flash and ~280 B of stack left, so each change needs care.

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
