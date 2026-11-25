#!/usr/bin/env bash
# Run a make target inside the pinned avr-gcc 4.3.5 (Debian Squeeze i386) image.
#
# Usage: toolchain/avr-make.sh <source-tree> <makefile> [make args...]
#   e.g. toolchain/avr-make.sh refs/ambika-yam controller/makefile bin
#
# Output: <tree>/build/<target>/ with .elf/.bin/.hex, .map, .size, .top_symbols.
# The compile runs with no network and no capabilities.
#
# Why i386: Squeeze's amd64 glibc needs vsyscall, which Docker Desktop's WSL2
# kernel disables (apt segfaults). The i386 userland doesn't use it, and the
# AVR cross-compiler output doesn't depend on the host architecture.
# Why the tmpfs copy: the 32-bit compiler can't stat files on the Windows bind
# mount (64-bit inode numbers -> EOVERFLOW). See in-container-build.sh.
set -euo pipefail

TREE="${1:?usage: $0 <source-tree> <makefile> [make args...]}"
MAKEFILE="${2:?usage: $0 <source-tree> <makefile> [make args...]}"
shift 2
IMAGE="${AVR_IMAGE:-ambika-squeeze:4.3.5}"
HERE="$(cd "$(dirname "$0")" && { pwd -W 2>/dev/null || pwd; })"
TREE_ABS="$(cd "$TREE" && { pwd -W 2>/dev/null || pwd; })"
TARGET="$(sed -n 's/^TARGET *= *//p' "$TREE/$MAKEFILE" | head -1 | tr -d '\r ')"

MSYS_NO_PATHCONV=1 exec docker run --rm \
  --platform linux/386 \
  --network none \
  --cap-drop=ALL \
  --tmpfs /w:exec,size=512m \
  -v "$TREE_ABS:/src" \
  -v "$HERE:/toolchain:ro" \
  "$IMAGE" \
  sh /toolchain/in-container-build.sh "$MAKEFILE" "$TARGET" "$@"
