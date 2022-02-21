/**
  TMR5 Generated Driver File
  File Name     tmr5.c      */

/**
  Section: Included Files
*/

#include <xc.h>
#include "tmr5.h"
#include "interrupt_manager.h"

void G_motor (void);

void TMR5_Initialize(void)
{
    //Set the Timer to the options selected in the GUI

    //T5GE disabled; T5GTM disabled; T5GPOL low; T5GGO done; T5GSPM disabled; 
    T5GCON = 0x00;

    //GSS T5G_pin; 
    T5GATE = 0x00;

    //CS FOSC; 
    T5CLK = 0x02;

    //TMR5H 99; 
    TMR5H = 0x63;

    //TMR5L 192; 
    TMR5L = 0xC0;

    // Clearing IF flag before enabling the interrupt.
    PIR8bits.TMR5IF = 0;

    // Enabling TMR5 interrupt.
    PIE8bits.TMR5IE = 1;

    // CKPS 1:1; NOT_SYNC synchronize; TMR5ON enabled; T5RD16 disabled; 
    T5CON = 0x32;
}


void __interrupt(irq(TMR5),base(8),low_priority) TMR5_ISR()
{
    G_motor();

    TMR5H = 0x63;
    TMR5L = 0xC0;

    TMR5IF=0;
}
/**
  End of File
*/
