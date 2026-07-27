/*
USART confugration notes
    -SERCOM must be configured by writing the operating mode bits in the CTRLA register (CTRLA.MODE)
    -SERCOM is enabled by setting the enable bit to '1' in the CTRLA register
    -Writing a '1' to the software reset bit of the CTRLA register will reset all registers to their initial state
    except for the DBGCTRL register
    -Baud Rate Generator:
        - for Asynchronous operation, divide-by-16 is used for TX wheras divide-by-1 is used for RX
        - for Synchronous operation, divide-by-2 is used for TX
    -See page 437 of the datasheet for CTRLA.MODE settings
    -See page 438 of the datasheet for baud frequency and register value calculations
    -See page 439 of the datasheet for baud register value vs frequency table
    -The following registers are enable protected:
        -CTRLA
        -CTRLB
        -BAUD
    -Basic Initialization
        -select Clock (0x0 for internal, 0x1 for external in CTRLA.MODE)
        -Select Asynchronus 0x0 or Synchronous 0x1 mode CTRLA.CMODE)
        -Select RX pin (CTRLA.RXPO)
        -Select TX and EXT CLK pin (CTRLA.TXPO)
        -Configure character size (CTRLB.CHSIZE)
        -Configure Endian (CTRLA.DORD)
        -In order to user parity mode
            -Enable Parity Mode (CTRLB.PMODE = 0x1)
            -Configure parity mode (CTRLB.MODE) for even or odd parity
        -Configure the number of stop bits (CTRLB.SBMODE)
        -For the internal clock, configure the baud rate generator (BAUD)
        -Enable transmitter and receiver (0x1 to CTRLB.RXEN and CTRLB.TXEN)
    -Error handling
        -RX has 3 error bits in the status register
    -A Loopback mode is available 
    -Start of frame detection can wake the CPU up from sleep
    -DMA is available for this peripheral
*/

#include "usart.h"
#include <component/sercom.h>
#include <xc.h>
#include <pic32cm1216mc00032.h>

void init_USART(){

    //Connect sercom 1 to APBC (for the USART)
    MCLK_REGS -> MCLK_APBCMASK = MCLK_APBCMASK_SERCOM1_Msk;

    //Configure CTRLA: internal clk, Generic clk disabled when transfer is finished, 16x sampling, TXP set to SERCOM_PAD[0], RXP set to SERCOM_PAD[1], Sample Adjustment set to 7-8-9, USART Frame, Async Mode, Rising XCK (TX), MSB first
    SERCOM1_REGS -> USART_INT.SERCOM_CTRLA = SERCOM_USART_INT_CTRLA_DORD_LSB | SERCOM_USART_INT_CTRLA_CPOL_IDLE_HIGH | SERCOM_USART_INT_CTRLA_CMODE_ASYNC |
    SERCOM_USART_INT_CTRLA_FORM_USART_FRAME_NO_PARITY | SERCOM_USART_INT_CTRLA_SAMPA_ADJ0 | SERCOM_USART_INT_CTRLA_RXPO_PAD1 |
    SERCOM_USART_INT_CTRLA_TXPO_PAD0 | SERCOM_USART_INT_CTRLA_SAMPR_16X_ARITHMETIC | SERCOM_USART_INT_CTRLA_RUNSTDBY_Msk | SERCOM_USART_INT_CTRLA_MODE_USART_INT_CLK;

    //Configure baud rate for 9600 Baud
    SERCOM1_REGS -> USART_INT.SERCOM_BAUD = (uint16_t)SERCOM_USART_INT_BAUD_BAUD(65326UL);

    //Configure CTRLB: 8 Bit char size, 1 stop bit, no collision detection, ST of Frame detection disabled, Data is not Encoded, Even Parity, TX enabled, RX disabled (for now), Normal UART tx
    SERCOM1_REGS -> USART_INT.SERCOM_CTRLB = SERCOM_USART_INT_CTRLB_RXEN(0x0UL) | SERCOM_USART_INT_CTRLB_RXEN_Msk | SERCOM_USART_INT_CTRLB_TXEN_Msk | SERCOM_USART_INT_CTRLB_PMODE_EVEN |
    SERCOM_USART_INT_CTRLB_ENC_DISABLE | SERCOM_USART_INT_CTRLB_SFDE(0x0UL) | SERCOM_USART_INT_CTRLB_COLDEN(0x0UL) | SERCOM_USART_INT_CTRLB_SBMODE_1_BIT | SERCOM_USART_INT_CTRLB_CHSIZE_8_BIT;

    //Synchronize the CTRLB register (LINCMD, RXEN, and TXEN have been updated)
    while((SERCOM1_REGS -> USART_INT.SERCOM_SYNCBUSY & SERCOM_USART_INT_SYNCBUSY_CTRLB_Msk) == SERCOM_USART_INT_SYNCBUSY_CTRLB_Msk);

    //Enable the USART
    SERCOM1_REGS -> USART_INT.SERCOM_CTRLA |= SERCOM_USART_INT_CTRLA_ENABLE_Msk;

    //Synchronize the USART
    while((SERCOM1_REGS -> USART_INT.SERCOM_SYNCBUSY & SERCOM_USART_INT_SYNCBUSY_ENABLE_Msk) == SERCOM_USART_INT_SYNCBUSY_ENABLE_Msk);

    //Enable the RX interrupt
    SERCOM1_REGS -> USART_INT.SERCOM_INTENSET = SERCOM_USART_INT_INTENSET_RXC_Msk;

    //Enable NVIC interrupt for SERCOM1
    NVIC_EnableIRQ(SERCOM1_IRQn);
}

void USART_sendChar(char charToSend){
    while((SERCOM1_REGS -> USART_INT.SERCOM_INTFLAG & SERCOM_USART_INT_INTFLAG_DRE_Msk) != SERCOM_USART_INT_INTFLAG_DRE_Msk){}
    SERCOM1_REGS -> USART_INT.SERCOM_DATA = charToSend;
}

void send_string(char *stringToSend){
    while(*stringToSend){
        while((SERCOM1_REGS -> USART_INT.SERCOM_INTFLAG & SERCOM_USART_INT_INTFLAG_DRE_Msk) != SERCOM_USART_INT_INTFLAG_DRE_Msk){}
        SERCOM1_REGS -> USART_INT.SERCOM_DATA = *stringToSend++;
    }
}

void SERCOM1_Handler(void){
    if((SERCOM1_REGS -> USART_INT.SERCOM_INTFLAG & SERCOM_USART_INT_INTFLAG_RXC_Msk) == SERCOM_USART_INT_INTFLAG_RXC_Msk){
        char data = SERCOM1_REGS->USART_INT.SERCOM_DATA;
        USART_sendChar(data);
    }
}