#include "2440addr.h"

//Function Declaration 
void Key_Port_Init(void);
void Key_IRQ_Port_Init(void);
int Key_Get_Pressed(void);
int Key_Wait_Get_Pressed(void);
void Key_Wait_Get_Released(void);

//Function
void Key_Port_Init(void)
{
	// KEYOUT[0:4] = GPB[0:2] & GPH[9] & GPB[4], KEYIN[0:1] = GPF[3:4]
	
	/* TODO : GPFCON - Input mode */
	rGPFCON &= ~(0xf<<6);
	rGPFUP &=~(0x3<<3);
	
	/* TODO : GPBCON & GPHCON - output mode */
	rGPBDAT |= 0x17<<0;
	rGPBCON &= ~(0x33f)<<0;
	rGPBCON |= 0x115<<0;
	rGPHDAT |= 0x1<<9;
	rGPHCON &= ~(0x3)<<18;
	rGPHCON |= 0x1<<18;
}

void Key_IRQ_Port_Init(void)
{
	/* TO DO :  GPFCON[4:3] = Interrupt mode (10) */ 
	rGPFCON &= ~(0x3<<6);
	rGPFCON |= (0x2<<6);
	
	/* KEYOUT[0:4] = GPBCON[4:0] : Output mode
	 * GPBDAT[4:0] : initial data is all 0 for falling interrupt
	 */
	rGPBDAT &= ~(0x17<<0);
	rGPBCON &= ~(0x33f<<0);
	rGPBCON |= 0x115<<0;
	rGPHDAT &= ~(0x1<<9);
	rGPHCON &= ~(0x3)<<18;
	rGPHCON |= 0x1<<18;
		
	/* EXTINT0[14:12] = falling edge  */
	rEXTINT0 &= ~(0x7<<12);
	rEXTINT0 |= (0x2<<12);
	
}


int Key_Get_Pressed()
{
	/* TO DO : 입력된 키값을 확인하여 리턴하는 함수 */
	int i,j;

	for(j=4 ; j>=0 ; j-- )
	{
		if (j==3) {
			rGPBDAT |= 0x17;
			rGPHDAT |= 0x1<<9;
			rGPHDAT &= ~(0x1<<9);
		} else {
			rGPHDAT |= 0x1<<9;
			rGPBDAT |= (0x17);
			rGPBDAT &= ~(0x1<<j);
		}


		if ((~(rGPFDAT>>3) & 1))
			return j+1;

	}
	return 0;

}

int Key_Wait_Get_Pressed()
{
	int a,i;
	while(!( a=Key_Get_Pressed()));
	for(i=0;i<0x3ff;i++);
	return a;
	
}

void Key_Wait_Get_Released()
{	
	while(Key_Get_Pressed());
}