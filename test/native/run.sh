#!/usr/bin/env bash
# Build and run the native firmware tests.
#
# Usage: test/native/run.sh [test-name-filter]
#
# Uses the host g++ on Linux when it exists, otherwise Docker image gcc:14
# (Windows/macOS). The build tree is build/native (git-ignored).
set -euo pipefail
cd "$(dirname "$0")/../.."
FILTER="${1:-}"
if [ "$(uname -s)" = Linux ] && command -v g++ >/dev/null; then
  exec make -f test/native/makefile -j"$(nproc)" TEST="$FILTER"
fi
ROOT="$(pwd -W 2>/dev/null || pwd)"
# Build in a container-local copy of the tree: make needs sane timestamps,
# and this keeps Linux objects out of the Windows checkout.
MSYS_NO_PATHCONV=1 exec docker run --rm -v "$ROOT:/src:ro" gcc:14 bash -c "
  set -e
  mkdir -p /w && cd /src
  tar --exclude=./build --exclude=./.git -cf - . | tar -C /w -xf -
  cd /w
  make -f test/native/makefile -j\$(nproc) TEST='$FILTER'
"
