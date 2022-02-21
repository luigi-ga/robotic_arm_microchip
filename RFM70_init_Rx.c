/*Copyright(c) 2019
   Project name: Rx   File: main_Rx.c, RFM70_init_Rx.c, RFM70.h
   Description: prova di trasmissione con RFM70
   MCU: PIC16F886   Oscillator: Interno con I/O su pin, 8 MHz
   Data:  16.04.2019                                              */

//#define _XTAL_FREQ 8000000

//#include "config_word_18F47K42.h"
#include <xc.h>
#include "RFM70.h"
#include "mcc_generated_files/mcc.h"
//Bank1 register initialization value

//In the array RegArrFSKAnalog,all the register value is the byte reversed!!!!!!!!!!!!!!!!!!!!!
const unsigned long Bank1_Reg0_13[]={       //latest config txt
0xE2014B40,
0x00004BC0,
0x028CFCD0,
0x41390099,
0x0B869Ef9,
0xA67F0624,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00127300,
0x36B48000,
};

const UINT8 Bank1_Reg14[]=
{
	0x41,0x20,0x08,0x04,0x81,0x20,0xCF,0xF7,0xFE,0xFF,0xFF
};

//Bank0 register initialization value
const UINT8 Bank0_Reg[][2]={
//{0,0x0F},//reflect RX_DR\TX_DS\MAX_RT,Enable CRC ,2byte,POWER UP,PRX
{0,0x3B},//abilita int RX_DR      \TX_DS\MAX_RT,Enable CRC ,1byte,POWER UP,PRX
//{1,0x3F},//Enable auto acknowledgement data pipe5\4\3\2\1\0
{1,0x00},//Disable auto acknowledgement data pipe5\4\3\2\1\0
{2,0x3F},//Enable RX Addresses pipe5\4\3\2\1\0
//{3,0x03},//RX/TX address field width 5byte
{3,0x01},//RX/TX address field width 3 byte
{4,0xff},//auto retransmission delay (4000us),auto retransmission count(15)
{5,0x17},//23 channel
//{6,0x17},//air data rate-1M,out power 0dbm,setup LNA gain  -sole
{6,0x11},//air data rate-1M,out power -10dbm,setup LNA gain 
{7,0x07},//
{8,0x00},//
{9,0x00},
{0xC,0xc3},//only LSB Receive address data pipe 2, MSB bytes is equal to RX_ADDR_P1[39:8]
{0xD,0xc4},//only LSB Receive address data pipe 3, MSB bytes is equal to RX_ADDR_P1[39:8]
{0xE,0xc5},//only LSB Receive address data pipe 4, MSB bytes is equal to RX_ADDR_P1[39:8]
{0xF,0xc6},//only LSB Receive address data pipe 5, MSB bytes is equal to RX_ADDR_P1[39:8]

//{0x11,0x20},//Number of bytes in RX payload in data pipe0(32 byte) 
//{0x12,0x20},//Number of bytes in RX payload in data pipe1(32 byte)
//{0x13,0x20},//Number of bytes in RX payload in data pipe2(32 byte)
//{0x14,0x20},//Number of bytes in RX payload in data pipe3(32 byte)
//{0x15,0x20},//Number of bytes in RX payload in data pipe4(32 byte)
//{0x16,0x20},//Number of bytes in RX payload in data pipe5(32 byte)

{0x11,0x02},//Number of bytes in RX payload in data pipe0(2 byte) 
{0x12,0x02},//Number of bytes in RX payload in data pipe1(2 byte)
{0x13,0x02},//Number of bytes in RX payload in data pipe2(2 byte)
{0x14,0x02},//Number of bytes in RX payload in data pipe3(2 byte)
{0x15,0x02},//Number of bytes in RX payload in data pipe4(2 byte)
{0x16,0x02},//Number of bytes in RX payload in data pipe5(2 byte)

{0x17,0x00},//fifo status
//{0x1C,0x3F},//Enable dynamic payload length data pipe5\4\3\2\1\0
{0x1C,0x00},//Disabele dynamic payload length data pipe5\4\3\2\1\0
//{0x1D,0x07} //Enables Dynamic Payload Length,Enables Payload with ACK,Enables the W_TX_PAYLOAD_NOACK command 
{0x1D,0x00} //Disables Dynamic Payload Length,Disables Payload with ACK,Disables the W_TX_PAYLOAD_NOACK command 
};


//const UINT8 RX0_Address[]={0x34,0x43,0x10,0x10,0x01};//Receive address data pipe 0
//const UINT8 RX1_Address[]={0x39,0x38,0x37,0x36,0xc2};//Receive address data pipe 1

const UINT8 RX0_Address[]={0x34,0x43,0x10};//Receive address data pipe 0
const UINT8 RX1_Address[]={0x39,0x38,0x37};//Receive address data pipe 1

extern UINT8 test_data;
extern UINT8  channel;
extern UINT8  power;
extern UINT8  data_rate;
extern UINT8 rx_buf[MAX_PACKET_LEN];

///////////////////////////////////////////////////////////////////////////////
//                  SPI access                                               //
///////////////////////////////////////////////////////////////////////////////

/* *************************************************
Function: SPI_RW();                                         
                                                            
Description:                                                
	Writes one UINT8 to RFM70, and return the UINT8 read 
**************************************************/
//UINT8 SPI_RW(UINT8 value){
//
//   SSPBUF = value;
//   while (!/*SSPSTAT.*/BF);
//   return SSPBUF;
// }



//#define SPI_RX_IN_PROGRESS 0x0
//uint8_t SPI1_Exchange8bit(uint8_t data)
//{
//    //One byte transfer count
//    SPI1TCNTL = 1;
//    SPI1TXB = data;
//
//    while(PIR2bits.SPI1RXIF == SPI_RX_IN_PROGRESS)
//    {
//    }
//
//    return (SPI1RXB);
//}


#define SPI_RX_IN_PROGRESS 0x0
UINT8 SPI_RW(UINT8 value){
 
    SPI1TXB = value;
    while(PIR2bits.SPI1RXIF == SPI_RX_IN_PROGRESS) ;
    return (SPI1RXB);
 }



                                                              
/**************************************************         
Function: SPI_Write_Reg();                                  
                                                            
Description:                                                
	Writes value 'value' to register 'reg'              
**************************************************/
void SPI_Write_Reg(UINT8 reg, UINT8 value)                 
{
  UINT8 status;
	CSN = 0;                   // CSN low, init SPI transaction
	status = SPI_RW(reg);      // select register
	SPI_RW(value);             // ..and write value to it..
	CSN = 1;                   // CSN high again
}                                                         
/**************************************************/        
                                                            
/**************************************************         
Function: SPI_Read_Reg();                                   
                                                            
Description:                                                
	Read one UINT8 from BK2421 register, 'reg'           
**************************************************/
UINT8 SPI_Read_Reg(UINT8 reg)                               
{                                                           
  UINT8 status,value;
	CSN = 0;              // CSN low, initialize SPI communication...
	status=SPI_RW(reg);   // Select register to read from..
	value = SPI_RW(0);    // ..then read register value
	CSN = 1;              // CSN high, terminate SPI communication
	return(value);        // return register value
}                                                           
/**************************************************/        
                                                            
/**************************************************         
Function: SPI_Read_Buf();                                   
                                                            
Description:                                                
	Reads 'length' #of length from register 'reg'         
**************************************************/
void SPI_Read_Buf(UINT8 reg, UINT8 *pBuf, UINT8 length)     
{                                                           
	UINT8 status, byte_ctr;
                                                            
	CSN = 0;                   // CSN low, initialize SPI communication...
	status = SPI_RW(reg);     // Select register to write, and read status UINT8
                                                            
	for(byte_ctr=0; byte_ctr<length; byte_ctr++)
		pBuf[byte_ctr] = SPI_RW(0);  // Perform SPI_RW to read UINT8 from RFM70

	CSN = 1;                      // CSN high, terminate SPI communication
}
/**************************************************/        
                                                            
/**************************************************         
Function: SPI_Write_Buf();                                  
                                                            
Description:                                                
	Writes contents of buffer '*pBuf' to RFM70         
**************************************************/
void SPI_Write_Buf(UINT8 reg, UINT8 *pBuf, UINT8 length)    
{                                                           
	UINT8 status, byte_ctr;
                                                            
	CSN = 0;                   // Set CSN low, init SPI tranaction
	status = SPI_RW(reg);      // Select register to write to and read status UINT8
	for(byte_ctr=0; byte_ctr<length; byte_ctr++) // then write all UINT8 in buffer(*pBuf) 
		SPI_RW(*pBuf++);                                    
	CSN = 1;                  // CSN high, terminate SPI communication

}
/**************************************************
Function: SwitchToRxMode();
Description:
	switch to Rx mode
**************************************************/
void SwitchToRxMode()
{
	UINT8 value;

	SPI_Write_Reg(FLUSH_RX,0);   //flush Rx

	value=SPI_Read_Reg(RFM_STATUS);	 // read register STATUS's value
	SPI_Write_Reg(WRITE_REG|RFM_STATUS, value);// clear RX_DR or TX_DS or MAX_RT interrupt flag

	CE=0;

	value=SPI_Read_Reg(CONFIG);	 // read register CONFIG's value
  //PRX
	value=value|0x01; //set bit 1
  SPI_Write_Reg(WRITE_REG | CONFIG, value); // Set PWR_UP bit, enable CRC(2 length) & Prim:RX. RX_DR enabled..
	CE=1;
}

/**************************************************
Function: SwitchToTxMode();
Description:
	switch to Tx mode
**************************************************/
void SwitchToTxMode()
{
	UINT8 value;
	SPI_Write_Reg(FLUSH_TX,0);//flush Tx

	CE=0;
	value=SPI_Read_Reg(CONFIG);	// read register CONFIG's value
 //PTX
	value=value&0xfe;//set bit 0
  SPI_Write_Reg(WRITE_REG | CONFIG, value); // Set PWR_UP bit, enable CRC(2 length) & Prim:RX. RX_DR enabled.
	CE=1;
}

/**************************************************
Function: SwitchCFG();
                                                            
Description:
	 access switch between Bank1 and Bank0 

Parameter:
	_cfg      1:register bank1
	          0:register bank0
Return:
     None
**************************************************/
void SwitchCFG(char _cfg)//1:Bank1 0:Bank0
{
	UINT8 Tmp;

	Tmp=SPI_Read_Reg(7);
	Tmp=Tmp&0x80;

	if ( ( (Tmp)&&(_cfg==0) ) || ( ((Tmp)==0)&&(_cfg) ) )
	{
		SPI_Write_Reg(ACTIVATE_CMD,0x53);
	}
}

/**************************************************
Function: SetChannelNum();
Description:
	set channel number

**************************************************/
void SetChannelNum(UINT8 ch)
{
	SPI_Write_Reg((UINT8)(WRITE_REG|5),(UINT8)(ch));
}



///////////////////////////////////////////////////////////////////////////////
//                  RFM70 initialization                                    //
///////////////////////////////////////////////////////////////////////////////
/**************************************************         
Function: RFM70_Initialize();                                  

Description:                                                
	register initialization
**************************************************/
void RFM70_Initialize()
{
	UINT8 i,j,temp;
 	UINT8 WriteArr[12];

	//delay more than 50ms.
	__delay_ms(200);
	
	SwitchCFG(0);

	for(i=0;i<20;i++)
	{
		SPI_Write_Reg((WRITE_REG|Bank0_Reg[i][0]),Bank0_Reg[i][1]);
	}
/*
//reg 10 - Rx0 addr
	SPI_Write_Buf((WRITE_REG|10),RX0_Address,5);
	
//REG 11 - Rx1 addr
	SPI_Write_Buf((WRITE_REG|11),RX1_Address,5);

//REG 16 - TX addr
	SPI_Write_Buf((WRITE_REG|16),RX0_Address,5);
*/
//reg 10 - Rx0 addr
	for(j=0;j<3;j++)
	{
		WriteArr[j]=RX0_Address[j];
	}
	SPI_Write_Buf((WRITE_REG|10),&(WriteArr[0]),3);
	
//REG 11 - Rx1 addr
	for(j=0;j<3;j++)
	{
		WriteArr[j]=RX1_Address[j];
	}
	SPI_Write_Buf((WRITE_REG|11),&(WriteArr[0]),3);
//REG 16 - TX addr
	for(j=0;j<3;j++)
	{
		WriteArr[j]=RX0_Address[j];
	}
	SPI_Write_Buf((WRITE_REG|16),&(WriteArr[0]),3);
	
//End Load Reg

	i=SPI_Read_Reg(29);//read Feature Register 
	if(i==0) // i!=0 showed that chip has been actived.so do not active again.
		SPI_Write_Reg(ACTIVATE_CMD,0x73);// Active
	for(i=22;i>=21;i--)
	{
		SPI_Write_Reg((WRITE_REG|Bank0_Reg[i][0]),Bank0_Reg[i][1]);
	}
	
//********************Write Bank1 register******************
	SwitchCFG(1);
	
	for(i=0;i<=8;i++)//reverse
	{
		for(j=0;j<4;j++)
			WriteArr[j]=(Bank1_Reg0_13[i]>>(8*(j) ) )&0xff;

		SPI_Write_Buf((WRITE_REG|i),&(WriteArr[0]),4);
	}

	for(i=9;i<=13;i++)
	{
		for(j=0;j<4;j++)
			WriteArr[j]=(Bank1_Reg0_13[i]>>(8*(3-j) ) )&0xff;

		SPI_Write_Buf((WRITE_REG|i),&(WriteArr[0]),4);
	}

	//SPI_Write_Buf((WRITE_REG|14),&(Bank1_Reg14[0]),11);
	for(j=0;j<11;j++)
	{
		WriteArr[j]=Bank1_Reg14[j];
	}
	SPI_Write_Buf((WRITE_REG|14),&(WriteArr[0]),11);

//toggle REG4<25,26>
	for(j=0;j<4;j++)
		//WriteArr[j]=(RegArrFSKAnalog[4]>>(8*(j) ) )&0xff;
		WriteArr[j]=(Bank1_Reg0_13[4]>>(8*(j) ) )&0xff;

	WriteArr[0]=WriteArr[0]|0x06;
	SPI_Write_Buf((WRITE_REG|4),&(WriteArr[0]),4);

	WriteArr[0]=WriteArr[0]&0xf9;
	SPI_Write_Buf((WRITE_REG|4),&(WriteArr[0]),4);

	//**************************Test spi*****************************//
	//SPI_Write_Reg((WRITE_REG|Bank0_Reg[2][0]),0x0f);
	//test_data = SPI_Read_Reg(0x02);

	__delay_ms(50);
	
//********************switch back to Bank0 register access******************
	SwitchCFG(0);
	//SwitchToRxMode();//switch to RX mode
}


