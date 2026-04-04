#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <xc.h>
#include "pic32cm1216mc00032.h"

#define LED_PIN (uint32_t)1U << 23U
#define SW_PIN (uint32_t)1U << 22U

void init_system(void);

#endif