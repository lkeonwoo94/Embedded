/*
 * =====================================================================
 * NAME         : Led.c
 *
 * Descriptions : Main routine for S3C2440
 *
 * IDE          : GCC-4.1.0
 *
 * Modification
 *	  
 * =====================================================================
 */

#include "2450addr.h"
#include "libc.h"

//Function Declaration
void Led_Init();
void Led_Display(int data);

void Led_Init()
{
	/* TO DO : Init GPIO port connected to LED 
	 * LED1:LED2:LED3:LED4 = GPG4:GPG5:GPG6:GPG7 */
	rGPGDAT |= (0xF<<4);
	rGPGCON &= ~(0xFF<<8);
	rGPGCON |= (0x55<<8);
		
}

void Led_Display(int data)
{
	int i;
	
	
	//** if ~ else�� ����� ��� 
	if(data & 0x1)		rGPGDAT &= ~(1<<4); 	
	else if(data & 0x3)	rGPGDAT &= ~(1<<5);  	
	else if(data & 0x5)	rGPGDAT &= ~(1<<6);	
	else				rGPGDAT &= ~(1<<7);

#if 0	
	//** switch ~ case�� ����� ��� 
	switch(data){
		
		case 1: 
			rGPGDAT &= ~(1<<4);
		
		case 3: 
			rGPGDAT &= ~(1<<5);
			
		case 5: 
			rGPGDAT &= ~(1<<6); 
			
		case 9: 
			rGPGDAT &= ~(1<<6); 
		}
#endif 

#if 0	
	//** ���׿����ڸ� ����� ��� 
	(data & 0x1)? (rGPGDAT &= ~(1<<4)):(rGPGDAT |= (1<<4));
	(data & 0x3)? (rGPGDAT &= ~(1<<5)):(rGPGDAT |= (1<<5));
	(data & 0x5)? (rGPGDAT &= ~(1<<6)):(rGPGDAT |= (1<<6));
	(data & 0x9)? (rGPGDAT &= ~(1<<7)):(rGPGDAT |= (1<<7));
#endif

	for(i=0;i<0x1ffff;i++);
	rGPGDAT |= (0xF<<4);
}