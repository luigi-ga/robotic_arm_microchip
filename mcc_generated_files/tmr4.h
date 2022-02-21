/**
  TMR4 Generated Driver API Header File
    File Name   tmr4.h  */

#ifndef TMR4_H
#define TMR4_H

/**
  Section: Included Files
*/

#include <stdint.h>
#include <stdbool.h>

#define TMR4_StartTimer()  T4CONbits.TMR4ON = 1;
#define TMR4_StopTimer()   T4CONbits.TMR4ON = 0;


void TMR4_Initialize(void);

#endif // TMR4_H
/**
 End of File
*/

