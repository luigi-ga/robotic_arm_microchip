/* File:   
 * Author: 
 * Comments:
 * Revision history: 
 */
  
#ifndef XC_HEADER_TEMPLATE_H
#define	XC_HEADER_TEMPLATE_H

#include <xc.h> // include processor files - each processor file is guarded.  

// TODO Insert appropriate #include <>

#define conf_pins_1 0b00001111    //motor phases are on LAT 0,1,2,3
#define conf_pins_2 0b11110000    //motor phases are on LAT 4,5,6,7

/*LEFT WRIST PINS DEFINE*/
#define LWM_1 LATC4               //phase 1 left wrist motor
#define LWM_2 LATC5               //phase 2 left wrist motor
#define LWM_3 LATC6               //phase 3 left wrist motor
#define LWM_4 LATC7               //phase 4 left wrist motor

/*RIGHT WRIST PINS DEFINE*/
#define RWM_1 LATD5               //phase 1 right wrist motor
#define RWM_2 LATD4               //phase 2 right wrist motor
#define RWM_3 LATD7               //phase 3 right wrist motor
#define RWM_4 LATD6               //phase 4 right wrist motor

/*BASE MOTOR PINS DEFINE*/
#define BM_1 LATD3                //phase 1 base motor
#define BM_2 LATD0                //phase 2 base motor
#define BM_3 LATD2                //phase 3 base motor
#define BM_4 LATD1                //phase 4 base motor

/*SHOULDER MOTOR PINS DEFINE*/
#define SM_1 LATC0                //phase 1 shoulder motor
#define SM_2 LATC2                //phase 2 shoulder motor
#define SM_3 LATC1                //phase 3 shoulder motor
#define SM_4 LATC3                //phase 4 shoulder motor

/*ELBOW MOTOR PINS DEFINE*/
#define EM_1 LATA2                //phase 1 elbow motor
#define EM_2 LATA0                //phase 2 elbow motor
#define EM_3 LATA3                //phase 3 elbow motor
#define EM_4 LATA1                //phase 4 elbow motor

/*GRIP MOTOR PINS DEFINE*/
#define GM_1 LATA6                //phase 1 grip motor
#define GM_2 LATA5                //phase 2 grip motor
#define GM_3 LATA7                //phase 3 grip motor
#define GM_4 LATA4                //phase 4 grip motor

/*GRIP STATUS*/
#define grip_close 0
#define grip_open  1

/*PUSH BUTTON*/
//#define PB_1 PORTBbits.RB5                  //push button 1
//#define PB_2 PORTBbits.RB4                  //push button 2
//#define PB_3 PORTAbits.RA2                  //push button 3
//#define PB_4 PORTAbits.RA1                  //push button 4


#define PB_pitch_down   (RX_PORTA & 0b00000001)
#define PB_backward     (RX_PORTA & 0b00000010)
#define PB_right        (RX_PORTA & 0b00000100)
#define PB_left         (RX_PORTA & 0b00001000)
#define PB_forward      (RX_PORTA & 0b00010000)
#define PB_pitch_up     (RX_PORTA & 0b00100000)

#define PB_open         (RX_PORTB & 0b00000001)
#define PB_up           (RX_PORTB & 0b00000010)
#define PB_roll_cw      (RX_PORTB & 0b00000100)
#define PB_roll_ccw     (RX_PORTB & 0b00001000)
#define PB_down         (RX_PORTB & 0b00010000)
#define PB_close        (RX_PORTB & 0b00100000)




/*SNAP SWITCH*/
#define SS_grip PORTEbits.RE2                    //snap switch on grip

/*ROBOT DIMENSIONS DEFINE (mm)*/
#define H 196.67                  //shoulder height                     
#define L 177.8                   //arm and forearm length
#define LL 86.52                  //hand lenght


/*STEP CONVERSION FACTORS*/
#define step_rad_base 1125.0             //step per radians on base motor
#define step_rad_shoulder 1125.0         //step per radians on shoulder motor
#define step_rad_elbow 672.0             //step per radians on elbow motor
#define step_rad_lwrist 241.0            //step per radians on lwrist motor
#define step_rad_rwrist 241.0            //step per radians on rwrist motor
#define step_mill_grip 14.6              //spep per millimeter on grip motor

/*MAX TIMER VALUE*/
#define min_timer_value 10000
#define max_timer_value 65535


/*VARIABLES*/

float X_c, Y_c, Z_c;                    //X,Y,Z coordinates
float Roll, Pitch;                      
float RR, R0, Z0;

float alfa, beta;
float base_rad, shoulder_rad, elbow_rad;
float pitch, roll;

//int lwrist_steps_copy;
int lwrist_steps;           //left wrist motor steps to take
int lwrist_steps_count;     //left wrist motor steps taken

//int rwrist_steps_copy;
int rwrist_steps;           //right wrist motor steps to take
int rwrist_steps_count;     //right wrist motor steps taken

//int base_steps_copy;
int base_steps;             //base motor steps to take
int base_steps_count;       //base motor steps taken

//int shoulder_steps_copy;
int shoulder_steps;         //shoulder motor step to take
int shoulder_steps_count;   //shoulder motor steps taken

//int elbow_steps_copy;
int elbow_steps;            //elbow motor step
int elbow_steps_count;      //elbow motor steps taken

float real_base_rad;
float real_shoulder_rad;
float real_elbow_rad;   

float next_shoulder_rad;
float next_elbow_rad; 

int next_shoulder_steps;
int next_elbow_steps; 
int next_grip_steps;

//signed char next_shoulder_direction;
//signed char next_elbow_direction;

int grip_steps;             //grip motor step
int grip_steps_count;       //grip motor steps taken
bit grip;

unsigned char TMR0H_value;
unsigned char TMR0L_value;
unsigned char TMR1H_value;
unsigned char TMR1L_value;
unsigned char TMR3H_value;
unsigned char TMR3L_value;

unsigned char next_TMR1H_value;
unsigned char next_TMR1L_value;
unsigned char next_TMR3H_value;
unsigned char next_TMR3L_value;


/*DEFINE PHASE SEQUENCE*/

unsigned char LWM_phases[8] =    //phase sequence for left wrist motor
{
    0b00010000,                  //C4     
    0b01010000,                  //C4-C6    
    0b01000000,                  //C6    
    0b01100000,                  //D6-C5    
    0b00100000,                  //C5   
    0b10100000,                  //C5-C7    
    0b10000000,                  //C7    
    0b10010000                   //C7-C4  
};
signed char LW_phase;            //this variables indicates the currently active phase

unsigned char RWM_phases[8] =    //phase sequence for right wrist motor
{
    0b00100000,                  //D5
    0b10100000,                  //D5-D7
    0b10000000,                  //D7
    0b10010000,                  //D7-D4
    0b00010000,                  //D4
    0b01010000,                  //D4-D6
    0b01000000,                  //D6
    0b01100000                   //D6-D5    
}; 
signed char RW_phase;            //this variables indicates the currently active phase

unsigned char BM_phases[8] =     //phase sequence for base motor
{
    0b00001000,                  //D3
    0b00001001,                  //D3-D0
    0b00000001,                  //D0
    0b00000101,                  //D0-D2
    0b00000100,                  //D2
    0b00000110,                  //D2-D1
    0b00000010,                  //D1
    0b00001010                   //D1-D3
};   
signed char B_phase;             //this variables indicates the currently active phase

unsigned char SM_phases[8] =     //phase sequence for shoulder motor
{
    0b00000001,                  //C0
    0b00000101,                  //C0-C2
    0b00000100,                  //C2
    0b00000110,                  //C2-C1
    0b00000010,                  //C1
    0b00001010,                  //C1-C3
    0b00001000,                  //C3
    0b00001001                   //C3-C0
}; 
signed char S_phase;             //this variables indicates the currently active phase
 
unsigned char EM_phases[8] =     //phase sequence for elbow motor
{
    0b00000100,                  //A2
    0b00000101,                  //A2-A0
    0b00000001,                  //A0
    0b00001001,                  //A0-A3
    0b00001000,                  //A3
    0b00001010,                  //A3-A1
    0b00000010,                  //A1
    0b00000110                   //A1-A2
};  
signed char E_phase;             //this variables indicates the currently active phase

unsigned char GM_phases[8] =     //phase sequence for grip motor
{
    0b01000000,                  //A6
    0b01100000,                  //A6-A5
    0b00100000,                  //A5
    0b10100000,                  //A5-A7
    0b10000000,                  //A7
    0b10010000,                  //A7-A4
    0b00010000,                  //A4
    0b01010000                   //A4-A6
}; 
signed char G_phase;             //this variables indicates the currently active phase 


unsigned char LAT_copy;

#endif	/* XC_HEADER_TEMPLATE_H */
