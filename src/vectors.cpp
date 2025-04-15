#include "irqs.hpp"

using IRQHandler = void (*)(void);

struct ResetVector {
  void *initial_sp;
  IRQHandler reset_handler;
  IRQHandler nmi_handler;
  IRQHandler hardfault_handler;
  IRQHandler memory_management_fault_handler;
  IRQHandler bus_fault_handler;
  IRQHandler usage_fault_handler;
  void *__reserved1[4];
  IRQHandler sv_call_handler;
  void *__reserved2[2];
  IRQHandler pend_sv_handler;
  IRQHandler systick_handler;
  IRQHandler irqs[139];
};

static_assert(sizeof(ResetVector) == 0x26C);

struct __LinkerSymbol;
extern __LinkerSymbol __stack_top;

extern "C" {

ResetVector const constinit reset_vector
    [[gnu::section(".vector"), gnu::used]] = {
        .initial_sp = &__stack_top,
        .reset_handler = handle_reset,
};
}
