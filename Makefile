# Independent SDCC build for the CH55x POV wand.
# Requires SDCC (installed at C:/Program Files (x86)/SDCC) and GNU Make.

SHELL := cmd.exe
.SHELLFLAGS := /C

SDCC_BIN := C:/Program Files (x86)/SDCC/bin
SDCC     := "$(SDCC_BIN)/sdcc.exe"
PACKIHX  := "$(SDCC_BIN)/packihx.exe"
export PATH := $(CURDIR)/tools/sdcc;$(SDCC_BIN);$(PATH)
BUILD    := build/sdcc
TARGET   := $(BUILD)/pov_wand

SOURCES  := boot.c font.c GPIO.C i2c.c key.c led.c main.c mpu6050.c pov.c PWM.C \
            shake.c SPI.C Public/Debug.C sdcc_stdio.c
OBJECTS  := $(addprefix $(BUILD)/,$(notdir $(SOURCES:.c=.rel)))
OBJECTS  := $(OBJECTS:.C=.rel)
HEADERS  := CH552.h font.h GPIO.H i2c.h key.h led.h main.h mpu6050.h pov.h boot.h \
            PWM.H shake.h SPI.H Public/Debug.H Public/CH554.H sdcc_compat.h

# CH552 has 16 KiB code flash and 1 KiB XRAM.  sdcc_compat.h supplies the
# CH55x register map and maps the Keil memory-space qualifiers to SDCC.
CFLAGS := -mmcs51 --model-small --xram-size 0x0400 --xram-loc 0x0000 \
          --code-size 0x4000 -I. -IPublic --include sdcc_compat.h

.PHONY: all clean rebuild
.DEFAULT_GOAL := all

all: $(TARGET).hex

$(TARGET).hex: $(TARGET).ihx
	$(PACKIHX) $< > $@

$(TARGET).ihx: $(OBJECTS)
	$(SDCC) $(CFLAGS) $(OBJECTS) -o $@

$(BUILD)/%.rel: %.c $(HEADERS) | $(BUILD)
	$(SDCC) -c $(CFLAGS) $< -o $@

$(BUILD)/%.rel: %.C $(HEADERS) | $(BUILD)
	$(SDCC) -c $(CFLAGS) $< -o $@

$(BUILD)/Debug.rel: Public/Debug.C $(HEADERS) | $(BUILD)
	$(SDCC) -c $(CFLAGS) $< -o $@

$(BUILD):
	if not exist "$@" mkdir "$@"

clean:
	-if exist "$(BUILD)" rmdir /s /q "$(BUILD)"

rebuild: clean all
