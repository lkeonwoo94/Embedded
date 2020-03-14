/***************************************************************
*
*	1. System Init Test 
* 
*	Created by MDS Tech. NT Div.(2Gr) (2007.3.1~4)
*
****************************************************************
*/

#include "2440addr.h"

void LED_Port_Init(void);
void LED_ON_Off(void);

void Main()
{
	int i;
	LED_Port_Init();

	for(i=0;;i++)
	{
		LED_ON_Off();	
	}

	
}

void LED_Port_Init()
{
/*  
	
	Configure LED4(GPB5) as OUTPUT
	
	ldr r0, =GPBCON	//0x56000010
	ldr r1, [r0]
	bic r1, r1, #0xc00
	orr r1, r1, #0x400
	str r1, [r0]

*/	
	rGPBCON &= ~(0x3<<10);
	rGPBCON |= (0x1<<10);
}

void LED_ON_Off()
{
/*	
	Make LED4(GPB5) to LOW
	
	ldr r0, =GPBDAT 
	ldr r1, [r0]
	orr r1, r1, #0x20
	bic r1, r1, #0x20
	str r1, [r0]
*/
	int i;

	rGPBDAT &= ~(0x1<<5);
	for(i=0;i<0xfffff;i++); /*  time delay   */
	
	rGPBDAT |= (0x1<<5);
	for(i=0;i<0xfffff;i++); /*  time delay   */
		
}
