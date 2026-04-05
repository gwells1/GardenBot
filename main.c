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

int main(){

    init_system();

    while(1){

        //LED_on();
        toggle_LED();
        simple_dly(512);
    }

    return 0;
}
