# SHOOZ wave 1 — hardware checks

Flash `build/shruthi1/shruthi1.syx` with the Shruthi's MIDI firmware update
procedure (see the Shruthi-1 manual).
Keep the stock YAM 0.05 `.syx` (`yam_firmware_builds/`) for rollback.

The SysEx reads below use `python utils/shooz_sysex.py` (needs
`pip install mido python-rtmidi`; `--list` shows the port names).

Please report: the **free stack** and **glitch** readings, and pass/fail
for each item.

## 0. Boot and settings

- [ ] The synth boots and plays a stock patch as before.
- [ ] Your system settings (MIDI channel, filter board, etc.) survived the
      update. They should: SHOOZ keeps the same settings layout.

## M2 — diagnostics (do this first, and again at the end)

- [ ] `shooz_sysex.py --in X --out Y version` prints `family SHOOZ,
      version 0.1`.
- [ ] Play hard for a few minutes: fast arpeggio on external clock, heavy
      modulation, switch patches, open the patch browser, send SysEx dumps.
      Then read `version` again. **Free stack ≥ 96 B** passes. Note the
      number either way.
- [ ] **Glitches since boot** stays at 0, or close to it, and the display
      doesn't flash `!` in normal playing.

## M1 — upstream 1.03 fixes

- [ ] Arpeggiator on **external** MIDI clock, transport running, no keys
      held: the first key you press starts the arpeggio straight away,
      instead of waiting for the next clock step.
- [ ] Sequencer mode with some steps set to legato: legato steps tie into
      the next step.
- [ ] Step sequencer mode: Stop doesn't cut a note you are holding.
- [ ] A patch with a long release: the tail fades out smoothly to silence,
      with no step at the very end.

## M3 — vintage drift

- [ ] System → MIDI page, 4th knob shows `vint`. 0 sounds exactly like
      before.
- [ ] Two detuned saws, `vint` 127, a held note: the pitch and the beating
      between the oscillators wander slowly. At 127 it should be clearly
      audible but not seasick; tell me if it's too much or too little.
- [ ] A resonant filter patch: the cutoff wanders slightly with `vint` up.
- [ ] Power-cycle: `vint` keeps its value (it's saved with the system
      settings).

## M4 — tempo

- [ ] Internal clock at 40, 120 and 240 BPM: the arpeggiator/sequencer runs
      at the right tempo. Compare against a metronome or DAW if you can.

## M5 — envelope curves

- [ ] Press the envelope/LFO button repeatedly: after LFO 2 comes
      **env curves** with `crv1` and `crv2`, then envelope 1 again.
- [ ] 0 sounds exactly like before. 4 gives linear segments. 7 gives a slow
      swelling attack and decays that hold, then drop.
- [ ] Save a patch with curves, load another patch, then reload it: the
      curves come back.
- [ ] Save a patch with both curves at 0: it still loads on stock YAM
      (optional; needs reflashing stock).
- [ ] `shooz_sysex.py ... patch` shows the curves of the current patch.

## Native-test fixes (see DECISIONS.md, 2026-11-26)

These changed code that every edit goes through, so they need a broad
check even though the native tests pass.

- [ ] **Every page edits as before.** Turn each knob on every page
      (oscillators, mixer, filter, envelopes, LFOs, env curves, mod
      matrix rows 1 and 12, operators, sequencer, system pages); the value
      changes and the sound follows. (Parameter access was rewritten.)
- [ ] **System settings survive a power cycle**: change MIDI channel,
      filter board and `vint`, power off and on.
- [ ] **Old patches load unchanged**: load several stock and pre-SHOOZ
      patches from internal and external banks and compare with how you
      remember them. (Loads are now clamped to valid ranges; valid data
      must not change.)
- [ ] **Foreign SysEx is ignored**: request a patch dump
      (`shooz_sysex.py ... patch`), then send any other device's SysEx
      (e.g. a universal identity request from a DAW or MIDI-OX, or the
      3 bytes `F0 7D F7`). The Shruthi must not send a second dump.
- [ ] **Out-of-range patch write is refused**: a patch write request
      (0x21) to slot 9999 shows `#` on the display and changes nothing.
- [ ] **Wavequence at the top**: oscillator 1 = `wavqnc`, parameter swept
      to 127. The last step sounds like the one before it (no burst of
      noise).
- [ ] **CSaw with parameter 0-10**: clean saw, no clicks or grit compared
      with parameter 11+.
- [ ] **Tempo pot fully down** shows `ext`, never `38`.
