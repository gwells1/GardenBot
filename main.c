/**
 * @file main.c
 * @author greg
 * @date 2026-03-31
 * @brief Main function
 */

#include "pic32cm1216mc00032.h"
#include <stdint.h>
#include "configuration.h"
#include "utilities.h"
#include "usart.h"

int main(){

    init_system();
    init_USART();

    while(1){

        //LED_on();
        toggle_LED();
        USART_sendChar("C");
        simple_dly(600000);
    }

    return 0;
}
