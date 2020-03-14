#include "2440addr.h"
#include "option.h"
#include "stdarg.h"

// DDI Layer
void Uart_Init(int baud);
void Uart_Printf(char *fmt,...);
char Uart_Get_Char(void);
char Uart_Get_Pressed(void);

// D/D Layer
void Uart_Send_Byte(int data);
void Uart_Send_String(char *pt);

void Uart_Send_Byte(int data)
{
	if(data=='\n')
	{
		while(!(rUTRSTAT0 & 0x2));
		WrUTXH0('\r');
	}
	while(!(rUTRSTAT0 & 0x2));
	WrUTXH0(data);
}               

void Uart_Send_String(char *pt)
{
	while(*pt)
	{
        	Uart_Send_Byte(*pt++);
	}
}

void Uart_Init(int baud)
{
	// PORT GPIO initial
	rGPHCON &= ~(0xf<<4);
	rGPHCON |= (0xa<<4);	

	// COM1 Port initial
	rUFCON0 = 0x0;
	rUMCON0 = 0x0;
	rULCON0 = 0x3;
	rUCON0  = 0x245;		
	rUBRDIV0= ((unsigned int)(PCLK/16./baud+0.5)-1 );
}

void Uart_Printf(char *fmt,...)
{
    va_list ap;
    char string[256];

    va_start(ap,fmt);
    vsprintf(string,fmt,ap);   // codewarrior 가 제공되는 함수 
    Uart_Send_String(string);
    va_end(ap);
}

char Uart_Get_Char(void)
{
    while(!(rUTRSTAT0 & 0x1));
    return RdURXH0();
}

char Uart_Get_Pressed(void)
{
    if(rUTRSTAT0 & 0x1)
    {
    	return RdURXH0();
    }
    else return 0;
}
