/*
 * =====================================================================
 * NAME         : libc.h
 *
 * Descriptions : Definition of S3C2440 Library prototype
 *
 * IDE          : CodeWarrior 2.0 or Later
 *
 * Modification
 *	   
 * =====================================================================
 */

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