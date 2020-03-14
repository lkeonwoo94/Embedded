/*
 * File:		main.c
 *
 * Purpose:		Sample LED Blink application in C for Integrator to demonstrate board initialization
 *				on power up and exception handling. On power on/reset LED1 will blink 5 times. 
 *				Then LED3 will blink 5 times under SWI. Finaly both LED's LED1 and LED3
 *				will blink 5 times on successful exit from SWI.
 *
 * Created on:	Dec 09, 2003
 * 
 * Created by: 	Manoj Mehta 
 *
 */

#define LED_ALPHA_MASK		0x00000001					
#define LED_LIGHTS_ON		0x0F
#define LED_LIGHTS_OFF		0x00
#define LED_LIGHTS_1_ON		0x01
#define LED_LIGHTS_3_ON		0x04
#define LED_LIGHTS_1_3_ON	0x05

#define LED_ALPHA	(*(unsigned long*)	(0x1A000000)) 	// LED_ALPHA Register on Integrator AP 
#define LED_LIGHTS	(*(unsigned char*) 	(0x1A000004)) 	// LED_LIGHTS Register on Integrator AP

void delay (unsigned long);
void LED_Blink();

int main ()
{	
	volatile long i=0;
	unsigned long j=0;
		
	while(LED_ALPHA & LED_ALPHA_MASK){}	// Wait for display idle status
	
	
	LED_LIGHTS	=	LED_LIGHTS_OFF;		// Set all LED to OFF
	
	for (j=0; j < 5; j++) 		// LED1(GREEN) will blink 5 times first on Power On / Reset
	{
			
		while(LED_ALPHA & LED_ALPHA_MASK){}
		LED_LIGHTS	=	LED_LIGHTS_OFF;
	
		delay(100000);
		
		while(LED_ALPHA & LED_ALPHA_MASK){}
		LED_LIGHTS	=	LED_LIGHTS_1_ON;
		
		delay(100000);
	
	}
	
	while(LED_ALPHA & LED_ALPHA_MASK){}
	LED_LIGHTS	=	LED_LIGHTS_OFF;
	
	delay(100000);				// Pause
	
	asm
	{
	
		swi 0x776655; 			// LED3 (RED) will blink 5 times under SWI 
	
	}


	for (j=0; j < 5; j++) 		// Both LED1 and LED3 will blink 5 times
	{
			
		while(LED_ALPHA & LED_ALPHA_MASK){}
		LED_LIGHTS	=	LED_LIGHTS_OFF;
	
		delay(100000);
		
		while(LED_ALPHA & LED_ALPHA_MASK){}
		LED_LIGHTS	=	LED_LIGHTS_1_3_ON;
		
		delay(100000);
	}
}

void delay(unsigned long count)	// Simple delay routine
{
	while(count)
	{
		count--;
	}
}

void LED_Blink() 				// LED3 blink routine. Called from SWI
{

	unsigned long i;
	unsigned long j;
	
	for (j=0; j < 5; j++)
	{
	
		while(LED_ALPHA & LED_ALPHA_MASK){}
		LED_LIGHTS	=	LED_LIGHTS_OFF;
	
		delay(100000);
		
		while(LED_ALPHA & LED_ALPHA_MASK){}
		LED_LIGHTS	=	LED_LIGHTS_3_ON;
		
		delay(100000);
	}
	
	while(LED_ALPHA & LED_ALPHA_MASK){}
	LED_LIGHTS	=	LED_LIGHTS_OFF;

	delay(100000);

}
