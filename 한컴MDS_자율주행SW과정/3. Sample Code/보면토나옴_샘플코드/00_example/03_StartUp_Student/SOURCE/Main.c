/*=========================*/
#include "my_lib.h"
#include "option.h"
#include "2450addr.h"
#include ".\images\bicycle.h"

int bss_test = 0;
void Main(void)
{
	int i, j;
	int test=0;
	
	Uart_Init(115200);
	Uart_Send_String("\nHello ARM !!!\n\n");

	/* LED Test */
	Led_Port_Init();
	for(i=0;i<32;i++) {
		Led_Display(i);
		for(j=0;j<0x1ffff;j++);
	}

	for (i=0;i<10;i++) 
	{
		Uart_Printf("%d. BSS area variable increment : %d (must be %d)\n",i, bss_test++, test++);
	}
	
	Uart_Printf("\nStartUp Code Finished\n");
	
#if 1
	/* Frame Buffer Access Test */
{
	Graphic_Init( );
	Lcd_Draw_BMP(0, 0, bicycle); 
}
#endif	
	
}
