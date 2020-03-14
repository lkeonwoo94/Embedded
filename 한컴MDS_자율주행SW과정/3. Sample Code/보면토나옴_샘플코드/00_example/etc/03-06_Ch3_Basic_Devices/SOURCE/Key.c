#include "2450addr.h"
#include "option.h"
#include "libc.h"

//Function Declaration 
void Key_Port_Init(void);
void Key_Get_Pressed_with_LED();
int Key_Get_Pressed();
int Key_Wait_Get_Pressed();
void Key_Wait_Get_Released();

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

void Key_Get_Pressed_with_LED()
{
	/* TO DO : [1]1번 key => LED1, [2]2번 key => LED2, [3]3번 key => LED3, [4]4번 key => LED4 */
	int i;	

	rGPFDAT &= ~(0x1<<7);

	if((~(rGPFDAT>>2)) & 0x1)
	{
		rGPGDAT &= ~(1<<4);
		for(i=0;i<0xffff;i++);
		rGPGDAT |= (1<<4);
	}
	if((~(rGPFDAT>>3)) & 0x1)
	{
		rGPGDAT &= ~(1<<5);
		for(i=0;i<0xffff;i++);
		rGPGDAT |= (1<<5);
	}
	if((~(rGPFDAT>>4)) & 0x1)
	{
		rGPGDAT &= ~(1<<6);
		for(i=0;i<0xffff;i++);
		rGPGDAT |= (1<<6);
	}
	if((~(rGPFDAT>>5)) & 0x1)
	{
		rGPGDAT &= ~(1<<7);
		for(i=0;i<0xffff;i++);
		rGPGDAT |= (1<<7);
	}
	
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