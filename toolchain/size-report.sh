#!/usr/bin/env bash
# Print flash/RAM usage of built Ambika (or Shruthi) targets, the delta against
# a saved baseline, and enforce the YAM+ resource gates from PLAN.md.
#
# Usage: toolchain/size-report.sh <source-tree> [--save-baseline]
#   Reads <tree>/build/<target>/<target>.size written by avr-make.sh.
#   Baseline is stored in <tree>/build/size-baseline.txt (one line per target).
# Exit status 1 if any gate fails.
set -euo pipefail

TREE="${1:?usage: $0 <source-tree> [--save-baseline]}"
SAVE="${2:-}"
BASE="$TREE/build/size-baseline.txt"

# target   flash cap (app area)   RAM   min flash free   min RAM free (static)
GATES="ambika_controller 61440 4096 512 225
ambika_voicecard 32256 2048 2048 768
shruthi1 64512 4096 256 200"

fail=0
printf '%-18s %8s %8s %8s %9s %8s %8s\n' target flash free Δflash staticRAM free ΔRAM
NEW=""
while read -r tgt cap ram min_flash min_ram; do
  f="$TREE/build/$tgt/$tgt.size"
  [ -f "$f" ] || continue
  read -r text data bss < <(awk 'NR==2 {print $1, $2, $3}' "$f")
  flash=$((text + data)); sram=$((data + bss))
  ffree=$((cap - flash)); rfree=$((ram - sram))
  dflash="-"; dram="-"
  if [ -f "$BASE" ]; then
    b=$(awk -v t="$tgt" '$1==t {print $2, $3}' "$BASE")
    if [ -n "$b" ]; then
      read -r bflash bram <<<"$b"
      dflash=$(printf '%+d' $((flash - bflash))); dram=$(printf '%+d' $((sram - bram)))
    fi
  fi
  flag=""
  if [ "$ffree" -lt "$min_flash" ]; then flag="$flag FLASH<$min_flash"; fail=1; fi
  if [ "$rfree" -lt "$min_ram" ]; then flag="$flag RAM<$min_ram"; fail=1; fi
  printf '%-18s %8d %8d %8s %9d %8d %8s%s\n' "$tgt" "$flash" "$ffree" "$dflash" "$sram" "$rfree" "$dram" "${flag:+  GATE FAIL:$flag}"
  NEW="$NEW$tgt $flash $sram"$'\n'
done <<<"$GATES"

if [ "$SAVE" = "--save-baseline" ]; then
  printf '%s' "$NEW" > "$BASE"
  echo "baseline saved to $BASE"
fi
echo "Note: RAM figures are static (.data+.bss). Stack headroom must be checked"
echo "on hardware with the OS-info page stack probe (gate: >= 96 B free)."
exit $fail
