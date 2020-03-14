#include "2440addr.h"

void Touch_Init(void);


void Touch_Init(void)
{
	rADCDLY = (50000); 
     /* TO DO : prescaler enable, prescaler value=39, Analog no input, 
      * 		Normal operation mode, Disable start, No operation */
	rADCCON =(1<<14)|(39<<6)|(0<<3)|(0<<2)|(0<<1)|(0);  
	 
	 /* TO DO :  For Waiting Interrupt Mode rADCTSC=0xd3 */
	rADCTSC =(0<<8)|(1<<7)|(1<<6)|(1<<4)|(0<<3)|(0<<2)|(3);

	
}

