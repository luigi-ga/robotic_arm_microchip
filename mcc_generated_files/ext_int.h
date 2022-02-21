/* EXT_INT Generated Driver File
   @File Name  ext_int.c
*/
#ifndef _EXT_INT_H
#define _EXT_INT_H
/**
    Section: Includes
*/
#include <xc.h>
/**
    Section: Macros
*/

#define EXT_INT0_InterruptFlagClear()   (PIR1bits.INT0IF = 0)
#define EXT_INT0_InterruptDisable()     (PIE1bits.INT0IE = 0)
#define EXT_INT0_InterruptEnable()      (PIE1bits.INT0IE = 1)
#define EXT_INT0_risingEdgeSet()        (INTCON0bits.INT0EDG = 1)
#define EXT_INT0_fallingEdgeSet()       (INTCON0bits.INT0EDG = 0)

void EXT_INT_Initialize(void);

#endif
