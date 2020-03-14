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
 * 420 : SW_DMA (�ǽ� 8-1 : SW DMA Trigger Test )
 *
 * 421 : UART_DMA (�ǽ� 8-2 : UART1�� ���� DMA trigger Test)
 *	
 * 422 : Timer_DMA (�ǽ� 8-3 : Timer�� ���� DMA trigger Test)
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
// �������� CACHE ������ �ƴҰ�
static	unsigned long src=0x33000000;
static	unsigned long dst=0x33100000;
static	unsigned int  size = 12; /* word size */
static	unsigned long pattern;

static void DMA0_ISR(void)
{
	/* ���ͷ�Ʈ ������� ���� on DMA0 */
	rINTSUBMSK |= (0x1<<18); 
	rINTMSK1 |= (0x1<<17);
	
	/* TO DO: Pendng Clear on DMA0 */



	
	Uart_Printf("__irq ISR������  ");	
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
	
	/* TODO : ���ͷ�Ʈ ���Ϳ� DMA0_ISR �Լ� ��� */
	pISR_DMA0 = (unsigned int)DMA0_ISR;
		
	/*  ���ͷ�Ʈ ��� on DMA0 */
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
// �������� CACHE ������ �ƴҰ�
static	unsigned long src=0x33000000;
static	unsigned long dst=0x33100000;
static	unsigned int  size = 12; /* word size */
static	unsigned long pattern;

static void DMA0_ISR(void)
{
	/* ���ͷ�Ʈ ������� ���� on DMA0 */
	rINTSUBMSK |= (0x1<<18); 
	rINTMSK1 |= (0x1<<17);
	
	/* TO DO: Pendng Clear on DMA0 */



	
	Uart_Printf("__irq ISR������  ");	
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
	
	/* TO DO : ���ͷ�Ʈ ���Ϳ� DMA0_ISR �Լ� ��� */
	pISR_DMA0 = (unsigned int)DMA0_ISR;
		
	/* TO DO : ���ͷ�Ʈ ��� on DMA0 */	
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
// �������� CACHE ������ �ƴҰ�
static	unsigned long src=0x33000000;
static	unsigned long dst=0x33100000;
static	unsigned int  size = 12; /* word size */
static	unsigned long pattern;

static void DMA0_ISR(void)
{
	/* ���ͷ�Ʈ ������� ���� on DMA0 */
	rINTSUBMSK |= (0x1<<18); 
	rINTMSK1 |= (0x1<<17);
	
	/* TO DO: Pendng Clear on DMA0 */
	rSUBSRCPND |= 0x1<<18;
	rSRCPND1 |= 0x1<<17;
	rINTPND1 |= 0x1<<17;
	
	Uart_Printf("__irq ISR������  ");	
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
	
	/* TODO : ���ͷ�Ʈ ���Ϳ� DMA0_ISR �Լ� ��� */
	pISR_DMA0 = (unsigned int)DMA0_ISR;
		
	/* TO DO : ���ͷ�Ʈ ��� on DMA0 */	
	rINTSUBMSK &= ~(0x1<<18);	
	rINTMSK1 &= ~(0x1<<17);
	
	DMA0_HW_Start();	
	Timer_Delay(1000);	

}
#endif
