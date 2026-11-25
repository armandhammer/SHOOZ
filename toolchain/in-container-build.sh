#!/bin/sh
# Runs inside the ambika-squeeze image. Called by avr-make.sh.
#   $1 = makefile (relative to the tree), $2 = target name, rest = make args
# /src = source tree (bind mount), /w = tmpfs scratch.
set -e
MAKEFILE="$1"; TARGET="$2"; shift 2

cd /src
tar cf - --exclude=.git --exclude=hardware_design --exclude=build \
  --exclude=yam_firmware_builds --exclude=documentation . | (cd /w && tar xf -)
cd /w

# Some trees were generated on Windows: '#include "controller\resources.h"'.
# Normalize backslashes inside #include lines (scratch copy only).
for f in $(grep -rl '^#include ".*\\' --include=*.cc --include=*.h . 2>/dev/null); do
  sed -i '/^#include "/ s#\\#/#g' "$f"
done

make -f "$MAKEFILE" \
  AVRLIB_TOOLS_PATH=/usr/bin/ AR=/usr/bin/avr-ar \
  OBJCOPY=/usr/bin/avr-objcopy OBJDUMP=/usr/bin/avr-objdump \
  SIZE=/usr/bin/avr-size NM=/usr/bin/avr-nm \
  "EXTRA_LD_FLAGS=,-Map=build/$TARGET/$TARGET.map" \
  "$@"

ELF="build/$TARGET/$TARGET.elf"
if [ -f "$ELF" ]; then
  avr-size "$ELF" > "build/$TARGET/$TARGET.size"
  avr-nm --size-sort -C -r -f bsd "$ELF" > "build/$TARGET/$TARGET.top_symbols"
fi

mkdir -p /src/build
rm -rf "/src/build/$TARGET"
cp -r "build/$TARGET" /src/build/
