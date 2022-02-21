/*
 * File:   Robotic Arm.c
 * Author: luigi
 *
 * Created on 17 dicembre 2018, 16.37
 */

#include <math.h> 
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "Definitions.h"
#include "Functions.h"
#include "mcc_generated_files/mcc.h"
#include "RFM70.h"



void motors_off (void)
{
    LWM_1 = LWM_2 = LWM_3 = LWM_4 = 0;
    RWM_1 = RWM_2 = RWM_3 = RWM_4 = 0;
    BM_1 = BM_2 = BM_3 = BM_4 = 0;
    SM_1 = SM_2 = SM_3 = SM_4 = 0;
    EM_1 = EM_2 = EM_3 = EM_4 = 0;
    GM_1 = GM_2 = GM_3 = GM_4 = 0;
}

void elbow_shoulder_motors_off (void)
{
    SM_1 = SM_2 = SM_3 = SM_4 = 0;
    EM_1 = EM_2 = EM_3 = EM_4 = 0;
}


void base_motors_off (void)
{
    BM_1 = BM_2 = BM_3 = BM_4 = 0;
}

void grip_motors_off (void)
{
    GM_1 = GM_2 = GM_3 = GM_4 = 0;    
}


void pitch_roll_motors_off (void)
{
   LWM_1 = LWM_2 = LWM_3 = LWM_4 = 0;
   RWM_1 = RWM_2 = RWM_3 = RWM_4 = 0;
}



void rad_calculation_auto (void)             /*this subroutine calculates the radians in automatic mode*/
{   
    base_rad = atan(Y_c/X_c);                //base radians calculation

    RR = sqrt(X_c*X_c+Y_c*Y_c);

    R0 = RR-LL*cos(Pitch);
    Z0 = Z_c-LL*sin(Pitch)-H;
    beta = atan(Z0/R0);
     
    alfa = (R0*R0+Z0*Z0);
    alfa = (4*L*L)/alfa-1;
    alfa = atan(sqrt(alfa));

    shoulder_rad = alfa+beta;                //shoulder radians calculation
    elbow_rad = beta-alfa;                   //eblow radians calculation    
}


void rad_calculation_manual (void)           /*this subroutine calculates the radians in automatic mode*/
{   
    beta = atan(Z0/R0);
    alfa = (R0*R0+Z0*Z0);
    alfa = (4*L*L)/alfa-1;
    alfa = atan(sqrt(alfa));
    shoulder_rad = alfa+beta;                //shoulder radians calculation
    elbow_rad = beta-alfa;                   //eblow radians calculation    
}

void next_rad_calculation_manual (void)           /*this subroutine calculates the radians in automatic mode*/
{   
    beta = atan(Z0/R0);
    alfa = (R0*R0+Z0*Z0);
    alfa = (4*L*L)/alfa-1;
    alfa = atan(sqrt(alfa));
    next_shoulder_rad = alfa+beta;                //shoulder radians calculation
    next_elbow_rad = beta-alfa;                   //eblow radians calculation    
}

void steps_calculation (void)          /*this subroutine calculates the steps*/
{
    shoulder_steps = round((shoulder_rad - real_shoulder_rad) * step_rad_shoulder);
    elbow_steps = round((elbow_rad - real_elbow_rad) * step_rad_elbow); 
    grip_steps = elbow_steps;
}

void next_steps_calculation (void)
{
    next_shoulder_steps = round((next_shoulder_rad - real_shoulder_rad) * step_rad_shoulder);
    next_elbow_steps = round((next_elbow_rad - real_elbow_rad) * step_rad_elbow);
    next_grip_steps = next_elbow_steps;
}

void real_rad_calculation (void)
{
    real_shoulder_rad += ((float)shoulder_steps / step_rad_shoulder);
    real_elbow_rad    += ((float)elbow_steps / step_rad_elbow);
}

void rad_copy (void)
{
    real_shoulder_rad= shoulder_rad;
    real_elbow_rad = elbow_rad;  
}

void values_update(void)
{
    shoulder_rad= next_shoulder_rad;
    elbow_rad = next_elbow_rad; 
    shoulder_steps = next_shoulder_steps;
    elbow_steps = next_elbow_steps;  
    grip_steps = next_grip_steps;
}



#define stopped              0
#define move_forward         1
#define move_backwards       2
#define move_up              3
#define move_down            4
#define move_forward_up      5
#define move_forward_down    6
#define move_backwards_up    7
#define move_backwards_down  8
#define turn_left            9
#define turn_right           10
#define open                 11
#define close                12
#define pitch_up             13
#define pitch_down           14
#define roll_cw              15
#define roll_ccw             16

#define LED   LATEbits.LATE0  
#define LED1  LATEbits.LATE1 


extern unsigned char RX_PORTA;
extern unsigned char RX_PORTB;

extern unsigned int copia_buf_0;
extern unsigned int copia_buf_1;

void main(void) 
{
    unsigned char elbow_shoulder_state = stopped;
    unsigned char base_state = stopped;
    unsigned char grip_state = stopped;
//    unsigned char pitch_state = stopped;
    unsigned char pitch_roll_state = stopped;
    
    SYSTEM_Initialize();
    RFM70_Initialize();
    SwitchToRxMode(); 

     __delay_ms(1000);   
    
//    LED1=0;
//    __delay_ms(2000);
//    LED1=1;
//    __delay_ms(2000);    
//     LED1=0;
//    __delay_ms(2000);
//    LED1=1;
//    __delay_ms(2000);    
    
  
    lwrist_steps = 0;      //positive counterclockwise - negative clockwise
    rwrist_steps = 0;      //positive counterclockwise - negative clockwise 
    base_steps = 0;        //positive left - negative right
    shoulder_steps = 0;    //positve up - negatve down
    elbow_steps = 0;       //positive extends - negative whithdraws
    grip_steps = 0;        //negative open - positive close
        
    /*STARTING COORDINATES*/    
    X_c = 130;  
    Y_c = 0;
    Z_c = 0;
    Roll = 0;
    Pitch = -M_PI/2;
    
    rad_calculation_auto();
    rad_copy();
 
    
    /*NEXT COORDINATES*/
    X_c = 130;
    Y_c = 0;
    Z_c = 50;
    Roll = 0;
    Pitch = -M_PI/2;
    
    rad_calculation_auto();
    steps_calculation();
    real_rad_calculation();
    
    /*STARTING PHASE*/
    LW_phase = 3; 
    RW_phase = 3; 
    B_phase = 3; 
    S_phase = 3; 
    E_phase = 3; 
    G_phase = 3; 
    
    GIEH=1;             //high_priority interrupt enabled
    GIEL=0;             //low_priority interrupt disabled
    GIE=1;    
    
    while(PB_forward)
    {
        EXT_INT0_InterruptDisable();    
        RX_PORTA= copia_buf_0;
        RX_PORTB= copia_buf_1;
        EXT_INT0_InterruptEnable();        
    }    
        

    SEG_start_check();
    GIEL=1;                       //low_priority interrupt enabled    
  
    while ((T3CONbits.TMR3ON==1) || (T1CONbits.TMR1ON==1) || (T5CONbits.TMR5ON==1));
         
    while(1)
    {
        EXT_INT0_InterruptDisable();    
        RX_PORTA= copia_buf_0;
        RX_PORTB= copia_buf_1;
        EXT_INT0_InterruptEnable();         
     
        
        
        
        switch (elbow_shoulder_state)
        { 
            case stopped:
                elbow_shoulder_motors_off();
                
                if(PB_forward_on())
                {
                    R0++; 
                    rad_calculation_manual();
                    steps_calculation();                    
                    real_rad_calculation(); 
  
                    R0++; 
                    next_rad_calculation_manual();
                    next_steps_calculation(); 

                    SEG_start_check (); 
                    elbow_shoulder_state = move_forward;
                } 
                
                if(PB_backward_on())
                {
                    R0--;
                    rad_calculation_manual();
                    steps_calculation();                    
                    real_rad_calculation();
  
                    R0--;
                    next_rad_calculation_manual();
                    next_steps_calculation(); 

                    SEG_start_check ();  
                    elbow_shoulder_state = move_backwards;
                }    
                
                if(PB_up_on())
                {
                    Z0++; 
                    rad_calculation_manual();
                    steps_calculation();                    
                    real_rad_calculation();
  
                    Z0++; 
                    next_rad_calculation_manual();
                    next_steps_calculation(); 

                    SEG_start_check(); 
                    elbow_shoulder_state = move_up;
                } 
                
                if(PB_down_on())
                {
                    Z0--; 
                    rad_calculation_manual();
                    steps_calculation();                    
                    real_rad_calculation();
  
                    Z0--; 
                    next_rad_calculation_manual();
                    next_steps_calculation(); 

                    SEG_start_check(); 
                    elbow_shoulder_state = move_down;
                }               
            break;             
            
            case move_forward:
                if((T1CONbits.ON==0) && (T3CONbits.ON==0) && (T5CONbits.ON==0))
                { 
                    if(PB_forward_off())
                    {
                        R0--;
                        elbow_shoulder_state = stopped;                        
                    }
                    else //(PB_1==0
                    {        
                        values_update();
                        SEG_start_check();
                        real_rad_calculation();
                        R0++;
                        next_rad_calculation_manual();
                        next_steps_calculation();
                        
                        if(PB_up_on()) elbow_shoulder_state = move_forward_up;
                        if(PB_down_on()) elbow_shoulder_state = move_forward_down;
                    }
                }
            break; 
            
            case move_backwards:
                if((T1CONbits.ON==0) && (T3CONbits.ON==0) && (T5CONbits.ON==0))
                { 
                    if(PB_backward_off())
                    {
                        R0++;
                        elbow_shoulder_state = stopped;                        
                    }
                    else //(PB_2==0
                    {
                        values_update();
                        SEG_start_check();
                        real_rad_calculation();
                        R0--;
                        next_rad_calculation_manual();
                        next_steps_calculation();
                        
                        if(PB_up_on()) elbow_shoulder_state = move_backwards_up;
                        if(PB_down_on()) elbow_shoulder_state = move_backwards_down;
                    }
                }
            break;    
                        
            case move_up:
                if((T1CONbits.ON==0) && (T3CONbits.ON==0) && (T5CONbits.ON==0))
                { 
                    if(PB_up_off())
                    {
                        Z0--;
                        elbow_shoulder_state = stopped;                        
                    }
                    else 
                    {
                        values_update();
                        SEG_start_check();
                        real_rad_calculation();
                        Z0++;
                        next_rad_calculation_manual();
                        next_steps_calculation();
                        
                        if(PB_forward_on()) elbow_shoulder_state = move_forward_up;
                        if(PB_backward_on()) elbow_shoulder_state = move_backwards_up;
                    }
                }
            break; 
            
            case move_down:
                if((T1CONbits.ON==0) && (T3CONbits.ON==0) && (T5CONbits.ON==0))
                { 
                    if(PB_down_off())
                    {
                        Z0++;
                        elbow_shoulder_state = stopped;                        
                    }
                    else 
                    {
                        values_update();
                        SEG_start_check();
                        real_rad_calculation();
                        Z0--;
                        next_rad_calculation_manual();
                        next_steps_calculation();
                        
                        if(PB_forward_on()) elbow_shoulder_state = move_forward_down;
                        if(PB_backward_on()) elbow_shoulder_state = move_backwards_down;
                    }
                }
            break; 
            
            case move_forward_up:
                if((T1CONbits.ON==0) && (T3CONbits.ON==0) && (T5CONbits.ON==0))
                { 
                    if(PB_forward_off())
                    {
                        R0--;
                        elbow_shoulder_state = move_up;                        
                    }  
                    
                    if(PB_up_off())
                    {
                        Z0--;
                        elbow_shoulder_state = move_forward;                        
                    }
                    
                    if((PB_forward_on())&&(PB_up_on())) 
                    {
                        values_update();
                        SEG_start_check();
                        real_rad_calculation();
                        R0++;
                        Z0++;
                        next_rad_calculation_manual();
                        next_steps_calculation();
                    }
                }
            break; 
            
            case move_forward_down:
                if((T1CONbits.ON==0) && (T3CONbits.ON==0) && (T5CONbits.ON==0))
                { 
                    if(PB_forward_off())
                    {
                        R0--;
                        elbow_shoulder_state = move_down;                        
                    }
                    
                    if(PB_down_off())
                    {
                        Z0++;
                        elbow_shoulder_state = move_forward;                        
                    }
                    
                    if((PB_forward_on())&&(PB_down_on()))
                    {
                        values_update();
                        SEG_start_check();
                        real_rad_calculation();
                        R0++;
                        Z0--;
                        next_rad_calculation_manual();
                        next_steps_calculation();
                    }
                }
            break; 
            
            case move_backwards_up:
                if((T1CONbits.ON==0) && (T3CONbits.ON==0) && (T5CONbits.ON==0))
                { 
                    if(PB_backward_off())
                    {
                        R0++;
                        elbow_shoulder_state = move_up;                        
                    }
                    
                    if(PB_up_off())
                    {
                        Z0--;
                        elbow_shoulder_state = move_backwards;                        
                    }
                    
                    if((PB_backward_on())&&(PB_up_on()))
                    {
                        values_update();
                        SEG_start_check();
                        real_rad_calculation();
                        R0--;
                        Z0++;
                        next_rad_calculation_manual();
                        next_steps_calculation();
                    }
                }
            break; 
            
            case move_backwards_down:
                if((T1CONbits.ON==0) && (T3CONbits.ON==0) && (T5CONbits.ON==0))
                { 
                    if(PB_backward_off())
                    {
                        R0++;
                        elbow_shoulder_state = move_down;                        
                    }
                    
                    if(PB_down_off())
                    {
                        Z0++;
                        elbow_shoulder_state = move_backwards;                        
                    }
                    
                    if((PB_backward_on())&&(PB_down_on()))
                    {
                        values_update();
                        SEG_start_check();
                        real_rad_calculation();
                        R0--;
                        Z0--;
                        next_rad_calculation_manual();
                        next_steps_calculation();
                    }
                }
            break;   
        } 
        
        
        
        switch (base_state)
        {
            case stopped:
                
                base_motors_off();
                
                if (PB_left_on())
                {
                    base_steps=1;
                    T2CONbits.ON=1;
                    base_state = turn_left;
                }
                
                if (PB_right_on())
                {
                    base_steps=-1;
                    T2CONbits.ON=1;                    
                    
                    base_state = turn_right;
                }                
            break;
                
            case turn_left:
                if (PB_left_off())
                {
                    T2CONbits.ON=0;                     
                    base_state = stopped;                    
                }
            break;
            
            case turn_right:
                if (PB_right_off())
                {
                    T2CONbits.ON=0;                     
                    base_state = stopped;                    
                }    
            break;                
        }
        

      

        
        switch (grip_state)
        {
            case stopped:
                
                if(PB_open_on())
                {
                    grip_steps++;                    
                    G_start_check();
                    grip_state = open;
                }
                
                if(PB_close_on())
                {
                    grip_steps--;                   
                    G_start_check();
                    grip_state = close;
                }                
            break;
                
            case open:
                if(T5CONbits.ON==0)
                {                     
                    if(PB_open_on())
                    {
                        G_start_check();
                        grip_steps++;
                    }
                    else
                    {                        
                        grip_state = stopped;
                    }
                }
            break;
            
            case close:
                if(T5CONbits.ON==0)
                {                     
                    if(PB_close_on())
                    {                        
                        G_start_check();
                        grip_steps--;
                    }
                    else
                    {
                        grip_state = stopped;
                    }
                }
            break;                
        }
        
        
        
        
        switch (pitch_roll_state)
        {
            case stopped:
                pitch_roll_motors_off();
                
                if(PB_pitch_up_on())
                {
                    lwrist_steps= 1;
                    rwrist_steps=-1;                   
                    T4CONbits.ON=1;
                    T6CONbits.ON=1;       
                    pitch_roll_state = pitch_up;
                }
                
                if(PB_pitch_down_on())
                {
                    lwrist_steps=-1;
                    rwrist_steps= 1;                   
                    T4CONbits.ON=1;
                    T6CONbits.ON=1;      
                    pitch_roll_state = pitch_down;
                } 

                if(PB_roll_cw_on())
                {
                    lwrist_steps= 1;
                    rwrist_steps= 1;                   
                    T4CONbits.ON=1;
                    T6CONbits.ON=1;                        
                    pitch_roll_state = roll_cw;
                }
                
                if(PB_roll_ccw_on())
                {
                    lwrist_steps= -1;
                    rwrist_steps= -1;                   
                    T4CONbits.ON=1;
                    T6CONbits.ON=1;                        
                    pitch_roll_state = roll_ccw;
                }    
            break;
                
            case pitch_up:
                if (PB_pitch_up_off())
                {
                    T4CONbits.ON=0;
                    T6CONbits.ON=0;  
                    pitch_roll_state = stopped;                    
                }                       
            break;
            
            case pitch_down:
                if (PB_pitch_down_off())
                {
                    T4CONbits.ON=0;
                    T6CONbits.ON=0;                      
                    pitch_roll_state = stopped;                    
                }                   
            break;  
            
            case roll_cw:
                if (PB_roll_cw_off())
                {
                    T4CONbits.ON=0;
                    T6CONbits.ON=0;                      
                    pitch_roll_state = stopped;                    
                }                   
            break; 
            
            case roll_ccw:
                if (PB_roll_ccw_off())
                {
                    T4CONbits.ON=0;
                    T6CONbits.ON=0;                      
                    pitch_roll_state = stopped;                    
                }                   
            break;         
        }        
    }
}
