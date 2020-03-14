/*
 * =====================================================================
 * NAME         : Main.c
 *
 * Descriptions : Main routine for S3C2450
 *
 * IDE          : GCC-4.1.0
 *
 * Modification
 *	  
 * =====================================================================
 */
#include "2450addr.h"
#include "option.h"

#define EXAMPLE 610

/*********** 6장 Exam ***************	
 * 
 * 610 : Touch Test (실습 9-1 : Touch Test)
 * 
 * 
 * Advanced Course
 * 1. make macro function 
 */
 
 /***************************************
 * 
 * Title: Touch Test
 * 
 ***************************************/

#if EXAMPLE == 610
//**ISR Declaration
void Touch_ISR(void) __attribute__ ((interrupt ("IRQ")));

volatile  int ADC_x, ADC_y;
volatile  int Touch_Pressed=0;

void Touch_ISR()
{
	/* 인터럽트 허용하지 않음 on Touch */
	rINTSUBMSK |= (0x1<<9);
	rINTMSK1 |= (0x1<<31);	
	
	/* TO DO: Pendng Clear on Touch */	



	
	if(rADCTSC & 0x100)
	{
		rADCTSC &= (0xff); 
		Touch_Pressed = 0;
		Uart_Send_String("Detect Stylus Up Interrupt Signal \n");
	}
	
	else
	{
		Uart_Send_String(" ISR 내부  \n");
		
		/* TO DO : Stylus Down, YM_out Enable, YP_out Disable, XM_out Disable, XP_out disable
		 * 		   XP Pull-up Disable, Auto Sequential measurement of X/Y, No operation mode */


		/* TO DO : ENABLE_START */		

		
		/* wait until End of A/D Conversion */
	while(!(rADCCON & (1<<15)));
		
		/*store X-Position & Y-Position Conversion data value to ADC_x, ADC_y */
	ADC_x = (rADCDAT0 & 0x3ff);
	ADC_y = (rADCDAT1 & 0x3ff);
		
		Touch_Pressed = 1;
		
		/* TO DO : change to Waiting for interrupt mode 
		 *		   Stylus Up, YM_out Enable, YP_out Disable, XM_out Disable, XP_out disable
		 * 		   XP Pull-up Disable, Normal ADC conversion, Waiting for interrupt mode */		

	}
	
	/* 인터럽트 다시 허용  on Touch */
	rINTSUBMSK &= ~(0x1<<9);
	rINTMSK1 &= ~(0x1<<31);
	
}

void Main(void)
{	
	Uart_Init(115200);
	Touch_Init();	
	
	Uart_Printf("*** Touch Test *** \n");
	
	/* TO DO : 인터럽트 벡터에 Touch_ISR 함수 등록 */

	
	/* TO DO :  인터럽트 허용 on Touch */


	
	while(1)
	{
		if(Touch_Pressed)
		{
			Uart_Printf("X : %d, Y: %d \n", ADC_x, ADC_y);	
			while(!(Touch_Pressed==0));
			Uart_Printf("Released\n\n");			
		}
	}
}

#endif 
