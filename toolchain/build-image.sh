#!/usr/bin/env bash
# Builds the ambika-squeeze:4.3.5 toolchain image without `docker build`.
#
# Needed where Docker's default seccomp profile blocks the 32-bit socket
# syscalls used by Squeeze's i386 apt (GitHub Actions runners: "socket (38:
# Function not implemented)"), and the old resolver can't use the host's DNS.
# The packages are installed in a container with seccomp relaxed and the
# archive host pinned, then the container is committed as the image. Only
# this one-time install step runs unconfined; compiles use the default
# profile with --network none.
#
# Where `docker build` works (e.g. Docker Desktop) you can use
# Dockerfile.squeeze-i386 instead; both produce the same toolchain.
#
# Usage: toolchain/build-image.sh
set -euo pipefail
HERE="$(cd "$(dirname "$0")" && pwd)"
IMAGE="${AVR_IMAGE:-ambika-squeeze:4.3.5}"
BASE="$(sed -n 's/^FROM //p' "$HERE/Dockerfile.squeeze-i386" | head -1)"
NAME="ambika-squeeze-build-$$"

IP="$(getent ahostsv4 archive.debian.org 2>/dev/null | awk 'NR==1 {print $1}' || true)"
ADD_HOST=()
if [ -n "$IP" ]; then
  echo "archive.debian.org -> $IP"
  ADD_HOST=(--add-host "archive.debian.org:$IP")
fi

docker rm -f "$NAME" >/dev/null 2>&1 || true
docker run --name "$NAME" --platform linux/386 \
  --security-opt seccomp=unconfined "${ADD_HOST[@]}" \
  -v "$HERE/install-packages.sh:/tmp/install-packages.sh:ro" \
  "$BASE" sh /tmp/install-packages.sh
docker commit --change 'WORKDIR /work' "$NAME" "$IMAGE" >/dev/null
docker rm "$NAME" >/dev/null
docker run --rm --platform linux/386 --network none "$IMAGE" \
  sh -c 'avr-gcc --version | head -1'
