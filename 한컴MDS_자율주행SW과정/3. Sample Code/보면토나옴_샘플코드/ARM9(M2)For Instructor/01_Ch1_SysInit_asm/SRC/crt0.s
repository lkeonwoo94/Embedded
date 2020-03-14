

#include "2440addr.inc"
	AREA Init, CODE, READONLY
	
	EXPORT _start

_start 

	ldr	r0,=WTCON			;watch dog disable 
	ldr	r1,=0x0         
	str	r1,[r0]

	ldr	r0,=INTMSK
	ldr	r1,=0xffffffff		;all interrupt disable
	str	r1,[r0]

	ldr	r0,=INTSUBMSK
	ldr	r1,=0x7fff			;all sub interrupt disable
	str	r1,[r0]
	
	;;;;;;;; Fclk: 400, Hclk: 100, Pclk: 50 ;;;;;;;;

	;Set clock PLL
	ldr	r0,=LOCKTIME
	ldr	r1,=0xffffff
	str	r1,[r0]

	;Configure Camera Clock
	ldr	r0,=CAMDIVN
	ldr	r1,=0x0 			
	str	r1,[r0]

	;Configure Clock Divide 	for FCLK:HCLK:PCLK
	ldr	r0,=CLKDIVN
	ldr	r1,=0x5 				; FCLK:HCLK:PCLK=(1:4:8)
	str	r1,[r0]

	;Configure MPLL
	ldr	r0,=MPLLCON
	ldr	r1,= 0x6e031   			; 399.65MHz(About 400MHz) @ 16.9344MHz
	str	r1,[r0]
	
; *** Test 6개의 LED중 첫번째 LED만 OFF(Clear) 시킴 ***
; 비트 연산으로 원하는 비트들만 0, 1로 만드는 방법 
; bic : 비트 clear 명령 => bic r1,r2,#0x1  => r1 = r2 & ~(0x1)
; orr : 비트 set 명령 => orr r1,r2,#0x1  => r1 = r2 | 0x1


	; Make LED4(GPB5) to LOW
	;Configure LED4(GPB5) as OUTPUT
	

	; Make LED4(GPB5) to LOW
		
	ldr r0, =GPBDAT
	ldr r1, [r0]
	bic r1, r1, #0x20
	str r1, [r0]

	;Configure LED4(GPB5) as OUTPUT
	
	ldr r0, =GPBCON
	ldr r1, [r0]
	bic r1, r1, #0xc00
	orr r1, r1, #0x400
	str r1, [r0]
	
0	
	b  %B0	
	
;TODO 1) FIX BWSCON
;TODO 2) FIX BANKCON6
;	 *  - Memory Type : Sync. DRAM
;	 *  - Column address number : 9-bit
;	 *  - RAS to CAS delay : 3 clock
;TODO 3) FIX REFRESH
;	 *  - REFEN, Auto Refresh 
;	 *  - Trp : 2 clock
;	 *  - Tsrc : 7 clock
;	 *  - Refresh count value : 0x459
;TODO 4) FIX MRSRB6, MRSRB7
;	 * CAS latency : 3 cycle

SMRDATA
	DCD 0x22121112
	DCD 0x00000700
	DCD 0x00000700 
	DCD 0x00000700
	DCD 0x00000700 
	DCD 0x00000700
	DCD 0x00000700
	DCD 0x00018006
	DCD 0x00018006
	DCD 0x008e067b
	DCD 0x32		
 	DCD 0x30		
	DCD 0x30

	
	END 