#pragma once

#include "core/ints.hpp"
using IRQHandler = void (*)(void);

#define FOR_EACH_SYSEXCEPT(X)                                                  \
  X(reset)                                                                     \
  X(nmi)                                                                       \
  X(hard_fault)                                                                \
  X(memory_management_fault)                                                   \
  X(bus_fault)                                                                 \
  X(usage_fault)

#define FOR_EACH_IRQ(X)                                                        \
  X(gpio_port_a, 0)                                                            \
  X(gpio_port_b, 1)                                                            \
  X(gpio_port_c, 2)                                                            \
  X(gpio_port_d, 3)                                                            \
  X(gpio_port_e, 4)                                                            \
  X(uart0, 5)                                                                  \
  X(uart1, 6)                                                                  \
  X(ssi0, 7)                                                                   \
  X(i2c0, 8)                                                                   \
  X(pwm0_fault, 9)                                                             \
  X(pwm0_gen0, 10)                                                             \
  X(pwm0_gen1, 11)                                                             \
  X(pwm0_gen2, 12)                                                             \
  X(qei0, 13)                                                                  \
  X(adc0_seq0, 14)                                                             \
  X(adc0_seq1, 15)                                                             \
  X(adc0_seq2, 16)                                                             \
  X(adc0_seq3, 17)                                                             \
  X(watchdog_01, 18)                                                           \
  X(timer0a, 19)                                                               \
  X(timer0b, 20)                                                               \
  X(timer1a, 21)                                                               \
  X(timer1b, 22)                                                               \
  X(timer2a, 23)                                                               \
  X(timer2b, 24)                                                               \
  X(analog_comp0, 25)                                                          \
  X(analog_comp1, 26)                                                          \
  X(sysctl, 28)                                                                \
  X(eeprom_ctl, 29)                                                            \
  X(gpio_port_f, 30)                                                           \
  X(uart2, 33)                                                                 \
  X(ss1, 34)                                                                   \
  X(timer3a, 35)                                                               \
  X(timer3b, 36)                                                               \
  X(i2c1, 37)                                                                  \
  X(qei1, 38)                                                                  \
  X(can0, 39)                                                                  \
  X(can1, 40)                                                                  \
  X(hibernation, 43)                                                           \
  X(usb, 44)                                                                   \
  X(pwm0_gen3, 45)                                                             \
  X(udma_software, 46)                                                         \
  X(udma_error, 47)                                                            \
  X(adc1_seq0, 48)                                                             \
  X(adc1_seq1, 49)                                                             \
  X(adc1_seq2, 50)                                                             \
  X(adc1_seq3, 51)                                                             \
  X(ssi2, 57)                                                                  \
  X(ssi3, 58)                                                                  \
  X(uart3, 59)                                                                 \
  X(uart4, 60)                                                                 \
  X(uart5, 61)                                                                 \
  X(uart6, 62)                                                                 \
  X(uart7, 63)                                                                 \
  X(i2c2, 68)                                                                  \
  X(i2c3, 69)                                                                  \
  X(timer4a, 70)                                                               \
  X(timer4b, 71)                                                               \
  X(timer5a, 92)                                                               \
  X(timer5b, 93)                                                               \
  X(hires_timer0a, 94)                                                         \
  X(hires_timer0b, 95)                                                         \
  X(hires_timer1a, 96)                                                         \
  X(hires_timer1b, 97)                                                         \
  X(hires_timer2a, 98)                                                         \
  X(hires_timer2b, 99)                                                         \
  X(hires_timer3a, 100)                                                        \
  X(hires_timer3b, 101)                                                        \
  X(hires_timer4a, 102)                                                        \
  X(hires_timer4b, 103)                                                        \
  X(hires_timer5a, 104)                                                        \
  X(hires_timer5b, 105)                                                        \
  X(sysexcept, 106)                                                            \
  X(pwm1_gen0, 134)                                                            \
  X(pwm1_gen1, 135)                                                            \
  X(pwm1_gen2, 136)                                                            \
  X(pwm1_gen3, 137)                                                            \
  X(pwm1_fault, 138)

#define MAKE_ISR(name, ...) extern "C" void handle_##name(void);
FOR_EACH_SYSEXCEPT(MAKE_ISR)
FOR_EACH_IRQ(MAKE_ISR)

#define MAKE_IRQNUM(name, num) name = num,
enum class IRQNumber : u8 { FOR_EACH_IRQ(MAKE_IRQNUM) };
