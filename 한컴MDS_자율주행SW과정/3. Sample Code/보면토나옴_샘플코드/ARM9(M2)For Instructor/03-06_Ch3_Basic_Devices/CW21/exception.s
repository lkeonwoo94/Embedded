/*

Contains first level exception handlers. These are implemented in assembly and call second
level handlers that are implemented in C.

The first(top)-level handler uses a BL (Branch with Link) instruction to jump to the
appropriate C function (second level).

Created on: Dec 03, 2003.

Created by: Manoj Mehta

*/  

	.export swi_handler
	.export	undef_handler
	.export	prefetch_abrt_handler
	.export	data_abrt_handler
	.export	irq_handler
	.export	fiq_handler

	.extern	SWI_C_Handler
	.extern	Undef_C_Handler
	.extern	PrefetchAbort_C_Handler
	.extern DataAbort_C_Handler
	.extern	IRQ_C_Handler
	.extern	FIQ_C_Handler
	
	.text
	
swi_handler:
	stmfd	sp!, { r0-r3, r12, lr }				; save all volatile registers
	ldr		r0, [lr, #-4]			            ; get address of SWI instruction into r0
	bic		r0,r0,#0xff000000                   ; mask top 8 bits of instruction to get SWI number
/*Because the SWI number is loaded into r0 by the assembly routine, this is passed to the 
C function (Second level) as the first parameter in accordance with the ARM Procedure Call 
Standard*/
	bl		SWI_C_Handler						; call the C handler
	ldmfd	sp!, { r0-r3, r12, pc }^			; restore volatile registers
;	movs	pc, lr								; and return
	
undef_handler:
	stmfd	sp!, { r0-r3, r12, lr }				; save all volatile registers
	ldr		r0, [ lr, #-4 ]						; opcode of the instruction before the exception
	bl		Undef_C_Handler						; call the C handler
	ldmfd	sp!, { r0-r3, r12, pc }^			; restore volatile registers
;	movs	pc, lr								; and return

prefetch_abrt_handler:
	sub		lr,lr,#4
	stmfd	sp!, { r0-r3, r12, lr }				; save all volatile registers
	ldr		r0, [ lr, #-4 ]						; opcode of the instruction before the exception
	bl		PrefetchAbort_C_Handler				; call the C handler
	ldmfd	sp!, { r0-r3, r12, pc }^			; restore volatile registers
;	subs	pc, lr, #4							; and return

data_abrt_handler:
	sub		lr,lr,#8
	stmfd	sp!, { r0-r3, r12, lr }				; save all volatile registers
	ldr		r0, [ lr, #-4 ]						; opcode of the instruction before the exception
	bl		DataAbort_C_Handler					; call the C handler
	ldmfd	sp!, { r0-r3, r12, pc }^			; restore volatile registers
;	subs	pc, lr, #8							; and return
						
irq_handler:
	sub		lr,lr,#4
	stmfd	sp!, { r0-r3, r12, lr }				; save all volatile registers
	ldr		r0, [ lr, #-4 ]						; opcode of the instruction before the exception
	bl		IRQ_C_Handler						; call the C handler
	ldmfd	sp!, { r0-r3, r12, pc }^			; restore volatile registers
;	subs	pc, lr, #4							; and return
		
fiq_handler:
	sub		lr,lr,#4
	stmfd	sp!, { r0-r3, r12, lr }				; save all volatile registers
	ldr		r0, [ lr, #-4 ]						; opcode of the instruction before the exception
	bl		FIQ_C_Handler						; call the C handler
	ldmfd	sp!, { r0-r3, r12, pc }^			; restore volatile registers
;	subs	pc, lr, #4							; and return
		