#pragma once

#define MAKE_ISR(name) extern "C" [[gnu::interrupt]] void handle_##name(void);

#define FOR_EACH_SYSEXCEPT(X)                                                  \
  X(reset)                                                                     \
  X(nmi)                                                                       \
  X(hard_fault)                                                                \
  X(memory_management_fault)                                                   \
  X(bus_fault)                                                                 \
  X(usage_fault)

FOR_EACH_SYSEXCEPT(MAKE_ISR)
