/************************************************ 
  NAME    : LCDLIB.H
  DESC    :
  Revision History
  2002.03.12 : draft ver 0.0
 ************************************************/

#ifndef __LCDLIB_H__
#define __LCDLIB_H__

#define MVAL		(13)
#define MVAL_USED 	(0)
#define M5D(n) ((n) & 0x1fffff)	// To get lower 21bits

//Selecting LCD type
//STN LCD Panel(320*240)
#define MODE_STN_1BIT 			(0x1001)
#define MODE_STN_2BIT  			(0x1002)
#define MODE_STN_4BIT  			(0x1004)
//Color STN LCD Panel(320*240)
#define MODE_CSTN_8BIT   		(0x2001)
#define MODE_CSTN_12BIT 		(0x2002)
#define MODE_CSTN_12BIT_UP 		(0x2004)
#define MODE_CSTN_16BIT 		(0x2008) // for 2440A
//TFT LCD Panel(240*320)
#define MODE_TFT_1BIT_240320    (0x4101)
#define MODE_TFT_8BIT_240320 	(0x4102)
#define MODE_TFT_16BIT_240320   (0x4104)
#define MODE_TFT_24BIT_240320   (0x4108)
//TFT LCD Panel(640*480)
#define MODE_TFT_1BIT_640480    (0x4201)
#define MODE_TFT_8BIT_640480    (0x4202)
#define MODE_TFT_16BIT_640480   (0x4204)
#define MODE_TFT_24BIT_640480   (0x4208)
//TFT LCD Panel(800*600)
#define MODE_TFT_1BIT_800600    (0x4401)
#define MODE_TFT_8BIT_800600    (0x4402)
#define MODE_TFT_16BIT_800600   (0x4404)
//TFT LCD Panel(320*240)
#define MODE_TFT_1BIT_320240    (0x5001)
#define MODE_TFT_8BIT_320240    (0x5002)
#define MODE_TFT_16BIT_320240   (0x5004)
#define MODE_TFT_24BIT_320240    (0x5008)


//Physical LCD resolution
//STN
#define LCD_XSIZE_STN 			(320)
#define LCD_YSIZE_STN 			(240)
//Color STN
#define LCD_XSIZE_CSTN 			(320)
#define LCD_YSIZE_CSTN 			(240)
//TFT 240320
#define LCD_XSIZE_TFT_240320 	(240)	
#define LCD_YSIZE_TFT_240320 	(320)
//TFT 320240
#define LCD_XSIZE_TFT_320240 	(320)	
#define LCD_YSIZE_TFT_320240 	(240)
//TFT 640480
#define LCD_XSIZE_TFT_640480 	(640)	
#define LCD_YSIZE_TFT_640480 	(480)
//TFT 800600
#define LCD_XSIZE_TFT_800600 	(800)	
#define LCD_YSIZE_TFT_800600 	(600)

//Virtual screen size
//STN
#define SCR_XSIZE_STN 			(LCD_XSIZE_STN*2)   //for virtual screen  
#define SCR_YSIZE_STN 			(LCD_YSIZE_STN*2)
//Color STN
#define SCR_XSIZE_CSTN 			(LCD_XSIZE_CSTN*2)   //for virtual screen  
#define SCR_YSIZE_CSTN 			(LCD_YSIZE_CSTN*2)
//TFT 240320
#define SCR_XSIZE_TFT_240320 	(LCD_XSIZE_TFT_240320*2)
#define SCR_YSIZE_TFT_240320 	(LCD_YSIZE_TFT_240320*2)
//TFT 320240
#define SCR_XSIZE_TFT_320240 	(LCD_XSIZE_TFT_320240*2)
#define SCR_YSIZE_TFT_320240 	(LCD_YSIZE_TFT_320240*2)
//TFT 640480
#define SCR_XSIZE_TFT_640480 	(LCD_XSIZE_TFT_640480*2)
#define SCR_YSIZE_TFT_640480 	(LCD_YSIZE_TFT_640480*2)
//TFT 800600
#define SCR_XSIZE_TFT_800600 	(LCD_XSIZE_TFT_800600*2)
#define SCR_YSIZE_TFT_800600 	(LCD_YSIZE_TFT_800600*2)

//Valid data 
//STN
#define HOZVAL_STN			(LCD_XSIZE_STN/4-1)	// Valid VD data line number is 4.
#define LINEVAL_STN			(LCD_YSIZE_STN-1)
//Color STN
#define HOZVAL_CSTN			(LCD_XSIZE_CSTN*3/8-1)	// Valid VD data line number is 8.
#define LINEVAL_CSTN		(LCD_YSIZE_CSTN-1)
//TFT240320
#define HOZVAL_TFT_240320	(LCD_XSIZE_TFT_240320-1)
#define LINEVAL_TFT_240320	(LCD_YSIZE_TFT_240320-1)
//TFT320240
#define HOZVAL_TFT_320240	(LCD_XSIZE_TFT_320240-1)
#define LINEVAL_TFT_320240	(LCD_YSIZE_TFT_320240-1)
//TFT640480
#define HOZVAL_TFT_640480	(LCD_XSIZE_TFT_640480-1)
#define LINEVAL_TFT_640480	(LCD_YSIZE_TFT_640480-1)
//TFT800600
#define HOZVAL_TFT_800600	(LCD_XSIZE_TFT_800600-1)
#define LINEVAL_TFT_800600	(LCD_YSIZE_TFT_800600-1)

//STN
#define WLH_STN	    		(0)
#define WDLY_STN			(0)
#define LINEBLANK_MONO		(1 &0xff) // MONO timing parameter for CPT CLS-040S-C3M(CHUNGHWA)
#define LINEBLANK_GRAY		(13 &0xff)// GRAY timing parameter for CPT CLS-040S-C3M(CHUNGHWA)
//CSTN timing parameter for LCBHBT161M(NANYA)
#define WLH_CSTN	        (0)
#define WDLY_CSTN			(0)
#define LINEBLANK_CSTN		(16 &0xff)
//Timing parameter for LTS350Q1(SAMSUNG) 
/*
#define VBPD_240320			((2-1)&0xff)
#define VFPD_240320			((3-1)&0xff)
#define VSPW_240320			((2-1) &0x3f)
#define HBPD_240320			((7-1)&0x7f)
#define HFPD_240320			((3-1)&0xff)
#define HSPW_240320			((4-1)&0xff)
*/
//Timing parameter for Toppoly 
#define VBPD_240320			((1)&0xff)
#define VFPD_240320			((2)&0xff)
#define VSPW_240320			((1) &0x3f)
#define HBPD_240320			((80)&0x7f)
#define HFPD_240320			((2)&0xff)
#define HSPW_240320			((1)&0xff)

//Timing parameter for LandScape type LCD
//Timing parameter for LTS350Q1(SAMSUNG) 
#define VBPD_320240		((3-1)&0xff)
#define VFPD_320240		((4-1)&0xff)
#define VSPW_320240		((5-1)&0x3f)
#define HBPD_320240		((6-1)&0x7f)
#define HFPD_320240		((6-1)&0xff)
#define HSPW_320240		((19-1)&0xff)

//Timing parameter for V16C6448AB(PRIME VIEW) 
#define VBPD_640480			((33-1)&0xff)
#define VFPD_640480			((10-1)&0xff)
#define VSPW_640480			((2-1) &0x3f)
#define HBPD_640480			((48-1)&0x7f)
#define HFPD_640480			((16-1)&0xff)
#define HSPW_640480			((96-1)&0xff)

//Timing parameter for LP104S5-B2AP(LGPHILIPS) 
#define VBPD_800600        	((2-1)&0xff)
#define VFPD_800600			((3-1)&0xff)
#define VSPW_800600			((1-1) &0x3f)
#define HBPD_800600			((30-1)&0x7f)
#define HFPD_800600			((30-1)&0xff)
#define HSPW_800600			((12-1)&0xff)


#define CLKVAL_STN_MONO		(20) 	
    // 30hz @100Mhz(HCLK),WLH=16hclk,WDLY=16hclk,LINEBLANK=1*8hclk,VD=4 
#define CLKVAL_STN_GRAY		(10) 	
    // 60hz @100Mhz,WLH=16hclk,WDLY=16hclk,LINEBLANK=13*8hclk,VD=4 
#define CLKVAL_CSTN			(9)   
    // 90Hz @100Mhz,WLH=16hclk,WDLY=16hclk,LINEBLANK=16*8hclk,VD=8  

//#define CLKVAL_TFT_240320	(12)
#define CLKVAL_TFT_240320	(6)	//chkim 050703
// 60hz @133Mhz
// (9) 60hz @100Mhz
#define CLKVAL_TFT_320240	(6)	//chkim 050703
// 60hz @133Mhz
// (9) 60hz @100Mhz
#define CLKVAL_TFT_640480 	(1)
    //53.5hz @90Mhz
    //VSYNC,HSYNC should be inverted
    //HBPD=47VCLK,HFPD=15VCLK,HSPW=95VCLK
    //VBPD=32HSYNC,VFPD=9HSYNC,VSPW=1HSYNC
#define CLKVAL_TFT_800600 	(0)
    //85hz @90Mhz
    //71hz @76Mhz
    //VSYNC,HSYNC should be inverted
    //HBPD=29VCLK,HFPD=29VCLK,HSPW=11VCLK
    //VBPD=1HSYNC,VFPD=2HSYNC,VSPW=0HSYNC
#define LCDFRAMEBUFFER _NONCACHE_STARTADDRESS 
    // 1. The LCD frame buffer should be write-through or non-cachable.
    // 2. The total frame memory should be inside 4MB.
    // 3. To meet above 2 conditions, the frame buffer should be 
    // inside the following regions.
    // 0x31000000~0x313ffffff,
    // 0x31400000~0x317ffffff,
    // 0x31800000~0x31bffffff,
    //        .....    
    // 0x33800000~0x33bffffff                


//Mono
extern U32 (*frameBuffer1Bit)[SCR_XSIZE_STN/32];
//Gray
extern U32 (*frameBuffer2Bit)[SCR_XSIZE_STN/16];
extern U32 (*frameBuffer4Bit)[SCR_XSIZE_STN/8];
//Color STN
extern U32 (*frameBuffer8Bit)[SCR_XSIZE_CSTN/4];
extern U32 (*frameBuffer12Bit)[SCR_XSIZE_CSTN*3/8]; // The least common multiple (between 12 and 32) is 96
extern U32 (*frameBuffer16Bit)[SCR_XSIZE_CSTN/2]; // for 2440A
//TFT 240320
extern U32 (*frameBuffer8BitTft240320)[SCR_XSIZE_TFT_240320/4];
extern U32 (*frameBuffer16BitTft240320)[SCR_XSIZE_TFT_240320/2];
extern U32 (*frameBuffer24BitTft240320)[SCR_XSIZE_TFT_240320];
//TFT 320240
extern U32 (*frameBuffer8BitTft320240)[SCR_XSIZE_TFT_320240/4];
extern U32 (*frameBuffer16BitTft320240)[SCR_XSIZE_TFT_320240/2];
//TFT 640480
extern U32 (*frameBuffer1BitTft640480)[SCR_XSIZE_TFT_640480/32];
extern U32 (*frameBuffer8BitTft640480)[SCR_XSIZE_TFT_640480/4];
extern U32 (*frameBuffer16BitTft640480)[SCR_XSIZE_TFT_640480/2];
extern U32 (*frameBuffer24BitTft640480)[SCR_XSIZE_TFT_640480]; // Unpacked 24bit 
//TFT 800600
extern U32 (*frameBuffer1BitTft800600)[SCR_XSIZE_TFT_800600/32];
extern U32 (*frameBuffer8BitTft800600)[SCR_XSIZE_TFT_800600/4];
extern U32 (*frameBuffer16BitTft800600)[SCR_XSIZE_TFT_800600/2];


void Lcd_Init(int type);
void MoveViewPort(int);
void Lcd_CstnOnOff(int onoff);
void Lcd_EnvidOnOff(int onoff);
void Lcd_PowerEnable(int invpwren,int pwren);
void Lcd_MoveViewPort(int vx,int vy,int type);
void Lcd_Lpc3600Enable(void);
void Lcd_Lcc3600Enable(void);
void Lcd_TconDisable(void);



#endif /*__LCDLIB_H__*/
