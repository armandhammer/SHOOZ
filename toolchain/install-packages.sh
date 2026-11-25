#!/bin/sh
# Installs the AVR toolchain into the Debian Squeeze i386 base image.
# Used by Dockerfile.squeeze-i386 and by CI (see build-image.sh).
#
# python-numpy: needed by the avrlib resource compiler (lookup tables,
# waveforms).
set -e
apt-get update -qq
apt-get install -y --no-install-recommends \
  gcc-avr avr-libc binutils-avr \
  make python python-numpy
apt-get clean
rm -rf /var/lib/apt/lists/*
