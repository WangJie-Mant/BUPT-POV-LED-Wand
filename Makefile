# macOS build for the CH551G POV wand.
# Override SDCC_HOME when needed: make SDCC_HOME=/path/to/sdcc

SHELL := /bin/sh

SDCC_HOME ?= $(HOME)/Documents/sdcc
CH55X_SDK ?= $(CURDIR)/.sdcc-sdk/include
SDCC      := $(SDCC_HOME)/bin/sdcc
PACKIHX   := $(SDCC_HOME)/bin/packihx

BUILD  := build/sdcc
TARGET := $(BUILD)/pov_wand

SOURCES  := boot.c font.c GPIO.C i2c.c key.c led.c main.c mpu6050.c pov.c PWM.C \
            shake.c SPI.C Public/Debug.C
OBJECTS := $(patsubst %.c,$(BUILD)/%.rel,$(patsubst %.C,$(BUILD)/%.rel,$(SOURCES)))
HEADERS  := CH552.H font.h GPIO.H i2c.h key.h led.h main.h mpu6050.h pov.h boot.h \
            PWM.H shake.h SPI.H Public/Debug.H Public/CH554.H sdcc_compat.h

# CH551G exposes 10 KiB user code space and 512 bytes XRAM.  Keep the small
# model for fast internal-RAM access, and place larger explicit buffers in xdata.
CFLAGS := -mmcs51 --model-small --xram-size 0x0200 --xram-loc 0x0000 \
          --code-size 0x2800 -I$(CH55X_SDK) -I. -IPublic \
          --include sdcc_compat.h

.PHONY: all clean rebuild check-toolchain
.DEFAULT_GOAL := all

all: $(TARGET).hex

$(TARGET).hex: $(TARGET).ihx
	$(PACKIHX) < $< > $@

$(TARGET).ihx: $(OBJECTS)
	$(SDCC) $(CFLAGS) $(OBJECTS) -o $@

$(BUILD)/%.rel: %.c $(HEADERS) | $(BUILD)
	@mkdir -p $(dir $@)
	$(SDCC) -c $(CFLAGS) $< -o $@

$(BUILD)/%.rel: %.C $(HEADERS) | $(BUILD)
	@mkdir -p $(dir $@)
	$(SDCC) -c $(CFLAGS) $< -o $@

check-toolchain:
	@test -x "$(SDCC)" || (echo "SDCC not found: $(SDCC)" >&2; exit 1)
	@test -x "$(PACKIHX)" || (echo "packihx not found: $(PACKIHX)" >&2; exit 1)
	@test -f "$(CH55X_SDK)/ch554.h" || (echo "CH55x SDK headers not found: $(CH55X_SDK)" >&2; exit 1)
	@$(SDCC) --version

$(BUILD):
	mkdir -p "$@"

clean:
	rm -rf $(BUILD)

rebuild: clean all
