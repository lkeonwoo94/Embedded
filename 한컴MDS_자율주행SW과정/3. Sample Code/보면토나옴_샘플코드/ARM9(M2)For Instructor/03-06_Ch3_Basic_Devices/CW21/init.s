; Exception handlers 


		.export	__reset							; execution begins here after RESET
		
		.extern swi_handler						; swi exception handler
		.extern	undef_handler					; undefined exception handler 
		.extern	prefetch_abrt_handler			; prefetch abort exception handler
		.extern	data_abrt_handler				; data abort exception handler
		.extern	irq_handler						; irq exception handler
		.extern	fiq_handler						; fiq exception handler
		.extern __init_board					; board startup code

		.section .reset

__reset:

; Setup exception handlers here
		ldr		pc, reset_handle				; RESET
		ldr		pc, undef_handle				; undefined instruction
		ldr		pc, swi_handle					; SWI
		ldr		pc, prefetch_handle				; prefetch abort
		ldr		pc, abort_handle				; data abort
		nop										; reserved
		ldr		pc, irq_handle					; IRQ
		ldr		pc, fiq_handle					; FIQ

; These locations hold the actual exception handlers addresses

reset_handle:
		.long	__init_board
undef_handle:
		.long	undef_handler
swi_handle:
		.long	swi_handler
prefetch_handle:
		.long	prefetch_abrt_handler
abort_handle:			
		.long	data_abrt_handler
irq_handle:
		.long	irq_handler
fiq_handle:
		.long	fiq_handler
		
   		.end
   		