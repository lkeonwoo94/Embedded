/*
 * =====================================================================
 * NAME         : Dma.c
 *
 * Descriptions : DMA Test Driver
 *
 * IDE          : CodeWarrior 2.0 or Later
 *
 * Modification
 *     Modified by MDS Tech. NT Div.(2Gr) (2007.3.1~4)
 * =====================================================================
 */
#include "2440addr.h"
#include "libc.h"

// Global Variables Declaration
// 목적지는 CACHE 영역이 아닐것
static	unsigned long src=0x33000000;
static	unsigned long dst=0x33100000;
static	unsigned int size = 12; /* word size */
static	unsigned long pattern;

//Function Declatation
void DMA0_SW_Init(void);
void DMA0_Timer_Init(void);
void DMA0_UART_Init(void);
void DMA0_SW_Start(void);
void DMA0_HW_Start(void);


void DMA0_SW_Init(void)
{
	/* Init DMASKTRIG on DMA0*/
	rDMASKTRIG0 = 0x0;
	
	/* TO DO : Select Base Address of Source and Destination*/
	rDISRC0 = src;
	rDIDST0 = dst;
	
	/*  Init Source & Destination Control Register on DMA0 
	 * (memory -> AHB bus, INC mode, CHK_INT = after auto-reload)
	 */
	/* TODO : */ 
	rDISRCC0 &= ~0x3;
	rDIDSTC0 &=~(0x7);
	
	/* TO DO : setting for S/W DMA request
	 * DCON0 : Handshake[31-1], HCLK[30-1], INT mode[29-1], Single Unit[28-0], Whole service[27-1],
	 * HW_select[26:24],  S/W trigger[23-0], Auto Reload ON[22-0], Byte size[21:20](Note: Word size<->Byte size)
	 */
	 
	rDCON0 = (0<<31)+(1<<30)+(1<<29)+(0<<28)+(1<<27)+(1<<24)+(0<<23)+(0<<22)+(0<<20)+size*4;
		
}

void DMA0_Timer_Init(void)
{
	/* Init DMASKTRIG on DMA0*/
	rDMASKTRIG0 = 0x0;
	
	/* TODO : Select Base Address of Source and Destination*/
	rDISRC0 =src;
	rDIDST0 =dst;
	
	/* TO DO : Init Source & Destination Control Register on DMA0 (memory -> AHB bus, INC mode)*/
	rDISRCC0 &= ~0x3;
	rDIDSTC0 &=~(0x7);
	
	/* TO DO : setting for H/W DMA request
     * DCON0 : Handshake[31-1], HCLK[30-1], INT mode[29-1], Single Unit[28-0], 
     * Whole service[27-1], Timer[26:24], H/W trigger[23-1], Auto Reload ON[22-0], 
     * Byte size[21:20](Note: Word size<->Byte size) */
	rDCON0 =(0<<31)+(1<<30)+(1<<29)+(0<<28)+(1<<27)+(3<<24)+
	(1<<23)+(0<<22)+(0<<20)+size*4;

	/* TO DO : Turn on Trigger*/
	rDMASKTRIG0 |= (0x1<<1);
		
}

void DMA0_UART_Init(void)
{
	/* Init DMASKTRIG on DMA0*/
	rDMASKTRIG0 = 0x0;
	
	/* TODO : Select Base Address of Source and Destination*/
	rDISRC0 =src;
	rDIDST0 =dst;

	/* TO DO : Init Source & Destination Control Register on DMA0 
	 * (memory -> AHB bus, INC mode, CHK_INT -> after auto-reload )
     */

	rDISRCC0 &= ~0x3;
	rDIDSTC0 &=~(0x7);
	
	/* TO DO : setting for H/W DMA request
	 * DCON0 : Handshake[31-1], HCLK[30-1], INT mode[29-1], Single Unit[28-0], Whole service[27-1], 
	 * Uart0[26:24], H/W trigger[23-1], Auto Reload ON[22-0], Byte size[21:20](Note: Word size<->Byte size)
	 */
	 
	rDCON0 =(0<<31)+(1<<30)+(1<<29)+(0<<28)+(1<<27)+(1<<24)+(1<<23)+(0<<22)+(0<<20)+size*4;
		
	 /* TO DO : Turn on Trigger*/
	rDMASKTRIG0 |= (0x1<<1);
		
}

void DMA0_SW_Start(void)
{
	MemFill(src, 0x00000000, size);
	MemFill(dst, 0x00000000, size);	
	Uart_Printf("\nStart Memory copy test With DMA\n");	
	
	/* memory copy test with DMA */
	pattern = 0x5555aaaa;
	Uart_Printf("Fill pattern [0x%08x] to [0x%08x]\n",pattern, src);
	MemFill(src, pattern, size);
	MemDump(src, size);
	Uart_Printf("\nCopy from [0x%08x] to [0x%08x] by DMA\n",src, dst);
	
	/* TO DO : Turn on Trigger*/
	rDMASKTRIG0 |= (0x1<<1);	
	/* TO DO : Start S/W Trigger in S/W Request mode */
	rDMASKTRIG0 |= (0x1);
		
}

void DMA0_HW_Start(void)
{
	MemFill(src, 0x00000000, size);
	MemFill(dst, 0x00000000, size);	
	Uart_Printf("\nStart Memory copy test With DMA\n");

	/* memory copy test with DMA */
	pattern = 0x5555aaaa;
	Uart_Printf("Fill pattern [0x%08x] to [0x%08x]\n",pattern, src);
	MemFill(src, pattern, size);
	MemDump(src, size);
	Uart_Printf("\nCopy from [0x%08x] to [0x%08x] by DMA\n",src, dst);
			
}