; Startup code for Integrator Board
; Created on: Dec 09, 2003
; Created by: Manoj Mehta

		.export	__init_board
		
		.extern __IRQ_Stack					; stack base for IRQ mode (defined in LCF)
		.extern __UNDEF_Stack				; stack base for UNDEF mode (defined in LCF)
		.extern __FIQ_Stack					; stack base for FIQ mode (defined in LCF)
		.extern __ABT_Stack					; stack base for ABT mode (defined in LCF)
		.extern __USR_Stack					; stack base for USR mode (defined in LCF)
        .extern __startup					; entry point in the runtime library
		.extern __data_start__				; data copy start
		.extern __data_end__				; data copy end
		.extern __endrodata__    			; data address in ROM

Mode_USR        .equ     0x10
Mode_FIQ        .equ     0x11
Mode_IRQ        .equ     0x12
Mode_SVC        .equ     0x13
Mode_ABT        .equ     0x17
Mode_UNDEF      .equ     0x1B
Mode_SYS        .equ     0x1F ; available on ARM Arch 4 and later

I_Bit           .equ     0x80 ; when I bit is set, IRQ is disabled
F_Bit           .equ     0x40 ; when F bit is set, FIQ is disabled

En_ICache		.equ	 0x1000  ; enable instruction cache
En_DCache		.equ	 0x4	 ; enable data cache


; Start of startup code

		.text

__init_board:

; No board initialization code needed for integrator as this is taken care of by the 
; board firmware. The application (S-REC) is directly flashed on to 0x24000000 using
; flash programmer and it runs on reset.

	
; --- Initialise stack pointer registers
; --- Now change to System mode and set up System/User mode stack.
	   MSR	   CPSR_c, #( Mode_SYS | I_Bit | F_Bit )
       LDR     SP, =__USR_Stack

; Enter IRQ mode and set up the IRQ stack pointer
       MSR     CPSR_c, #( Mode_IRQ | I_Bit | F_Bit )
      LDR     SP, =__IRQ_Stack
       
; Enter FIQ mode and set up the FIQ stack pointer
       MSR     CPSR_c, #( Mode_FIQ |I_Bit |F_Bit )
       LDR     SP, =__FIQ_Stack

; Enter ABT mode and set up the ABT stack pointer
       MSR     CPSR_c, #( Mode_ABT |I_Bit |F_Bit )
       LDR     SP, =__ABT_Stack
        
; Enter UNDEF mode and set up the UNDEF stack pointer
        MSR     CPSR_c, #( Mode_UNDEF |I_Bit | F_Bit )
        LDR     SP, =__UNDEF_Stack
        
; Enter SVC mode
; Do not setup the SVC stack as it will be set by the runtime library
        MSR     CPSR_c, #( Mode_SVC | I_Bit | F_Bit )
                
; ROM to RAM copy: copy the .data segment from ROM to RAM
copy_to_ram:
	ldr		r0, =__data_start__		; where to copy data
	ldr		r1, =__data_end__		; end of data copy
	sub		r2, r1, r0				; length of data
	ldr		r1, =__endrodata__		; address of data in FLASH
moveloop:
	ldr		r3, [r1], #4			; load one word and increment source
	str		r3, [r0], #4			; store one wors and increment destination
	subs	r2, r2, #4				; more words ?
	bne		moveloop				; loop through all data
	
	b		__startup				; jump to the normal startup code in supervisor mode

   .end
                        
