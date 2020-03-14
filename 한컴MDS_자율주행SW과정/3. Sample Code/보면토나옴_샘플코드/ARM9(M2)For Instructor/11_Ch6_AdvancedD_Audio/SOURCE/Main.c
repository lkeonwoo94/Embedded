#include "2440addr.h"
#include "my_lib.h"

#define	EXAMPLE	711

unsigned char *buf = (unsigned char *)0x32000000;


#if EXAMPLE==710
void Main(void)
{
	Uart_Init(115200);		
	
	AC97_Port_Init();
	AC97_Cold_Reset(5000);
	AC97_Init();
	
	Uart_Printf("AC97 MIC. to Speaker Loopback Test\n");
	AC97_Codec_CMD_Write(0x2, 0xa0a);	//Master volume setting
	AC97_Codec_CMD_Write(0xe, 0x8);		//MIC volume setting

#if 0
	Uart_Printf("Master Vol.     : 0x%04x\n", AC97_Codec_STAT_Read(0x2));
	Uart_Printf("MIC Vol.        : 0x%04x\n", AC97_Codec_STAT_Read(0xe));
#endif
	
	while(1);
}
#endif

#if EXAMPLE==711
void Main(void)
{
	int wave_size = 0;
	unsigned int *wave_start_addr;

	wave_size = *(int *)(0x32000000 + 40);
	wave_start_addr = (unsigned int *)(buf+44);

	
	Uart_Init(115200);		
	
	AC97_Port_Init();
	AC97_Cold_Reset(5000);
	AC97_Init();

	AC97_Codec_CMD_Write(0x2, 0xa0a);	//Master volume setting
	AC97_Codec_CMD_Write(0x18, 0x808);	//PCM_OUT volume
	AC97_Codec_CMD_Write(0x2a, 0x1);	//VAR enable
	AC97_Codec_CMD_Write(0x2c, 0x5622);	//PCM DAC output sample rate
	AC97_Codec_CMD_Write(0x32, 0x5622);	//PCM DAC output sample rate	
	AC97_Codec_CMD_Write(0x6a, 0x400);	//Data Flow Control, DAC-to-Analog out

#if 0
	Uart_Printf("Reset           : 0x%04x\n", AC97_Codec_STAT_Read(0x0));
	Uart_Printf("Master Vol.     : 0x%04x\n", AC97_Codec_STAT_Read(0x2));
	Uart_Printf("MIC Vol.        : 0x%04x\n", AC97_Codec_STAT_Read(0xe));
	Uart_Printf("PCM DAC Rate    : 0x%04x\n", AC97_Codec_STAT_Read(0x2c));
	Uart_Printf("PCM ADC Rate    : 0x%04x\n", AC97_Codec_STAT_Read(0x32));
	Uart_Printf("Data Flow Ctrl. : 0x%04x\n", AC97_Codec_STAT_Read(0x6a));
	Uart_Printf("Vendor ID1      : 0x%04x\n", AC97_Codec_STAT_Read(0x7c));
	Uart_Printf("Vendor ID2      : 0x%04x\n", AC97_Codec_STAT_Read(0x7e));
#endif

	AC97_PlayWave_DMA3(wave_start_addr, (unsigned int)((wave_size-8)>>2));
}

#endif




