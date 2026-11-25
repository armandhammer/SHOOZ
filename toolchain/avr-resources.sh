#!/usr/bin/env bash
# Regenerate (or check) a target's resources.{cc,h} inside the pinned image.
#
# Usage: toolchain/avr-resources.sh <source-tree> <makefile> [check|write]
#   check (default): exit 1 if the regenerated files differ from the tree.
#   write:           copy the regenerated files into the tree.
set -euo pipefail

TREE="${1:?usage: $0 <source-tree> <makefile> [check|write]}"
MAKEFILE="${2:?usage: $0 <source-tree> <makefile> [check|write]}"
MODE="${3:-check}"
IMAGE="${AVR_IMAGE:-ambika-squeeze:4.3.5}"
HERE="$(cd "$(dirname "$0")" && { pwd -W 2>/dev/null || pwd; })"
TREE_ABS="$(cd "$TREE" && { pwd -W 2>/dev/null || pwd; })"

# On Linux, run as the calling user (see avr-make.sh).
USER_OPT=()
if [ "$(uname -s)" = Linux ]; then
  USER_OPT=(--user "$(id -u):$(id -g)")
fi

MSYS_NO_PATHCONV=1 exec docker run --rm \
  --platform linux/386 \
  --network none \
  --cap-drop=ALL \
  "${USER_OPT[@]}" \
  --tmpfs /w:exec,size=512m,mode=1777 \
  -v "$TREE_ABS:/src" \
  -v "$HERE:/toolchain:ro" \
  "$IMAGE" \
  sh /toolchain/in-container-resources.sh "$MAKEFILE" "$MODE"
