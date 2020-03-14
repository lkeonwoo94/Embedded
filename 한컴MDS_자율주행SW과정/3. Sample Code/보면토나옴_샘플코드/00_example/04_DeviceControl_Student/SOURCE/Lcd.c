#include "2450addr.h"
#include "option.h"

//LCD config (MDS2450)

#define LCD_XSIZE 		(480)  	
#define LCD_YSIZE 		(272)  

#define VBPD		9 
#define VFPD		1  
#define VSPW		1 
#define HBPD		42 
#define HFPD		1 
#define HSPW		1 
#define CLKVAL		13 

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
	if(onoff)
	{
		rVIDCON0 |= (0x3<<0);
	}
	else
	{
		rVIDCON0 |=  (0x1<<1));
		rVIDCON0 &= ~(0x1<<0));
	}
}    

void Lcd_Port_Init(void)
{
	rGPGDAT = rGPGDAT | (0x1<<4);	//GPG4 LCD Power Enable
	rGPGCON = rGPGCON & (~(0x3<<8)|(0x1<<8));//GPG4 output
	rGPCUDP = 0xffffffff; 
	rGPCCON = 0xaaaaaaaa;
	rGPDUDP = 0xffffffff; 
	rGPDCON = 0xaaaaaaaa;

}

void Lcd_Init(void)
{
	rVIDCON0=(0x0<<22)+(CLKVAL<<6)+(0x1<<13)+(1<<2);// PNRMODE(BGR), ENVID=off
	rVIDCON1= (1<<6)+(1<<5);
	rWINCON0=(0x7<<2)+(1<<0); //16bpp
	rVIDTCON0=(VBPD<<16)+(VFPD<<8)+(VSPW);
	rVIDTCON1=(HBPD<<16)+(HFPD<<8)+(HSPW);
	rVIDTCON2=(LINEVAL<<11)+(HOZVAL);
	
	//rLCDCON1=(CLKVAL<<8)+(0x3<<5)+(0xc<<1); // TFT LCD panel,16bpp TFT,ENVID=off
	//rLCDCON2=(VBPD<<24)+(LINEVAL<<14)+(VFPD<<6)+(VSPW);
	//rLCDCON3=(HBPD<<19)+(HOZVAL<<8)+(HFPD);
	//rLCDCON4=(HSPW);
	//rLCDCON5=(0x1<<9)+(0x1<<8)+(0x1); // 5:5:5:I format, Swap Enable
	//rLCDINTMSK |= 0x3;
	//rTPAL=0;
}

#define MASK23(n) ((n) & 0x00ffffff)

void Lcd_Set_Address(unsigned int fp)
{
	rVIDW00ADD0B0=(fp>>24)<<24;
	rVIDW01ADD1=MASK23(fp+(LCD_XSIZE*LCD_YSIZE));
	rVIDW01ADD2=LCD_XSIZE;
	//rLCDSADDR1=((fp>>22)<<21);
	//rLCDSADDR2=M5D(fp+(LCD_XSIZE*LCD_YSIZE));
	//rLCDSADDR3=LCD_XSIZE;
}

void Graphic_Init(void)
{
     Lcd_Set_Address((unsigned int)0x33000000);
     Lcd_Port_Init();
     Lcd_Init();
     Lcd_Envid_On_Off(1);
}

// ������ ���� ���� (S3C2440A�� ������ ������ �ּҰ� 4MB align �Ǿ�� ��)
// ������ ������ �ּҴ� 0x33800000���� ��

#define Fb_ptr  ((volatile unsigned short (*)[LCD_XSIZE])0x33000000)


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

