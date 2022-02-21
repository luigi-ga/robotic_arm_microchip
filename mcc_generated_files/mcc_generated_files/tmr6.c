/**
  TMR6 Generated Driver File
File Name   tmr6.c    */

/**
  Section: Included Files
*/

#include <xc.h>
#include "tmr6.h"
#include "interrupt_manager.h"

void RW_motor (void);

void TMR6_Initialize(void)
{
    // Set TMR6 to the options selected in the User Interface

    // T6CS LFINTOSC; 
    T6CLKCON = 0x04;

    // T6PSYNC Synchronized; T6MODE Software control; T6CKPOL Rising Edge; T6CKSYNC Synchronized; 
    T6HLT = 0xA0;

    // T6RSEL T6CKIPPS pin; 
    T6RST = 0x00;

    // PR6 154; 
    T6PR = 0x9A;

    // TMR6 0; 
    T6TMR = 0x00;

    // Clearing IF flag before enabling the interrupt.
    PIR9bits.TMR6IF = 0;

    // Enabling TMR6 interrupt.
    PIE9bits.TMR6IE = 1;

    // T6CKPS 1:1; T6OUTPS 1:1; TMR6ON on; 
    T6CON = 0x00;
}

void __interrupt(irq(TMR6),base(8),low_priority) TMR6_ISR()
{ 
    RW_motor(); 

    TMR6IF=0;
}

/**
  End of File
*/