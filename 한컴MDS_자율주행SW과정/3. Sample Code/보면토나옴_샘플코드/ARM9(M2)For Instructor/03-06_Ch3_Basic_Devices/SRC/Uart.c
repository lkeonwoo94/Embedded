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
#include "libc.h"

// Function Declaration
void Uart_Init(int baud);
void Uart_Printf(char *fmt,...);
void Uart_Send_String(char *pt);
void Uart_Send_Byte(int data);
char Uart_Get_Char();

void Uart_Init(int baud)
{
	int pclk;
	pclk = PCLK;
	
	// PORT GPIO initial
	rGPHCON &= ~(0xf<<4);
	rGPHCON |= (0xa<<4);

	rUFCON0 = 0x0;
	rUMCON0 = 0x0; 
	
	/* TODO : Line Control(Normal mode, No parity, One stop bit, 8bit Word length */
	rULCON0 = 0x3;

	/* TODO : Transmit & Receive Mode is polling mode  */
	rUCON0  = (1<<2)|(1);

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
		/* TODO : 문자 하나씩 증가시키면서 문자열 출력  */
		/*YOUR CODE HERE*/
		Uart_Send_Byte(*pt++);			
	}	
}

void Uart_Send_Byte(int data)
{
	if(data=='\n')
	{
		while(!(rUTRSTAT0 & 0x2));
		WrUTXH0('\r');
	}
	
	/*YOUR CODE HERE*/
	while(!(rUTRSTAT0 & 0x2));	
		WrUTXH0(data);
	//(*(unsigned char *)UTXH0) = (unsigned char)data;
}

char Uart_Get_Char()
{
	/* TODO : UTRSTAT0의 값을 확인하여 문자열 입력   */	
	/*YOUR CODE HERE*/
	while(!(rUTRSTAT0 & 0x1));	
		return RdURXH0();
	//return *(volatile unsigned char *)URXH0;
}