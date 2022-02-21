/**
  TMR3 Generated Driver File
    File Name   tmr3.c      */

/**
  Section: Included Files
*/

#include <xc.h>
#include "tmr3.h"
#include "interrupt_manager.h"

void E_motor (void);

void TMR3_Initialize(void)
{
    //Set the Timer to the options selected in the GUI

    //T3GE disabled; T3GTM disabled; T3GPOL low; T3GGO done; T3GSPM disabled; 
    T3GCON = 0x00;

    //GSS T3G_pin; 
    T3GATE = 0x00;

    //CS FOSC; 
    T3CLK = 0x02;

    //TMR3H 99; 
    TMR3H = 0x63;

    //TMR3L 192; 
    TMR3L = 0xC0;

    // Clearing IF flag before enabling the interrupt.
    PIR6bits.TMR3IF = 0;

    // Enabling TMR3 interrupt.
    PIE6bits.TMR3IE = 1;

    // CKPS 1:1; NOT_SYNC synchronize; TMR3ON enabled; T3RD16 disabled; 
    T3CON = 0x32;
}



void __interrupt(irq(TMR3),base(8),low_priority) TMR3_ISR()
{
    E_motor();
    
    TMR3H = 0x63;
    TMR3L = 0xC0;

    TMR3IF=0;
}


/**
  End of File
*/
