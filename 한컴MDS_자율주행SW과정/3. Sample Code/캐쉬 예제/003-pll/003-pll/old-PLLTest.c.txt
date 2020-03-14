/************************************************
 * NAME    : PLLTest.c
 ************************************************/

#include <stdlib.h>
#include <string.h>
#include "def.h"
#include "option.h"
#include "2440addr.h"
#include "2440slib.h"
#include "2440lib.h"
#include "pll.h"

void Led_Toggle_Test();


/*
 [ PLL_ON_START
			 ; Added for confirm clock divide. for 2440.
			; Setting value F:H:Pclk = 1:2:2
			ldr	r0,=CLKDIVN
			ldr	r1,=CLKDIV_VAL		; 0=1:1:1, 1=1:1:2, 2=1:2:2, 3=1:2:4, 4=1:4:4, 0x5=1:4:8, 7=1:3:6
											;CLKDIV_VAL	EQU	7	; 0=1:1:1, 1=1:1:2, 2=1:2:2, 3=1:2:4, 4=1:4:4, 5=1:4:8, 6=1:3:3, 7=1:3:6.
			str	r1,[r0]
     
    		[ CLKDIV_VAL>1 		; means Fclk:Hclk is not 1:1.
				bl MMU_SetAsyncBusMode
			|
				bl MMU_SetFastBusMode	; default value.
			]

			;Configure UPLL
			ldr	r0,=UPLLCON
			ldr	r1,=((U_MDIV<<12)+(U_PDIV<<4)+U_SDIV) 
			str	r1,[r0]

			nop	; Caution: After UPLL setting, at least 7-clocks delay must be inserted for setting hardware be completed.
			nop
			nop
			nop
			nop
			nop
			nop

			;		[ FCLK = 399650000
			;			M_MDIV		EQU	110		;	Fin=16.9344MHz
			;			M_PDIV		EQU	3
			;			[ CPU_SEL = 32440001
			;				M_SDIV		EQU	1		;	2440A
			;			|
			;				M_SDIV		EQU	1		;	2440X
			;			]
			;		]
			;	[ ÃÊ±â ]	 Fin = 16.9344MHz
			;				FCLK = 399.65 MHz
			;				HCLK = 133.22 MHz
			;				PCLK = 066.60 MHz
			str	r1,[r0]
			;Configure MPLL
			ldr	r0,=MPLLCON
			ldr	r1,=((M_MDIV<<12)+(M_PDIV<<4)+M_SDIV)  
			str	r1,[r0]
	]
*/
void Main(void)
{
	int i;
	
    MMU_DisableICache();
    
	Port_Init();
	Uart_Init(PCLK, 115200);
	Uart_Select(0);
	
    Uart_Printf("\n====================================\n");
	Uart_Printf(" MBA-2440 PLL Clock Test Program\n");
	Uart_Printf("====================================\n");
    
	// Display 6 and 9
	for (i=0; i<10; i++) {
		Led_Toggle_Test();
	}

	Uart_Printf(" Press Any Key to change clock...\n");	
    Uart_Getch();
	Uart_Printf(" MPLL Change Starting...\n");
	
	// Change clock frequency ratio as 1:4:8	
	ChangeClockDivider(2,1);				// 1:4:8    
	
	//	ChangeMPllValue(118,2,2);    	//	FCLK = 266.72 MHz
	
	ChangeMPllValue(60,4,1);				//	FCLK = 95.96 MHz
													//	HCLK = 23.99 MHz
													// 	PCLK = 11.995 MHz
	while(1) {
		Led_Toggle_Test();
	}			
}
    

void Led_Toggle_Test()
{
	int j,k,l;

	Led_Display(6);

	for(j=0;j<500;j++)   {
      for(k=0;k<500;k++)
       l++;
    }

	Led_Display(9);		
	for(j=0;j<500;j++)  {
      for(k=0;k<500;k++)
       l++;
    }		
}
