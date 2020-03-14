#include "2440addr.h"
#include "option.h"
#include "libc.h"

//Function Declaration 
void Key_Port_Init(void);
void Key_Get_Pressed_with_LED();
int Key_Get_Pressed();
int Key_Wait_Get_Pressed();
void Key_Wait_Get_Released();

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

void Key_Get_Pressed_with_LED()
{
	/* TO DO : SW2/4/6/8/10 => LED4, SW3/5/7/9/11 => LED5 */
	int i;

	rGPBDAT &= ~(0x17<<0); rGPHDAT &= ~(0x1<<9);

	if((~(rGPFDAT>>3)) & 0x1)
	{
		rGPBDAT &= ~(1<<5);
		for(i=0;i<0xffff;i++);
		rGPBDAT |= (1<<5);
	}
	if((~(rGPFDAT>>4)) & 0x1)
	{
		rGPBDAT &= ~(1<<6);
		for(i=0;i<0xffff;i++);
		rGPBDAT |= (1<<6);
	}

	
}

int Key_Get_Pressed()
{
	/* TO DO : �Էµ� Ű���� Ȯ���Ͽ� �����ϴ� �Լ� */
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

		for(i=0;i<2;i++)
		{
			if(~(rGPFDAT>>3) & (0x1<<i))
				return i*5+1+j;
		}
	}
	return 0;

}

int Key_Wait_Get_Pressed()
{
	/* TO DO : Ű�� �������� ������ ���� �����ϵ��� ��ٷ� �ִ� �Լ� */
	int a;
	while(!( a=Key_Get_Pressed()));
	return a;
	
}

void Key_Wait_Get_Released()
{	
	/* TO DO : Ű�� �������� �ʾ��� ���� ��Ÿ���� �Լ� */
	while(Key_Get_Pressed());
}