/**
  TMR6 Generated Driver API Header File
    File Name   tmr6.h  */

#ifndef TMR6_H
#define TMR6_H

/**
  Section: Included Files
*/

//#include <stdint.h>
//#include <stdbool.h>

#define TMR6_StartTimer()  T6CONbits.TMR6ON = 1;
#define TMR6_StopTimer()   T6CONbits.TMR6ON = 0;


void TMR6_Initialize(void);

#endif // TMR6_H
/**
 End of File
*/

