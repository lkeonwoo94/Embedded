/*
 * =====================================================================
 * NAME         : Timer.c
 *
 * Descriptions : Timer Test Driver
 *
 * IDE          : CodeWarrior 2.0 or Later
 *
 * Modification
 *     Modified by MDS Tech. NT Div.(2Gr) (2007.3.1~4)
 * =====================================================================
 */

#include "2440addr.h"
#include "option.h"

//Function Declaration
void Timer_Init(void);
void Timer_DMA_Init(void);
void Timer_Delay(int msec);

void Timer_Init(void)
{
	/* TO DO :	Timer0 Init 
	* Prescaler value : 255, dead zone length = 0
	* Divider value : 1/16, no DMA mode
	* New frequency : (PCLK/(Prescaler value+1))*Divider value 
	= (50Mhz/(256))*(1/16)	= 12.207Khz(12207Hz)
	*/

	/* TCON설정 :Dead zone disable,  auto reload on, output inverter off
	*  manual update no operation, timer0 stop, TCNTB0=0, TCMPB0 =0
	*/
	rTCON  = (0<<4)|(1<<3)|(1<<2)|(0<<1)|(0);
	rTCNTB0 = 0;
	rTCMPB0 = 0;

  
}

void Timer_DMA_Init(void)
{
	/* TO DO : Timer0 Init 
	* Prescaler value : 255, dead zone length = 0
	* Divider value : 1/16,  DMA mode
	* New frequency : (PCLK/(Prescaler value+1))*Divider value 
	= (50Mhz/(256))*(1/16)	= 12.207Khz(12207Hz)
	*/
	rTCFG0 = (0<<8)|(0xff); // 256
	rTCFG1 = (1<<20)|(3); // (1/16)

	/* TCON설정 :Dead zone disable,  auto reload on, output inverter off
	*  manual update no operation, timer0 stop, TCNTB0=0, TCMPB0 =0
	*/
	rTCON  = (0<<4)|(1<<3)|(1<<2)|(0<<1)|(0);
	rTCNTB0 = 0;
	rTCMPB0 = 0;
  
}

void Timer_Delay(int msec)
{
	/*
	* 1) TCNTB0설정 : 넘겨받는 data의 단위는 msec이다.
	*   따라서 msec가 그대로 TCNTB0값으로 설정될 수는 없다.
	* 2) manual update후에  timer0를 start시킨다. 
	* 	 note : The bit has to be cleared at next writing.
	* 3) TCNTO0값이 0이 될때까지 기다린다. 	
	*/
	int i;
	rTCNTB0 = 12.207*msec;	

	rTCON |= (1<<1)|(0);
	rTCON &= ~(1<<1);
	
	rTCON |= 1;
	
//	while(!(rTCNTO0 == 0));
	while(rTCNTO0 != 0);
	
}