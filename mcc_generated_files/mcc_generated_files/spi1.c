/* SPI1 Generated Driver File    spi1.c
*/
 
/**
  Section: Included Files
*/

#include <xc.h>
#include "spi1.h"

/**
  Section: Macro Declarations
*/

#define SPI_RX_IN_PROGRESS 0x0

/**
  Section: Module APIs
*/

void SPI1_Initialize(void)
{
    // Set the SPI1 module to the options selected in the User Interface
		// SSP active high; SDOP active high; FST disabled; SMP Middle; CKP Idle:Low, Active:High; CKE Active to idle; SDIP active high; 
		SPI1CON1 = 0x40;
		// SSET disabled; RXR suspended if the RxFIFO is full; TXR required for a transfer; 
		SPI1CON2 = 0x03;
		// BAUD 0; 
//		SPI1BAUD = 0x07;
		SPI1BAUD = 31;        
        
		// CLKSEL HFINTOSC; 
		SPI1CLK = 0x01;
		// BMODE last byte; LSBF MSb first; EN enabled; MST bus master; 
		//SPI1CON0 = 0x82;
        SPI1CON0 = 0x83;    //cambiato BMODE=1 sembra più simile a MSSP
}


/**
 End of File
*/