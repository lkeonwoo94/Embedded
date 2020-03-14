/*
 * =====================================================================
 * NAME         : Main.c
 *
 * Descriptions : Main routine for S3C2440
 *
 * IDE          : CodeWarrior 2.0 or Later
 *
 * Modification
 *     Modified by MDS Tech. NT Div.(2Gr) (2007.3.1~4)
 * =====================================================================
 */
#include "2440addr.h"

#define EXAMPLE 422
/*	
 * 420 : SW_DMA (�ǽ� 8-1 : SW DMA Trigger Test )
 *
 * 421 : UART_DMA (�ǽ� 8-2 : Timer�� ���� DMA trigger Test)
 *	
 * 422 : Timer_DMA (�ǽ� 8-3 : UART0�� ���� DMA trigger Test)
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
static void __irq  DMA0_ISR(void);

// Global Variables Declaration
// �������� CACHE ������ �ƴҰ�
static	unsigned long src=0x33000000;
static	unsigned long dst=0x33100000;
static	unsigned int  size = 12; /* word size */
static	unsigned long pattern;

static void __irq  DMA0_ISR(void)
{
	/* ���ͷ�Ʈ ������� ���� on DMA1 */
	rINTMSK |= (0x1<<17);
	
	/* TO DO: Pendng Clear on DMA1 */
	rSRCPND |= 0x1<<17;
	rINTPND |= 0x1<<17;
	
	Uart_Printf("__irq ISR������  ");	
	MemDump(dst, 12); 	
	
	/*  TO DO: Stop DMA0 trigger  */
	rDMASKTRIG0 |= 0x1<<2;
	
	/* Masking Disable on DMA1 */
	rINTMSK &= ~(0x1<<17);
	
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
	rINTMSK &= ~(0x1<<17);

	DMA0_SW_Start();

	while(1);
	
}
#endif
 

/***************************************
 * 
 * Title: UART_DMA
 * 
 ***************************************/

#if EXAMPLE == 421


//** ISR Function declaration 
static void __irq  DMA0_ISR(void);
// Global Variables Declaration
// �������� CACHE ������ �ƴҰ�
static	unsigned long src=0x33000000;
static	unsigned long dst=0x33100000;
static	unsigned int  size = 12; /* word size */
static	unsigned long pattern;

static void __irq  DMA0_ISR(void)
{
	/* ���ͷ�Ʈ ������� ���� */
	rINTMSK |= (0x1<<17);
	
	/* TO DO: Pendng Clear on DMA */
	rSRCPND |= 0x1<<17;
	rINTPND |= 0x1<<17;
	
	Uart_Printf("__irq ISR������  ");	
	MemDump(dst, 12); 	
	
	/* Masking Disable on DMA1 */
	rINTMSK &= ~(0x1<<17);
	
}

void Main(void)
{	
	char value;

	Uart_DMA_Init(115200);	
	DMA0_UART_Init();

	Uart_Send_Byte('\n');
	Uart_Send_Byte('A');	
	Uart_Send_String("Hello Uart Test...!!!\n");
	
	/* TODO : ���ͷ�Ʈ ���Ϳ� DMA0_ISR �Լ� ��� */
	pISR_DMA0 = (unsigned int)DMA0_ISR;

	/*  ���ͷ�Ʈ ��� on DMA0 */		
	rINTMSK &= ~(0x1<<17);
	
	DMA0_HW_Start();

	while(1);
}
#endif

 /***************************************
 * 
 * Title: Timer_DMA
 * 
 ***************************************/

#if EXAMPLE == 422
//** ISR Function declaration 
static void __irq  DMA0_ISR(void);
// Global Variables Declaration
// �������� CACHE ������ �ƴҰ�
static	unsigned long src=0x33000000;
static	unsigned long dst=0x33100000;
static	unsigned int  size = 12; /* word size */
static	unsigned long pattern;

static void __irq  DMA0_ISR(void)
{
	/* ���ͷ�Ʈ ������� ���� on DMA0  */
	rINTMSK |= (0x1<<17);
	
	/* TO DO: Pendng Clear on DMA0 */
	rSRCPND |= 0x1<<17;
	rINTPND |= 0x1<<17;
	
	Uart_Printf("__irq ISR������  ");	
	MemDump(dst, 12); 	
		
	/* Masking Disable on DMA0  */
	rINTMSK &= ~(0x1<<17);
	
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
	rINTMSK &= ~(0x1<<17);
	
	DMA0_HW_Start();	
	Timer_Delay(1000);	

}
#endif




