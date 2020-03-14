/*
 * =====================================================================
 * NAME         : Led.c
 *
 * Descriptions : Main routine for S3C2440
 *
 * IDE          : CodeWarrior 2.0 or Later
 *
 * Modification
 *	  
 * =====================================================================
 */

#include "2440addr.h"
#include "libc.h"

//Function Declaration
void Led_Init();
void Led_Display(int data);

void Led_Init()
{
	/* TO DO : Init GPIO port connected to LED 
	 * LED[4:9] = GPB[5:10] */
	rGPBDAT |= (0x3f<<5);
	rGPBCON &= ~(0xfff<<10);
	rGPBCON |= (0x555<<10);
		
}

void Led_Display(int data)
{
	int i;
	
#if 0
	//** if ~ else를 사용할 경우 
	if(data == 0x1)
		rGPBDAT &= ~(1<<5); 	
	else if(data == 0x2)	
		rGPBDAT &= ~(1<<6); 	
	else if(data == 0x3)
		rGPBDAT &= ~(1<<7);
	else if(data == 0x4)
		rGPBDAT &= ~(1<<8);
	else if(data == 0x5)
		rGPBDAT &= ~(1<<9);
	else
		rGPBDAT &= ~(1<<10);
	 
#endif
	
#if 0
	//** switch ~ case를 사용할 경우 
	switch(data){
	
	case 1: 
		rGPBDAT &= ~(1<<5);
		break;
	case 2: 
		rGPBDAT &= ~(1<<6);
		break;
	case 3: 
		rGPBDAT &= ~(1<<7);
		break;
	case 4:
		rGPBDAT &= ~(1<<8);
		break;
	case 5:
		rGPBDAT &= ~(1<<9);
		break;
	default:
		rGPBDAT &= ~(1<<10);
		break;
	}
#endif 

#if 1
	//** 삼항연산자를 사용할 경우 
	(data == 1)? (rGPBDAT &= ~(1<<5)):(rGPBDAT |= (1<<5));
	(data == 2)? (rGPBDAT &= ~(1<<6)) :(rGPBDAT |= (1<<6));
	(data == 3)? (rGPBDAT &= ~(1<<7)):(rGPBDAT |= (1<<7));
	(data == 4)? (rGPBDAT &= ~(1<<8)):(rGPBDAT |= (1<<8));
	(data == 5)? (rGPBDAT &= ~(1<<9)):(rGPBDAT |= (1<<9));
	(data == 6)? (rGPBDAT &= ~(1<<10)):(rGPBDAT |= (1<<10));					
#endif

	for(i=0;i<0xfffff;i++);

	rGPBDAT |= (0x3f<<5);
}