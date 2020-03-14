/*
 * =====================================================================
 * NAME         : Main.c
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
#include "DEMO256.h"
#include "scape.h"
#include "my_lib.h"

#define EXAMPLE 620

/*	
 * 620 : 실습 10-1 Non-Palletized mode Test
 * 
 * 621 : 실습 10-2 Palletized mode Test
 *	
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
#define WHITE	0xfffe
#define BLUE	0x003e
#define GREEN	0x07c0
#define RED		0xf800

void Main(void)
{	
	int i,j,k=0;
	int color=0x;
	
	Uart_Init(115200);	
	Lcd_Port_Init();
	NonPal_Lcd_Init();
	

	Uart_Send_Byte('\n');
	Uart_Send_Byte('A');
	Uart_Send_String("Hello LCD Test...!!!\n");
	
	for(j=0; j<272; j++)
	{
		for(i=0; i<480; i++)
			NonPal_Put_Pixel(i,j,WHITE);
			
	}
	Uart_Send_String("Hello LCD Test...!!!\n");		
	
	
#if 1
	{
	NonPal_Put_Pixel(0,0,RED);
	NonPal_Put_Pixel(319,0,RED);
	NonPal_Put_Pixel(0,239,RED);
	NonPal_Put_Pixel(319,239,RED);
	NonPal_Put_Pixel(160,120,RED);
	}
#endif	

#if 1
	{
	for(j=0; j<120; j+=1)
		{		
		for(i=0; i<160; i+=1)
			NonPal_Put_Pixel(i,j,RED);
		}
	}
#endif

#if 1

	Lcd_Draw_BMP(0, 0, scape);
 
#endif 
	Uart_Send_String("Test Finished...!!!\n");
}	


#endif 
 
 /***************************************
 * 
 * Title: Palletized mode Test
 * 
 ***************************************/

#if EXAMPLE == 621

void Main(void)
{	
	int i,j,k=0;
	int color=0x;
	
	Uart_Init(115200);
	Lcd_Port_Init();
	Palette_Init();	
	Lcd_Init();

	Uart_Send_Byte('\n');
	Uart_Send_Byte('A');	
	Uart_Send_String("Hello LCD Test...!!!\n");
	
	for(j=0; j<272; j++)
	{
		for(i=0; i<480; i++)
			Put_Pixel(i,j,0x80);
			
	}
	
	
	Uart_Send_String("Hello LCD Test...!!!\n");

#if 1
	{
	Put_Pixel(0,0,(int)0x00);
	Put_Pixel(319,0,(int)0x00);
	Put_Pixel(0,239,(int)0x00);
	Put_Pixel(319,239,(int)0x00);
	Put_Pixel(160,120,(int)0x00);			
	}
#endif	

#if 1
	{
	for (j=0;j<120; j+=2)
		for(i=1; i<160; i+=2)
			Put_Pixel(i,j,0x33); 

	}
#endif

#if 1	
	for(j=240; j>0; j--)
	{		
		for(i=0; i<320; i++)
			Put_Pixel(i,j,DEMO256[k++]);
	} 
#endif

	Uart_Send_String("Test Finished...!!!\n");	
	
}	
#endif 
