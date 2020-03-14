/*
 * =====================================================================
 * NAME         : libc.h
 *
 * Descriptions : Definition of S3C2450 Library prototype
 *
 * IDE          : GCC-4.1.0
 *
 * Modification
 *	   
 * =====================================================================
 */
#ifndef __LIBC_H__
#define __LIBC_H__

extern void MemFill(unsigned long ptr, unsigned long pattern, int size);
extern void MemDump(unsigned long ptr, int size);

void DMA0_SW_Init(void);
void DMA0_Timer_Init(void);
void DMA0_UART_Init(void);
void DMA0_SW_Start(void);
void DMA0_HW_Start(void);

void Uart_Init(int baud);
void Uart_DMA_Init(int baud);
void Uart_Printf(char *fmt,...);
void Uart_Send_String(char *pt);
void Uart_Send_Byte(int data);
char Uart_Get_Char();

void Timer_Init(void);
void Timer_DMA_Init(void);
void Timer_Delay(int msec);

#endif
