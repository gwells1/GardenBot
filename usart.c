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
    //Configure CTRLA: internal clk, Generic clk disabled when transfer is finished, 16x sampling, TXP set to SERCOM_PAD[0], RXP set to SERCOM_PAD[1], Sample Adjustment set to 7-8-9, USART Frame, Async Mode, Rising XCK (TX), MSB first
    SERCOM0_REGS -> USART_INT.SERCOM_CTRLA = SERCOM_USART_INT_CTRLA_MODE_USART_INT_CLK_Val | SERCOM_USART_INT_CTRLA_RUNSTDBY(0x0U) | SERCOM_USART_INT_CTRLA_SAMPR_16X_ARITHMETIC_Val | SERCOM_USART_INT_CTRLA_TXPO(0x0U) | SERCOM_USART_INT_CTRLA_RXPO(0x1U) | SERCOM_USART_INT_CTRLA_SAMPA(0x0U) | SERCOM_USART_INT_CTRLA_FORM(0x0U) | SERCOM_USART_INT_CTRLA_CMODE_ASYNC | SERCOM_USART_INT_CTRLA_CPOL(0x0U) | SERCOM_USART_INT_CTRLA_DORD_MSB; 
    //Configure CTRLB: 8 Bit char size, 1 stop bit, no collision detection, ST of Frame detection disabled, Data is not Encoded, Even Parity, TX enabled, RX disabled (for now), Normal UART tx
    SERCOM0_REGS -> USART_INT.SERCOM_CTRLB = SERCOM_USART_INT_CTRLB_CHSIZE_8_BIT | SERCOM_USART_INT_CTRLB_SBMODE_1_BIT | SERCOM_USART_INT_CTRLB_COLDEN(0x0U) | SERCOM_USART_INT_CTRLB_SFDE(0x0U) | SERCOM_USART_INT_CTRLB_ENC_DISABLE | SERCOM_USART_INT_CTRLB_PMODE_EVEN | SERCOM_USART_INT_CTRLB_TXEN(0x1U) | SERCOM_USART_INT_CTRLB_RXEN(0x0U) | SERCOM_USART_INT_CTRLB_LINCMD(0x0U);
    //Configure baud rate for 9600 Baud
    SERCOM0_REGS -> USART_INT.SERCOM_BAUD = SERCOM_USART_INT_BAUD_BAUD(0xFF2DUL);
    //Enable the Transmitter (For now, enable receiver later.  Consider enabling the transmitter in another function)
    SERCOM0_REGS -> USART_INT.SERCOM_CTRLA |= SERCOM_USART_INT_CTRLA_ENABLE(0x1UL);
}

void USART_sendChar(char letter){
    SERCOM0_REGS -> USART_INT.SERCOM_DATA = letter;
}