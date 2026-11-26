#!/usr/bin/env python3
"""SHOOZ Shruthi-1 SysEx client: version/diagnostics and patch dumps.

Usage:
  python utils/shooz_sysex.py --selftest           # offline framing test
  python utils/shooz_sysex.py --list               # list MIDI ports
  python utils/shooz_sysex.py --in "X" --out "Y" version
  python utils/shooz_sysex.py --in "X" --out "Y" patch

Live use needs: pip install mido python-rtmidi

Frame (Mutable Instruments): F0 00 21 02 00 02 <cmd> <arg> <payload as
hi/lo nibbles> <checksum hi> <checksum lo> F7, checksum = sum(payload) & 0xff.

The version reply (0x0c) is 2 bytes on stock YAM. SHOOZ appends: family
(2 = SHOOZ), SHOOZ version (0xMm), number of oscillator shapes, patch
layout, worst-case free stack since boot (bytes, max 255) and audio
glitches (buffer underruns) since boot.
"""

import argparse
import sys
import time

HEADER = [0x00, 0x21, 0x02, 0x00, 0x02]  # MI manufacturer id + Shruthi-1.


def encode(command, argument=0, payload=()):
  """Returns the SysEx data bytes (without F0/F7, as mido expects)."""
  data = list(HEADER) + [command & 0x7f, argument & 0x7f]
  checksum = 0
  for byte in payload:
    data += [byte >> 4, byte & 0x0f]
    checksum = (checksum + byte) & 0xff
  data += [checksum >> 4, checksum & 0x0f]
  return data


def decode(data):
  """Parses SysEx data bytes (without F0/F7). Returns (cmd, arg, payload)."""
  data = list(data)
  if data[:5] != HEADER:
    raise ValueError('not a Shruthi SysEx message')
  command, argument = data[5], data[6]
  nibbles = data[7:]
  if len(nibbles) % 2:
    raise ValueError('odd number of nibbles')
  raw = [(nibbles[i] << 4) | nibbles[i + 1] for i in range(0, len(nibbles), 2)]
  payload, checksum = raw[:-1], raw[-1]
  if sum(payload) & 0xff != checksum:
    raise ValueError('bad checksum')
  return command, argument, payload


def describe_version(payload):
  lines = ['ROM version %d.%d' % (payload[0], payload[1])]
  if len(payload) < 8:
    lines.append('stock YAM (no SHOOZ capability bytes)')
    return '\n'.join(lines)
  family, version, shapes, layout, stack, glitches = payload[2:8]
  lines.append('family %s, version %d.%d, oscillator shapes %d, '
               'patch layout %d' % ('SHOOZ' if family == 2 else family,
                                    version >> 4, version & 15, shapes,
                                    layout))
  lines.append('free stack (worst case since boot): %d B%s' % (
      stack, '' if stack >= 96 else '  << below the 96 B gate'))
  lines.append('audio glitches since boot: %d%s' % (
      glitches, '+' if glitches == 255 else ''))
  return '\n'.join(lines)


def describe_patch(payload):
  name = ''.join(chr(c) for c in payload[68:76]).rstrip()
  marker = chr(payload[91]) if len(payload) > 91 else '?'
  lines = ['patch "%s", format marker %r' % (name, marker)]
  if marker == '&':
    curves = payload[77]
    lines.append('envelope curves: env1 %d, env2 %d (0 = stock, 4 = linear, '
                 '7 = inverted)' % ((curves >> 2) & 7, curves >> 5))
  else:
    lines.append('envelope curves: stock')
  return '\n'.join(lines)


def describe(command, argument, payload):
  if command == 0x0c:
    return describe_version(payload)
  if command == 0x01:
    return describe_patch(payload)
  return 'command 0x%02x, argument %d, %d bytes' % (
      command, argument, len(payload))


def selftest():
  # Round trip, including bytes with the high bit set.
  payload = [0, 1, 0x7f, 0x80, 0xff, 0x55]
  assert decode(encode(0x01, 3, payload)) == (0x01, 3, payload)
  # Requests carry an empty payload and a 00 00 checksum.
  assert encode(0x1c) == HEADER + [0x1c, 0x00, 0x00, 0x00]
  # A SHOOZ version reply as the firmware builds it.
  text = describe(*decode(encode(0x0c, 0, [1, 0, 2, 0x01, 43, 1, 180, 3])))
  assert 'SHOOZ, version 0.1' in text and '180 B' in text, text
  assert 'glitches since boot: 3' in text, text
  # A stock reply.
  assert 'stock YAM' in describe(*decode(encode(0x0c, 0, [1, 0])))
  # A patch with curves 3 and 7.
  patch = [0] * 92
  patch[68:76] = [ord(c) for c in 'BASS    ']
  patch[77] = 1 | (3 << 2) | (7 << 5)
  patch[91] = ord('&')
  text = describe(*decode(encode(0x01, 0, patch)))
  assert '"BASS"' in text and 'env1 3, env2 7' in text, text
  # Corruption is detected.
  bad = encode(0x01, 0, [1, 2, 3])
  bad[-1] ^= 1
  try:
    decode(bad)
    raise AssertionError('checksum not checked')
  except ValueError:
    pass
  print('selftest: ok')


def main():
  parser = argparse.ArgumentParser(description=__doc__.split('\n')[0])
  parser.add_argument('request', nargs='?', choices=['version', 'patch'])
  parser.add_argument('--in', dest='inport')
  parser.add_argument('--out', dest='outport')
  parser.add_argument('--selftest', action='store_true')
  parser.add_argument('--list', action='store_true')
  args = parser.parse_args()

  if args.selftest:
    selftest()
    return
  import mido  # Only needed for live use.
  if args.list:
    print('inputs: ', mido.get_input_names())
    print('outputs:', mido.get_output_names())
    return
  if not (args.request and args.inport and args.outport):
    parser.error('request, --in and --out are required')

  data = encode(0x1c if args.request == 'version' else 0x11)
  with mido.open_input(args.inport) as inp, mido.open_output(args.outport) as out:
    out.send(mido.Message('sysex', data=data))
    deadline = time.time() + 3.0
    while time.time() < deadline:
      for msg in inp.iter_pending():
        if msg.type != 'sysex':
          continue
        try:
          print(describe(*decode(msg.data)))
        except ValueError as e:
          print('ignored message:', e)
      time.sleep(0.01)


if __name__ == '__main__':
  sys.exit(main())
