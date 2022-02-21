/* File:   MioRA.c
 * Author: luigi
 *
 * Created on 17 dicembre 2018, 16.37
 */

#include "Definitions.h"


/*SUBROUTINES*/

void LW_motor_LAT (void)                                   /*this subroutine change the port status*/
{
    LAT_copy = LATC;                                         
    LAT_copy = (LAT_copy & conf_pins_1);                  
    LATC = (LAT_copy | LWM_phases[LW_phase]);
}

void RW_motor_LAT (void)                                   /*this subroutine change the port status*/
{
    LAT_copy = LATD;
    LAT_copy = (LAT_copy & conf_pins_1);
    LATD = (LAT_copy | RWM_phases[RW_phase]);
}

void B_motor_LAT (void)                                    /*this subroutine change the port status*/
{
    LAT_copy = LATD;
    LAT_copy = (LAT_copy & conf_pins_2);
    LATD = (LAT_copy | BM_phases[B_phase]);
}

void S_motor_LAT (void)                                    /*this subroutine change the port status*/
{
    LAT_copy = LATC;
    LAT_copy = (LAT_copy & conf_pins_2);
    LATC = (LAT_copy | SM_phases[S_phase]);    
}

void E_motor_LAT (void)                                    /*this subroutine change the port status*/
{
    LAT_copy = LATA;
    LAT_copy = (LAT_copy & conf_pins_2);
    LATA = (LAT_copy | EM_phases[E_phase]);
}

void G_motor_LAT (void)                                    /*this subroutine change the port status*/
{
    LAT_copy = LATA;
    LAT_copy = (LAT_copy & conf_pins_1);
    LATA = (LAT_copy | GM_phases[G_phase]);
}
 

void LW_motor (void)                 /*this subroutine check if the motors have to move*/
{
//    if(lwrist_steps_count != lwrist_steps)    //if the number of desired steps hasn't been reached (clockwise)
//    {
        if(lwrist_steps>0)
        {
           LW_phase++;
//           lwrist_steps_count++;
        }
        else
        {
           LW_phase--;
//           lwrist_steps_count--;            
        }
        if(LW_phase>7) LW_phase=0;
        if(LW_phase<0) LW_phase=7; 
        LW_motor_LAT();
//    }
//    else
//    {
//        T4CONbits.ON=0;                       //fermo timer e motore
//    }
}

void RW_motor (void)                 /*this subroutine check if the motors have to move*/
{
//    if(rwrist_steps_count != rwrist_steps)    //if the number of desired steps hasn't been reached (clockwise)
//    {
        if(rwrist_steps>0)
        {
           RW_phase++;
//           rwrist_steps_count++;
        }
        else
        {
           RW_phase--;
//           rwrist_steps_count--;            
        }
        if(RW_phase>7) RW_phase=0;
        if(RW_phase<0) RW_phase=7; 
        RW_motor_LAT();
//    }
//    else
//    {
//        T6CONbits.ON=0;                       //fermo timer e motore
//    }
}

void B_motor (void)                 /*this subroutine check if the motors have to move*/
{
//    if(base_steps_count != base_steps)    //if the number of desired steps hasn't been reached (clockwise)
//    {
        if(base_steps>0)
        {
           B_phase++;
//           base_steps_count++;
        }
        else
        {
           B_phase--;
//           base_steps_count--;            
        }
        if(B_phase>7) B_phase=0;
        if(B_phase<0) B_phase=7; 
        B_motor_LAT();
//    }
//    else
//    {
//        T2CONbits.ON=0;                       //fermo timer e motore
//    }
}

void S_motor (void)                      /*this subroutine manage the phases of the motors*/
{
    if(shoulder_steps_count !=shoulder_steps)    //if the number of desired steps hasn't been reached (clockwise)
    {
        if(shoulder_steps>0)
        {
            S_phase++;
            shoulder_steps_count++;
        }
        else
        {
            S_phase--;
            shoulder_steps_count--;  
        }
        if(S_phase>7) S_phase=0;
        if(S_phase<0) S_phase=7;
        S_motor_LAT();        
    }
    else
    {
        T1CONbits.ON=0;                       //fermo timer e motore
    }
}

void E_motor (void)                       /*this subroutine manage the phases of the motors*/
{
    if(elbow_steps_count != elbow_steps)    //if the number of desired steps hasn't been reached (clockwise)
    {
        if(elbow_steps>0)
        {
           E_phase++;
           elbow_steps_count++;
        }
        else
        {
           E_phase--;
           elbow_steps_count--;            
        }
        if(E_phase>7) E_phase=0;
        if(E_phase<0) E_phase=7; 
        E_motor_LAT();
    } 
   else
    {
        T3CONbits.ON=0;                       //fermo timer e motore
    }       
}

 



void G_motor (void)                 /*this subroutine check if the motors have to move*/
{
    if(grip_steps_count != grip_steps)    //if the number of desired steps hasn't been reached (clockwise)
    {
        if(grip_steps>0)
        {
            if(SS_grip == 1)
            {
                G_phase++;
                grip_steps_count++;                
            }
            else 
                T5CONbits.ON=0;                 //fermo timer e motore
        }
        else
        {
           G_phase--;
           grip_steps_count--;            
        }
        if(G_phase>7) G_phase=0;
        if(G_phase<0) G_phase=7; 
        G_motor_LAT();
    }
    else
    {
        T5CONbits.ON=0;                 //fermo timer e motore
        grip_steps=0;
    }
}

void SEG_start_check (void)   /*this subroutine check if the motors have to move*/
{    
    if(shoulder_steps != 0)                 //if shoulder motor has to move 
    {
        shoulder_steps_count=0;         
        T1CONbits.ON=1;
    }
    
    if(elbow_steps != 0)                    //if elbow motor has to move
    {
        elbow_steps_count=0;         
        T3CONbits.ON=1;        
    }
    
    if(grip_steps != 0)                    //if elbow motor has to move
    {
        grip_steps_count=0;         
        T5CONbits.ON=1;        
    }
}

//void B_start_check (void)   /*this subroutine check if the motors have to move*/
//{    
//    if(base_steps != 0)                 //if shoulder motor has to move 
//    {
//        base_steps_count=0;  
////        base_steps = 0;
//        T2CONbits.ON=1;
//    }
//}

void G_start_check (void)   /*this subroutine check if the motors have to move*/
{    
    if(grip_steps != 0)                 //if shoulder motor has to move 
    {
        grip_steps_count=0;  
//        grip_steps = 0;
        T5CONbits.ON=1;
    }
}

//void LWRW_start_check (void)   /*this subroutine check if the motors have to move*/
//{    
//    if(lwrist_steps != 0)                 //if shoulder motor has to move 
//    {
//        lwrist_steps_count=0;  
//        lwrist_steps = 0;
//        T4CONbits.ON=1;
//    }
//    
//    if(rwrist_steps != 0)                 //if shoulder motor has to move 
//    {
//        rwrist_steps_count=0;  
//        rwrist_steps = 0;
//        T6CONbits.ON=1;
//    }
//}