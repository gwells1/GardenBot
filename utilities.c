#include "utilities.h"
#include "configuration.h"
#include <pic32cm1216mc00032.h>

void simple_delay(uint32_t delay){
    while(delay > 0){
        delay--;
    }
}

void LED_on(){
    PORT_REGS->GROUP[0].PORT_OUTCLR = LED_PIN; // Turn on LED (active low)
}

void LED_off(){
    PORT_REGS->GROUP[0].PORT_OUTSET = LED_PIN; // Turn off LED (active low)
}

void toggle_LED(){
    PORT_REGS->GROUP[0].PORT_OUTTGL = LED_PIN; // Toggle LED (active low)
}