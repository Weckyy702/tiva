ARCHPREFIX ?= arm-none-eabi-
BUILDDIR ?= build
BIN ?= firmware.elf
IMG ?= firmware.bin
LINKERSCRIPT ?= src/default.ld

CC = $(ARCHPREFIX)gcc
CXX = $(ARCHPREFIX)g++
OBJCOPY = $(ARCHPREFIX)objcopy

# Disable floating point instructions for now
CFLAGS = -mcpu=cortex-m4+nofp -mthumb
CFLAGS += -O0
CFLAGS += -fno-common -ffreestanding -ffunction-sections -fdata-sections
CFLAGS += -Wall -Wextra -Wpedantic
CFLAGS += -ggdb
CFLAGS += -nostartfiles

CXXFLAGS += -fno-exceptions
CXXFLAGS += -std=c++23

CPPFLAGS += -Iinclude -MD -MP

LDFLAGS = $(CFLAGS) -T $(LINKERSCRIPT) -Xlinker --gc-sections --specs=nosys.specs

SRCS := $(shell find src -name '*.c' -o -name '*.cpp')
OBJS := $(SRCS:%=$(BUILDDIR)/%.o)
DEPS := $(OBJS:.o=.d)


$(IMG): $(BIN)
	$(OBJCOPY) -Obinary $< $@

$(BIN): $(OBJS) $(LINKERSCRIPT)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

$(BUILDDIR)/%.cpp.o: %.cpp Makefile
	mkdir -p $(dir $@)
	$(CXX) -c $< -o $@ $(CXXFLAGS) $(CPPFLAGS)

all: img

img: $(IMG)

firmware: $(BIN)

clean:
	rm -f $(IMG) $(BIN) $(OBJS)

install: all
	mkdir -p $(PREFIX)/bin 
	cp $(IMG) $(BIN) $(PREFIX)/bin/

.PHONY: all clean install firmware img

-include $(shell find $(BUILDDIR) -name '*.d')
