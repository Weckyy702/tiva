ARCHPREFIX ?= arm-none-eabi-
BUILDDIR ?= build/
BIN ?= $(BUILDDIR)firmware.elf
LINKERSCRIPT ?= src/default.ld

CC = $(ARCHPREFIX)gcc
CXX = $(ARCHPREFIX)g++

# Disable floating point instructions for now
CFLAGS = -mcpu=cortex-m4+nofp -mthumb 
CFLAGS += -Og
CFLAGS += -fno-common -ffreestanding -ffunction-sections -fdata-sections
CFLAGS += -Wall -Wextra -Wpedantic -Werror -Wno-error=pedantic
CFLAGS += -ggdb
CFLAGS += -nostartfiles

CXXFLAGS = $(CFLAGS)
CXXFLAGS += -fno-exceptions
CXXFLAGS += -std=gnu++23

CPPFLAGS += -Iinclude -MD -MP

LDFLAGS = $(CFLAGS) -T $(LINKERSCRIPT) -Xlinker --gc-sections --specs=nosys.specs

SRCS := $(shell find src -name '*.c' -o -name '*.cpp')
OBJS := $(SRCS:%=$(BUILDDIR)%.o)
DEPS := $(OBJS:.o=.d)

$(BIN): $(OBJS) $(LINKERSCRIPT)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

$(BUILDDIR)%.cpp.o: %.cpp Makefile
	mkdir -p $(dir $@)
	$(CXX) -c $< -o $@ $(CXXFLAGS) $(CPPFLAGS)

upload: $(BIN)
	openocd -f openocd.cfg -c "program $(BIN)" -c "verify_image $(BIN)" -c "shutdown"

firmware: $(BIN)

clean:
	rm -f $(IMG) $(BIN) $(OBJS)

install: all
	mkdir -p $(PREFIX)/bin 
	cp $(BIN) $(PREFIX)/bin/

.PHONY: all clean install firmware upload

-include $(shell find $(BUILDDIR) -name '*.d')
