

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
	

	; Make LED2(GPG5) to LOW
		
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
	
	;Set memory control registers
    ldr	r0,=SMRDATA
	ldr	r1,=BWSCON		; BWSCON Address (Start Address)
	add	r2, r0, #52		; End address of SMRDATA => total registers = 52/4 = 13개
0       
	ldr	r3, [r0], #4	; post increment
	str	r3, [r1], #4  	; post increment
	cmp	r2, r0
	bne	%B0

	; C언어의 변수 영역을 설정하기 위한 루틴
	; 기본적인 메모리 설정이 완료되고 수행하여야 한다
	; 컴파일러가 main() 이전에 __main()등 특정 루틴을 삽입하면
	; 해당 루틴이 이 과정을 대신한다. 
	; 단지 본 프로그램에서 b __main만 수행하면 된다

	IMPORT  |Image$$RO$$Limit|  	; End of ROM code (=start of ROM data)
	IMPORT  |Image$$RW$$Base|   	; Base of RAM to initialise
	IMPORT  |Image$$ZI$$Base|   	; Base and limit of area
	IMPORT  |Image$$ZI$$Limit|  	; to zero initialise
	
	; Copy and paste RW data/zero initialized data
	ldr		r0, =|Image$$RO$$Limit|	; Get pointer to ROM data
	ldr		r1, =|Image$$RW$$Base|  ; and RAM copy
	ldr		r3, =|Image$$ZI$$Base|	; start of ZI area
	
	; RW-DATA copy to RAM Area
	cmp		r0, r1      			; Check that they are different
	beq		%F2
1       
	cmp		r1, r3					; Copy init data
	ldrcc		r2, [r0], #4		;--> LDRCC r2, [r0] + ADD r0, r0, #4         
	strcc	r2, [r1], #4			;--> STRCC r2, [r1] + ADD r1, r1, #4
	bcc		%B1
2       
	ldr	r1, =|Image$$ZI$$Limit| 	; Top of zero init segment
	mov		r2, #0
3       
	cmp		r3, r1					; Zero init
	strcc	r2, [r3], #4
	bcc		%B3	
	
UserStack_Offset			EQU		0x2000  
SVCStack_Offset				EQU		0x4000
UndefStack_Offset			EQU		0x4400
AbortStack_Offset			EQU		0x4800
FIQStack_Offset				EQU		0x4C00
IRQStack_Offset				EQU		0x5C00
STACK_BASE_Offset			EQU 	0x5C00	

	ldr		r1, =|Image$$ZI$$Limit|	
	add 	sp, r1, #SVCStack_Offset
	
	IMPORT  Main    ; The main entry of mon program 
	
	bl Main

0	
	b  %B0	
	
;TODO 1) FIX BWSCON
;TODO 2) FIX BANKCON6
;	 *  - Memory Type : Sync. DRAM
;	 *  - Column address number : 10-bit
;	 *  - RAS to CAS delay : 3 clock
;TODO 3) FIX REFRESH
;	 *  - REFEN, Auto Refresh 
;	 *  - Trp : 2 clock
;	 *  - Tsrc : 7 clock
;	 *  - Refresh count value : 0x67b
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