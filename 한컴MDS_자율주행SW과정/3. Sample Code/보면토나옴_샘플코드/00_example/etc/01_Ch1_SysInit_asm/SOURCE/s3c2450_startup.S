
#include "2450addr.inc"

	/* CONFIG_CLK_534_133_66	*/
	.equ	Startup_MDIV,		267
	.equ	Startup_PDIV,		3
	.equ	Startup_SDIV,		1
	.equ	Startup_EPLLSTOP,	0
	.equ	Startup_ARMCLKdiv,	0
	.equ	Startup_PREdiv,		0x1
	.equ	Startup_HCLKdiv,	0x1
	.equ	Startup_PCLKdiv,	1
	
	.equ	CLK_DIV_VAL,	((Startup_ARMCLKdiv<<9)|(Startup_PREdiv<<4)|(Startup_PCLKdiv<<2)|(Startup_HCLKdiv)|(1<<3))
	.equ	MPLL_VAL,	((Startup_EPLLSTOP<<24)|(Startup_MDIV<<14)|(Startup_PDIV<<5)|(Startup_SDIV))
	.equ	EPLL_VAL,	(32<<16)|(1<<8)|(2<<0)
	

	.text
	.globl _start
_start:
	ldr	r0,=WTCON			/* watch dog disable  */
	ldr	r1,=0x0         
	str	r1,[r0]

	ldr	r0,=INTMSK1
	ldr	r1,=0xffffffff		/* all interrupt disable */
	str	r1,[r0]
	ldr	r0,=INTMSK2
	ldr	r1,=0xffffffff
	str	r1,[r0]

	ldr	r0,=INTSUBMSK
	ldr	r1,=0x7fff			/* all sub interrupt disable */
	str	r1,[r0]

	/* Set clock PLL */	
	ldr	r0,=CLKDIV0CON			/* Configure Clock Divide 	for FCLK:HCLK:PCLK  */
	ldr	r1,=CLK_DIV_VAL
	str	r1,[r0]
	
	ldr	r0,=LOCKCON0		/* Set MPLL LockTime*/
	ldr	r1,=0xe10
	str	r1,[r0]

	ldr	r0,=MPLLCON			/* Configure MPLL */
	ldr	r1,=MPLL_VAL   		/* 532MHz @ 12MHz */
	str	r1,[r0]
	
	ldr	r0,=LOCKCON1		/*Set EPLL LockTime*/
	ldr	r1, =0x1780
	str	r1, [r0]
	
	ldr	r0,=EPLLCON			/*Set EPLL*/
	ldr	r1, =EPLL_VAL		
	str	r1, [r0]
	
	ldr	r0,=CLKSRCCON		/* set CLKSRC to fit MPLL and USB */
	ldr	r1, [r0]
	orr	r1, r1, #0x50
	str	r1, [r0]
	
	/* *** Test 3개의 LED중 가운데 LED만 ON 시킴 ***
	 * 비트 연산으로 원하는 비트들만 0, 1로 만드는 방법 
	 * bic : 비트 clear 명령 => bic r1,r2,#0x1  => r1 = r2 & ~(0x1)
	 * orr : 비트 set 명령 => orr r1,r2,#0x1  => r1 = r2 | 0x1
	 */

	/* Make LED2(GPG5) to LOW
	 * Configure LED2(GPG5) as OUTPUT
	 */	

//	 Make LED2(GPG5) to LOW
		
	ldr r0, =GPGDAT 
	ldr r1, [r0]
	bic r1, r1, #0x20
	str r1, [r0]

//	Configure LED2(GPG5) as OUTPUT
	
	ldr r0, =GPGCON
	ldr r1, [r0]
	bic r1, r1, #0xc00
	orr r1, r1, #0x400
	str r1, [r0]
	
0:
	b  0b