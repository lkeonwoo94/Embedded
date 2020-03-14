/***************************************************************
*
*	1. System Init Test 
* 
*	Created by MDS Tech. NT Div.(2Gr) (2015.10.30)
*
****************************************************************
*/

#include "2450addr.h"

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
	
	Configure LED2(GPG5) as OUTPUT
	
	ldr r0, =GPGCON	//0x56000060
	ldr r1, [r0]
	bic r1, r1, #0xc00
	orr r1, r1, #0x400
	str r1, [r0]

*/	
	
	rGPGCON &= ~(0x3<<10);
	rGPGCON |= (0x1<<10);	
	
}

void LED_ON_Off()
{
/*	
	Make LED2(GPG5) to LOW
	
	ldr r0, =GPGDAT 
	ldr r1, [r0]
	orr r1, r1, #0x20
	bic r1, r1, #0x20
	str r1, [r0]
*/
	int i;
	
	rGPGDAT &= ~(0x1<<5);	
	for(i=0;i<0xfffff;i++); /*  time delay   */
	
	rGPGDAT |= (0x1<<5);	
	for(i=0;i<0xfffff;i++); /*  time delay   */
	
		
}