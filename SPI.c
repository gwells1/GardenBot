#include "definitions.h"
#include <component/sercom.h>
#include <pic32cm1216mc00032.h>

void init_SPI(){
    //Connect APBC to SERCOM0
    MCLK_REGS -> MCLK_APBCMASK |= MCLK_APBCMASK_SERCOM0_Msk;

    /* Basic SPI initialization
     * 1. Select SPI host mode
     * 2. Select transfer mode for the clock polarity bit and the clock phase bit
     * 3. Select the frame format value
     * 4. Configure the Data in Pinout field for the SERCOM pads of the receiver
     * 5. Configure the Data Out Pinout bit group for the transmitter
     * 6. Configure the character size value
     * 7. Write the Data Order Bit
     * 8. Select the desired baud rate
     * 9. if Hardware SS control is required, write '1' to the HOST SPI Select Enable bit in the CTRLB register
     * 10. Enable the receiver
     */

     /* Configure CTRLA
      * DORD: MSB first [0x0], enable-protected, not synchronized
      * CPOL: SCK is low when idle [0x0], enable-protected, not synchronized
      * CPHA: rising, sample.  Falling, change [0x0], enable-protected, not synchronized
      * FORM: SPI_FRAME [0x00]. enable-protected, not synchronized
      * DIPO: Data In Pinout = PAD[0] (PA08). [0x0] enable-protected, not synchronized
      * DOPO: Data Out Pinout [0x1]. enable protected, not synchronized
      *     DO          =   PAD[2] (PA10)
      *     SCK         =   PAD[3] (PA11)
      *     client !SS  =   PAD[1] (PA9)
      * IBON: Immediate buffer overflow notification [0x0], enable-protected, not synchronized
      * RUNSTDBY: Generic clock is enabled in all sleep modes [0x1]. enable-protected, not synchronized
      * MODE: Operating mode - SPI host operation [0x3], enable-protected, not synchronized
     */

     SERCOM0_REGS -> SPIM.SERCOM_CTRLA = SERCOM_SPIM_CTRLA_DIPO_PAD0 | SERCOM_SPIS_CTRLA_DOPO(0x1) |
     SERCOM_SPIM_CTRLA_RUNSTDBY_Msk | SERCOM_SPIM_CTRLA_MODE_SPI_MASTER;

     // Configure BAUD rate for 9600 baud
     SERCOM0_REGS -> SPIM.SERCOM_BAUD = (uint16_t)SERCOM_SPIM_BAUD_BAUD(65326UL);

     /* Configure CTRLB
     *  RXEN: enable receiver [0x1]. enable-protected, not synchronized
     *  AMODE: Address mode (not applicable in this case) [0x0], enable-protected, not synchronized
     *  MSSEN: Enable Host SPI Select [0x1]. enable-protected, not synchronized
     *  SSDE: enable SS low detector [0x1]. enable-protected, not synchronized
     *  CHSIZE: 8-bit character size [0x0]. enable-protected, not synchronized
     */
     SERCOM0_REGS -> SPIM.SERCOM_CTRLB = SERCOM_SPIM_CTRLB_RXEN_Msk | SERCOM_SPIM_CTRLB_MSSEN_ENABLE |
     SERCOM_SPIM_CTRLB_SSDE_ENABLE | SERCOM_SPIM_CTRLB_CHSIZE_8_BIT;

     //Synchronize the CTRLB register
     while((SERCOM0_REGS -> SPIM.SERCOM_SYNCBUSY & SERCOM_SPIM_SYNCBUSY_CTRLB_Msk) == SERCOM_SPIM_SYNCBUSY_CTRLB_Msk){}

     //Enable the SPI
     SERCOM0_REGS -> SPIM.SERCOM_CTRLA |= SERCOM_SPIM_CTRLA_ENABLE_Msk;

     //Synchronize the SPI
     while((SERCOM0_REGS -> SPIM.SERCOM_SYNCBUSY & SERCOM_SPIM_SYNCBUSY_ENABLE_Msk) == SERCOM_SPIM_SYNCBUSY_ENABLE_Msk){}

     // Enable the RX interrupt
     SERCOM0_REGS -> SPIM.SERCOM_INTENSET = SERCOM_SPIM_INTENSET_RXC_Msk;

     //Enable NVIC interrupt for SERCOM1
     NVIC_EnableIRQ(SERCOM0_IRQn);
}

void spi_data_exchange(uint8_t cmd){
    while((SERCOM0_REGS->SPIM.SERCOM_INTFLAG & SERCOM_SPIM_INTFLAG_DRE_Msk) != SERCOM_SPIM_INTFLAG_DRE_Msk){}
    SERCOM0_REGS->SPIM.SERCOM_DATA = cmd;
}

void SERCOM0_Handler(void){
    //Check if RX complete interrupt flag is set
    if(SERCOM0_REGS->SPIM.SERCOM_INTFLAG & SERCOM_SPIM_INTFLAG_RXC_Msk){
        // Read received character
        //received_char = SERCOM0_REGS->SPIM.SERCOM_DATA
        
        //add your code here to process/store received_char
    }
}