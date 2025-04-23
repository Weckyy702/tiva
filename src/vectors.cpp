#include "irqs.hpp"

struct IRQHandlers {
  IRQHandler gpio_port_a_handler;
  IRQHandler gpio_port_b_handler;
  IRQHandler gpio_port_c_handler;
  IRQHandler gpio_port_d_handler;
  IRQHandler gpio_port_e_handler;
  IRQHandler uart0_handler;
  IRQHandler uart1_handler;
  IRQHandler ssi0_handler;
  IRQHandler i2c0_handler;
  IRQHandler pwm0_fault_handler;
  IRQHandler pwm0_gen0_handler;
  IRQHandler pwm0_gen1_handler;
  IRQHandler pwm0_gen2_handler;
  IRQHandler qei0_handler;
  IRQHandler adc0_seq0_handler;
  IRQHandler adc0_seq1_handler;
  IRQHandler adc0_seq2_handler;
  IRQHandler adc0_seq3_handler;
  IRQHandler watchdog_01_handler;
  IRQHandler timer0a_handler;
  IRQHandler timer0b_handler;
  IRQHandler timer1a_handler;
  IRQHandler timer1b_handler;
  IRQHandler timer2a_handler;
  IRQHandler timer2b_handler;
  IRQHandler analog_comp0_handler;
  IRQHandler analog_comp1_handler;
  IRQHandler __reserved0[1]{};
  IRQHandler sysctl_handler;
  IRQHandler eeprom_ctl_handler;
  IRQHandler gpio_port_f_handler;
  IRQHandler __reserved1[2]{};
  IRQHandler uart2_handler;
  IRQHandler ss1_handler;
  IRQHandler timer3a_handler;
  IRQHandler timer3b_handler;
  IRQHandler i2c1_handler;
  IRQHandler qei1_handler;
  IRQHandler can0_handler;
  IRQHandler can1_handler;
  IRQHandler __reserved2[2]{};
  IRQHandler hibernation_handler;
  IRQHandler usb_handler;
  IRQHandler pwm0_gen3_handler;
  IRQHandler udma_software_handler;
  IRQHandler udma_error_handler;
  IRQHandler adc1_seq0_handler;
  IRQHandler adc1_seq1_handler;
  IRQHandler adc1_seq2_handler;
  IRQHandler adc1_seq3_handler;
  IRQHandler __reserved3[5]{};
  IRQHandler ssi2_handler;
  IRQHandler ssi3_handler;
  IRQHandler uart3_handler;
  IRQHandler uart4_handler;
  IRQHandler uart5_handler;
  IRQHandler uart6_handler;
  IRQHandler uart7_handler;
  IRQHandler __reserved4[4]{};
  IRQHandler i2c2_handler;
  IRQHandler i2c3_handler;
  IRQHandler timer4a_handler;
  IRQHandler timer4b_handler;
  IRQHandler __reserved5[20]{};
  IRQHandler timer5a_handler;
  IRQHandler timer5b_handler;
  IRQHandler hires_timer0a_handler;
  IRQHandler hires_timer0b_handler;
  IRQHandler hires_timer1a_handler;
  IRQHandler hires_timer1b_handler;
  IRQHandler hires_timer2a_handler;
  IRQHandler hires_timer2b_handler;
  IRQHandler hires_timer3a_handler;
  IRQHandler hires_timer3b_handler;
  IRQHandler hires_timer4a_handler;
  IRQHandler hires_timer4b_handler;
  IRQHandler hires_timer5a_handler;
  IRQHandler hires_timer5b_handler;
  IRQHandler sysexcept_handler;
  IRQHandler __reserved6[27]{};
  IRQHandler pwm1_gen0_handler;
  IRQHandler pwm1_gen1_handler;
  IRQHandler pwm1_gen2_handler;
  IRQHandler pwm1_gen3_handler;
  IRQHandler pwm1_fault_handler;
};
static_assert(sizeof(IRQHandlers) == 139 * sizeof(IRQHandler));

struct ResetVector {
  void *initial_sp;
  IRQHandler reset_handler;
  IRQHandler nmi_handler;
  IRQHandler hard_fault_handler;
  IRQHandler memory_management_fault_handler;
  IRQHandler bus_fault_handler;
  IRQHandler usage_fault_handler;
  void *__reserved1[4]{};
  IRQHandler sv_call_handler;
  void *__reserved2[2]{};
  IRQHandler pend_sv_handler;
  IRQHandler systick_handler;
  IRQHandlers irqs;
};

static_assert(sizeof(ResetVector) == 0x26C);

struct __LinkerSymbol;
extern "C" __LinkerSymbol __stack_top;
extern "C" void null_handler();

#define SET_EXCEPTION_HANDLER(name, ...) .name##_handler = handle_##name,

extern "C" constinit ResetVector const reset_vector [[gnu::section(".vector"),
                                                      gnu::used]] = {
    .initial_sp = &__stack_top,
    FOR_EACH_SYSEXCEPT(SET_EXCEPTION_HANDLER).sv_call_handler = null_handler,
    .pend_sv_handler = null_handler,
    .systick_handler = null_handler,
    .irqs = {FOR_EACH_IRQ(SET_EXCEPTION_HANDLER)}};
