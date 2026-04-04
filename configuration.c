#include "configuration.h"

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
    
}