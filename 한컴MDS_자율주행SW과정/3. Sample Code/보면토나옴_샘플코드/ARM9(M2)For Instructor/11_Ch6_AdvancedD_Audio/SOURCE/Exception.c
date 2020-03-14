#include "2440addr.h"

void Exception_Init(void);
void Undef_Handler(void);
void Pabort_Handler(void);
void Dabort_Handler(void);
void SWI_Handler(void);

void SWI_Handler(void)
{
	Uart_Printf("SWI exception.\n");
	for(;;);
}

void Undef_Handler(void) 
{
	Uart_Printf("Undefined instruction exception.\n");
	for(;;);
}

void Pabort_Handler(void)
{
	Uart_Printf("Pabort exception.\n");
	for(;;);
}

void Dabort_Handler(void)
{
	Uart_Printf("Dabort exception.\n");
	for(;;);
}

void Exception_Init(void)
{
	pISR_UNDEF  = (unsigned)Undef_Handler;
	pISR_SWI    = (unsigned)SWI_Handler;
	pISR_PABORT = (unsigned)Pabort_Handler;
	pISR_DABORT = (unsigned)Dabort_Handler;
	// Disable Interrupt
	rINTMOD     = 0x0;
	rINTMSK     = BIT_ALLMSK;		
	rINTSUBMSK  = BIT_SUB_ALLMSK;	
	// Clear All Previous Pending Bits
	rSUBSRCPND = 0xffffffff;
	rSRCPND = 0xffffffff;
	rINTPND = 0xffffffff;
}
