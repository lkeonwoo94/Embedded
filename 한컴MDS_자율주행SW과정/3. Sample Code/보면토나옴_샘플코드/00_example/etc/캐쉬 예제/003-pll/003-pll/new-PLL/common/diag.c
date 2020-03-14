/****************************************************************************
 * file name	: diag.c
 * Date			: 15. 04. 2005
 * Version		: 1.0
 * Description	: diagnostic MAIN function
 *
 *
 ****************************************************************************/
 
#include <stdlib.h>
#include <string.h>

#include "def.h"
#include "option.h"
#include "2440addr.h"
#include "2440lib.h" 
#include "mmu.h" 

#if USE_MAIN
#include <stdio.h>
#endif


/**************** User test program header file ********************/
//#include	"PD6710.h"		// PCMCIA
//#include	"nwait.h"		// nWAIT signal
//#include	"camif.h"
//#include	"ac97.h"		//Added to S3C2440A
//#include	"nand.h"		//NAND flash
//#include	"stone.h"		// Stepping stone
//#include	"User_Test.h"
//#include	"cpuspeed.h"	// Cpu speed test.

//#include	"Flash.h"		//NOR flash
#include	"int.h"			// Interrupt
#include	"Userlib.h"
#include	"power.h"
#include	"lcd.h"
#include	"iic.h"
#include	"rtc.h"
#include	"spi.h"
#include	"uart_test.h"
#include	"uart0.h"
#include	"uart1.h"
#include	"uart2.h"
#include	"Glib.h"
#include	"LCDlib.h"

#include	"nor_test.h"
#include	"nand_test.h"
#include	"k9f5608.h"
#include	"k9s1208.h"
#include	"Am29lv800.h"
#include	"strata32.h"

#include	"dma.h"
#include	"sdi.h"
#include	"timer.h"
#include	"iis.h"
#include	"irda.h"
#include	"adcts.h"
#include	"dvstest.h"
#include	"pwr_c.h"
#include    "cs8900.h"
#include	"usb.h"
#include	"usblib.h"


void Isr_Init(void);
void HaltUndef(void);
void HaltSwi(void);
void HaltPabort(void);
void HaltDabort(void);

void Clk0_Enable(int clock_sel);
void Clk1_Enable(int clock_sel);
void Clk0_Disable(void);
void Clk1_Disable(void);
void Test_PD6710(void);


extern void Calc_Clock(int print_msg);
extern void diag_ide(void);
extern U32 Mdiv, Pdiv, Sdiv, Fclk, Hclk, Pclk, Hdivn, Pdivn, Hclk_Ratio, Pclk_Ratio, Ref_Cnt;
extern U32 U_Mdiv, U_Pdiv, U_Sdiv, Uclk;

void *function[][2]=
{
//	(void *)Manual_Register_Set,"Manual Reg. Set ", // init enable
//	(void *)Test_PD6710,		"PCMCIA test     ", // init enable
//	(void *)Test_WaitPin,		"nWAIT test      ",	
//	(void *)Camera_Test,		"Camera test     ",
//	(void *)ProgramFlash,		"Program Flash   ",
//	(void *)Test_ISram,			"stepping ston test",
//	(void *)Test_Nand,			"Nand Flash      ",
//	(void *)AC97_Test,			"AC97 	   		 ",
//	(void *)User_Test,			"User Test       ",
//	(void *)Test_CpuSpeed,		"Cpu speed       ",	

	(void *)Uart_Test,			"UART 		     ",
	(void *)Power_Test,			"Power/Clock     ",
	(void *)Timer_Test,			"Timer 		     ",
	(void *)Rtc_Test,			"RTC        	 ",
	(void *)Test_Adc,			"ADC test        ",
	(void *)Test_AdcTs,			"Touch Screen test",
	(void *)NOR_flash_test,		"NOR flash test	 ",
	(void *)NAND_flash_test,	"NAND flash test ",
	(void *)Test_DMA,			"DMA 		     ",
	(void *)Test_Int,			"Interrupt 	     ",
	(void *)Spi_Test,			"SPI         	 ",
	(void *)Iic_Test,			"IIC         	 ",
	(void *)Test_SDI,			"SDIO     	     ",
	(void *)IIS_Test,			"IIS   	    	 ",
	(void *)IrDA_Test,			"IrDA Test       ",
	(void *)Lcd_Test,			"TFT-LCD 	     ",
	(void *)CS8900_Test,        "CS8900_Ethernet ",
	(void *)USB_download,		"USB download	 ",
	(void *)Test_PD6710, 		"PCMCIA Test	 ",
	0,0
};

// Clock select argument.
#define	UCLK_SEL	(1)
#define	HCLK_SEL	(3)
#define	PCLK_SEL	(4)
#define	DCLK_SEL	(5)
// Hidden
#define	MPLL_SEL	(0)
#define	FCLK_SEL	(2)

//===================================================================



void xmain(void)
{
	int i, sel, voltage=120;
	unsigned int mpll_val;

	Port_Init();	// GPIO port init.
	Led_Display(0x1);
//	MMU_Init();		// MMU init. I/D cache on.
	Led_Display(0x8);
	
/*
//////// user can set clock again.	/////////
	Delay(0);
	voltage=110;
	Delay(1);
#if FIN==12000000				// 12MHz.
	ChangeUPllValue(56,2,2);		// 48MHz
	for(i=0; i<7; i++);
	ChangeClockDivider(13,12);
	ChangeMPllValue(68,1,1);		//2440x
#else	// else xtal_in=16.9344MHz.
	ChangeUPllValue(60,4,2);		// 48MHz
	for(i=0; i<7; i++);
	ChangeClockDivider(13,12);
	//ChangeMPllValue(118,2,2);		//265Mhz
	//ChangeMPllValue(98,1,2);		//299Mhz
	//ChangeMPllValue(97,1,2);		//295Mhz
	ChangeMPllValue(110,3,1);		//398Mhz
	//ChangeMPllValue(120,2,1);		//531Mhz
#endif
//////// user can set clock again.	/////////
*/

	Led_Display(0x2);
	Calc_Clock(1); 					// initial value '0'
	UPDATE_REFRESH(Hclk);

	Isr_Init();
	Uart_Init(Pclk, 115200);
	Uart_Select(0); 		// uart0 select
	Uart_TxEmpty(0);		// uart0 select

	// timer setting for delay 100us unit.
	//Check whether or not the POWER_OFF wake-up.
	Delay(0);	//calibrate Delay()
	
	 //Turn on LCD.
//	Test_Lcd_Tft_8Bit_240320_On;

	//Check_SleepWakeUp();  //It's needed only for sleep mode test.
	//Save the wasted power consumption on GPIO.
	//rIISPSR=(2<<5)|(2<<0); //IIS_LRCK=44.1Khz @384fs,PCLK=50Mhz.
	// Set I/O strength control.
	rDSC0 = (0<<31)|(0x3<<8)|(0xff<<0);
//	rDSC0 = (0<<31)|(0x0<<8)|(0x00<<0);
	// nEN_DSC	[31]	: 0:I/O drive strength enable, 1:Disable
	// DSC_ADR	[9:8]	: Addr drive strength, 0:10mA, 1:8mA, 2:6mA, 3:4mA
	// DSC_DATA	[7:0]	: DATA drive strength, 0:12mA, 1:10mA, 2:8mA, 3:6mA
	rDSC1 = (0x3<<28)|(0x3<<26)|(0xfffff<<0);
//	rDSC1 = (0x0<<28)|(0x0<<26)|(0x00000<<0);
	// DSC_SCK1	[29:28]	: SCLK1, 0:16mA, 1:12mA, 2:8mA, 3:6mA
	// DSC_SCK0	[27:26]	: SCLK0, 0:16mA, 1:12mA, 2:8mA, 3:6mA
	// DSC_SCKE	[25:24]	: SCLKE, 0:10mA, 1:8mA, 2:6mA, 3:4mA
	// DSC_SDR	[23:22]	: nRAS/nCAS, 0:10mA, 1:8mA, 2:6mA, 3:4mA
	// DSC_NFC	[21:20]	: Nand flash(nFCE,nFRE,nFWE,CLE,ALE), 0:10mA, 1:8mA, 2:6mA, 3:4mA
	// DSC_BE	[19:18]	: nBE[3:0], 0:10mA, 1:8mA, 2:6mA, 3:4mA
	// DSC_WOE	[17:16]	: nBE[3:0], 0:10mA, 1:8mA, 2:6mA, 3:4mA
	// DSC_CS7	[15:14]	: nGCS7, 0:10mA, 1:8mA, 2:6mA, 3:4mA
	// DSC_CS6	[13:12]	: nGCS6, 0:10mA, 1:8mA, 2:6mA, 3:4mA
	// DSC_CS5	[11:10]	: nGCS5, 0:10mA, 1:8mA, 2:6mA, 3:4mA
	// DSC_CS4	[9:8]	: nGCS4, 0:10mA, 1:8mA, 2:6mA, 3:4mA
	// DSC_CS3	[7:6]	: nGCS3, 0:10mA, 1:8mA, 2:6mA, 3:4mA
	// DSC_CS2	[5:4]	: nGCS2, 0:10mA, 1:8mA, 2:6mA, 3:4mA
	// DSC_CS1	[3:2]	: nGCS1, 0:10mA, 1:8mA, 2:6mA, 3:4mA
	// DSC_CS0	[1:0]	: nGCS0, 0:10mA, 1:8mA, 2:6mA, 3:4mA
	Uart_Printf("uDSC0:0x%x, uDSC1:0x%x\n", rDSC0, rDSC1);

///////////////////// start testprogram ////////////////////////
	Uart_Printf("\n\n*****************************************************************\n");
	Uart_Printf("*           _   ___   _ ___   ___         _                     *\n");
	Uart_Printf("*          /_\\ |_ _| | |_ _| / __|_  _ __| |_ ___ _ __          *\n");
	Uart_Printf("*         / _ \\ | | || || |  \\__ \\ || (_-<  _/ -_) '  \\         *\n");
	Uart_Printf("*        /_/ \\_\\___\\__/|___| |___/\\_, /__/\\__\\___|_|_|_|        *\n");
	Uart_Printf("*                                 |__/                          *\n");
	Uart_Printf("*                                                               *\n");
	Uart_Printf("*              __  ______  ___   ___ ____ ____ ___              *\n");
	Uart_Printf("*             /  |/  / _ )/ _ | |_  / / // / // _ \\             *\n");
	Uart_Printf("*            / /|_/ / _  / __ |/ __/_  _/_  _/ // /             *\n");
	Uart_Printf("*           /_/  /_/____/_/ |_/____//_/  /_/ \\___/              *\n");
	Uart_Printf("*                                                               *\n");
	Uart_Printf("*                  (http://www.aijisytem.com)                   *\n");
	Uart_Printf("*****************************************************************\n");
	Uart_Printf("\n\n+-------------------------------------------------+\n");
	Uart_Printf("|    MBA2440A Firmware-Test ver 1.0 (%dM SDRAM)   |\n",
		MBA2440_MEM_SIZE>>20);
	Uart_Printf("+-------------------------------------------------+\n");
	Uart_Printf("+------------- [ SFR Information  ] --------------+\n");
	Uart_Printf("| [CPU ID    ] = %xh\n"	, rGSTATUS1);
	Uart_Printf("| [rSTATUS2  ] = 0x%x\n"	, rGSTATUS2);
	Uart_Printf("| [rSTATUS3  ] = 0x%x\n"	, rGSTATUS3);
	Uart_Printf("| [rSTATUS4  ] = 0x%x\n"	, rGSTATUS4);
	Uart_Printf("+------------- [CLOCK Information ]---------------+\n");
	Uart_Printf("| [FREQ_INPUT] = %6.4f(0x%x)\n"		,(float)FIN/MEGA, FIN);
	Uart_Printf("| [FCLK(Core)] = %4.1fMhz(0x%x)\n"	,(float)Fclk/MEGA, Fclk);
	Uart_Printf("| [HCLK(AHB) ] = %4.1fMhz(0x%x)\n"	,(float)Hclk/MEGA, Hclk);
	Uart_Printf("| [PCLK(APB) ] = %4.1fMhz(0x%x)\n"	,(float)Pclk/MEGA, Pclk);		
	Uart_Printf("| [UCLK(USB) ] = %4.1fMhz(0x%x)\n"	,(float)Uclk/MEGA, Uclk);
	Uart_Printf("+-------------------------------------------------+\n");

	Clk0_Enable(2);	// 0:MPLLin, 1:UPLL, 2:FCLK, 3:HCLK, 4:PCLK, 5:DCLK0
	Clk1_Enable(3);	// 0:MPLLout,1:UPLL, 2:RTC,  3:HCLK, 4:PCLK, 5:DCLK1	

////////////////////// menu start ///////////////////////////
	while(1) {
	   	i = 0;
		Uart_Printf("+-------- [MBA2440A DIAGNOSTIC Test Menu] --------+\n");
		while(1) {   //display menu
			Uart_Printf("| %2d:%s\n",i+1,function[i][1]);
			i++;
			if((int)(function[i][0])==0) {
				break;
			}
		}
		Uart_Printf("+-------------------------------------------------+\n");		
		Uart_Printf(" Select the number to test : ");
		sel = Uart_GetIntNum();
		sel--;
		Uart_Printf("+-------------------------------------------------+\n\n\n");		

		if(sel>=0 && (sel<(sizeof(function)/8)) ){
			( (void (*)(void)) (function[sel][0]) )();
		}else if(sel == -2){
		}else{
			Uart_Printf("Wrong number seleted.. Try again!!\n\n\n");
		}
	}
} // end of main().

//===================================================================
void Isr_Init(void)
{
    pISR_UNDEF  = (unsigned)HaltUndef;
    pISR_SWI    = (unsigned)HaltSwi;
    pISR_PABORT = (unsigned)HaltPabort;
    pISR_DABORT = (unsigned)HaltDabort;
	
    rINTMOD     = 0x0;					 //All=IRQ mode
    rINTMSK     = BIT_ALLMSK;			  //All interrupt is masked.
    rINTSUBMSK  = BIT_SUB_ALLMSK;		  //All sub-interrupt is masked. <- April 01, 2002 SOP
}

//===================================================================
void HaltUndef(void)
{
    Uart_Printf("Undefined instruction exception.\n");
    while(1);
}

//===================================================================
void HaltSwi(void)
{
#if !SEMIHOSTING	
		Uart_Printf("SWI exception!!!\n");
		while(1);
#endif	
}

//===================================================================
void HaltPabort(void)
{
    Uart_Printf("Pabort exception.\n");
    while(1);
}

//===================================================================
void HaltDabort(void)
{
    Uart_Printf("Dabort exception.\n");
    while(1);
}

void Clk0_Enable(int clock_sel)	
{	// 0:MPLLin, 1:UPLL, 2:FCLK, 3:HCLK, 4:PCLK, 5:DCLK0
	rMISCCR = rMISCCR&~(7<<4) | (clock_sel<<4);
	rGPHCON = rGPHCON&~(3<<18) | (2<<18);
}
void Clk1_Enable(int clock_sel)
{	// 0:MPLLout, 1:UPLL, 2:RTC, 3:HCLK, 4:PCLK, 5:DCLK1	
	rMISCCR = rMISCCR&~(7<<8) | (clock_sel<<8);
	rGPHCON = rGPHCON&~(3<<20) | (2<<20);
}
void Clk0_Disable(void)
{
	rGPHCON = rGPHCON&~(3<<18);	// GPH9 Input
}
void Clk1_Disable(void)
{
	rGPHCON = rGPHCON&~(3<<20);	// GPH10 Input
}
