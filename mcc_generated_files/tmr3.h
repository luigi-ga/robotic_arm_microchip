/**
  TMR3 Generated Driver API Header File
  File Name   tmr3.h        */

#ifndef TMR3_H
#define TMR3_H

/**
  Section: Included Files
*/

//#include <stdbool.h>
//#include <stdint.h>

/**
  Section: TMR3 APIs
*/

#define TMR3_StartTimer()  T3CONbits.TMR3ON = 1;
#define TMR3_StopTimer()   T3CONbits.TMR3ON = 0;

void TMR3_Initialize(void);


#endif // TMR3_H
/**
 End of File
*/
