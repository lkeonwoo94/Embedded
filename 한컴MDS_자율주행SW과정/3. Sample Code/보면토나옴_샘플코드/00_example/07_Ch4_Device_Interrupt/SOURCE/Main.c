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

#define EXAMPLE 412
/*	
 * 410 : 실습 7-2 : Timer_Interrupt Test
 *
 * 411 : 실습 7-1 : UART_Interrupt Test
 *	
 * 412 : 실습 7-3 : Key_Interrupt Test
 * 
 */


/***************************************
 * 
 * Title: Timer_Interrupt
 * 
 ***************************************/

#if EXAMPLE == 410

// ISR Declaration
void Timer0_ISR(void) __attribute__ ((interrupt ("IRQ")));

void Timer0_ISR()
{
	/* 해당 인터럽트 Masking */ 

	rINTMSK1 |= (1<<10);	
	/* TODO : Pending Register Clear */
	rSRCPND1 |= (1<<10);
	rINTPND1 |= (1<<10);	

	Uart_Send_String("Timer ISR\n");
	
	/* 해당 인터럽트 UnMasking */
	rINTMSK1 &= ~(1<<10);
}

void Main()
{
	Uart_Init(115200);	

	Uart_Send_Byte('\n');
	Uart_Send_Byte('A');	
	Uart_Send_String("Hello Timer Interrupt Test...!!!\n");
	
	Timer_Init();
	
	/* TODO : 인터럽트 벡터에 Timer0_ISR 함수 등록 */
	pISR_TIMER0 = (unsigned int )Timer0_ISR;

	/* Interrupt Unmasking */
	rINTMSK1 &= ~(1<<10);
	
	Timer_Delay(1000);
		
}

#endif


/***************************************
 * 
 * Title: UART_Interrupt
 * 
 ***************************************/

#if EXAMPLE == 411

static char Input_Char;

//** ISR Function declaration 
static void Uart_RX1_ISR(void) __attribute__ ((interrupt ("IRQ")));;

static void Uart_RX1_ISR(void)
{
	/* TO DO : UART1_RX 가 다시 발생하지 않도록 Masking  */
	rINTSUBMSK |=(0x1<<3);
	rINTMSK1 |=(0x1<<23);
	
	/* TO DO: Pendng Clear on UART1_RX,UART1_ERR */
 
	rSUBSRCPND |= (0x1<<3); //UART1_RX
	rSRCPND1 |=(0x1<<23);
	rINTPND1 |=(0x1<<23);
	
	/* ISRoutine Execution*/
	Uart_Send_Byte('\n');
	Uart_Send_String("Uart Receive data is OK..!!\n");
	
	#if 0
	if(Uart_Check_Overrun_Error()) 	Uart_Send_Byte('*'); Uart_Send_Byte('\n');
	#endif
	
	/* UnMasking on UART1_RX */  
	rINTSUBMSK &=~(0x1<<3);
	rINTMSK1 &=~(0x1<<23);

}

void Main(void)
{	

	Uart_Init(115200);	

	Uart_Send_Byte('\n');
	Uart_Send_Byte('A');	
	Uart_Send_String("Hello Uart Interrupt Test...!!!\n");
	
	/* TODO : 인터럽트 벡터에 Uart_RX1_ISR 함수 등록 */
	pISR_UART1 = (unsigned int)Uart_RX1_ISR;
		
	/* TO DO : 인터럽트 허용 on UART1_RX,ERR  */
	rINTSUBMSK &=~(0x1<<3);  //UART1_RX
	rINTSUBMSK &=~(0x1<<5); //UART1_ERR
	rINTMSK1 &=~(0x1<<23);
		
	for(;;)
	{
		Input_Char=Uart_Get_Char();
		Uart_Printf("Input charter is : %c \n ", Input_Char);
	}
			
			
}

#endif

/***************************************
 * 
 * Title: Key_Interrupt (External Interrupt)
 * 
 ***************************************/

#if EXAMPLE == 412

// Global Variables Declaration
volatile int Key_Value = 0;

// ISR Declaration
void Key_ISR(void) __attribute__ ((interrupt ("IRQ")));;

void Key_ISR()
{
	unsigned int temp;

	/* 해당 인터럽트 Masking */ 
	rINTMSK1 |= (0x7<<2);
	rEINTMASK |= (0x7<<4);

	/* 키를 읽기 위하여 Polling 함수 사용 */
	temp = rGPFCON;
	
	/* TO DO :  1) GPFCON[6:2] change to Input mode 
	 *          2) 입력된 키값을 확인하여 변수에 저장 
     */		 
	rGPFCON &= ~(0x3ff<<4);	
	Key_Value = Key_Get_Pressed();

    /* 반드시 port를 복원하기 위하여 저장한 값으로 복원 */
	rGPFCON = temp;

	/* TO DO : Keyout을 0로 하여 키 입력 대기상태로 바꿈 */
	rGPGDAT &= ~0x1;
	rGPFDAT	&= ~(0x1<<7);
	
	/* TO DO: Pendng Clear on EINT2,3,4,5,6 */
	rEINTPEND |= (0x7<<4);
	rSRCPND1 |= (0x7<<2);
	rINTPND1 |= (0x7<<2);
	
	/* 해당 인터럽트 UnMasking */ 
	rINTMSK1 &= ~(0x7<<2);
	rEINTMASK &= ~(0x7<<4);	
}

void Main(void)
{	
	int a,i;
	
	Led_Init();
	Uart_Init(115200);
	Key_IRQ_Port_Init();
	
	/* TODO : 인터럽트 벡터에 Key_ISR 함수 등록 */
	//pISR_EINT3 = (unsigned int)Key_EINT3_ISR;	
	pISR_EINT2 = (unsigned int)Key_ISR;
	pISR_EINT3 = (unsigned int)Key_ISR;
	pISR_EINT4_7 = (unsigned int)Key_ISR;
	/* TO DO : 인터럽트 허용 on EINT2,3,4,5,6*/	
	//rINTMSK &= ~(1<<3);
	rINTMSK1 &= ~(0x7<<2);
	rEINTMASK &= ~(0x7<<4);	

	Uart_Send_String("Key ISR Test \n");
	
	for(;;)
	{
		if(Key_Value)
		Uart_Printf("Key Value =%d\n",  Key_Value); 
		Key_Value = 0;			
	}
			
}
#endif