#include "configuration.h"
#include <component/gclk.h>
#include <component/port.h>
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
    PORT_REGS->GROUP[0].PORT_DIR = LED_PIN | USART_TX;     // Set LED pin as an output
    //PORT_REGS->GROUP[0].PORT_DIR = USART_TX;    // Set USART TX pin as an output
    PORT_REGS->GROUP[0].PORT_OUT = SW_PIN; // Set switch pin high (pull-up)
    PORT_REGS->GROUP[0].PORT_PINCFG[22] = 0x6UL; // Configure port control for switch, enable internal pullup, enable input buffer 
    PORT_REGS->GROUP[0].PORT_PINCFG[23] = 0x0UL; // Configure port control for LED, no pullup, enable output buffer
    PORT_REGS->GROUP[0].PORT_PINCFG[8] = 0x1UL; //Configure port control to enable the peripheral multiplexer on PA8 (will need to do this on PA9 when  RX  is added)
    //ToDo: Figure out how to configure the ports for peripheral operation
    PORT_REGS->GROUP[0].PORT_PMUX[4] &= 0xF0UL;
    PORT_REGS->GROUP[0].PORT_PMUX[4] |= 0x02UL;
    //PORT_REGS->GROUP[0].PORT_WRCONFIG =  PORT_WRCONFIG_HWSEL(0x0UL) | PORT_WRCONFIG_WRPINCFG(0x1UL) | PORT_WRCONFIG_WRPMUX(0x2UL) | PORT_WRCONFIG_PMUXEN(0x1UL) | PORT_WRCONFIG_PINMASK(0x8UL); 
    PORT_REGS->GROUP[0].PORT_OUTSET = LED_PIN; // Turn off LED (active low)
}

void init_OSCCTRL(){
    //Configure Oscillator controller to run at 48MHz using OSC48M
    uint32_t calibValue = (uint32_t)(((*(uint64_t*)0x00806020UL)>>19) & 0x3fffffUL); // Read factory calibration value for 48MHz oscillator
    OSCCTRL_REGS->OSCCTRL_CAL48M = calibValue;

    //Seclect the division value
    OSCCTRL_REGS->OSCCTRL_OSC48MDIV = (uint8_t)OSCCTRL_OSC48MDIV_DIV(0x0UL);

    //Wait for Synchronization
    while((OSCCTRL_REGS->OSCCTRL_OSC48MSYNCBUSY & OSCCTRL_OSC48MSYNCBUSY_Msk) == OSCCTRL_OSC48MSYNCBUSY_Msk);

    //Wait for OSC48M ready state
    while((OSCCTRL_REGS->OSCCTRL_STATUS & OSCCTRL_STATUS_OSC48MRDY_Msk) != OSCCTRL_STATUS_OSC48MRDY_Msk);

    OSCCTRL_REGS->OSCCTRL_OSC48MCTRL |= (uint8_t)OSCCTRL_OSC48MCTRL_ONDEMAND_Msk; // Enable on-demand mode for power saving
}

void init_GCLK(){
    //Configure GCLK0 to run at 48MHz using the OSC48M for the main clock
    GCLK_REGS->GCLK_GENCTRL[0] = GCLK_GENCTRL_DIV(0x00UL) | GCLK_GENCTRL_SRC(6UL) | GCLK_GENCTRL_GENEN_Msk;
    
    //Wait for synchronization to complete
    while((GCLK_REGS->GCLK_SYNCBUSY & GCLK_SYNCBUSY_GENCTRL0_Msk) == GCLK_SYNCBUSY_GENCTRL0_Msk);

    //Configure GCLK1 to run at 48MHz using the OSC48M for the SERCON0 clock
    GCLK_REGS->GCLK_GENCTRL[1] = GCLK_GENCTRL_DIV(0x0000UL) | GCLK_GENCTRL_SRC(6UL) | GCLK_GENCTRL_GENEN_Msk;

    //Wait for synchronization to complete
    while((GCLK_REGS->GCLK_SYNCBUSY & GCLK_SYNCBUSY_GENCTRL1_Msk) == GCLK_SYNCBUSY_GENCTRL1_Msk);

    //Enable peripheral channel for SERCOM0 on GCLK1
    GCLK_REGS->GCLK_PCHCTRL[19] = GCLK_PCHCTRL_WRTLOCK(0x0U) | GCLK_PCHCTRL_CHEN(0x1U) | GCLK_PCHCTRL_GEN_GCLK1;
}