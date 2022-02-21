/* EXT_INT Generated Driver File
   @File Name     ext_int.c
 */ 

 /**
   Section: Includes
 */
#include <xc.h>
#include "ext_int.h"
#include "interrupt_manager.h"
#include "..\RFM70.h"
#include "..\Definitions.h"

//#define LED  LATDbits.LATD2
UINT8 rx_buf[MAX_PACKET_LEN];

//extern unsigned char RX_PORTA;
//extern unsigned char RX_PORTB;

unsigned char RX_PORTA=0xFF;
unsigned char RX_PORTB=0xFF;

unsigned int copia_buf_0=0xFF;
unsigned int copia_buf_1=0xFF;



void __interrupt(irq(INT0),base(8)) INT0_ISR()
{
    EXT_INT0_InterruptFlagClear();

    SPI_Read_Buf(RD_RX_PLOAD,rx_buf,MAX_PACKET_LEN);// read receive payload from RX_FIFO buffer
    SPI_Write_Reg(WRITE_REG|RFM_STATUS,0x7E);// clear RX_DR or TX_DS or MAX_RT interrupt flag

    copia_buf_0= rx_buf[0];
    copia_buf_1= rx_buf[1];
    return;    
}

void EXT_INT_Initialize(void)
{
    // Clear the interrupt flag
    // Set the external interrupt edge detect
    EXT_INT0_InterruptFlagClear();   
    EXT_INT0_fallingEdgeSet();    
    // Set Default Interrupt Handler
    EXT_INT0_InterruptEnable();      
}

