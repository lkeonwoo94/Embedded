#include "2450addr.h"
#include "option.h"

//LCD config (M2)

#define LCD_XSIZE 		(480)  	
#define LCD_YSIZE 		(272)  

#define VBPD		1 
#define VFPD		1  
#define VSPW		9 
#define HBPD		1 
#define HFPD		1 
#define HSPW		40 
#define CLKVAL		6 

#define HOZVAL		(LCD_XSIZE-1)
#define LINEVAL		(LCD_YSIZE-1)

// LCD

void Lcd_Init(void);
void Lcd_Envid_On_Off(int onoff);
void Lcd_Port_Init(void);
void Lcd_Set_Address(unsigned int fp);

// Graphic

void Graphic_Init(void);
void Lcd_Put_Pixel(int x, int y, int c);

// Functions

void Lcd_Envid_On_Off(int onoff)
{
	(onoff) ? (rLCDCON1 |= 1) : (rLCDCON1 &= ~0x1);
}    

void Lcd_Port_Init(void)
{
	rGPGDAT = rGPGDAT | (0x1<<4);
	rGPGCON = rGPGCON & (~(0x3<<8)|(0x1<<8));
	rGPCUDP = 0xffffffff; 
	rGPCCON = 0xaaaaaaaa;
	rGPDUDP = 0xffffffff; 
	rGPDCON = 0xaaaaaaaa;

}

void Lcd_Init(void)
{
	rLCDCON1=(CLKVAL<<8)+(0x3<<5)+(0xc<<1); // TFT LCD panel,16bpp TFT,ENVID=off
	rLCDCON2=(VBPD<<24)+(LINEVAL<<14)+(VFPD<<6)+(VSPW);
	rLCDCON3=(HBPD<<19)+(HOZVAL<<8)+(HFPD);
	rLCDCON4=(HSPW);
	rLCDCON5=(0x1<<9)+(0x1<<8)+(0x1); // 5:5:5:I format, Swap Enable
	rLCDINTMSK |= 0x3;
	rTPAL=0;
}

#define M5D(n) ((n) & 0x1fffff)

void Lcd_Set_Address(unsigned int fp)
{
	rLCDSADDR1=((fp>>22)<<21);
	rLCDSADDR2=M5D(fp+(LCD_XSIZE*LCD_YSIZE));
	rLCDSADDR3=LCD_XSIZE;
}

void Graphic_Init(void)
{
     Lcd_Set_Address((unsigned int)0x33800000);
     Lcd_Port_Init();
     Lcd_Init();
     Lcd_Envid_On_Off(1);    
}

// 프레임 버퍼 설정 (S3C2440A는 프레임 버퍼의 주소가 4MB align 되어야 함)
// 프레임 버퍼의 주소는 0x33800000으로 함

#define Fb_ptr  ((volatile unsigned short (*)[LCD_XSIZE])0x33800000)


__inline void Lcd_Put_Pixel(int x,int y,int color)
{
	Fb_ptr[y][x]=(unsigned short)color;
}

void Lcd_Draw_BMP(int x, int y, const unsigned short int *fp)
{
	register int width = fp[0], height = fp[1];
	register int xx, yy;
	
	for(yy=0;yy<height;yy++)
	{
		for(xx=0;xx<width;xx++)
		{
			 Lcd_Put_Pixel(xx+x,yy+y,(int)fp[yy*width+xx+2]);
		} 
	}
}

