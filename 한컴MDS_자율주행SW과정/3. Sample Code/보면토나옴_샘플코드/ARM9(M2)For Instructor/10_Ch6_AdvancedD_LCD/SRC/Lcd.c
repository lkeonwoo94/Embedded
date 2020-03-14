/*
 * =====================================================================
 * NAME         : Lcd.c
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
#include "my_lib.h"

#define LCD_SIZE_X (480)
#define LCD_SIZE_Y (272)
#define CLKVAL  	4
#define HOZVAL 	   (LCD_SIZE_X-1)
#define LINEVAL    (LCD_SIZE_Y-1)

//#define VBPD (10)
//#define VFPD (10)
//#define VSPW (5)
//#define HBPD (10)
//#define HFPD (10)
//#define HSPW (5)

#define VBPD (10)
#define VFPD (4)
#define VSPW (10)
#define HBPD (45)
#define HFPD (8)
#define HSPW (41)

#define M5D(n) ((n) & 0x1fffff)	// To get lower 21bits

#define  NonPal_Fb   ((volatile unsigned short(*)[480]) FRAME_BUFFER)
#define  Fb   ((volatile unsigned long(*)[120]) FRAME_BUFFER)


//Function Declaration
void Lcd_Port_Init(void);
void Lcd_Init(void);
void NonPal_Lcd_Init(void);
void Palette_Init(void);
void Put_Pixel(unsigned long x, unsigned long y, unsigned long pal_addr);
void NonPal_Put_Pixel(int x, int y, int color);
void Lcd_Draw_BMP(int x, int y, const unsigned char *fp);

static unsigned short bfType;
static unsigned int bfSize;
static unsigned int bfOffbits;
static unsigned int biWidth, biWidth2;
static unsigned int biHeight;

void Lcd_Port_Init(void)
{
	
	rGPCUP = 0xffffffff; 
	rGPCCON &= ~(0xffffffff);
	rGPCCON |= 0xaaaaaaaa;
	
	rGPDUP = 0xffffffff; 
	rGPDCON &= ~(0xffffffff);
	rGPDCON |= 0xaaaaaaaa;
	
	/* GPG4 is setted as LCD_PWREN */
	rGPGUP=rGPGUP&(~(1<<4))|(1<<4); // Pull-up disable
	rGPGCON=rGPGCON&(~(3<<8))|(3<<8); //GPG4=LCD_PWREN		
}

void Lcd_Init()
{	

	//	Fb = (unsigned long (*)[80])FRAME_BUFFER; 
	
	/* TO DO : setting for LCD control 
	* CLKVAL=1, PNRMODE=TFT Lcd panel, BPPMODE=8bpp for TFT, ENVID=disable
	*/
//	rLCDCON1 |= (CLKVAL<<8)|(0<<7)|(3<<5)|(0xb<<1)|(0<<0); // (만약 16bpp이면 0xc<<1)
//	rLCDCON2 |= (VBPD<<24)|(LINEVAL<<14)|(VFPD<<6)|(VSPW<0);
//	rLCDCON3 |= (HBPD<<19)|(HOZVAL<<8)|(HFPD<<0);
//	rLCDCON4 |= (13<<8)|(HSPW<07);
//	rLCDCON5 |= (0<<12)|(1<<11)|(0<<10)|(1<<9)|(1<<8)|(0<<3)|(0<<1)|(0<<0);

	rLCDCON1 = (CLKVAL<<8)|(0<<7)|(3<<5)|(0xb<<1)|(0<<0); // (만약 16bpp이면 0xc<<1)
	rLCDCON2 = (VBPD<<24)|(LINEVAL<<14)|(VFPD<<6)|(VSPW<0);
	rLCDCON3 = (HBPD<<19)|(HOZVAL<<8)|(HFPD<<0);
	rLCDCON4 = (0<<8)|(HSPW<07);
	rLCDCON5 = (0<<12)|(0<<11)|(0<<10)|(1<<9)|(1<<8)|(1<<3)|(0<<1)|(0<<0);	
	
	rLCDSADDR1 = ((FRAME_BUFFER>>22)<<21)+(0x1fffff&(FRAME_BUFFER>>1));
	rLCDSADDR2 = (0x1fffff & (((FRAME_BUFFER)+((LCD_SIZE_X)*(LCD_SIZE_Y)))>>1));
	rLCDSADDR3 = (LCD_SIZE_X);
	
	rTPAL = 0;   
	rTCONSEL &= ~(0x7);
	
	/* TO DO : ENVID Enable for video output and LCD control signal */  
	rLCDCON1 |= 1;
}

void NonPal_Lcd_Init()
{	
	 
	//	NonPal_Fb = (unsigned short int (*)[320])FRAME_BUFFER; 
	
	/* TO DO : setting for LCD control 
	* CLKVAL=1, PNRMODE=TFT Lcd panel, BPPMODE=16bpp for TFT, ENVID=disable
	*/
	rLCDCON1 = (CLKVAL<<8)|(0<<7)|(3<<5)|(0xc<<1)|(0<<0);
	rLCDCON2 = (VBPD<<24)|(LINEVAL<<14)|(VFPD<<6)|(VSPW<0);
	rLCDCON3 = (HBPD<<19)|(HOZVAL<<8)|(HFPD<<0);
	rLCDCON4 = (0<<8)|(HSPW<07);
	rLCDCON5 = (0<<12)|(0<<11)|(0<<10)|(1<<9)|(1<<8)|(1<<3)|(0<<1)|(0<<0);
	
	/* TO DO : Half-Word swap Enable  */
	rLCDCON5 |= 1;	
	rLCDSADDR1= ((FRAME_BUFFER>>22)<<21)+(0x1fffff&(FRAME_BUFFER>>1));
	rLCDSADDR2 = (0x1fffff&(FRAME_BUFFER>>1))+(0x1fffff & ((FRAME_BUFFER + (LCD_SIZE_X)*(LCD_SIZE_Y)*2)>>1));
	rLCDSADDR3= LCD_SIZE_X;

	rTPAL = 0;
	rTCONSEL &= ~(0x7);     
	
	/* TO DO : ENVID Enable for video output and LCD control signal */
	rLCDCON1 |= 1;
}

 
void Put_Pixel(unsigned long x, unsigned long y, unsigned long pal_addr)
{	
	Fb[y][x/4] = (Fb[y][x/4]
	&~(0xff000000>>((x)%4)*8))|((pal_addr&0x000000ff)<<((4-1-((x)%4))*8));	
}

void NonPal_Put_Pixel(int x, int y, int color)
{
	/* TO DO : Fill FRAMEBUFFER with color value  */
	NonPal_Fb[y][x] = (unsigned short int)color;	
}

void Palette_Init()
{
	int i;
	unsigned int * palette;
	rLCDCON5 |= (1<<11);
	palette = (unsigned int *)PALETTE;
	for(i=0;i<256;i++)
		*palette ++ = DEMO256pal[i];
		
}

void Lcd_Draw_BMP(int x, int y, const unsigned char *fp)
{
     int xx=0, yy=0;	
     unsigned int tmp;
     unsigned char tmpR, tmpG, tmpB;
	
     bfType=*(unsigned short *)(fp+0);
     bfSize=*(unsigned short *)(fp+2);
     tmp=*(unsigned short *)(fp+4);
     bfSize=(tmp<<16)+bfSize;
     bfOffbits=*(unsigned short *)(fp+10);
     biWidth=*(unsigned short *)(fp+18);    
     biHeight=*(unsigned short *)(fp+22);    
     biWidth2=(bfSize-bfOffbits)/biHeight;	
     for(yy=0;yy<biHeight;yy++)
     {
         for(xx=0;xx<biWidth;xx++)
         {
             tmpB=*(unsigned char *)(fp+bfOffbits+(biHeight-yy-1)*biWidth*3+xx*3+0);
             tmpG=*(unsigned char *)(fp+bfOffbits+(biHeight-yy-1)*biWidth*3+xx*3+1);
             tmpR=*(unsigned char *)(fp+bfOffbits+(biHeight-yy-1)*biWidth*3+xx*3+2);
             tmpR>>=3;
             tmpG>>=3;
             tmpB>>=3;
             
             if(xx<biWidth2) NonPal_Put_Pixel(x+xx,y+yy,(tmpR<<11)+(tmpG<<6)+(tmpB<<1));
         } 
     }
    
}