# Native (host) unit tests for the SHOOZ (Shruthi) firmware.
#
# Run from the repository root on Linux (or via test/native/run.sh, which
# uses Docker image gcc:14 on Windows/macOS):
#   make -f test/native/makefile             # build and run everything
#   make -f test/native/makefile TEST=Curve  # tests whose name contains Curve
#   make -f test/native/makefile SANITIZE=1  # with AddressSanitizer
#
# The firmware sources are compiled unmodified with the host g++ against the
# shims in test/native/shim (fake AVR registers, EEPROM, PROGMEM) and the
# stubs in test/native/stubs (the I2C patch EEPROM). A few avrlib headers
# that busy-wait on interrupt-driven buffers, use AVR assembly, or lack
# return statements are copied into $(BUILD)/override with a sed patch, so
# the avrlib submodule stays pristine. See test/native/README.md.

BUILD    ?= build/native
CXX      ?= g++
OPT      ?= -O1
COMMON   := $(OPT) -g -w -fshort-enums -ffunction-sections -fdata-sections \
            -DNATIVE_HOST_BUILD \
            -D__PROG_TYPES_COMPAT__ -DF_CPU=20000000L \
            -D__AVR_ATmega644P__ -DATMEGA644P -DSERIAL_RX_0 \
            -DDISABLE_DEFAULT_UART_RX_ISR \
            -include test/native/harness/native_hooks.h
ifeq ($(SANITIZE),1)
COMMON   += -fsanitize=address -fno-omit-frame-pointer
LDFLAGS  += -fsanitize=address
BUILD    := $(BUILD)-asan
endif
OVR      := $(BUILD)/override
INCLUDES := -I$(OVR) -Itest/native/stubs -Itest/native/shim \
            -Itest/native/harness -I.
CXXFLAGS := -std=gnu++98 -fno-exceptions $(COMMON)

OVERRIDES := $(OVR)/avrlib/op.h $(OVR)/avrlib/ring_buffer.h \
             $(OVR)/avrlib/serial.h \
             $(OVR)/avrlib/avrlib.h $(OVR)/avrlib/devices/hd44780_lcd.h \
             $(OVR)/avrlib/audio_output.h $(OVR)/shruthi/midi_dispatcher.h \
             $(OVR)/avrlib/devices/buffered_display.h

# diagnostics.cc paints RAM up to RAMEND from .init3; the harness stubs it.
# The external EEPROM is replaced by
# test/native/stubs/avrlib/devices/external_eeprom.h, so the I2C driver
# isn't needed (the Wii nunchuk driver isn't used by the Shruthi).
# avrlib/time.cc busy-waits on the millisecond counter: patched copy.
FW_CC   := $(filter-out shruthi/diagnostics.cc avrlib/devices/wii_nunchuk.cc \
                        avrlib/time.cc, \
             $(wildcard avrlib/*.cc avrlib/devices/*.cc shruthi/*.cc)) \
           $(OVR)/avrlib/time.cc
TESTS   := $(wildcard test/native/tests/*.cc)
HARNESS := test/native/harness/test_main.cc test/native/harness/shruthi_env.cc
SRCS    := $(FW_CC) $(TESTS) $(HARNESS)
OBJS    := $(patsubst %,$(BUILD)/obj/%.o,$(SRCS))

all: run

$(BUILD)/shruthi_tests: $(OBJS)
	$(CXX) $(LDFLAGS) -Wl,--gc-sections -o $@ $^

run: $(BUILD)/shruthi_tests
	@$(BUILD)/shruthi_tests $(TEST)

# shruthi.cc holds the firmware main() and the ISRs.
$(BUILD)/obj/shruthi/shruthi.cc.o: EXTRA := -Dmain=firmware_main

$(BUILD)/obj/%.cc.o: %.cc $(OVERRIDES)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(EXTRA) $(INCLUDES) -MMD -c $< -o $@

# Generated header overrides. Each sed must change something: the check
# after it fails the build if upstream code moved.
$(OVR)/avrlib/op.h: avrlib/op.h
	@mkdir -p $(dir $@)
	sed -e '/^#define USE_OPTIMIZED_OP/d' \
	    -e '/uint32_t difference = av - bv;/{n;s/sum >> 8/difference >> 8/;n;s/sum & 0xff/difference \& 0xff/;}' \
	    $< > $@
	! grep -q '^#define USE_OPTIMIZED_OP' $@
	grep -q 'result.fractional = difference & 0xff' $@

$(OVR)/avrlib/ring_buffer.h: avrlib/ring_buffer.h
	@mkdir -p $(dir $@)
	sed -e 's/while (!writable());/while (!writable()) { AVRLIB_BUSY_WAIT(); }/' \
	    -e 's/while (!readable());/while (!readable()) { AVRLIB_BUSY_WAIT(); }/' \
	    $< > $@
	test "$$(grep -c AVRLIB_BUSY_WAIT $@)" = 2

$(OVR)/avrlib/audio_output.h: avrlib/audio_output.h
	@mkdir -p $(dir $@)
	sed 's/while (!writable());/while (!writable()) { AVRLIB_BUSY_WAIT(); }/' $< > $@
	grep -q AVRLIB_BUSY_WAIT $@

# UART transmit: report every byte written to a data register, so the
# harness sees what goes out on MIDI (UART 0) and to the DSP board (UART 1).
$(OVR)/avrlib/serial.h: avrlib/serial.h
	@mkdir -p $(dir $@)
	sed 's/{ \*DataRegister::ptr() = value; }/{ *DataRegister::ptr() = value; native_uart_tx(DataRegister::ptr(), value); }/' \
	    $< > $@
	grep -q native_uart_tx $@

# Delay() waits for the timer ISR to advance milliseconds(), and has no
# return statement (see below).
$(OVR)/avrlib/time.cc: avrlib/time.cc
	@mkdir -p $(dir $@)
	sed 's/  while (milliseconds() < t);/  while (milliseconds() < t) { AVRLIB_BUSY_WAIT(); }\n  return t;/' \
	    $< > $@
	grep -q 'return t;' $@

$(OVR)/shruthi/midi_dispatcher.h: shruthi/midi_dispatcher.h
	@mkdir -p $(dir $@)
	sed 's/while (OutputBuffer::readable());/while (OutputBuffer::readable()) { AVRLIB_BUSY_WAIT(); }/' \
	    $< > $@
	grep -q AVRLIB_BUSY_WAIT $@

# Non-void functions without a return statement: avr-gcc 4.3.5 returns
# garbage, but modern g++ treats reaching the end as unreachable and drops
# the code after the call.
$(OVR)/avrlib/avrlib.h: avrlib/avrlib.h
	@mkdir -p $(dir $@)
	sed 's/{ \*ptr() = value; }/{ *ptr() = value; return *this; }/' $< > $@
	test "$$(grep -c 'return \*this;' $@)" = 4

$(OVR)/avrlib/devices/hd44780_lcd.h: avrlib/devices/hd44780_lcd.h
	@mkdir -p $(dir $@)
	sed -e 's/static inline uint8_t Write(uint8_t character)/static inline void Write(uint8_t character)/' \
	    -e 's/static inline uint8_t Write(const char\* s)/static inline void Write(const char* s)/' \
	    -e 's/\(OutputBuffer::Overwrite2(LCD_[^;]*;\)/\1 return 1;/' \
	    $< > $@
	test "$$(grep -c 'static inline void Write(' $@)" = 2
	test "$$(grep -c 'Overwrite2(LCD_.*return 1;' $@)" = 2

# Print() tests *text before the row count, so a full 16-character line
# reads the byte after it (the edit overview page's second line ends the
# 33-byte line buffer). The value is never used; ASan flags it anyway.
$(OVR)/avrlib/devices/buffered_display.h: avrlib/devices/buffered_display.h
	@mkdir -p $(dir $@)
	sed 's/while (\*text && row)/while (row \&\& *text)/' $< > $@
	grep -q 'while (row && \*text)' $@

clean:
	rm -rf $(BUILD)

.PHONY: all run clean
-include $(OBJS:.o=.d)
