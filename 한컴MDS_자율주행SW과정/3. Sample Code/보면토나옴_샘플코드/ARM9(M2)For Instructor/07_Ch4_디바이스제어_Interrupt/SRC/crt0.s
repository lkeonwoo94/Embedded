/*
 * =====================================================================
 * NAME         : crt0.s
 *
 * Descriptions : C Run-time 0 start up codes for Samsung S3C2440
 *				  ISR Routine included
 *
 * IDE          : CodeWarrior 2.0 or Later
 *
 * Modification
 *	   2006.9.12 by JunGyu Park
 * =====================================================================
 */

#include "2440addr.inc"
;	GET 2440addr.inc

#define	_ISR_STARTADDRESS 		0x33ffff00  

; macro 정의

    	MACRO
$HandlerLabel HANDLER $HandleLabel

$HandlerLabel
	sub		sp,sp,#4		   ; decrement sp(to store jump address)
	stmfd	sp!,{r0}		   	; PUSH the work register to stack(lr does't push because 
						   					; it return to original address)
	ldr		r0,=$HandleLabel  ; load the address of HandleXXX to r0
	ldr		r0,[r0]           ; load the contents(service routine start address) of HandleXXX
	str		r0,[sp,#4]        ; store the contents(ISR) of HandleXXX to stack
	ldmfd	sp!,{r0,pc}       ; POP the work register and pc(jump to ISR)
	MEND

	AREA    Init,CODE,READONLY

	EXPORT _start
	
_start

	; ResetHandler가 처음부터 나오는 것이 아니라 vector 주소 영역에는 reset vector가 존재해야 한다
	; exception이 발생하면 ARM은 하드웨어적으로 다음 주소로 분기된다
	b	ResetHandler
	b	HandlerUndef	;handler for Undefined mode
	b	HandlerSWI	;handler for SWI interrupt
	b	HandlerPabort	;handler for PAbort
	b	HandlerDabort	;handler for DAbort
	b	.						;reserved
	b	HandlerIRQ	;handler for IRQ interrupt
	b	HandlerFIQ	;handler for FIQ interrupt
	
	LTORG   
HandlerFIQ      HANDLER HandleFIQ
HandlerIRQ      HANDLER HandleIRQ
HandlerUndef    HANDLER HandleUndef
HandlerSWI      HANDLER HandleSWI
HandlerDabort   HANDLER HandleDabort
HandlerPabort   HANDLER HandlePabort	

	; IRQ Handler 생성
	; IRQ는 발생 소스가 다양하기 때문에 해당 C루틴의 주소를 획득하여야 한다
	EXPORT IsrIRQ
IsrIRQ  
	sub	sp,sp,#4       ;reserved for PC
	stmfd	sp!,{r8-r9}   
	
	ldr	r9,=INTOFFSET
	ldr	r9,[r9]
	ldr	r8,=HandleEINT0
	add	r8,r8,r9,lsl #2
	ldr	r8,[r8]
	str	r8,[sp,#8]
	ldmfd	sp!,{r8-r9,pc}	
	
ResetHandler

	ldr	r0,=WTCON			;watch dog disable 
	ldr	r1,=0x0         
	str	r1,[r0]

	ldr	r0,=INTMSK
	ldr	r1,=0xffffffff		;all interrupt disable
	str	r1,[r0]

	ldr	r0,=INTSUBMSK
	ldr	r1,=0x7fff			;all sub interrupt disable
	str	r1,[r0]

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

;	;GPHCON (prevent for buzzer noise)
;	ldr	r0,=GPHCON
;	ldr	r1,= 0x00100000 ;(GPH10 -> Output)
;	str	r1,[r0]
        
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

;=======================================================================================
	;Set memory control registers
    ldr	r0,=SMRDATA
	ldr	r1,=BWSCON	; BWSCON Address (Start Address)
	add	r2, r0, #52	; End address of SMRDATA => total registers = 52/4 = 13개
0       
	ldr	r3, [r0], #4     ; post increment
	str	r3, [r1], #4 	 ; post increment
	cmp	r2, r0
	bne	%B0

; C언어의 변수 영역을 설정하기 위한 루틴
	; 기본적인 메모리 설정이 완료되고 수행하여야 한다
	; 컴파일러가 main() 이전에 __main()등 특정 루틴을 삽입하면
	; 해당 루틴이 이 과정을 대신한다. 
	; 단지 본 프로그램에서 b __main만 수행하면 된다

	IMPORT  |Image$$RO$$Limit|  ; End of ROM code (=start of ROM data)
	IMPORT  |Image$$RW$$Base|   ; Base of RAM to initialise
	IMPORT  |Image$$ZI$$Base|   ; Base and limit of area
	IMPORT  |Image$$ZI$$Limit|  ; to zero initialise
	
	IMPORT  Main    ; The main entry of mon program 

	; Copy and paste RW data/zero initialized data
	ldr		r0, =|Image$$RO$$Limit|   ; Get pointer to ROM data
	ldr		r1, =|Image$$RW$$Base|  ; and RAM copy
	ldr		r3, =|Image$$ZI$$Base|    ; start of ZI area
	
	; 만약 RO-LIMIT == RW-BASE 라면?
	; 이미 RW-DATA는 RW 영역에 있다는 것을 의미한다
	; 복사가 필요없다
	
	; RW-DATA copy to RAM Area
	cmp		r0, r1      		; Check that they are different
	beq		%F2
1       
	cmp		r1, r3			; Copy init data
	ldrcc		r2, [r0], #4	;--> LDRCC r2, [r0] + ADD r0, r0, #4         
	strcc	r2, [r1], #4	;--> STRCC r2, [r1] + ADD r1, r1, #4
	bcc		%B1
2       
	ldr	r1, =|Image$$ZI$$Limit| 	; Top of zero init segment
	mov		r2, #0
3       
	cmp		r3, r1			; Zero init
	strcc	r2, [r3], #4
	bcc		%B3
;========================================================================================
	; stack의 생성
	; 기본적으로 C언어 프로그램에서 사용하는 스택이 생성되어야
	; 함수호출과 지역변수의 사용이 가능하다

	; 우선 전원 인가시 SVC 모드이므로 
	; SVC 모드에서만 프로그램이 구동된다고 가정하면
	; 다른 모드의 stack은 설정할 필요가 없게 된다
	; 그러므로 간단히 현재 모드의 sp만 설정하면 된다

	;The location of stacks
	; stack layout design
	; 사용자 임의로 목적에 맞게 재설계 되어야 한다
	; 현재 설계는 ZI-LIMIT을 스택의 제일 위로 본다

STACK_BASE_ADDR		EQU		0x5C00 	; total  19KB
UserStack				EQU		0x2000  	; 8KB => ZI-LIMT : (ZI-LIMIT+0x2000)
SVCStack				EQU		0x4000	; 8KB => (ZI-LIMIT+0x2000) : (ZI-LIMIT+0x4000)
UndefStack				EQU		0x4400	; 1KB => (ZI-LIMIT+0x4000) : (ZI-LIMIT+0x4400)
AbortStack				EQU		0x4800	; 1KB => (ZI-LIMIT+0x4400) : (ZI-LIMIT+0x4800)
IRQStack				EQU		0x5800	; 4KB => (ZI-LIMIT+0x4800) : (ZI-LIMIT+0x5800)
FIQStack				EQU		0x5C00	; 1KB => (ZI-LIMIT+0x5800) : (ZI-LIMIT+0x5c00)

	; Exception 처리를 위하여 각 모드의 스택을 설정하여야 한다
	; 우선 각 모드의 스택을 설정하기 위하여는 모드 강제 전환이 필요하다
	; 이는 SVC모드부터 시작하여 각 모드로 CPSR을 수정하여 전환한다

Mode_USR			EQU    0x10
Mode_FIQ			EQU    0x11
Mode_IRQ			EQU    0x12
Mode_SVC			EQU    0x13
Mode_ABT			EQU    0x17
Mode_UNDEF			EQU    0x1B
Mode_SYS			EQU    0x1F

I_Bit				EQU    0x80 ; when I bit is set, IRQ is disabled
F_Bit				EQU    0x40 ; when F bit is set, FIQ is disabled
	
	ldr		r1, =|Image$$ZI$$Limit| 	; Top of zero init segment	
	
	msr     	CPSR_c, #Mode_ABT:OR:F_Bit:OR:I_Bit
	add		sp, r1, #AbortStack
	
	msr     	CPSR_c, #Mode_UNDEF:OR:F_Bit:OR:I_Bit
	add		sp, r1, #UndefStack	
	
	msr     	CPSR_c, #Mode_SVC:OR:F_Bit:OR:I_Bit
	add		sp, r1, #SVCStack	
	
	msr		CPSR_c, #Mode_FIQ:OR:I_Bit		; Change to FIQ mode
	add		sp, r1, #FIQStack	
	
	msr		CPSR_c, #Mode_IRQ:OR:I_Bit		; Change to IRQ mode
	add		sp, r1, #IRQStack	

	; 이전에는 SVC 모드에서 USER 프로그램이 호출되었으나 이제는 system 모드에서 진입한다
	msr		CPSR_c, #Mode_SYS         		; Change to System mode	
	add		sp, r1, #UserStack
	
	; 여기서 IRQ가 발생할때 위에서 만든 IsrIRQ 루틴으로 분기하기 위한 ISR_VECTOR 설정을 한다

	; Setup IRQ handler
	ldr		r0,=HandleIRQ  
	ldr		r1,=IsrIRQ			
	str	r1,[r0]	
	
;======================================================================================

	; 컴파일러의 startup 루틴을 호출하거나 혹은 임의의 Main을 호출
	; b Main하면 C 함수에서 돌아오지 않음을 가정하는 것이며
	; bl 하면 되돌아 올수도 있음을 가정한다.
	; 따라서 되록아 온 후 할 일이 없으면 b %B0 하면 무한 루프가 형성된다.
	; 이때, 절대로 임베디드 시스템은 프로그램 종료가 없어야 하므로
	; bl main한 후 돌아와서 무한루프를 형성하지 않는 일을 없도록 주의해야 한다

	; LOOP forever	
	bl Main
0    	
    b	%b0
;=========================================================================    	
; MEMORY 설정을 위한 Table
; 구동하고자 하는 시스템에 따라 설정은 달라진다
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
	
	
	
	; C에서 처리할 Exception과 Interrupt 함수 주소를 저장할 위치
	; startup은 이 주소에서 함수주소를 획득하여 분기한다.
ALIGN

    	AREA RamData, DATA, READWRITE

        ^   _ISR_STARTADDRESS
; .=0x30000000
HandleReset 	#   4
HandleUndef 	#   4
HandleSWI		#   4
HandlePabort    #   4
; .=0x30000010
HandleDabort    #   4
HandleReserved  #   4
HandleIRQ		#   4
HandleFIQ		#   4

; .=0x30000020
;IntVectorTable
HandleEINT0		#   4
HandleEINT1		#   4
HandleEINT2		#   4
HandleEINT3		#   4
; .=0x30000030
HandleEINT4_7	#   4
HandleEINT8_23	#   4
HandleCAM		#   4
HandleBATFLT	#   4
; .=0x30000040
HandleTICK		#   4
HandleWDT		#   4
HandleTIMER0 	#   4
HandleTIMER1 	#   4
; .=0x30000050
HandleTIMER2 	#   4
HandleTIMER3 	#   4
HandleTIMER4 	#   4
HandleUART2  	#   4
; .=0x30000060
HandleLCD 		#   4
HandleDMA0		#   4
HandleDMA1		#   4
HandleDMA2		#   4
; .=0x30000070
HandleDMA3		#   4
HandleMMC		#   4
HandleSPI0		#   4
HandleUART1	#   4
; .=0x30000080
HandleNFCON	#   4
HandleUSBD		#   4
HandleUSBH		#   4
HandleIIC		#   4
; .=0x30000090
HandleUART0 	#   4
HandleSPI1 		#   4
HandleRTC 		#   4
HandleADC 		#   4
; .=0x300000a0


	END
    	
    	
