#!/bin/sh
# Runs inside the ambika-squeeze image. Called by avr-resources.sh.
#   $1 = makefile (e.g. controller/makefile), $2 = check | write
# Regenerates <RESOURCES>/../resources.{cc,h} with the avrlib resource compiler.
#   check: compare with the files in the tree (ignoring CR and the Windows '\'
#          in the generated #include line) and print a diff summary.
#   write: copy the regenerated files back into the tree.
set -e
MAKEFILE="$1"; MODE="${2:-check}"

cd /src
tar cf - --exclude=.git --exclude=hardware_design --exclude=build \
  --exclude=yam_firmware_builds --exclude=documentation . | (cd /w && tar xf - --no-same-owner)
cd /w

RES_DIR="$(sed -n 's/^RESOURCES *= *//p' "$MAKEFILE" | tr -d '\r ' | head -1)"
OUT_DIR="$(dirname "$RES_DIR")"
[ -n "$RES_DIR" ] || { echo "no RESOURCES in $MAKEFILE" >&2; exit 1; }

mkdir -p /w/orig
for f in resources.cc resources.h; do
  tr -d '\r' < "$OUT_DIR/$f" | sed '/^#include "/ s#\\#/#g' > "/w/orig/$f"
done

python avrlib/tools/resources_compiler.py "$RES_DIR/resources.py"

STATUS=0
for f in resources.cc resources.h; do
  if cmp -s "/w/orig/$f" "$OUT_DIR/$f"; then
    echo "$OUT_DIR/$f: identical"
  else
    echo "$OUT_DIR/$f: DIFFERS"
    diff -u "/w/orig/$f" "$OUT_DIR/$f" | head -40
    STATUS=1
  fi
done

if [ "$MODE" = "write" ]; then
  cp "$OUT_DIR/resources.cc" "$OUT_DIR/resources.h" "/src/$OUT_DIR/"
  echo "wrote $OUT_DIR/resources.{cc,h}"
  exit 0
fi
exit $STATUS
