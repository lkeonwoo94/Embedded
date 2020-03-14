/*****************************************
  NAME: power.c
  DESC: SLOW,HOLD mode test
  HISTORY:
  03.23.2002:purnnamu: first release for 2410
  06.02.2002:DonGo: Modified for 2440
  05.20.2005: modified for MBA2440
 *****************************************/
 
#include "def.h"
#include "option.h"
#include "2440addr.h"
#include "2440lib.h"
#include "2440slib.h" 

#include "lcdlib.h"
#include "sleep.h"
#include "power.h"
#include "pwr_c.h"
#include "pll.h"
#include "idle.h"
#include "iotest.h"
//#include "dvstest.h"

void __irq SlowEint0Int(void);
void Clk0_Enable(int clock_sel)	;

volatile int slowExit;


void * func_power_test[][2]=
{	
	//                          			"0123456789012345678"
	//Power mode test
	(void *)Check_SleepWakeUp,				"WakeUp status     ",
	(void *)Test_SlowMode,					"Slow mode test    ",
	(void *)Test_HoldMode,					"Hold mode test    ",
	//Clock test
	(void *)Test_Locktime,					"Lock time test    ",
//	(void *)Test_PLL,						"PLL change test   ",
	(void *)Manual_Change_Pll,				"PLL change(manual)",
//	(void *)Manual_Change_Pll_Iostrength,	"IO strneght test  ",
	(void *)Test_PllOnOff,					"PLL On/Off test   ",	
//	(void *)MeasurePowerConsumption,		"Power consumption ",	
	// Sleep mode test
	(void *)Test_IdleMode,					"Idle mode test    ",
	(void *)Test_MMUIdleMode, 				"Idle mode(MMU)    ",
	(void *)Test_SleepMode,					"Sleep mode test   ",
	(void *)Test_StopMode,					"Stop mode test   ",
//	(void *)Test_SleepMode_100Hz,			"Sleep mode 100Hz  ",
//	(void *)Test_BattFaultInterrupt,		"nBATT_FLT intr    ",
//	(void *)Test_InitSDRAM,					"SDRAM init        ",
	// I/O strength test.
	(void *)Test_IO_Strength, 				"IO Strength       ",
//	(void *)Dvs_Test,			 			"DVS test          ",
	
	0,0
};


void Power_Test(void)
{
	int i, sel;

	// Battery fault setting.
	rMISCCR = (rMISCCR & ~(0x7<<20)) | (1<<22) | (1<<21) | (0<<20);
		
	while(1)
	{
		i=0;
		Uart_Printf("+-------------[ Power/Clock test ]----------------+\n");
		while(1)
		{   //display menu
			Uart_Printf("| %2d:%s\n",i+1,func_power_test[i][1]);
			i++;
			if((int)(func_power_test[i][0])==0)	break;
		}

		Uart_Printf("| %2d:Previous menu\n", i+1);
		Uart_Printf("+-------------------------------------------------+\n");
		Uart_Printf(" Select the number to test : ");
		sel = Uart_GetIntNum();
		sel--;
		Uart_Printf("+-------------------------------------------------+\n\n\n");
		if(sel == i){
			return;
		}if(sel>=0 && (sel<((sizeof(func_power_test)-1)/8)) ){
			( (void (*)(void)) (func_power_test[sel][0]) )();
		}else{
			Uart_Printf("Wrong number seleted.. Try again!!\n\n\n");
		}
	}
}


//////////////////////////////////////////////////////////////////////////

void Test_SlowMode(void)
{
	int i;
	unsigned int saveREFRESH;

	slowExit=0;

	// GPIO and Interrupt setting
	rGPFCON=(rGPFCON & ~(0x3<<0)) | (0x2<<0); //PF0=EINT0
	rEXTINT0=(rEXTINT0&~(0x7<<0)) | (0x2<<0); //EINT0=falling edge triggered

	pISR_EINT0=(U32)SlowEint0Int;
	rINTMSK=~BIT_EINT0;		// Unmask eint0

	Uart_Printf("[SLOW MODE TEST]\n");
	Uart_Printf("  Press KEY1(EINT0) key to exit SLOW mode\n");
	Uart_Printf("  Check the CLKOUT0 pad clock is the same as X-tal input in Slow mode.\n");
	Uart_Printf("  Compare the LED Blink speed at each mode.\n");
	Uart_Printf("\n  Press any key to enter slow mode.\n");	
	Uart_TxEmpty(0);	//To avoid being crushed the character

	Clk0_Enable(2);	// 0:MPLLin, 1:UPLL, 2:FCLK, 3:HCLK, 4:PCLK, 5:DCLK0

	while(!slowExit) {
		Led_Display(0xa);
		//DoQsort(); 
		for(i=0; i<100; i++);
		
		Led_Display(0x5);
		//DoQsort();
		for(i=0; i<100; i++);

		if(Uart_GetKey()!=0) break;
	}
	Uart_Printf("Slow mode ...\n");
	Uart_Printf("After KEY1 button.. just wait a moment..\n");
	rCLKSLOW=(1<<7)|(1<<5)|(1<<4)|(0<<0); //FCLK=FIN/1,SLOW mode,MPLL=off,UPLL=off 

	// Re-setting the refresh count for 16.9344MHz HCLK.
	saveREFRESH=rREFRESH;
	rREFRESH=(1<<23)|(U32)(2048+1-16.93*7.8); //Trp=2clk,Trc=4clk

	while(!slowExit) {
		Led_Display(0xa);
		DoQsort(); 
		//for(i=0; i<100; i++);
		
		Led_Display(0x5);
		DoQsort();
		//for(i=0; i<100; i++);
	}

	rINTMSK=BIT_ALLMSK;

	rCLKSLOW=0|(1<<4)|(0<<5);//PLL on,MPLL=on
	for(i=0;i<2048;i++); //S/W MPLL lock-time
	rCLKSLOW=0|(0<<4)|(0<<5);//NORMAL mode,PLL on,MPLL=on
	Uart_Printf("\n\nslow mode test complete\n\n");
}


void __irq SlowEint0Int(void)
{
	Uart_Printf("\nKEY1 is pressed\n");
	ClearPending(BIT_EINT0);
	slowExit=1;
}


void Test_HoldMode(void)
{
  
	Uart_Printf("[Power Saving Mode by Stopping Each Block]\n");

	Uart_Printf("LCD ENVID is turned off.\n");
	Lcd_EnvidOnOff(0);
	Uart_Printf("Check the current cunsumption. Type any key to proceed.\n");	
	//Except GPIO,UART0
	rCLKCON=0xffff0;	// All enable. sleep disable, Idle trable.
	Uart_Getch();

	Uart_Printf("Nand off.\n");
	rCLKCON&=~(1<<4);
	Uart_Getch();

	Uart_Printf("LCD off.\n");
	rCLKCON&=~(1<<5);
	Lcd_EnvidOnOff(0);
	Uart_Getch();
	
	Uart_Printf("USB host off(DP0/DN0 is suspended).\n");
	rCLKCON&=~(1<<6);
	rMISCCR|=(1<<12); //USB port0 = suspend
	Uart_Getch();
	
	Uart_Printf("USB device off(DP1/DN1 is also suspended).\n");
	rCLKCON&=~(1<<7);
	rMISCCR|=(1<<13); //USB port1 = suspend
	Uart_Getch();

	Uart_Printf("PWM Timer off.\n");
	rCLKCON&=~(1<<8);
	Uart_Getch();

	Uart_Printf("SDI off.\n");
	rCLKCON&=~(1<<9);
	Uart_Getch();

	Uart_Printf("UART1 off.\n");
	rCLKCON&=~(1<<11);
	Uart_Getch();

	Uart_Printf("UART2 off.\n");
	rCLKCON&=~(1<<12);
	Uart_Getch();

	Uart_Printf("RTC_control off.\n");
	rCLKCON&=~(1<<14);
	Uart_Getch();
	
	Uart_Printf("ADC off.\n");
	rADCCON|=(1<<2);	// ADC stand-by mode select
	rCLKCON&=~(1<<15);
	Uart_Getch();
	
	Uart_Printf("IIC off.\n");
	rCLKCON&=~(1<<16);
	Uart_Getch();
	
	Uart_Printf("IIS off.\n");
	rCLKCON&=~(1<<17);
	Uart_Getch();
	
	Uart_Printf("SPI off.\n");
	rCLKCON&=~(1<<18);
	Uart_Getch();

	Uart_Printf("Camera off.\n");
	rCLKCON&=~(1<<19);
	Uart_Getch();
	
	Uart_Printf("Return to Normal Mode.\n\n\n");		
	rCLKCON=0xffff0; 
	rADCCON&=(1<<2);
	rMISCCR&=~((1<<12)|(1<<13)); //USB port0,1 = normal
	Lcd_EnvidOnOff(1);
}


void Clk0_Enable(int clock_sel)	
{	// 0:MPLLin, 1:UPLL, 2:FCLK, 3:HCLK, 4:PCLK, 5:DCLK0
	rMISCCR = rMISCCR&~(7<<4) | (clock_sel<<4);
	rGPHCON = rGPHCON&~(3<<18) | (2<<18);
}