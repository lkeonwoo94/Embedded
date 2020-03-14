/*

Contains second level exception handlers in C. Called from First level Handlers
that are implemented in assembly.

Created on: Dec 03, 2003

Created by: Manoj Mehta

*/

extern void LED_Blink();

void SWI_C_Handler(unsigned number);
void Undef_C_Handler();
void PrefetchAbort_C_Handler();
void DataAbort_C_Handler();
void IRQ_C_Handler();
void FIQ_C_Handler();

void SWI_C_Handler( unsigned number)
{

/*SWI number is loaded into r0 by the assembly routine (First level handler). This is 
the first parameter in accordance with the ARM Procedure Call Standard*/

	switch (number)
		{
			case 0 : /* SWI number 0 code */
				break;
			case 1 : /* SWI number 1 code */
				break;
			case 0x776655:
				LED_Blink();
				break;
			default : /* Unknown SWI - report error */
				;
		}
}


void Undef_C_Handler()
{
	
	// Second level Undefined exception handler code in C.
	
}


void PrefetchAbort_C_Handler()
{
	
	// Second level Prefetch Abort handler code in C.
	
}

void DataAbort_C_Handler()
{
	
	// Second level Data Abort handler code in C.
	
}

void IRQ_C_Handler()
{

	// Second level IRQ handler code in C.
	
}

void FIQ_C_Handler()
{

	// Second level FIQ handler code in C.
		
}


