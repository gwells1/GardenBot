/**
 * @file main.c
 * @author greg
 * @date 2026-03-31
 * @brief Main function
 */

#include "definitions.h"
#include <pic32cm1216mc00032.h>
#include <stdint.h>

int main(){

    init_system();
    init_USART();
    //init_SPI();

     send_string("SPI Weather Click Example\n");

    while(1){

        send_string("Dummy Data:\n");
        toggle_LED();
        simple_delay(3600000);
    }

    return 0;
}

