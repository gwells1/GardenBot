#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <xc.h>
#include "pic32cm1216mc00032.h"

#define LED_PIN (uint32_t)1U << 23U
#define SW_PIN (uint32_t)1U << 22U
#define USART_TX (uint32_t)1U << 8U
#define USART_RX (uint32_t)1U << 9U

void init_system(void);
void init_ports(void);
void init_OSCCTRL(void);
void init_GCLK(void);

#endif