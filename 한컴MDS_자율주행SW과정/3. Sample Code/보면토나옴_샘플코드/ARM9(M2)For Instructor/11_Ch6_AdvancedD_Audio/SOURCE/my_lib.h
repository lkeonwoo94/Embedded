//=============================================================================
// File Name : my_lib.h
//=============================================================================

// UART.c
extern void Uart_Init(int baud);
extern void Uart_Printf(char *fmt,...);
extern void Uart_Send_Byte(int data);
extern void Uart_Send_String(char *pt);

extern char Uart_Get_Char(void);
extern char Uart_Get_Pressed(void);

extern void Timer0_Init(void);
extern void Timer0_Delay(unsigned int msec);

extern void AC97_Port_Init(void);
extern void AC97_Init(void);
extern void AC97_Cold_Reset(unsigned int msec);
extern void AC97_Warm_Reset(unsigned int msec);
extern unsigned AC97_Codec_CMD_Write(short reg, short data);
extern unsigned AC97_Codec_STAT_Read(short reg);
extern void AC97_PlayWave_DMA3(unsigned int *start_addr, unsigned int play_size);