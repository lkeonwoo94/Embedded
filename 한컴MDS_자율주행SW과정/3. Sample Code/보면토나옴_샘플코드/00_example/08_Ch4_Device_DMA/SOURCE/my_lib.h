#ifndef _MY_LIB_H_
#define _MY_LIB_H_

//Uart.c 
void Uart_Init(int baud);
void Uart_Printf(char *fmt,...);
void Uart_Send_String(char *pt);
void Uart_Send_Byte(int data);
char Uart_Get_Char(void);

//Touch.c
void Touch_Init(void);

//Main.c 
void __irq Touch_ISR(void);

#endif
