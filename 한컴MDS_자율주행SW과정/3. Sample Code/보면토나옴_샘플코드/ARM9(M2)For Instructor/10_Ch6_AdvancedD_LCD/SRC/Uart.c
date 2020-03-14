/*
 * =====================================================================
 * NAME         : Uart.c
 *
 * Descriptions : Uart Test Driver
 *
 * IDE          : CodeWarrior 2.0 or Later
 *
 * Modification
 *
 * =====================================================================
 */
#include "2440addr.h"
#include <stdarg.h>

// Function Declaration
void Uart_Init(int baud);
void Uart_Printf(char *fmt,...);
void Uart_Send_String(char *pt);
void Uart_Send_Byte(int data);
char Uart_Get_Char();

void Uart_Init(int baud)
{
	// PORT GPIO initial
	rGPHCON &= ~(0xf<<4);
	rGPHCON |= (0xa<<4);

	//nCTS0 nRTS0 Enable
	rGPHCON &= ~(0xf<<0);
	rGPHCON |= (0xa<<0);

	// COM1 Port initial
	/* TODO :  Non-FiFo모드 */
	rUFCON0 = 0x0;
	/* TODO : FIFO 모드 --> FIFO모드에서는 어떻게 구현되는가?*/
	//rUFCON0 = (1<<6)|(1<<4)|(1<<0);
	rUMCON0 = 0x0;
	/* TODO : Line Control(Normal mode, No parity, One stop bit, 8bit Word length */
	rULCON0 = 0x3;
	/* TODO : Transmit & Receive Mode is polling mode  */
	rUCON0  = (1<<2)|(1);
	/* TODO : Transmit & Receive Mode is DMA0 Request */
	//rUCON0 = (1<<9)|(6<<1)|(1<<2)|(2);
	/* TODO : baud rate 설정  */
	rUBRDIV0= ((unsigned int)(PCLK/16./baud+0.5)-1 );
}

void Uart_Printf(char *fmt,...)
{
    va_list ap;
    char string[256];

    va_start(ap,fmt);
    vsprintf(string,fmt,ap);
    Uart_Send_String(string);
    va_end(ap);		
}

void Uart_Send_String(char *pt)
{
	while(*pt)
	{
			/* TODO :  */
		Uart_Send_Byte(*pt++);		
	}	
}

void Uart_Send_Byte(int data)
{
	if(data=='\n')
	{
		/* TODO :  */
		while(!(rUTRSTAT0 & 0x2));
		WrUTXH0('\r');
	}
		/* TODO :  */
	while(!(rUTRSTAT0 & 0x2));	
		(*(unsigned char *)UTXH0) = (unsigned char)data;
		//WrUTXH0(data);
}

char Uart_Get_Char()
{
	/* TODO :  */
	while(!(rUTRSTAT0 & 0x1));	
	return *(volatile unsigned char *)URXH0;
	//return RdURXH0(); 
}