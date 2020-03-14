;=========================================
; NAME: 2410INIT.S
; DESC: C start up codes
;       Configure memory, ISR ,stacks
;	Initialize C-variables
;=========================================

	INCLUDE option.aa
	INCLUDE memcfg.aa
	INCLUDE 2410addr.aa

BIT_SELFREFRESH EQU	(1<<22)

;Pre-defined constants
USERMODE	EQU 	0x10
FIQMODE		EQU 	0x11
IRQMODE 	EQU 	0x12
SVCMODE		EQU 	0x13
ABORTMODE	EQU 	0x17
UNDEFMODE   EQU 	0x1b
MODEMASK    EQU		0x1f
NOINT       EQU 	0xc0

;The location of stacks
UserStack	EQU	(_STACK_BASEADDRESS-0x3800)		;0x33ff4800 ~ 
SVCStack	EQU	(_STACK_BASEADDRESS-0x2800) 	;0x33ff5800 ~
UndefStack	EQU	(_STACK_BASEADDRESS-0x2400) 	;0x33ff5c00 ~
AbortStack	EQU	(_STACK_BASEADDRESS-0x2000) 	;0x33ff6000 ~
IRQStack	EQU	(_STACK_BASEADDRESS-0x1000)		;0x33ff7000 ~
FIQStack	EQU	(_STACK_BASEADDRESS-0x0)		;0x33ff8000 ~ 


    	MACRO
$HandlerLabel HANDLER $HandleLabel

$HandlerLabel
	sub	sp,sp,#4			;decrement sp(to store jump address)
	stmfd	sp!,{r0}        ;PUSH the work register to stack(lr does't push because it return to original address)
	ldr     r0,=$HandleLabel;load the address of HandleXXX to r0
	ldr     r0,[r0]         ;load the contents(service routine start address) of HandleXXX
	str     r0,[sp,#4]      ;store the contents(ISR) of HandleXXX to stack
	ldmfd   sp!,{r0,pc}     ;POP the work register and pc(jump to ISR)
	MEND
	

	IMPORT  |Image$$RO$$Limit|  ; End of ROM code (=start of ROM data)
	IMPORT  |Image$$RW$$Base|   ; Base of RAM to initialise
	IMPORT  |Image$$ZI$$Base|   ; Base and limit of area
	IMPORT  |Image$$ZI$$Limit|  ; to zero initialise
	
	IMPORT  Main    ; The main entry of mon program 
	
	AREA    Init,CODE,READONLY

	ENTRY 

	b	ResetHandler  
	b	HandlerUndef	;handler for Undefined mode
	b	HandlerSWI		;handler for SWI interrupt
	b	HandlerPabort	;handler for PAbort
	b	HandlerDabort	;handler for DAbort
	b	.				;reserved
	b	HandlerIRQ		;handler for IRQ interrupt 
	b	HandlerFIQ		;handler for FIQ interrupt

;@0x20
	b	.
	
HandlerFIQ      HANDLER HandleFIQ
HandlerIRQ      HANDLER HandleIRQ
HandlerUndef    HANDLER HandleUndef
HandlerSWI      HANDLER HandleSWI
HandlerDabort   HANDLER HandleDabort
HandlerPabort   HANDLER HandlePabort

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

;=======
; ENTRY  
;=======
ResetHandler
	ldr	r0,=WTCON       ;watch dog disable 
	ldr	r1,=0x0         
	str	r1,[r0]

	ldr	r0,=INTMSK
	ldr	r1,=0xffffffff  ;all interrupt disable
	str	r1,[r0]

	ldr	r0,=INTSUBMSK
	ldr	r1,=0x7ff		;all sub interrupt disable
	str	r1,[r0]

	;To reduce PLL lock time, adjust the LOCKTIME register. 
	ldr	r0,=LOCKTIME
	ldr	r1,=0xffffff
	str	r1,[r0]
        
	;Configure MPLL
	ldr	r0,=MPLLCON          
	ldr	r1,=((M_MDIV<<12)+(M_PDIV<<4)+M_SDIV)  ;Fin=12MHz,Fout=50MHz
	str	r1,[r0]

	;Set memory control registers
	ldr	r0, =SMRDATA
	ldr	r1, =BWSCON	;BWSCON Address
	add	r2, r0, #52	;End address of SMRDATA
0       
	ldr	r3, [r0], #4    
	str	r3, [r1], #4    
	cmp	r2, r0		
	bne	%B0
	
    ;Initialize stacks
	bl	InitStacks
	
  	; Setup IRQ handler
	ldr	r0,=HandleIRQ       ;This routine is needed
	ldr	r1,=IsrIRQ          ;if there isn't 'subs pc,lr,#4' at 0x18, 0x1c
	str	r1,[r0]

	;Copy and paste RW data/zero initialized data
	ldr	r0, =|Image$$RO$$Limit| ; Get pointer to ROM data
	ldr	r1, =|Image$$RW$$Base|  ; and RAM copy
	ldr	r3, =|Image$$ZI$$Base|  
	
	;Zero init base => top of initialised data
	cmp	r0, r1      ; Check that they are different
	beq	%F2
1       
	cmp	r1, r3      ; Copy init data
	ldrcc	r2, [r0], #4    ;--> LDRCC r2, [r0] + ADD r0, r0, #4         
	strcc	r2, [r1], #4    ;--> STRCC r2, [r1] + ADD r1, r1, #4
	bcc	%B1
2       
	ldr	r1, =|Image$$ZI$$Limit| ; Top of zero init segment
	mov	r2, #0
3       
	cmp	r3, r1      ; Zero init
	strcc	r2, [r3], #4
	bcc	%B3

	bl	Main        ;Don't use main() because ......
	b	.                       

;function initializing stacks
InitStacks
	;Don't use DRAM,such as stmfd,ldmfd......
	;SVCstack is initialized before
	;Under toolkit ver 2.5, 'msr cpsr,r1' can be used instead of 'msr cpsr_cxsf,r1'
	mrs	r0,cpsr
	bic	r0,r0,#MODEMASK
	orr	r1,r0,#UNDEFMODE|NOINT
	msr	cpsr_cxsf,r1		;UndefMode
	ldr	sp,=UndefStack
	
	orr	r1,r0,#ABORTMODE|NOINT
	msr	cpsr_cxsf,r1		;AbortMode
	ldr	sp,=AbortStack

	orr	r1,r0,#IRQMODE|NOINT
	msr	cpsr_cxsf,r1		;IRQMode
	ldr	sp,=IRQStack
    
	orr	r1,r0,#FIQMODE|NOINT
	msr	cpsr_cxsf,r1		;FIQMode
	ldr	sp,=FIQStack

	bic	r0,r0,#MODEMASK|NOINT
	orr	r1,r0,#SVCMODE
	msr	cpsr_cxsf,r1		;SVCMode
	ldr	sp,=SVCStack
	
	;USER mode has not be initialized.
	
	mov	pc,lr 
	;The LR register won't be valid if the current mode is not SVC mode.
	

	LTORG

SMRDATA DATA
; The following parameter is not optimized.                     
; Memory access cycle parameter strategy
; 1) The memory settings is  safe parameters even at HCLK=75Mhz.
; 2) SDRAM refresh period is for HCLK=75Mhz. 

	DCD (0+(B1_BWSCON<<4)+(B2_BWSCON<<8)+(B3_BWSCON<<12)+(B4_BWSCON<<16)+(B5_BWSCON<<20)+(B6_BWSCON<<24)+(B7_BWSCON<<28))
	DCD ((B0_Tacs<<13)+(B0_Tcos<<11)+(B0_Tacc<<8)+(B0_Tcoh<<6)+(B0_Tah<<4)+(B0_Tacp<<2)+(B0_PMC))   ;GCS0
	DCD ((B1_Tacs<<13)+(B1_Tcos<<11)+(B1_Tacc<<8)+(B1_Tcoh<<6)+(B1_Tah<<4)+(B1_Tacp<<2)+(B1_PMC))   ;GCS1 
	DCD 0x0700   ;GCS2 reset value
	DCD 0x0700   ;GCS3 reset value
	DCD 0x0700   ;GCS4 reset value
	DCD 0x0700   ;GCS5 reset value
	DCD ((B6_MT<<15)+(B6_Trcd<<2)+(B6_SCAN))    ;GCS6
	DCD 0x18008 ;GCS7 reset value
	DCD ((REFEN<<23)+(TREFMD<<22)+(Trp<<20)+(Trc<<18)+(Tchr<<16)+REFCNT)    

	DCD 0x32            ;SCLK power saving mode, BANKSIZE 128M/128M

	DCD 0x30            ;MRSR6 CL=3clk
	DCD 0x30            ;MRSR7

    	ALIGN


    	AREA RamData, DATA, READWRITE

        ^   _ISR_STARTADDRESS
HandleReset 	#   4
HandleUndef 	#   4
HandleSWI   	#   4
HandlePabort    #   4
HandleDabort    #   4
HandleReserved  #   4
HandleIRQ   	#   4
HandleFIQ   	#   4

HandleEINT0   	#   4
HandleEINT1   	#   4
HandleEINT2   	#   4
HandleEINT3   	#   4
HandleEINT4_7	#   4
HandleEINT8_23	#   4
HandleRSV6		#   4
HandleBATFLT   	#   4
HandleTICK		#   4
HandleWDT		#   4
HandleTIMER0 	#   4
HandleTIMER1 	#   4
HandleTIMER2 	#   4
HandleTIMER3 	#   4
HandleTIMER4 	#   4
HandleUART2  	#   4
HandleLCD 		#   4
HandleDMA0		#   4
HandleDMA1		#   4
HandleDMA2		#   4
HandleDMA3		#   4
HandleMMC		#   4
HandleSPI0		#   4
HandleUART1		#   4
HandleRSV24		#   4
HandleUSBD		#   4
HandleUSBH		#   4
HandleIIC		#   4
HandleUART0		#   4
HandleSPI1 		#   4
HandleRTC 		#   4
HandleADC 		#   4

        END
