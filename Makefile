PREFIX ?= arm-none-eabi-
BUILDDIR ?= build
BIN ?= firmware.elf
LINKERSCRIPT ?= src/default.ld

CC = $(PREFIX)gcc
CXX = $(PREFIX)g++

CFLAGS = 
CFLAGS += -O0
CFLAGS += -fno-common -ffreestanding -fno-exceptions
CFLAGS += -Wall -Wextra -Wpedantic
CFLAGS += -ggdb
CFLAGS += -nostartfiles

LDFLAGS = $(CFLAGS) -T $(LINKERSCRIPT) -Xlinker --gc-sections --specs=nosys.specs

SRCS := $(shell find src -name '*.c' -o -name '*.cpp')
OBJS := $(SRCS:%=$(BUILDDIR)/%.o)
DEPS := $(OBJS:.o=.d)


$(BIN): $(OBJS) $(LINKERSCRIPT)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

$(BUILDDIR)/%.cpp.o: %.cpp
	mkdir -p $(dir $@)
	$(CXX) -c $< -o $@ $(CXXFLAGS) $(CPPFLAGS)

$(BUILDDIR)/%.c.o: src/%.c
	mkdir -p $(dir $@)
	$(CC) -c $< -o $@ $(CFLAGS) $(CPPFLAGS)

firmware: $(BIN)

.PHONY: all clean firmware
