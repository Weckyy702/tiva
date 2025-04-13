PREFIX ?= arm-none-eabi-
BUILDDIR ?= build
BIN ?= firmware.elf
IMG ?= firmware.bin
LINKERSCRIPT ?= src/default.ld

CC = $(PREFIX)gcc
CXX = $(PREFIX)g++

# Disable floating point instructions for now
CFLAGS = -mcpu=cortex-m4+nofp -mthumb
CFLAGS += -O0
CFLAGS += -fno-common -ffreestanding -ffunction-sections
CFLAGS += -Wall -Wextra -Wpedantic
CFLAGS += -ggdb
CFLAGS += -nostartfiles

CXXFLAGS += -fno-exceptions

LDFLAGS = $(CFLAGS) -T $(LINKERSCRIPT) -Xlinker --gc-sections --specs=nosys.specs

SRCS := $(shell find src -name '*.c' -o -name '*.cpp')
OBJS := $(SRCS:%=$(BUILDDIR)/%.o)
DEPS := $(OBJS:.o=.d)


$(IMG): $(BIN)
	$(PREFIX)objcopy -Obinary $< $@

$(BIN): $(OBJS) $(LINKERSCRIPT)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

$(BUILDDIR)/%.cpp.o: %.cpp Makefile
	mkdir -p $(dir $@)
	$(CXX) -c $< -o $@ $(CXXFLAGS) $(CPPFLAGS)

all: img

img: $(IMG)

firmware: $(BIN)

clean:
	rm -f $(BIN) $(OBJS)

.PHONY: all clean firmware
