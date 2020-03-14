#include "2440addr.h"
#include "option.h"
#include "macro.h"

void AC97_Port_Init(void);
void AC97_Init(void);
void AC97_Cold_Reset(unsigned int msec);
void AC97_Warm_Reset(unsigned int msec);
unsigned AC97_Codec_CMD_Write(short reg, short data);
unsigned AC97_Codec_STAT_Read(short reg);
void AC97_PlayWave_DMA3(unsigned int *start_addr, unsigned int play_size);

void __irq Dma3_Stop(void)
{
	rINTMSK |= (0x1<<20);	//Masking on DMA3
	rSRCPND |= (0x1<<20);	//Pending Register Clear
	rINTPND |= (0x1<<20);	//Pending Interrupt Clear

	Uart_Printf("\nEnd of Play!!!\n");
	
	rDMASKTRIG3 = rDMASKTRIG3 | (0x1<<2);	//DMASKTRIG3 : DMA3 Stop

	rAC_GLBCTRL &= ~(1<<2);	//AC-link off
	
	/* TO DO : unmasking on DMA2 */
	rINTMSK &= ~(0x1<<20);	//UnMasking on DMA3
}

void AC97_Port_Init(void)
{
	//---------------------------------------------------------------------------------
	//   				             PORT E GROUP
	//
	//	Ports  :      GPE4           GPE3          GPE2         GPE1           GPE0 
	//	Signal : AC97_SDATA_OUT	AC97_SDATA_IN	nAC97_RST	AC97_BIT_CLK	AC97_SYNC
	//	Binary :       11             11            11           11             11
	//---------------------------------------------------------------------------------
	// TO DO :
	rGPEUP  = rGPEUP & ~(0x1f) | 0x1f;
	rGPECON = rGPGCON & ~(0x3ff) | (0x3ff);
	
	rGPADAT  = rGPADAT & ~(0x1<<16);	// Speaker SHDN diable
	rGPACON  = rGPACON & ~(0x1<<16);
}


void AC97_Init(void)
{
	// PCM out DMA mode, Transfer data enable, AC-link on
	// TO DO :
	rAC_GLBCTRL = (2<<12)|(1<<3)|(1<<2);

}

void AC97_Cold_Reset(unsigned int msec)
{
	rAC_GLBCTRL |= (1<<0);
	Timer0_Delay(msec);
	rAC_GLBCTRL &= ~(1<<0);	
}

void AC97_Warm_Reset(unsigned int msec)
{
	rAC_GLBCTRL |= (1<<1);
	Timer0_Delay(msec);
	rAC_GLBCTRL &= ~(1<<1);	
}

unsigned AC97_Codec_CMD_Write(short reg, short data)
{
	/* AC97 CODEC command Register setting
	   AC_CODEC_CMD register
	   bit[31:24] : reserved
	   bit[23]		: 0 - command write		
					: 1 - status read
	   bit[22:16]	: codec command address
	   bit[15:0]	: codec command data
	*/
	/* TO DO : codec command address = reg
			   codec command data = data
	*/
	rAC_CODEC_CMD = (unsigned)(reg<<16 | data);
	Timer0_Delay(100);		// time delay
	rAC_CODEC_CMD = (unsigned)((0x80 + reg)<<16);
	Timer0_Delay(100);		// time delay
	return (rAC_CODEC_CMD & 0xffff);
}

unsigned AC97_Codec_STAT_Read(short reg)
{
	rAC_CODEC_CMD = (unsigned)((0x80 + reg)<<16);
	Timer0_Delay(100);
	return (rAC_CODEC_STAT & 0xffff);
}

void AC97_PlayWave_DMA3(unsigned int *start_addr, unsigned int play_size)
{
	//Register DMA3 interrupt ISR
	pISR_DMA3 = (unsigned long)Dma3_Stop;
	rINTMSK &= ~(0x1<<20);
	
	//DMA3 Register Setting
	// TO DO :
	rDISRC3 = (unsigned int)(start_addr);
	// AHB, Increment
	// TO DO :
	rDISRCC3 = (0<<1)+(0<<0);
	rDIDST3 = ((unsigned int)AC_PCMDATA);
	// APB, Fixed
	// TO DO :
	rDIDSTC3 = (0<<2)+(1<<1)+(1<<0);
	
	/* Synch to APB clock, Enalble CURR_TC interrupt,
	   A unit transfer, Single service, PCMOUT, H/W request,
	   Auto Reload off, Data size is word, play_size */
	// TO DO :
	rDCON3 = (0<<30)+(1<<29)+(0<<28)+(0<<27)+(6<<24)+(1<<23)+(1<<22)+(2<<20)+(play_size);
	
	rDMASKTRIG3 = (0<<2)+(1<<1)+(0<<0);		// No-stop, DMA2 channel On, and No-sw trigger
	
	Uart_Printf("\nPlay...\n");
	
}