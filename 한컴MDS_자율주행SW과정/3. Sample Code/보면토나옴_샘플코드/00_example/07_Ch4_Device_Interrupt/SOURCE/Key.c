#include "2450addr.h"
#include "option.h"
#include "libc.h"

//Function Declaration 
void Key_Port_Init(void);
void Key_IRQ_Port_Init(void);
int Key_Get_Pressed(void);
int Key_Wait_Get_Pressed(void);
void Key_Wait_Get_Released(void);

//Function
void Key_Port_Init(void)
{
	/* GPFCON -Input Mode GPF[2:6] */
	/* YOUR CODE HERE */
	rGPFCON &= ~(0x3ff<<4);
	rGPFUDP &= ~(0x1f<<2);
	
	/* GPFCON, GPGCON - outputmode GPF7, GPG0 */
	/* YOUR CODE HERE */	
	rGPGDAT |= 0x1;
	rGPFDAT	|= 0x1<<7;
	
	rGPGCON &= ~(0x3);
	rGPGCON |= 0x1;	
	rGPFCON &= ~(0x3<<14);
	rGPFCON |= 0x1<<14;	
	
}

void Key_IRQ_Port_Init(void)
{

	/* TO DO :  GPFCON[6:2] = Interrupt mode (10) */ 
	rGPFCON &= ~(0x3ff<<4);
	rGPFCON |= (0x2aa<<4);
	
	/* KEYOUT[0:1] = GPGCON[0],GPFCON[7]  : Output mode
	 *GPGCON[0],GPFCON[7]  : initial data is all 0 for falling interrupt
	 */
	rGPGDAT &= ~0x1;
	rGPFDAT	&= ~(0x1<<7);
	
	rGPGCON &= ~(0x3);
	rGPGCON |= 0x1;	
	rGPFCON &= ~(0x3<<14);
	rGPFCON |= 0x1<<14;
	
	/* EXINT0[26:8] = falling edge  */	
	rEXTINT0 &= ~((0x7<<24)|(0x7<<20)|(0x7<<16)|(0x7<<12)|(0x7<<8));
	rEXTINT0 |= ((0x2<<24)|(0x2<<20)|(0x2<<16)|(0x2<<12)|(0x2<<8));
	
}

int Key_Get_Pressed()
{
	/* TO DO : 입력된 키값을 확인하여 리턴하는 함수 */
	int i, keyval;
	
	/* YOUR CODE HERE */
	for(i=0; i<2; i++)
	{	
		rGPFDAT |= 0x1<<7;
		rGPGDAT |= 0x1<<0;
		(i==1)?(rGPGDAT &= ~0x1):(rGPFDAT &= ~(0x1<<7));

		keyval = ((~rGPFDAT>>2) & 0x1F);
		switch(keyval)
		{
			case 1 : return (1+(5*i));
			case 2 : return (2+(5*i));
			case 4 : return (3+(5*i));
			case 8 : return (4+(5*i));
			case 16 : return (5+(5*i));
		}	
	}

	return 0;

}

int Key_Wait_Get_Pressed()
{
	/* TO DO : 키가 눌려졌을 때에만 값을 리턴하도록 기다려 주는 함수 */
	int a; 
	while (! (a= Key_Get_Pressed()));
	return a; 
	
}

void Key_Wait_Get_Released()
{	
	/* TO DO : 키가 눌려지지 않았을 때를 나타내는 함수 */
	while (Key_Get_Pressed());
	Uart_Send_String("released\n");
}