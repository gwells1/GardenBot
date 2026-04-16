#ifndef USART_H
#define USART_H

#include <stdint.h>
#include <xc.h>
#include "pic32cm1216mc00032.h"

void init_USART();
void USART_sendChar(char letter);

#endif