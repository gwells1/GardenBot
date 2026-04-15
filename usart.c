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
#include <pic32cm1216mc00032.h>

void init_USART(){
    //ToDo: Select Clock
    //ToDo: Select Asynchronous Mode
    //ToDo: Configure RX pin
    //ToDo: Configure TX pin
    //ToDo: Set Character size to 8 bits
    //ToDo: Configure Endianness (MSB first)
    //ToDo: Disable parity mode (for now)
    //ToDo: Set number of stop bits to 1
    //ToDo: Configure baud rate
    //ToDo: Enable the Transmitter (For now, enable receiver later.  Consider enabling the transmitter in another function)
}