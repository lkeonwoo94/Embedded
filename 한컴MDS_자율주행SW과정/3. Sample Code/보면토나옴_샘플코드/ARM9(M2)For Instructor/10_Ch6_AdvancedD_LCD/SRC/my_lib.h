#ifndef __MY_LIB_H__
#define __MY_LIB_H__


// Uart.c
void Uart_Init(int baud);
void Uart_Printf(char *fmt,...);
void Uart_Send_String(char *pt);
void Uart_Send_Byte(int data);
char Uart_Get_Char();

// Lcd.c
void Lcd_Port_Init(void);
void Lcd_Init(void);
void NonPal_Lcd_Init(void);
void Palette_Init(void);
void Put_Pixel(unsigned long x, unsigned long y, unsigned long pal_addr);
void NonPal_Put_Pixel(int x, int y, int color);
void Lcd_Draw_BMP(int x, int y, const unsigned char *fp);

#endif