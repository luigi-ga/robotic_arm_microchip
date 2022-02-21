/**
  TMR2 Generated Driver File
    File Name   tmr2.c      */

/**
  Section: Included Files
*/

#include <xc.h>
#include "tmr2.h"
#include "interrupt_manager.h"

void B_motor (void);

void TMR2_Initialize(void)
{
    // Set TMR2 to the options selected in the User Interface

    // T2CS LFINTOSC; 
    T2CLKCON = 0x04;

    // T2PSYNC Synchronized; T2MODE Software control; T2CKPOL Rising Edge; T2CKSYNC Synchronized; 
    T2HLT = 0xA0;

    // T2RSEL T2CKIPPS pin; 
    T2RST = 0x00;

    // PR2 154; 
    T2PR = 0x9A;

    // TMR2 0; 
    T2TMR = 0x00;

    // Clearing IF flag before enabling the interrupt.
    PIR4bits.TMR2IF = 0;

    // Enabling TMR2 interrupt.
    PIE4bits.TMR2IE = 1;

    // T2CKPS 1:1; T2OUTPS 1:1; TMR2ON on; 
    T2CON = 0x00;
}



void __interrupt(irq(TMR2),base(8),low_priority) TMR2_ISR()
{  
    B_motor(); 

    TMR2IF=0;
}



/**
  End of File
*/