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
#include "libc.h"
#include "option.h"


#define EXAMPLE 420
/*	
 * 420 : SW_DMA (실습 8-1 : SW DMA Trigger Test )
 *
 * 421 : UART_DMA (실습 8-2 : UART1에 의한 DMA trigger Test)
 *	
 * 422 : Timer_DMA (실습 8-3 : Timer에 의한 DMA trigger Test)
 * 
 * 
 * Advanced Course
 * 1. make macro function 
 */
 
 /***************************************
 * 
 * Title: SW_DMA
 * 
 ***************************************/

#if EXAMPLE == 420

//** ISR Function declaration 
static void DMA0_ISR(void) __attribute__ ((interrupt ("IRQ")));
// Global Variables Declaration
// 목적지는 CACHE 영역이 아닐것
static	unsigned long src=0x33000000;
static	unsigned long dst=0x33100000;
static	unsigned int  size = 12; /* word size */
static	unsigned long pattern;

static void DMA0_ISR(void)
{
	/* 인터럽트 허용하지 않음 on DMA0 */
	rINTSUBMSK |= (0x1<<18); 
	rINTMSK1 |= (0x1<<17);
	
	/* TO DO: Pendng Clear on DMA0 */



	
	Uart_Printf("__irq ISR실행결과  ");	
	MemDump(dst, 12); 	
	
	/*  TO DO: Stop DMA0 trigger  */

	
	/* Masking Disable on DMA0 */
	rINTSUBMSK &= ~(0x1<<18);
	rINTMSK1 &= ~(0x1<<17);
	
}

void Main(void)
{	
	char value;

	Uart_Init(115200);	
	DMA0_SW_Init();

	Uart_Send_Byte('\n');
	Uart_Send_Byte('A');	
	Uart_Send_String("Hello Uart Test...!!!\n");
	
	/* TODO : 인터럽트 벡터에 DMA0_ISR 함수 등록 */
	pISR_DMA0 = (unsigned int)DMA0_ISR;
		
	/*  인터럽트 허용 on DMA0 */
	rINTSUBMSK &= ~(0x1<<18);	
	rINTMSK1 &= ~(0x1<<17);
	
	DMA0_SW_Start();
	
}
# endif
 

/***************************************
 * 
 * Title: UART_DMA
 * 
 ***************************************/

#if EXAMPLE == 421


//** ISR Function declaration 
static void DMA0_ISR(void) __attribute__ ((interrupt ("IRQ")));;
// Global Variables Declaration
// 목적지는 CACHE 영역이 아닐것
static	unsigned long src=0x33000000;
static	unsigned long dst=0x33100000;
static	unsigned int  size = 12; /* word size */
static	unsigned long pattern;

static void DMA0_ISR(void)
{
	/* 인터럽트 허용하지 않음 on DMA0 */
	rINTSUBMSK |= (0x1<<18); 
	rINTMSK1 |= (0x1<<17);
	
	/* TO DO: Pendng Clear on DMA0 */



	
	Uart_Printf("__irq ISR실행결과  ");	
	MemDump(dst, 12); 	
	
	/*  TO DO: Stop DMA0 trigger  */

	
	/* Masking Disable on DMA0 */
	rINTSUBMSK &= ~(0x1<<18);
	rINTMSK1 &= ~(0x1<<17);
}

void Main(void)
{	
	char value;

	Uart_DMA_Init(115200);	
	DMA0_UART_Init();

	Uart_Send_Byte('\n');
	Uart_Send_Byte('A');	
	Uart_Send_String("Hello Uart Test...!!!\n");
	
	/* TO DO : 인터럽트 벡터에 DMA0_ISR 함수 등록 */
	pISR_DMA0 = (unsigned int)DMA0_ISR;
		
	/* TO DO : 인터럽트 허용 on DMA0 */	
	rINTSUBMSK &= ~(0x1<<18);
	rINTMSK1 &= ~(0x1<<17);
	
	DMA0_HW_Start();
	
	while(1){
		Uart_Printf("Input Value = : ");	
		value = Uart_Get_Char();
		Uart_Printf("value=%c \n", value);								
	}
}
# endif

 /***************************************
 * 
 * Title: Timer_DMA
 * 
 ***************************************/

#if EXAMPLE == 422
//** ISR Function declaration 
static void DMA0_ISR(void) __attribute__ ((interrupt ("IRQ")));;
// Global Variables Declaration
// 목적지는 CACHE 영역이 아닐것
static	unsigned long src=0x33000000;
static	unsigned long dst=0x33100000;
static	unsigned int  size = 12; /* word size */
static	unsigned long pattern;

static void DMA0_ISR(void)
{
	/* 인터럽트 허용하지 않음 on DMA0 */
	rINTSUBMSK |= (0x1<<18); 
	rINTMSK1 |= (0x1<<17);
	
	/* TO DO: Pendng Clear on DMA0 */
	rSUBSRCPND |= 0x1<<18;
	rSRCPND1 |= 0x1<<17;
	rINTPND1 |= 0x1<<17;
	
	Uart_Printf("__irq ISR실행결과  ");	
	MemDump(dst, 12); 	
	
	/*  TO DO: Stop DMA0 trigger  */
	rDMASKTRIG0 |= 0x1<<2;
	
	/* Masking Disable on DMA0 */
	rINTSUBMSK &= ~(0x1<<18);
	rINTMSK1 &= ~(0x1<<17);
	
}

void Main(void)
{	
	char value;

	Uart_Init(115200);	
	DMA0_Timer_Init();
	
	Timer_DMA_Init();

	Uart_Send_Byte('\n');
	Uart_Send_Byte('A');	
	Uart_Send_String("Hello Uart Test...!!!\n");
	
	/* TODO : 인터럽트 벡터에 DMA0_ISR 함수 등록 */
	pISR_DMA0 = (unsigned int)DMA0_ISR;
		
	/* TO DO : 인터럽트 허용 on DMA0 */	
	rINTSUBMSK &= ~(0x1<<18);	
	rINTMSK1 &= ~(0x1<<17);
	
	DMA0_HW_Start();	
	Timer_Delay(1000);	

}
#endif
