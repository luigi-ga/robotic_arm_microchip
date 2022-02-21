
/* File:
 * Author: 
 * Comments:
 * Revision history: 
 */

#ifndef FUNZIONI_H
#define	FUNZIONI_H

#include <xc.h> // include processor files - each processor file is guarded.  


void LW_motor_LAT (void);                           /*this subroutine change the port status*/

void RW_motor_LAT (void);                           /*this subroutine change the port status*/

void B_motor_LAT (void);                            /*this subroutine change the port status*/

void S_motor_LAT (void);                            /*this subroutine change the port status*/

void E_motor_LAT (void);                            /*this subroutine change the port status*/

void G_motor_LAT (void);                            /*this subroutine change the port status*/

void SEG_start_check (void);

//void B_start_check(void);

void G_start_check(void);

void LWRW_start_check(void);


#endif	/* FUNZIONI_H */