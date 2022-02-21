/**
  TMR1 Generated Driver File
  File Name  tmr1.c                 */

/**
  Section: TMR1 APIs
*/

#include <xc.h>
#include "tmr1.h"
#include "interrupt_manager.h"

void S_motor (void);

void TMR1_Initialize(void)
{
    //Set the Timer to the options selected in the GUI

    //T1GE disabled; T1GTM disabled; T1GPOL low; T1GGO done; T1GSPM disabled; 
    T1GCON = 0x00;

    //GSS T1G_pin; 
    T1GATE = 0x00;

    //CS FOSC; 
    T1CLK = 0x02;

    //TMR1H 99; 
    TMR1H = 0x63;

    //TMR1L 192; 
    TMR1L = 0xC0;

    // Clearing IF flag before enabling the interrupt.
    PIR4bits.TMR1IF = 0;

    // Enabling TMR1 interrupt.
    PIE4bits.TMR1IE = 1;


    // CKPS 1:8; NOT_SYNC synchronize; TMR1ON enabled; T1RD16 enabled; 
    T1CON = 0x32;
}



void __interrupt(irq(TMR1),base(8),low_priority) TMR1_ISR()
{
    S_motor();     
                
    TMR1H = 0x63;
    TMR1L = 0xC0;

    TMR1IF=0;
}


/**
  End of File
*/
