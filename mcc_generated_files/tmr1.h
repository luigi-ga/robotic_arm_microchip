/**
  TMR1 Generated Driver API Header File
  File Name    tmr1.h           */

#ifndef TMR1_H
#define TMR1_H

/**
  Section: Included Files
*/
//#include <stdbool.h>
//#include <stdint.h>

/**
  Section: TMR1 APIs
*/

#define TMR1_StartTimer()  T1CONbits.TMR1ON = 1;
#define TMR1_StopTimer()   T1CONbits.TMR1ON = 0;

void TMR1_Initialize(void);


#endif // TMR1_H
/**
 End of File
*/
