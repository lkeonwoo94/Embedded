/**********************************************
  NAME: pwr_c.c
  DESC: 2410 power consumption measurement code
  HISTORY:
  04.09.2002:purnnamu: first release for 2410
  06.02.2003:DonGo: Modified for 2440
 **********************************************/
 
#include <stdlib.h>
#include <string.h>
#include "def.h"
#include "option.h"
#include "2440addr.h"
#include "2440lib.h"
#include "2440slib.h"

#include "pwr_c.h"
#include "mmu.h"

#include "lcdlib.h"

//Options for current measurement
#define QUICK_SORT		(1)
#define DHRYSTONE21   	(2)
#define CPU_WORK		QUICK_SORT //DHRYSTONE21 

void PWR_Lcd_Tft_16Bit_240320_On(void);
static void Lcd_Port_Init(void);
void PWR_StartTimer(void);
void StartDmaMem2Mem(void);
void PWR_StartIIS(void);
int compare1(const void *a,const void *b);
int compare2(const void *a,const void *b);


#define NUM_SORT_DATA	1024
static int dim2[NUM_SORT_DATA];  //128KB,which is bigger than D-Cache(16KB)



extern U32 Mps_Val[][4];
U32 TMP_FCLK=400000000;




extern int No_Of_Mps_Val;

extern Calc_Clock(int print_msg);
extern U32 Mdiv, Pdiv, Sdiv, Fclk, Hclk, Pclk, Hdivn, Pdivn, Hclk_Ratio, Pclk_Ratio, Ref_Cnt;


void MeasurePowerConsumption(void)
{
	int i,j, hdiv_val, pdiv_val, select;
	volatile int a,b,c;

	Uart_Printf("[Measure the power consumption of S3C2440]\n");
	
	MMU_Init();

#if 0
	Uart_Printf("(1)203MHz,(2)305MHz,(3)400MHz(1:4:8),(4)400MHz(1:3:6),(5)533MHz\n");
	Uart_Printf("Select Clock Frequency to test(0 or Enter to skip) : ");
	select = Uart_GetIntNum();
	
	// Clock setting
	ChangeUPllValue(56,2,2);		// 48MHz

	switch(select) {
		case 1:	// 203.2MHz
			ChangeClockDivider(12,12);	// 1:2:4
			ChangeMPllValue(246,13,0);
		break;
		case 2:	// 305MHz
			ChangeClockDivider(13,12);	// 1:3:6
			ChangeMPllValue(119,3,0);
		break;
		case 3:	// 400MHz, 1:4:8
			ChangeClockDivider(14,12);
			ChangeMPllValue(92,1,0);
		break;
		case 4:	// 400MHz, 1:3:6
			ChangeClockDivider(13,12);	// 1:4:8
			ChangeMPllValue(92,1,0);
		break;
		case 5:	// 533MHz
			ChangeClockDivider(14,12);	// 1:4:8
			ChangeMPllValue(214,3,0);
		break;
		case 0:
		default:
		break;
	}
#endif
	
	Calc_Clock(1);
	UPDATE_REFRESH(Hclk);
	//Uart_Init(Pclk, 115200);

	// Clock off unused block.
	rCLKCON &= ~( (1<<19) | (1<<18) | (0<<17) | (1<<16) | \
				(1<<15) | (0<<14) | (0<<13) | (0<<12) | \
				(0<<11) | (0<<10) | (1<<9) | (0<<8) | \
				(0<<7) | (0<<6) | (0<<5) | (1<<4) );

	Uart_Printf("Add Mem to Mem DMA(y/n) ? ");
	if(Uart_Getch()=='y') {
		Uart_Printf("\n- DMA Mem to Mem(1024 words).\n");
		StartDmaMem2Mem();
	}
	Uart_Printf("\n");

	Uart_Printf("- Run 5-Timers (130KHz).\n");	
	PWR_StartTimer();

	Uart_Printf("- TFT-LCD 240x320 16bit is running.\n");
	Lcd_PowerEnable(0,1);
	PWR_Lcd_Tft_16Bit_240320_On();
	
	Uart_Printf("- IIS(DMA2) is running(CDCLK=16.9Mhz,LRCK=44.1Khz).\n");
	PWR_StartIIS();
	
#if CPU_WORK==QUICK_SORT
	//qsort;
	for(i=0;i<NUM_SORT_DATA;i++) dim2[i]=i;

	Uart_Printf("- CPU JOB:quick sort of 65536 integer data.\n");	
	Uart_Printf("status:  ");
	i=0;
	while(1)
	{
		qsort(dim2,NUM_SORT_DATA,sizeof(int),compare1);
		qsort(dim2,NUM_SORT_DATA,sizeof(int),compare2);
		
		Uart_Printf("\b%1d", i++%10);
		if(Uart_GetKey()) break;
	}
#else
	Uart_Printf("- CPU JOB:Dhrystone 2.1 code.\n");
	Uart_Printf("status:  ");
	i=0;
	while(1)
	{
		dhrystone21();
		Uart_Printf("\b%1d", i++%10);
		if(Uart_GetKey()) break;
	}

#endif
	Uart_Printf("\nExit\n");	
}


int compare1(const void *a,const void *b)
{
	
	if(*(int *)a>*(int *)b)
		return 1;
	else if(*(int *)a==*(int *)b)
		return 0;
	else 
		return -1;
}

int compare2(const void *a,const void *b)
{
	
	if(*(int *)a>*(int *)b)
		return -1;
	else if(*(int *)a==*(int *)b)
		return 0;
	else 
		return 1;
}

void DoQsort(void) //function for SLOW mode current current consumption
{
		qsort(dim2,NUM_SORT_DATA,sizeof(int),compare1);
		qsort(dim2,NUM_SORT_DATA,sizeof(int),compare2);
}

static unsigned save_rGPCUP,save_rGPCDAT,save_rGPCCON;
static unsigned save_rGPDUP,save_rGPDDAT,save_rGPDCON; 

#if 1
static void Lcd_Port_Init(void)
{
	save_rGPCCON=rGPCCON;
	save_rGPCDAT=rGPCDAT;
	save_rGPCUP=rGPCUP;
	save_rGPDCON=rGPDCON;
	save_rGPDDAT=rGPDDAT;
	save_rGPDUP=rGPDUP;
	rGPCUP=0xffffffff; // Disable Pull-up register
	rGPCCON=0xaaaaaaaa; //Initialize VD[7:0],LCDVF[2:0],VM,VFRAME,VLINE,VCLK,LEND 
	rGPDUP=0xffffffff; // Disable Pull-up register
	rGPDCON=0xaaaaaaaa; //Initialize VD[23:8]
}
#endif

void PWR_Lcd_Tft_16Bit_240320_On(void)
{
	Lcd_Port_Init();
	Lcd_Init(MODE_TFT_16BIT_240320);
	Glib_Init(MODE_TFT_16BIT_240320);

	//Uart_Printf("TFT 64K-color(16bit) LCD on.\n");
	
	//Lcd_Lpc3600Enable();
	Lcd_Lcc3600Enable();

	Lcd_PowerEnable(0, 1);
	Lcd_EnvidOnOff(1);

	Glib_ClearScr(0, MODE_TFT_16BIT_240320);
	Glib_FilledRectangle(0,0,119,159,0xf800);	// R
	Glib_FilledRectangle(120,0,240,159,0x07e0);	// G
	Glib_FilledRectangle(0,160,119,320,0x001f);	// B
	Glib_FilledRectangle(120,160,240,320,0xffff);	// W

}

void PWR_StartTimer(void)
{
	//Uart_Printf("All 5 timers are running(130KHz).\n");
	
	rTCFG0=0x8080;   //Prescaler=128; 
	rTCFG1=0x11111;  //Devider=1/4;	Period: 66.7MHz/12/4 = 130KHz.
	rTCNTB0=0x8000;
	rTCMPB0=0x4000;
	rTCNTB1=0x8000;
	rTCMPB1=0x4000;
	rTCNTB2=0x8000;
	rTCMPB2=0x4000;
	rTCNTB3=0x8000;
	rTCMPB3=0x4000;
	rTCNTB4=0x8000;
	rTCON=0x6aaa0a; // Auto reload.
	rTCON=0x599909; //run
}



static int buf1[1024],buf2[1024];

void __irq PWR_IsrDma0(void)
{
	ClearPending(BIT_DMA0);
	rDMASKTRIG0=0x3; 	
	//Uart_Printf("$");
}


void StartDmaMem2Mem(void)
{
	//Uart_Printf("seamless DMA0 SDRAM->SDRAM transfer is running.\n");
	
	pISR_DMA0=(unsigned int)PWR_IsrDma0;	
	rINTMSK=rINTMSK&~(BIT_DMA0);
 
	rDISRC0=(U32)buf1;
	rDISRCC0=(0<<1)|(0<<0); //src=AHB,increment
	rDIDST0=(U32)buf2;
	rDIDSTC0=(0<<1)|(0<<0); //dst=AHB,increment
	rDCON0=(1<<31)|(1<<29)|(1<<27)|(2<<20)|(1024);
		//handshake,done int. enable,whole mode,DSZ=word,TC=1024
	rDMASKTRIG0=0x3; 			
}	

static U16 buf3[4096];

void __irq PWR_IsrDma2(void)
{
	ClearPending(BIT_DMA2);
	//Uart_Printf("#");
}

void PWR_StartIIS(void)
{
	U32 iis_div_val=3;
	
	//Uart_Printf("IIS(DMA2) is running(CDCLK=16.9Mhz,LRCK=44.1Khz).\n");

	pISR_DMA2=(unsigned int)PWR_IsrDma2;	
	rINTMSK=rINTMSK&~(BIT_DMA2);

	rGPECON=rGPECON&~(3<<8|3<<4|3<<2|3<<0)|(2<<8|2<<4|2<<2|2<<0); //I2SSDO,CDCLK,I2SSCLK,I2SLRCK
		
	rDISRC2=(U32)buf3; 
	rDISRCC2=(0<<1)+(0<<0);//src=AHB,increment
	rDIDST2=((U32) IISFIFO );
	rDIDSTC2=(1<<1)+(1<<0); //APB,fix
	rDCON2=(1<<31)|(0<<30)|(1<<29)|(0<<28)|(0<<27)|(0<<24)|(1<<23)|(0<<22)|(1<<20)|(4096);
	//handshake, sync PCLK, TC int, single tx, single service, I2SSDO, I2S request, 
	//auto-reload, half-word,
	rDMASKTRIG2=(1<<1)+0;	//DMA2 channel on, no-sw trigger 

	iis_div_val = (U32)(((float)Pclk/16934400.0)+0.5)-1;
	rIISPSR=(iis_div_val<<5)|(iis_div_val<<0); //IIS_LRCK=44.1Khz @384fs,PCLK=50 or 66.7Mhz.
	
	rIISCON=(1<<5)+(1<<2)+(1<<1);
	//Tx DMA enable,Rx idle,prescaler enable
	rIISMOD=(2<<6)|(1<<3)|(1<<2)|(1<<0);
	//Master,Tx,L-ch=low,iis,16bit ch.,CDCLK=384fs,IISCLK=32fs

	rIISFCON=(1<<15)+(1<<13);	//Tx DMA,Tx FIFO enable

	rIISCON |=0x1;
}

