#include "configuration.h"
//#include <component/gclk.h>
//#include <component/oscctrl.h>
#include <pic32cm1216mc00032.h>

#pragma config NVMCTRL_BOOTPROT = SIZE_0BYTES
#pragma config BODVDDUSERLEVEL = 0x0U
#pragma config BODVDD_DIS = ENABLED
#pragma config BODVDD_ACTION = NONE
#pragma config WDT_ENABLE = DISABLED
#pragma config WDT_ALWAYSON = DISABLED
#pragma config WDT_PER = CYC8
#pragma config WDT_WINDOW = CYC8
#pragma config WDT_EWOFFSET = CYC8
#pragma config WDT_WEN = DISABLED
#pragma config BODVDD_HYST = DISABLED
#pragma config NVMCTRL_REGION_LOCKS = 0xffffD

void init_system(void){
    
    NVMCTRL_REGS->NVMCTRL_CTRLB = NVMCTRL_CTRLB_RWS(3U);

    init_ports();
    init_OSCCTRL();
    init_GCLK();
}

void init_ports(){
    //Configure Ports (BaseAddress: 0x41000000)
    PORT_REGS->GROUP[0].PORT_DIR = LED_PIN; // Set LED pin as output
    PORT_REGS->GROUP[0].PORT_OUT = SW_PIN; // Set switch pin high (pull-up)
    PORT_REGS->GROUP[0].PORT_PINCFG[22] = 0x6UL; // Configure port control for switch, enable internal pullup, enable input buffer 
    PORT_REGS->GROUP[0].PORT_PINCFG[23] = 0x0UL; // Configure port control for LED, no pullup, enable output buffer

    PORT_REGS->GROUP[0].PORT_OUTSET = LED_PIN; // Turn off LED (active low)
}

void init_OSCCTRL(){
    //Configure Oscillator controller to run at 48MHz using OSC48M
    uint32_t calibValue = (uint32_t)(((*(uint64_t*)0x00806020UL)>>19) & 0x3fffffUL); // Read factory calibration value for 48MHz oscillator
    OSCCTRL_REGS->OSCCTRL_CAL48M = calibValue;

    //Seclect the division value
    OSCCTRL_REGS->OSCCTRL_OSC48MDIV = (uint8_t)OSCCTRL_OSC48MDIV_DIV(0xFUL);

    //Wait for Synchronization
    while((OSCCTRL_REGS->OSCCTRL_OSC48MSYNCBUSY & OSCCTRL_OSC48MSYNCBUSY_Msk) == OSCCTRL_OSC48MSYNCBUSY_Msk);

    //Wait for OSC48M ready state
    while((OSCCTRL_REGS->OSCCTRL_STATUS & OSCCTRL_STATUS_OSC48MRDY_Msk) != OSCCTRL_STATUS_OSC48MRDY_Msk);

    OSCCTRL_REGS->OSCCTRL_OSC48MCTRL |= (uint8_t)OSCCTRL_OSC48MCTRL_ONDEMAND_Msk; // Enable on-demand mode for power saving
}

void init_GCLK(){
    GCLK_REGS->GCLK_GENCTRL[0] = GCLK_GENCTRL_DIV(0x00UL) | GCLK_GENCTRL_SRC(6UL) | GCLK_GENCTRL_GENEN_Msk;

    while((GCLK_REGS->GCLK_SYNCBUSY & GCLK_SYNCBUSY_GENCTRL0_Msk) == GCLK_SYNCBUSY_GENCTRL0_Msk);
}