//===================================================================
// File Name : 2440lib.c
// Function  : S3C2410 PLL,Uart, LED, Port Init
// Date      : March 20, 2002
// Version   : 0.0
// History
//   0.0 : Programming start (February 20,2002) -> SOP
//===================================================================

#include "def.h"
#include "option.h"
#include "2440addr.h"
#include "2440lib.h"
#include "2440slib.h" 

#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#define PreScaler  (PCLK/1000000-1)

extern char Image$$RW$$Limit[];
void *mallocPt=Image$$RW$$Limit;

//***************************[ SYSTEM ]***************************************************
//static int delayLoopCount = 400;

void Delay(int time)
{
    
    int i;
    for(i=0; i<time; i++);

}

//***************************[ PORTS ]****************************************************
void Port_Init(void)
{
	// ---------------------------------------------------------------------------
    // ---------------------------------------------------------------------------
    //	CAUTION : Follow the configuration order for setting the ports. 
    //	1) setting value(GPnDAT) 
    //	2) setting control register  (GPnCON)
    //	3) configure pull-up resistor(GPnUP)  
	// ---------------------------------------------------------------------------
    

	//	-----------------------------------------------------------------------------
	//	-----------------------------------------------------------------------------
    //	[ PORT A GROUP ]
	//	32bit data bus configuration  
    //	#define	rGPACON    (*(volatile unsigned *)0x56000000) 	//	Port A control
    // 	rGPACON = 0x7fffff (초기값); 
   	//	-----------------------------------------------------------------------------
    //	Ports  :			GPA22 	GPA21  		GPA20 		GPA19 	GPA18 	GPA17 	GPA16 
    //	Signal :			nFCE 	nRSTOUT	nFRE   		nFWE  	ALE   	CLE  		nGCS5  
    //	Binary :				1			1				1, 			1		   	1   		1    		1   ,  
	//	-----------------------------------------------------------------------------
	//	Ports  : GPA15 	GPA14 	GPA13 	GPA12  		GPA11		GPA10  		GPA9   		GPA8
	//	Signal : nGCS4 	nGCS3 	nGCS2 	nGCS1		ADDR26		ADDR25 	ADDR24 	ADDR23
	//	Binary : 1     		1     		1     		1,				1				1      			1      			1   ,
	//	-----------------------------------------------------------------------------	
    //	Ports  : GPA7		GPA6		GPA5		GPA4			GPA3			GPA2			GPA1			GPA0
    //	Signal : ADDR22	ADDR21 ADDR20 ADDR19		ADDR18		ADDR17		ADDR16		ADDR0 
    //	Binary : 1			1			1			1,  			1				1     			1				1    
   	//	-----------------------------------------------------------------------------
  
	 //	GPA 포트에 모든핀들을 기능 핀으로 설정
    rGPACON = 0x7fffff; 



	//	-----------------------------------------------------------------------------	
	//	-----------------------------------------------------------------------------
    //	[ PORT B GROUP ]
    //	#define rGPBCON    (*(volatile unsigned *)0x56000010) 	//	Port B control
    //	rGPBCON = 0x00 (초기값)
    //	#define	rGPBUP     (*(volatile unsigned *)0x56000018) 	//	Pull-up control B
    //	rGPBUP = 0x00 (초기값)
    //	-----------------------------------------------------------------------------
    //	Ports  : GPB10		GPB9    	GPB8		GPB7		GPB6     
    //	Signal : nXDREQ0	nXDACK0 	nXDREQ1	nXDACK1	nSS_KBD  
    //	Setting: INPUT			OUTPUT   	INPUT  		OUTPUT		INPUT     
    //	Binary : 00  ,			01       		00  ,			01				00   ,     
    //	-----------------------------------------------------------------------------
    //	Ports  : GPB5			GPB4   		GPB3   		GPB2		GPB1      		GPB0
    //	Signal : nDIS_OFF	L3CLOCK 	L3DATA 		L3MODE	nIrDATXDEN 	Keyboard
    //	Setting: OUTPUT		OUTPUT 	OUTPUT 	OUTPUT		OUTPUT    		OUTPUT
    //	Binary : 01				01  ,   		01    			01   ,			01        			01
	//	-----------------------------------------------------------------------------
	
    rGPBCON = 0x044555;
    rGPBUP  = 0x7ff;     						// The pull up function is disabled GPB[10:0]




    //	-----------------------------------------------------------------------------
	//	-----------------------------------------------------------------------------
    //	[ PORT C GROUP ]
    //	#define rGPCCON    (*(volatile unsigned *)0x56000020) 		//	Port C control
    //	rGPCCON = 0x00 (초기값)
    //	#define rGPCUP     (*(volatile unsigned *)0x56000028) 			//	Pull-up control C
    //	rGPCUP = 0x00 (초기값)
    //	-----------------------------------------------------------------------------
    //	Ports  : GPC15	GPC14 	GPC13 	GPC12 	GPC11 	GPC10 	GPC9 	GPC8 
    //	Signal : VD7   		VD6   	VD5   	VD4   	VD3   	VD2   	VD1		VD0  
    //	Binary : 10   		10  , 		10    		10  , 		10    		10  , 		10   		10  , 
    //	-----------------------------------------------------------------------------
    //	Ports  : GPC7		GPC6   	GPC5 	GPC4 	GPC3  	GPC2  	GPC1 	GPC0
    //	Signal : LCDVF2	LCDVF1 	LCDVF0 	VM 		VFRAME VLINE 	VCLK 		LEND
    //	Binary : 10			10  ,  	10   		10 , 		10     	10 , 		10   		10 
    //	-----------------------------------------------------------------------------
    
    //	LCD Device를 제어하기 위한 기능 핀 설정, GPC 포트를 기능 핀으로 설정
    rGPCCON = 0xaaaaaaaa;       
    rGPCUP  = 0xffff;								// The pull up function is disabled GPC[15:0] 




    //	-----------------------------------------------------------------------------
	//	-----------------------------------------------------------------------------
    //	[ PORT D GROUP ]
    //	#define rGPDCON    (*(volatile unsigned *)0x56000030) 	//	Port D control
    //	rGPDCON = 0x00 (초기값)
    //	#define rGPDUP     (*(volatile unsigned *)0x56000038) 	//	Pull-up control D
    //	rGPDUP = 0xF000 (초기값)
    //	-----------------------------------------------------------------------------
    //	Ports  : GPD15	GPD14 	GPD13 	GPD12 	GPD11 	GPD10 	GPD9 	GPD8 
    //	Signal : VD23  	VD22  	VD21  	VD20  	VD19  	VD18  	VD17 	VD16 
    //	Binary : 10    		10  , 		10    		10  , 		10    		10  , 		10   		10 , 
    //	-----------------------------------------------------------------------------
    //	Ports  : GPD7 		GPD6 	GPD5 	GPD4 	GPD3 	GPD2 	GPD1 	GPD0
    //	Signal : VD15 		VD14 	VD13 	VD12 	VD11 	VD10 	VD9  		VD8
    //	Binary : 10   		10 , 		10   		10 , 		10   		10 ,		10   		10
    //	-----------------------------------------------------------------------------
    
    //	LCD Device를 제어하기 위한 기능 핀 설정, GPD 포트를 기능 핀으로 설정
    rGPDCON = 0xaaaaaaaa;       
    rGPDUP  = 0xffff;     	// The pull up function is disabled GPD[15:0]





    //	-----------------------------------------------------------------------------
	//	-----------------------------------------------------------------------------
    // 	[ PORT E GROUP ]
    //	#define rGPECON    (*(volatile unsigned *)0x56000040) 	//	Port E control
    //	rGPECON = 0x00 (초기값)
    //	#define rGPEUP     (*(volatile unsigned *)0x56000048) 	//	Pull-up control E
    //	rGPEUP = 0x00 (초기값)
    //	-----------------------------------------------------------------------------
    // 	Ports  :	GPE15   GPE14  GPE13   GPE12		GPE11    GPE10		GPE9			GPE8		
    // 	Signal :	IICSDA	IICSCL	SPICLK  SPIMOSI		SPIMISO  SDDATA3  SDDATA2  SDDATA1 	
    // 	Binary :  10			10  ,		10			10  ,			10			  10   ,		10				10   ,   
    //	-----------------------------------------------------------------------------
    //	Ports  : GPE7  	 GPE6  	GPE5   	GPE4  	GPE3   	 GPE2  	 GPE1    	GPE0    
    //	Signal : SDDATA0 SDCMD SDCLK 	I2SSDO 	I2SSDI 	 CDCLK 	 I2SSCLK 	I2SLRCK     
    //	Binary : 10    		10  , 		10     	10  ,  	10     	 10  ,		10      		10 
    //	-----------------------------------------------------------------------------
    
    rGPECON = 0xaaaaaaaa;       
    rGPEUP  = 0xffff;     	//  The pull up function is disabled GPE[15:0]

	


    //	-----------------------------------------------------------------------------
	//	-----------------------------------------------------------------------------
    //	[ PORT F GROUP ]
    //	#define rGPFCON    (*(volatile unsigned *)0x56000050) 	//	Port F control
    //	rGPFCON = 0x00 (초기값)
    //	#define rGPFUP     (*(volatile unsigned *)0x56000058) 	//	Pull-up control F
    //	rGPFUP = 0x00 (초기값)
    //	-----------------------------------------------------------------------------
    //	Ports  : GPF7		GPF6   	GPF5   	GPF4  	GPF3     		GPF2  	GPF1   	GPF0
    //	Signal : nLED_8	nLED_4 	nLED_2 	nLED_1 	nIRQ_PCMCIA EINT2 	KBDINT 	EINT0
    //	EINT   : EINT7		EINT6		EINT5		EINT4		EINT3				EINT2		EINT1		EINT0
    //	Setting: Output		Output 	Output 	Output 	EINT3    			EINT2 	EINT1  	EINT0    
    //	Binary : 01			01 ,		01     	01  ,  	10       			10  , 		10     	10
    //	-----------------------------------------------------------------------------
    
    rGPFCON = 0x55aa;
    rGPFUP  = 0xff;     	// 	The pull up function is disabled GPF[7:0]




	//	-----------------------------------------------------------------------------
	//	-----------------------------------------------------------------------------
    //	[  PORT G GROUP ]
	//	#define rGPGCON    (*(volatile unsigned *)0x56000060) 	//	Port G control
	//	rGPGCON = 0x00 (초기값)
	//	#define rGPGUP     (*(volatile unsigned *)0x56000068) 	//	Pull-up control G
	//	rGPGUP = 0x00 (초기값)
    //	-----------------------------------------------------------------------------
    //	Ports  : GPG15 	GPG14 	GPG13 	GPG12 	GPG11   GPG10    		GPG9  			  
    //	Signal : nYPON	YMON 	nXPON 	XMON  	EINT19 	DMAMODE1 	DMAMODE0 	
    //	Setting: nYPON	YMON 	nXPON 	XMON  	EINT19  Output   			Output  			
    //	Binary : 11    		11 , 		11    		11  , 		10			01    ,			01      			
    //	-----------------------------------------------------------------------------
	//  Ports  : GPG8         GPG7			GPG6    		GPG5			GPG4     		GPG3
	//  Signal : DMASTART	KBDSPICLK KBDSPIMOSI	KBDSPIMISO	LCD_PWREN  EINT11
	//  Setting: Output		SPICLK1		SPIMOSI1		SPIMISO1		LCD_PWRDN  EINT11
	//  Binary : 01   ,			11				11     			11					11   ,  			10	
	//	-----------------------------------------------------------------------------
    //	Ports  :  GPG2		GPG1		GPG0    
    //	Signal : 	nSS_SPI		IRQ_LAN	IRQ_PCMCIA
    //	Setting: 	nSS0			EINT9			EINT8
    //	Binary : 	11  ,			10				10
    //	-----------------------------------------------------------------------------
    
    rGPGCON = 0xff95ffba;
    rGPGUP  = 0xffff;    	// 	The pull up function is disabled GPG[15:0]




	//	-----------------------------------------------------------------------------
	//	-----------------------------------------------------------------------------
   	//	[ PORT H GROUP ]
   	//	#define rGPHCON    (*(volatile unsigned *)0x56000070) 	//	Port H control
   	//	rGPHCON = 0x00 (초기값)
   	//	#define rGPHUP     (*(volatile unsigned *)0x56000078) 	//	Pull-up control H
   	//	rGPHUP = 0x00 (초기값)
   	//	-----------------------------------------------------------------------------
    //	Ports  : GPH10		GPH9  		GPH8		GPH7		GPH6		GPH5		GPH4		 
    //	Signal : CLKOUT1	CLKOUT0	UCLK		nCTS1	nRTS1	RXD1		TXD1		
    //	Binary : 10   ,			10				10 ,		11			11  ,		10			10 ,		
    //	-----------------------------------------------------------------------------
    //	Ports  : 	GPH3			GPH2			GPH1		GPH0 
    //	Signal :	RXD0			TXD0			nRTS0	nCTS0
    //	Binary :	10				10 ,			10			10
    //	-----------------------------------------------------------------------------
    
    rGPHCON = 0x2afaaa;
    rGPHUP  = 0x7ff;    	//	The pull up function is disabled GPH[10:0]






	//	-----------------------------------------------------------------------------
	//	-----------------------------------------------------------------------------
	//	Added for S3C2440X, DonGo
	//	[ PORT J GROUP ]
   	//	#define rGPJCON    (*(volatile unsigned *)0x560000d0) 	//	Port H control
   	//	rGPHCON = 0x00 (초기값)
   	//	#define rGPJUP     (*(volatile unsigned *)0x560000d8) 	//	Pull-up control H
   	//	rGPHUP = 0x00 (초기값)
	//	-----------------------------------------------------------------------------
	//	Ports	:		GPJ12			GPJ11			 GPJ10		GPJ9		GPJ8				
	//	Signal :		CAMRESET		CAMCLKOUT	CAMHREF	CAMVS	CAMPCLKIN		
	//	Setting:		Out				Out				CAMHREF	CAMVS	CAMPCLKIN		
	//	Binary :		01					01					10				10			10					
	//	PU_OFF :	1					0 					1				1			1					
	//---------------------------------------------------------------------------------------
	//	Ports	:		GPJ7		GPJ6		GPJ5		GPJ4		GPJ3		GPJ2		GPJ1		 GPJ0
	//	Signal :		CAMD7	CAMD6	CAMD5	CAMD4	CAMD3	CAMD2	CAMD1	CAMD0
	//	Setting:		CAMD7	CAMD6	CAMD5	CAMD4	CAMD3	CAMD2	CAMD1	CAMD0
	//	Binary :		10			10			10			10			10			10			10			10
	//	PU_OFF :	1			1			1			1			1			1			1			1
	//---------------------------------------------------------------------------------------

	rGPJDAT = (1<<12)|(0<<11);
	rGPJCON = 0x016aaaa;
	rGPJUP	= ~((0<<12)|(1<<11));

	rGPJDAT = (0<<12)|(0<<11);
	rGPJCON = 0x016aaaa;
	rGPJUP	= 0x1fff;			//~((1<<12)|(1<<11));

	
	//	rGPJCON = 0x02aaaaaa;
	//	rGPJUP  = 0x1fff;    // The pull up function is disabled GPH[10:0]




	//	-----------------------------------------------------------------------------
	//	-----------------------------------------------------------------------------
    //	External interrupt will be falling edge triggered. 
    //	#define rEXTINT0   (*(volatile unsigned *)0x56000088) 	//	External interrupt control register 0
	//	#define rEXTINT1   (*(volatile unsigned *)0x5600008c) 	//	External interrupt control register 1
	//	#define rEXTINT2   (*(volatile unsigned *)0x56000090) 	//	External interrupt control register 2
	//	-----------------------------------------------------------------------------
	//	0x010 : Falling Edge Triggered
    //	External interrupt will be falling edge triggered. 
    rEXTINT0 = 0x22222222;    // EINT[7:0]
    rEXTINT1 = 0x22222222;    // EINT[15:8]
    rEXTINT2 = 0x22222222;    // EINT[23:16]
}

//***************************[ UART ]******************************
static int whichUart=1;

void Uart_Init(int pclk,int baud)
{
    #define Baudrate (PCLK/16./115200+0.5) 

    int i;
    if(pclk == 0)
    pclk    = PCLK;
    rUFCON0 = 0x0;   //UART channel 0 FIFO control register, FIFO disable
    rUFCON1 = 0x0;   //UART channel 1 FIFO control register, FIFO disable
    rUFCON2 = 0x0;   //UART channel 2 FIFO control register, FIFO disable
    rUMCON0 = 0x0;   //UART chaneel 0 MODEM control register, AFC disable
    rUMCON1 = 0x0;   //UART chaneel 1 MODEM control register, AFC disable
//UART0
    rULCON0 = 0x3;   //Line control register : Normal,No parity,1 stop,8 bits
     //    [10]       [9]     [8]        [7]        [6]      [5]         [4]           [3:2]        [1:0]
     // Clock Sel,  Tx Int,  Rx Int, Rx Time Out, Rx err, Loop-back, Send break,  Transmit Mode, Receive Mode
     //     0          1       0    ,     0          1        0           0     ,       01          01
     //   PCLK       Level    Pulse    Disable    Generate  Normal      Normal        Interrupt or Polling
    rUCON0  = 0x245;   // Control register
    rUBRDIV0=( (int)(Baudrate) -1 );   //Baud rate divisior register 0
//UART1

    rULCON1 = 0x3;
    rUCON1  = 0x245;
    rUBRDIV1=( (int)(Baudrate) -1 );
	//rUBRDIV1=( (int)(pclk/16./baud+0.5) -1 );
//UART2
    rULCON2 = 0x3;
    rUCON2  = 0x245;
    rUBRDIV2=( (int)(Baudrate) -1 );
	//rUBRDIV2=( (int)(pclk/16./baud+0.5) -1 );    

    for(i=0;i<100;i++);
}

//===================================================================
void Uart_Select(int ch)
{
    whichUart = ch;
}


//===================================================================
void Uart_TxEmpty(int ch)
{
    if(ch==0)
        while(!(rUTRSTAT0 & 0x4)); //Wait until tx shifter is empty.
          
    else if(ch==1)
        while(!(rUTRSTAT1 & 0x4)); //Wait until tx shifter is empty.
        
    else if(ch==2)
        while(!(rUTRSTAT2 & 0x4)); //Wait until tx shifter is empty.
}

//=====================================================================
char Uart_Getch(void)
{
    if(whichUart==0)
    {       
        while(!(rUTRSTAT0 & 0x1)); //Receive data ready
        return RdURXH0();
    }
    else if(whichUart==1)
    {       
        while(!(rUTRSTAT1 & 0x1)); //Receive data ready
        return RdURXH1();
    }
    else if(whichUart==2)
    {
        while(!(rUTRSTAT2 & 0x1)); //Receive data ready
        return RdURXH2();
    }
}

//====================================================================
char Uart_GetKey(void)
{
    if(whichUart==0)
    {       
        if(rUTRSTAT0 & 0x1)    //Receive data ready
            return RdURXH0();
        else
            return 0;
    }
    else if(whichUart==1)
    {
        if(rUTRSTAT1 & 0x1)    //Receive data ready
            return RdURXH1();
        else
            return 0;
    }
    else if(whichUart==2)
    {       
        if(rUTRSTAT2 & 0x1)    //Receive data ready
            return RdURXH2();
        else
            return 0;
    }    
}


//=====================================================================
void Uart_SendByte(int data)
{
    if(whichUart==0)
    {
        if(data=='\n')
        {
            while(!(rUTRSTAT0 & 0x2));
            Delay(10);                 //because the slow response of hyper_terminal 
            WrUTXH0('\r');
        }
        while(!(rUTRSTAT0 & 0x2));   //Wait until THR is empty.
        Delay(10);
        WrUTXH0(data);
    }
    else if(whichUart==1)
    {
        if(data=='\n')
        {
            while(!(rUTRSTAT1 & 0x2));
            Delay(10);                 //because the slow response of hyper_terminal 
            rUTXH1 = '\r';
        }
        while(!(rUTRSTAT1 & 0x2));   //Wait until THR is empty.
        Delay(10);
        rUTXH1 = data;
    }   
    else if(whichUart==2)
    {
        if(data=='\n')
        {
            while(!(rUTRSTAT2 & 0x2));
            Delay(10);                 //because the slow response of hyper_terminal 
            rUTXH2 = '\r';
        }
        while(!(rUTRSTAT2 & 0x2));   //Wait until THR is empty.
        Delay(10);
        rUTXH2 = data;
    }       
}               

//====================================================================
void Uart_SendString(char *pt)
{
    while(*pt)
        Uart_SendByte(*pt++);
}

//====================================================================
void Uart_GetString(char *string)
{
    char *string2 = string;
    char c;
    while((c = Uart_Getch())!='\r')
    {
        if(c=='\b')
        {
            if( (int)string2 < (int)string )
            {
                Uart_Printf("\b \b");
                string--;
            }
        }
        else 
        {
            *string++ = c;
            Uart_SendByte(c);
        }
    }
    *string='\0';
    Uart_SendByte('\n');
}

//=====================================================================
int Uart_GetIntNum(void)
{
    char str[30];
    char *string = str;
    int base     = 10;
    int minus    = 0;
    int result   = 0;
    int lastIndex;    
    int i;
    
    Uart_GetString(string);
    
    if(string[0]=='-')
    {
        minus = 1;
        string++;
    }
    
    if(string[0]=='0' && (string[1]=='x' || string[1]=='X'))
    {
        base    = 16;
        string += 2;
    }
    
    lastIndex = strlen(string) - 1;
    
    if(lastIndex<0)
        return -1;
    
    if(string[lastIndex]=='h' || string[lastIndex]=='H' )
    {
        base = 16;
        string[lastIndex] = 0;
        lastIndex--;
    }

    if(base==10)
    {
        result = atoi(string);
        result = minus ? (-1*result):result;
    }
    else
    {
        for(i=0;i<=lastIndex;i++)
        {
            if(isalpha(string[i]))
            {
                if(isupper(string[i]))
                    result = (result<<4) + string[i] - 'A' + 10;
                else
                    result = (result<<4) + string[i] - 'a' + 10;
            }
            else
                result = (result<<4) + string[i] - '0';
        }
        result = minus ? (-1*result):result;
    }
    return result;
}


//=====================================================================
//If you don't use vsprintf(), the code size is reduced very much.

void Uart_Printf(char *fmt,...)
{
    va_list ap;
    char string[256];

    va_start(ap,fmt);
    vsprintf(string,fmt,ap);
    Uart_SendString(string);
    va_end(ap);
}


//**************************[ BOARD LED ]*********************************
void Led_Display(int data)
{
	//	Active is low.(LED On)
    //	GPF7		GPF6		GPF5		 GPF4
    //	nLED_8	nLED4	nLED_2	nLED_1
	//	rGPFDAT = (rGPFDAT & 0xf) | !((data & 0xf)<<4);
    rGPFDAT = (rGPFDAT & ~(0xf<<4)) | ((~data & 0xf)<<4);    

	//	data : 6
	//	rGPFDAT = (rGPFDAT & 0xFFFFFF0F) | (0x90) => 0xFFFFFF9F

	//	data : 9
	//	rGPFDAT = (rGPFDAT & 0xFFFFFF0F) | (0x60) => 0xFFFFFF6F
}





//*************************[ MPLL ]*******************************
//	-----------------------------------------------------------------------------
//
//		ChangeMPllValue(118,2,2);    		// FCLK=266.72MHz	
//		ChangeMPllValue(60,4,1);				// FCLK=95.96MHz
//	
//	#define rMPLLCON    (*(volatile unsigned *)0x4c000004)	//MPLL Control
//
//	[PLLCON]		[Bit]				[Description]						[Initial State]
//	MDIV				[19:12]			Main divider control				0x96 / 0x4d
//	PDIV				[09:04]			Pre-divider control				0x03 / 0x03
//	SDIV				[01:00]			Post divider control				0x0 / 0x0
//
//	Input Frequency		Output Frequency			MDIV				PDIV		SDIV
//	12.0000MHz			048.00 MHz (Note)		56(0X38)		2			2
//	12.0000MHz			096.00 MHz (Note)		56(0x38)		2			1
//	12.0000MHz			271.50 MHz				173(0xad)		2			2
//	12.0000MHz			304.00 MHz				68(0x44)		1			1
//	12.0000MHz			405.00 MHz				127(0x7f)		2			1
//	12.0000MHz			532.00 MHz				125(0x7d)		1			1
//	16.9344MHz			047.98 MHz (Note)		60(0x3c)		4			2
//	16.9344MHz			095.96 MHz (Note)		60(0x3c)		4			1
//	16.9344MHz			266.72 MHZ				118(0x76)		2			2
//	16.9344MHz			296.35 MHZ				97(0x61)		1			2
//	16.9344MHz			399.65 MHz				110(0x6e)		3			1
//	16.9344MHz			530.61 MHz				86(0x56)		1			1
//	16.9344MHz			533.43 MHz				118(0x76)		1			1
//	[NOTE]	The 48.00MHz and 96MHz output is used for UPLLCON register.
//	-----------------------------------------------------------------------------
void ChangeMPllValue(int mdiv,int pdiv,int sdiv)
{
    rMPLLCON = (mdiv<<12) | (pdiv<<4) | sdiv;
}







// Modified for 2440.
//************************[ HCLK, PCLK ]***************************
//	-----------------------------------------------------------------------------
//	Change clock frequency ratio  FCLK : HCLK : PCLK
//
//			Change clock frequency ratio as 1:4:8	
//			ChangeClockDivider(2,1);			// 1:4:8    
//
//	#define rCLKDIVN    (*(volatile unsigned *)0x4c000014)		//	Clock divider control
//
//	[CLKDIVN]		[Bit]					[Description]
//	DIVN_UPL		[03]			UCLK select register (UCLK must be 48MHz for USB)
//										0 : UCLK = UPLL clock			
//												=> Set to 0, when UPLL clock is set as 48MHz
//										1 : UCLK = UPLL clock /2
//												=> Set to 1, when UPLL clock is set as 96MHz
//	HDIVN			[02:01]		00 :	HCLK = FCLK/1
//										01 :	HCLK = FCLK/2
//										10 :	HCLK = FCLK/4  when CAMDIVN[9] = 0
//												HCLK = FCLK/8  when CAMDIVN[9] = 1
//										11 :	HCLK = FCLK/3  when CAMDIVN[8] = 0
//												HCLK = FCLK/6  when CAMDIVN[8] = 1
//	PDIVN			[00]			0 :		PCLK has the clock same as the HCLK/1
//										1 :		PCLK has the clock same as the HCLK/2
//	-----------------------------------------------------------------------------

/*
// for 2410.
void ChangeClockDivider(int hdivn,int pdivn)
{
     // hdivn,pdivn FCLK:HCLK:PCLK
     //     0,0         1:1:1 
     //     0,1         1:1:2 
     //     1,0         1:2:2
     //     1,1         1:2:4
    rCLKDIVN = (hdivn<<1) | pdivn;    

    if(hdivn)
        MMU_SetAsyncBusMode();
    else 
        MMU_SetFastBusMode();
}
*/
void ChangeClockDivider(int hdivn_val,int pdivn_val)
{
	int hdivn=2, pdivn=0;
	
     // hdivn_val (FCLK:HCLK)ratio hdivn
     // 11           1:1       (0)
     // 12           1:2       (1)
     // 13           1:3       (3) 
     // 14           1:4       (2)
     // pdivn_val (HCLK:PCLK)ratio pdivn
     // 11           1:1       (0)
     // 12           1:2       (1)
	switch(hdivn_val) {
		case 11: hdivn=0; break;
		case 12: hdivn=1; break;
		case 13: hdivn=3; break;
		case 14: hdivn=2; break;
	}
	
	switch(pdivn_val) {
		case 11: pdivn=0; break;
		case 12: pdivn=1; break;
	}
	
	//	Uart_Printf("Clock division change [hdiv:%x, pdiv:%x]\n", hdivn, pdivn);
    rCLKDIVN = (hdivn<<1) | pdivn;
	//	 rCLKDIVN = (hdivn_val<<1) | pdivn_val

    if(hdivn!=0)
        MMU_SetAsyncBusMode();
	/* else 
		MMU_SetFastBusMode();
	*/
}







//**************************[ UPLL ]*******************************
void ChangeUPllValue(int mdiv,int pdiv,int sdiv)
{
    rUPLLCON = (mdiv<<12) | (pdiv<<4) | sdiv;
}




void Max1718_Set(int voltage)
{

     int vtg;
	//////////////////////////////////////////////
	 //   D4  D3  D2  D1  D0
	 //	0	1	 0 	0	0		// 1.35V
	 //	0	1	 0 	0	1		// 1.30V
	 //	0	1	 0 	1	0		// 1.25V
	 //	0	1	 0 	1	1		// 1.20V
	 //	0	1	 1 	0	0		// 1.15V
	 //	0	1	 1 	0	1		// 1.10V
	 //	0	1	 1 	1	0		// 1.05V
	 //	0	1	 1 	1	1		// 1.00V
	 //	1	0	 0 	0	1		// 0.95V
	 //	1	0	 0 	1	1		// 0.90V
	 //	1	0	 1 	0	1		// 0.85V
	 //	1	0	 1 	1	1		// 0.80V
	 
    vtg=voltage;
     switch (vtg)
	{
	/*
	case 135:
		rGPBDAT=(rGPBDAT&0x77f)|(0<<7);	//D4
		rGPFDAT=(rGPFDAT&0x0f)|(1<<7)|(0<<6)|(0<<5)|(0<<4);	//D3~0
	break;
	
	
	case 125:
		rGPBDAT=(rGPBDAT&0x77f)|(0<<7);    //D4
		rGPFDAT=(rGPFDAT&0x0f)|(1<<7)|(0<<6)|(1<<5)|(0<<4); //D3~0
	break;*/
	
	case 130:
		rGPBDAT=(rGPBDAT&0x77f)|(0<<7);	//D4
		rGPFDAT=(rGPFDAT&0x0f)|(1<<7)|(0<<6)|(0<<5)|(1<<4); //D3~0
		break;
		
	case 120:
		rGPBDAT=(rGPBDAT&0x77f)|(0<<7);	//D4
		rGPFDAT=(rGPFDAT&0x0f)|(1<<7)|(0<<6)|(1<<5)|(1<<4); //D3~0
	break;
/*
	case 115:
		rGPBDAT=(rGPBDAT&0x77f)|(0<<7);	//D4
		rGPFDAT=(rGPFDAT&0x0f)|(1<<7)|(1<<6)|(0<<5)|(0<<4); //D3~0
	break;
*/
	case 110:
		rGPBDAT=(rGPBDAT&0x77f)|(0<<7);	//D4
		rGPFDAT=(rGPFDAT&0x0f)|(1<<7)|(1<<6)|(0<<5)|(1<<4); //D3~0
	break;
/*
	case 105:
		rGPBDAT=(rGPBDAT&0x77f)|(0<<7);	//D4
		rGPFDAT=(rGPFDAT&0x0f)|(1<<7)|(1<<6)|(1<<5)|(0<<4); //D3~0
	break;

	case 100:
		rGPBDAT=(rGPBDAT&0x77f)|(0<<7);	//D4
		rGPFDAT=(rGPFDAT&0x0f)|(1<<7)|(1<<6)|(1<<5)|(1<<4); //D3~0
	break;
	*/
/*
	case 95:
		rGPBDAT=(rGPBDAT&0x77f)|(1<<7);	//D4
		rGPFDAT=(rGPFDAT&0x0f)|(0<<7)|(0<<6)|(0<<5)|(1<<4); //D3~0
	break;

	case 90:
		rGPBDAT=(rGPBDAT&0x77f)|(1<<7);	//D4
		rGPFDAT=(rGPFDAT&0x0f)|(0<<7)|(0<<6)|(1<<5)|(1<<4); //D3~0
	break;

	case 85:
		 rGPBDAT=(rGPBDAT&0x77f)|(1<<7);	//D4
		 rGPFDAT=(rGPFDAT&0x0f)|(0<<7)|(1<<6)|(0<<5)|(1<<4); //D3~0
	break;

    case 80:
		rGPBDAT=(rGPBDAT&0x77f)|(1<<7);    //D4
	   rGPFDAT=(rGPFDAT&0x0f)|(0<<7)|(1<<6)|(1<<5)|(1<<4); //D3~0
	break;
*/
	default:	// 1.2V
		rGPBDAT=(rGPBDAT&0x77f)|(0<<7);	//D4
		rGPFDAT=(rGPFDAT&0x0f)|(1<<7)|(0<<6)|(1<<5)|(1<<4); //D3~0
	break;

		
	}
	 
	
	 rGPBCON=(rGPBCON&0x3f3fff)|(1<<14);	// GPB7: Output
	
	 rGPFCON=(rGPFCON&0x00ff)|(0x5500);  // GPF4~7: Output 
	
		  
	 rGPBDAT&=~(1<<8);   //Latch enable
	 rGPBCON=(rGPBCON&0x3cffff)|(1<<16);	// GPB8: Output
	
	 rGPBDAT|=(1<<10);   //Output enable
	 rGPBCON=(rGPBCON&0x0fffff)|(1<<20);	// GPB10: Output
		
	 rGPBDAT|=(1<<8);	//Latch disable


}
