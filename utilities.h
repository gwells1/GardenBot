#ifndef UTILITIES_H
#define UTILITIES_H

#include <stdint.h>
#include <xc.h>
#include "pic32cm1216mc00032.h"

void simple_dly(uint32_t);
void LED_on();
void LED_off();
void toggle_LED();

#endif