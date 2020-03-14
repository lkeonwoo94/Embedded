/*=========================*/
#include "my_lib.h"
#include "option.h"
#include "2450addr.h"
#include ".\images\bicycle.h"

void Main(void)
{
	
#if 1
	/* Testing LED with GPIO */
	int i, j;
	
	Led_Port_Init();
	for(i=0;i<16;i++) {
		Led_Display(i);
		for(j=0;j<0x1ffff;j++);
	}
#endif
	
	/* Initialize UART */
	Uart_Init(115200);
	Uart_Send_String("\nHello ARM !!!\n\n");
	
#if 1 /* UART TEST */
	while(1)
	{
	Uart_Send_String("Press any Key (Waiting for key input) : ");
	Uart_Printf("\nInput character is [%c]\n",Uart_GetChar());
	}
#endif

#if 0 /* TIMER TEST */

	Uart_Send_String("TIMER TEST !!!\n\n");
	Timer_Init();	
	while(1)
	{
		Uart_Send_String("1 second passed...\n");
		Timer_Delay(1000); // ´ÜÀ§´Â msec
	}	 
#endif
	
#if 0 /* KEY TEST */
	Uart_Send_String("Press any key : waiting .....\n");
	Key_Port_Init();
	
	for(;;)
	{
		Uart_Printf("Key Value =%d\n",  Key_Wait_Get_Pressed()); 
		Key_Wait_Get_Released();
	}
#endif

#if 0 /* KEY Interrupt TEST */
	/* External Interrupt Test */
	Uart_Send_String("Press any key : waiting key interrupt.....\n");	
	Key_INT_Init();
#endif

	Uart_Send_String("\n\n");

#if 0
	/* Frame Buffer Access Test */
{
	Graphic_Init( );
	Lcd_Draw_BMP(0, 0, bicycle); 
	Uart_Send_String("==================End");
}
#endif	
	
}
