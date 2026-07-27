#include "definitions.h"

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

    init_OSCCTRL();
    init_GCLK();
    init_ports();
    //init_USART
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
    GCLK_REGS->GCLK_GENCTRL[0] = GCLK_GENCTRL_DIV(1UL) | GCLK_GENCTRL_SRC(6UL) | GCLK_GENCTRL_GENEN_Msk;
    
    //Wait for synchronization to complete
    while((GCLK_REGS->GCLK_SYNCBUSY & GCLK_SYNCBUSY_GENCTRL0_Msk) == GCLK_SYNCBUSY_GENCTRL0_Msk);

    //Enable peripheral channel for SERCOM1 on GCLK0
    GCLK_REGS->GCLK_PCHCTRL[20] = GCLK_PCHCTRL_WRTLOCK(0x0U) | GCLK_PCHCTRL_CHEN(0x0U) | GCLK_PCHCTRL_CHEN_Msk;

    //wait for synchronization
    while((GCLK_REGS->GCLK_PCHCTRL[20] & GCLK_PCHCTRL_CHEN_Msk) != GCLK_PCHCTRL_CHEN_Msk);

}

void init_ports(){
    //Configure Ports (BaseAddress: 0x41000000)
    PORT_REGS->GROUP[0].PORT_DIR = ((uint32_t)LED_PIN | (uint32_t)USART_TX_PIN );     // Set LED pin as an output
    //PORT_REGS->GROUP[0].PORT_DIR = (uint32_t)USART_TX_PIN;     // Set LED pin as an output
    //PORT_REGS->GROUP[0].PORT_OUT = SW_PIN; // Set switch pin high (pull-up)
    PORT_REGS->GROUP[0].PORT_PINCFG[0] = (uint8_t)0x1UL; //Configure port control to enable the peripheral multiplexer on PA0
    PORT_REGS->GROUP[0].PORT_PINCFG[1] = (uint8_t)0x1UL; //Configure port control to enable the peripheral multiplexer on PA1
    PORT_REGS->GROUP[0].PORT_PINCFG[22] = (uint8_t)0x6UL; // Configure port control for switch, enable internal pullup, enable input buffer 
    PORT_REGS->GROUP[0].PORT_PINCFG[23] = (uint8_t)0x0UL; // Configure port control for LED, no pullup, enable output buffer
    //Figure out how to configure the ports for peripheral operation
    PORT_REGS->GROUP[0].PORT_PMUX[0] = (uint8_t)0x33UL; //Configure PA0 and PA1 for peripheral function D (SERCOM_ALT)
    //PORT_REGS->GROUP[0].PORT_WRCONFIG =  PORT_WRCONFIG_HWSEL(0x0UL) | PORT_WRCONFIG_WRPINCFG(0x1UL) | PORT_WRCONFIG_WRPMUX(0x2UL) | PORT_WRCONFIG_PMUXEN(0x1UL) | PORT_WRCONFIG_PINMASK(0x8UL); 
    PORT_REGS->GROUP[0].PORT_OUTSET |= LED_PIN; // Turn off LED (active low)
}
