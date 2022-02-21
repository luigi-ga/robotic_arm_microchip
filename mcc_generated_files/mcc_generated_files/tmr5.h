/**
  TMR5 Generated Driver API Header File
    File Name   tmr5.h  */

#ifndef TMR5_H
#define TMR5_H

/**
  Section: Included Files
*/

//#include <stdbool.h>
//#include <stdint.h>

/**
  Section: TMR5 APIs
*/
#define TMR5_StartTimer()  T5CONbits.TMR5ON = 1;
#define TMR5_StopTimer()   T5CONbits.TMR5ON = 0;

void TMR5_Initialize(void);


#endif // TMR5_H
/**
 End of File
*/
