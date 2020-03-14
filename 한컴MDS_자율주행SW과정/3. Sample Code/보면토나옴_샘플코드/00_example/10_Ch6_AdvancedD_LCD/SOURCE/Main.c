/*
 * =====================================================================
 * NAME         : Main.c
 *
 * Descriptions : Main routine for S3C2450
 *
 * IDE          : GCC-4.1.0
 *
 * Modification
 *	  
 * =====================================================================
 */
#include "2450addr.h"
#include "scape.h"
#include "my_lib.h"
#include "option.h"

#define EXAMPLE 620

/*	
 * 620 : ½Ç½À 10-1 Non-Palletized mode Test	
 * 
 * Advanced Course
 * 
 */
 
  /***************************************
 * 
 * Title: Non-Palletized mode Test
 * 
 ***************************************/

#if EXAMPLE == 620
#define BLACK	0x0000
#define WHITE	0xFFFF
#define BLUE	0x001F
#define GREEN	0x03E0
#define RED		0x7C00

#define  NonPal_Fb   ((volatile unsigned short(*)[480]) FRAME_BUFFER)

void Main(void)
{	
	int i,j,k=0;
	int color=0;
	
	Uart_Init(115200);	
	Lcd_Port_Init();
	NonPal_Lcd_Init();
	

	Uart_Send_Byte('\n');
	Uart_Send_Byte('A');	
	Uart_Send_String("Hello LCD Test...!!!\n");
	
	for(j=0; j<272; j++)
	{
		for(i=0; i<480; i++)
		{
			NonPal_Put_Pixel(i,j,WHITE);
		}
	}
	Uart_Send_String("Hello LCD Test...!!!\n");		
	
	
#if 1
	{
		NonPal_Put_Pixel(0,0,RED);
		NonPal_Put_Pixel(479,0,RED);
		NonPal_Put_Pixel(0,271,RED);
		NonPal_Put_Pixel(479,271,RED);
		NonPal_Put_Pixel(240,136,RED);			
	}
#endif	

#if 1
	{
		for(j=0; j<136; j++)
		{		
			for(i=0; i<240; i++)
				NonPal_Put_Pixel(i,j,RED);
		}
	}
	{
		for(j=136; j<272; j++)
		{		
			for(i=0; i<240; i++)
				NonPal_Put_Pixel(i,j,BLUE);
		}
	}
	{
		for(j=0; j<136; j++)
		{		
			for(i=240; i<480; i++)
				NonPal_Put_Pixel(i,j,GREEN);
		}
	}
#endif

#if 1	

	Lcd_Draw_BMP(0, 0, scape); 
 
#endif 
	Uart_Send_String("Test Finished...!!!\n");
}	


#endif 
