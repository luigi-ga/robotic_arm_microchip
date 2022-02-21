/**
  TMR4 Generated Driver File
    File Name   tmr4.c  */

/**
  Section: Included Files
*/

#include <xc.h>
#include "tmr4.h"
#include "interrupt_manager.h"

void LW_motor (void);

void TMR4_Initialize(void)
{
    // Set TMR4 to the options selected in the User Interface

    // T4CS LFINTOSC; 
    T4CLKCON = 0x04;

    // T4PSYNC Synchronized; T4MODE Software control; T4CKPOL Rising Edge; T4CKSYNC Synchronized; 
    T4HLT = 0xA0;

    // T4RSEL T4CKIPPS pin; 
    T4RST = 0x00;

    // PR4 154; 
    T4PR = 0x9A;

    // TMR4 0; 
    T4TMR = 0x00;

    // Clearing IF flag before enabling the interrupt.
    PIR7bits.TMR4IF = 0;

    // Enabling TMR4 interrupt.
    PIE7bits.TMR4IE = 1;

    // T4CKPS 1:1; T4OUTPS 1:1; TMR4ON on; 
    T4CON = 0x00;
}





void __interrupt(irq(TMR4),base(8),low_priority) TMR4_ISR()
{
    LW_motor();  

    TMR4IF=0;    
}


/**
  End of File
*/