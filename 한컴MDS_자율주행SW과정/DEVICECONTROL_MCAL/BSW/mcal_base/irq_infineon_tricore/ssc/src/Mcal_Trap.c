/******************************************************************************
**                                                                           **
** Copyright (C) Infineon Technologies (2013)                                **
**                                                                           **
** All rights reserved.                                                      **
**                                                                           **
** This document contains proprietary information belonging to Infineon      **
** Technologies. Passing on and copying of this document, and communication  **
** of its contents is not permitted without prior written authorization.     **
**                                                                           **
*******************************************************************************
**                                                                           **
**  $FILENAME   : Mcal_Trap.c $                                              **
**                                                                           **
**  $CC VERSION : \main\23 $                                                 **
**                                                                           **
**  $DATE       : 2015-11-10 $                                               **
**                                                                           **
**  AUTHOR      : DL-AUTOSAR-Engineering                                     **
**                                                                           **
**  VENDOR      : Infineon Technologies                                      **
**                                                                           **
**  DESCRIPTION : This file contains                                         **
**                - Trap functionality (only for illustration purpose)       **
**                                                                           **
**  MAY BE CHANGED BY USER [yes/no]: Yes                                     **
**                                                                           **
******************************************************************************/

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/

/* Inclusion of Platform_Types.h and Compiler.h */
#include "Std_Types.h"
/* Inclusion of Tasking sfr file */
#include "IfxScu_reg.h"
#include "IfxCpu_reg.h"
#include "Mcal.h"
#include "Test_Print.h"
#include "Mcal_Options.h"

/********************************************************************************
**                      Imported Compiler Switch Check                        **
*******************************************************************************/

/********************************************************************************
**                      Private Macro Definitions                             **
*******************************************************************************/
#ifdef _TASKING_C_TRICORE_
#if (_TASKING_C_TRICORE_ == 1U)
#define DEBUG()  __debug()
#endif /* #if (_TASKING_C_TRICORE_ == 1U) */
#endif

#ifdef _GNU_C_TRICORE_
#if (_GNU_C_TRICORE_ == 1U)
#define DEBUG() __asm__ volatile ("debug")
#endif /* #if (_GNU_C_TRICORE_ == 1U) */
#endif

#ifdef _DIABDATA_C_TRICORE_
#if (_DIABDATA_C_TRICORE_ == 1U)
#define DEBUG() __debug()
#define __debug _debug
#endif /* #if (_DIABDATA_C_TRICORE_ == 1U) */
#endif

/********************************************************************************
**                      Private Type Definitions                              **
*******************************************************************************/

/********************************************************************************
**                      Private Function Declarations                         **
*******************************************************************************/

/********************************************************************************
**                      Global Constant Definitions                           **
*******************************************************************************/

/********************************************************************************
**                      Global Variable Definitions                           **
*******************************************************************************/
volatile uint32 MtlTrapTst_Unexpected_Trap_Count;
/********************************************************************************
**                      Private Constant Definitions                          **
*******************************************************************************/

/********************************************************************************
**                      Private Variable Definitions                          **
*******************************************************************************/
#if (IFX_MCAL_USED == STD_ON)
#define MCAL_TRAP_START_SEC_VAR_32BIT
#include "MemMap.h"
#else
#define IFX_MCAL_TRAP_START_SEC_VAR_32BIT_ASIL_B
#include "Ifx_MemMap.h"
#endif
static uint32 UVALCON0;
static uint32 TrapIdentification[8][8];
#if (IFX_MCAL_USED == STD_ON)
#define MCAL_TRAP_STOP_SEC_VAR_32BIT
#include "MemMap.h"
#else
#define IFX_MCAL_TRAP_STOP_SEC_VAR_32BIT_ASIL_B
#include "Ifx_MemMap.h"
#endif


/********************************************************************************
**                      Private Function Definitions                          **
*******************************************************************************/
#if (IFX_MCAL_USED == STD_ON)
#define MCAL_TRAP_START_SEC_CODE_CPU0_TRAP
#include "MemMap.h"
#else
#define IFX_MCAL_TRAP_START_SEC_CODE_CPU0_TRAP_ASIL_B
#include "Ifx_MemMap.h"
#endif
void cpu0_trap_0 (void);
#if (IFX_MCAL_USED == STD_ON)
#define MCAL_TRAP_STOP_SEC_CODE_CPU0_TRAP
#include "MemMap.h"
#else
#define IFX_MCAL_TRAP_STOP_SEC_CODE_CPU0_TRAP_ASIL_B
#include "Ifx_MemMap.h"
#endif

#if (IFX_MCAL_USED == STD_ON)
#define MCAL_TRAP_START_SEC_CODE_CPU1_TRAP
#include "MemMap.h"
#else
#define IFX_MCAL_TRAP_START_SEC_CODE_CPU1_TRAP_ASIL_B
#include "Ifx_MemMap.h"
#endif
void cpu1_trap_0 (void);
#if (IFX_MCAL_USED == STD_ON)
#define MCAL_TRAP_STOP_SEC_CODE_CPU1_TRAP
#include "MemMap.h"
#else
#define IFX_MCAL_TRAP_STOP_SEC_CODE_CPU1_TRAP_ASIL_B
#include "Ifx_MemMap.h"
#endif

#if ( MCAL_NO_OF_CORES == 3U )
#if (IFX_MCAL_USED == STD_ON)
#define MCAL_TRAP_START_SEC_CODE_CPU2_TRAP
#include "MemMap.h"
#else
#define IFX_MCAL_TRAP_START_SEC_CODE_CPU2_TRAP_ASIL_B
#include "Ifx_MemMap.h"
#endif
void cpu2_trap_0 (void);
#if (IFX_MCAL_USED == STD_ON)
#define MCAL_TRAP_STOP_SEC_CODE_CPU2_TRAP
#include "MemMap.h"
#else
#define IFX_MCAL_TRAP_STOP_SEC_CODE_CPU2_TRAP_ASIL_B
#include "Ifx_MemMap.h"
#endif
#endif

#if (IFX_MCAL_USED == STD_ON)
#define MCAL_TRAP_START_SEC_CODE
#include "MemMap.h"
#else
#define IFX_MCAL_TRAP_START_SEC_CODE_ASIL_B
#include "Ifx_MemMap.h"
#endif

void _trap_0( void );
void _trap_1( void );
void _trap_2( void );
void _trap_3( void );
void _trap_4( void );
void _trap_5( void );
void _trap_6( void );
void _trap_7( void );




/********************************************************************************
**                      Global Function Definitions                           **
*******************************************************************************/

/******************************************************************************
** Syntax : void _trap_0( void )                                             **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Sample Service for  class 0 trap                            **
**                                                                           **
*****************************************************************************/
/* Trap class 0 handler. */
void _trap_0( void )
{
  uint32 tin;

  __asm ("svlcx");

  __GETTIN (tin);


  TrapIdentification[0][tin] = 1;
  switch(tin)
   {
     case 0:
          print_f("\nClass 0: Virtual Address Fill Trap occurred\n");
          get_char();

          break;

     case 1:
          print_f("\nClass 0: Virtual Address Protection Trap occurred\n");
          get_char();

          break;

     default:
          /* Halt the execution if debug mode enabled.*/
          DEBUG();
          break;
   }
  __asm ("rslcx \n");
  __asm ("rfe \n");
}
/******************************************************************************
** Syntax : void _trap_1( void )                                             **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Sample handler for  class 1 trap                            **
**                                                                           **
*****************************************************************************/
/* Trap class 1 handler. */
void _trap_1( void )
{
  uint32 tin;

  __asm ("svlcx");

  __GETTIN (tin);

  TrapIdentification[1][tin] = 1;
  switch(tin)
   {
     case 1:
          print_f("\nClass 1: Privilege Instruction Trap occurred\n");
          get_char();

          break;

     case 2:
          print_f("\nClass 1: Memory Protection Read Trap occurred\n");
          get_char();

          break;

     case 3:
          print_f("\nClass 1: Memory Protection Write Trap occurred\n");
          get_char();

          break;

     case 4:
          print_f("\nClass 1: Memory Protection Execution Trap occurred\n");
          get_char();

          break;

     case 5:
          print_f("\nClass 1: Memory Protection Peripheral Access Trap occurred\n");
          get_char();

          break;

     case 6:
          print_f("\nClass 1: Memory Protection Null Address Trap occurred\n");
          get_char();
          break;

     case 7:
          print_f("\nClass 1: Global Register Write Protection Trap occurred\n");
          get_char();

          break;


     default:
          /* Halt the execution if debug mode enabled.*/
          DEBUG();
          break;
   }
  __asm ("rslcx\n");
  __asm ("rfe \n");
}
/******************************************************************************
** Syntax : void _trap_2( void )                                             **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Sample handler for  class 2 trap                            **
**                                                                           **
*****************************************************************************/
/* Trap class 2 handler. */
void _trap_2( void )
{
  uint32 tin;

  __asm ("svlcx");

  __GETTIN (tin);

  TrapIdentification[2][tin] = 1;
  switch(tin)
   {
     case 1:
          print_f("\nClass 2: Illegal Opcode Trap occurred\n");
          get_char();

          break;

     case 2:
          print_f("\nClass 2: Unimplemented Opcode Trap occurred\n");
          get_char();

          break;

     case 3:
          print_f("\nClass 2: Invalid Operand Specification Trap occurred\n");
          get_char();

          break;

     case 4:
          print_f("\nClass 2: Data Address Alignment Trap occurred\n");
          get_char();

          break;

     case 5:
          print_f("\nClass 2: Invalid Local Memory Address Trap occurred\n");
          get_char();

          break;

     default:
          /* Halt the execution if debug mode enabled.*/
          DEBUG();
          break;
   }
  __asm ("rslcx \n");
  __asm ("rfe \n");
}
/******************************************************************************
** Syntax : void _trap_3( void )                                             **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Sample handler for  class 3 trap                            **
**                                                                           **
*****************************************************************************/

/* Trap class 3 handler. */
void _trap_3( void )
{
  /* No local variables used in this function */
  /* No function calls to be performed */
  uint32 tin;

  __asm ("svlcx");

  __GETTIN (tin);

  TrapIdentification[3][tin] = 1;

    UVALCON0  = (uint32) SCU_WDTCPU0_CON0.U;
    SCU_WDTCPU0_CON0.U = SCU_WDTCPU0_CON0.U & ~0x00000001 ;

    UVALCON0 |=  0x000000F1;       /*  set HWPW1 = 1111b */
    UVALCON0 &= ~0x00000002;       /*  set WDTLCK = 0 */
    UVALCON0 &= ~0x0000000C;       /*  set HWPW0 = 00b */

    SCU_WDTCPU0_CON0.U =  UVALCON0;          /*  unlock access */

    SCU_WDTCPU0_CON0.U  |=  0x000000F2;      /*  set HWPW1 = 1111b and WDTLCK = 1 */
    SCU_WDTCPU0_CON0.U  &= ~0x0000000C;      /*  set HWPW0 = 00b */
  switch(tin)
  {
     case 1:
         /* Free context list depletion trap */
     case 2:
         /* Call depth overflow trap occurred */

     case 3:
         /* Call depth underflow trap occurred */
     case 4:
         /* Free context list underflow trap */
     case 5:
         /* call stack underflow trap */
     case 6:
         /* context type trap */
     case 7:
         /* Nesting error */
         /* Perform reset */
         SCU_SWRSTCON.B.SWRSTREQ = 1U;
         break;
     default:
          /* Halt the execution if debug mode enabled.*/
          DEBUG();
          break;
  }
  __asm ("rslcx \n");
  __asm ("rfe \n");

/* The return statement here intentionally removed because compiler will
   generate SVLCX instruction in the begining of trap3 handler which again
   results in trap3 because there is no free CSA, so the warning generated by
   compiler here should be ignored */
}

/******************************************************************************
** Syntax : void _trap_4( void )                                             **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Sample handler for  class 4 trap                            **
**                                                                           **
*****************************************************************************/
/* Trap class 4 handler. */
void _trap_4( void )
{
  uint32 tin;

  __asm ("svlcx\n");

  __GETTIN (tin);

  TrapIdentification[4][tin] = 1;
  switch(tin)
   {
     case 1:
          print_f("\nClass 4: Program Fetch Synchronous Error Trap occurred\n");
          get_char();

          break;

     case 2:
          print_f("\nClass 4: Data Access Synchronous Error Trap occurred\n");
          get_char();

          break;

     case 3:
          print_f("\nClass 4: Data Access Asynchronous Error Trap occurred\n");
          get_char();

          break;

     default:
          /* Halt the execution if debug mode enabled.*/
          DEBUG();
          break;
   }
  __asm ("rslcx \n");
  __asm ("rfe \n");
}
/******************************************************************************
** Syntax : void _trap_5( void )                                             **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Sample handler for  class 5 trap                            **
**                                                                           **
*****************************************************************************/
/* Trap class 5 handler. */
void _trap_5( void )
{
  uint32 tin;

  __asm ("svlcx");

  __GETTIN (tin);

  TrapIdentification[5][tin] = 1;
  switch(tin)
   {
     case 1:
          print_f("\nClass 5: Arithemetic Overflow Trap occurred\n");
          get_char();

          break;

     case 2:
          print_f("\nClass 5: Sticky Arithemetic Overflow Trap occurred\n");
          get_char();

          break;

     default:
          /* Halt the execution if debug mode enabled.*/
          DEBUG();
          break;
   }
  __asm ("rslcx \n");
  __asm ("rfe \n");
}

/******************************************************************************
** Syntax : void _trap_6( void )                                             **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Sample handler for  class 6 trap                            **
**                                                                           **
*****************************************************************************/

/* *INDENT-OFF* */


/* Trap class 6 handler. */
void _trap_6( void )
{

    uint8 tin;
  __asm ("svlcx");

  __GETTIN (tin);

  /* TIN can be any number between 0 and 255.
   * storing the tin number in
   * TrapIdentification[6][0]
   */
  TrapIdentification[6][0] = tin;
  #if defined IFX_MCAL_RUN_MODE_DEFINE
  #if (IFX_MCAL_RUN_MODE_DEFINE != (0U))

  if ((MCAL_TIN_NO_ENDINIT == tin) || (MCAL_TIN_CPU_ENDINIT == tin)|| \
                                              (MCAL_TIN_SAFETY_ENDINIT == tin))
  {
    #if defined _DIABDATA_C_TRICORE_
    #if (_DIABDATA_C_TRICORE_ == 1U)

    uint32 TempAddress;
    #endif
    /*if defined _DIABDATA_C_TRICORE_*/
    #endif
    /*if (_DIABDATA_C_TRICORE_ == 1U)*/
    uint32 *SFR;
    uint32 SetMask;
    uint32 ClearMask;

    #ifdef _TASKING_C_TRICORE_
    #if (_TASKING_C_TRICORE_ == 1U)
      __asm("mov.aa %0,a4" : "=a"(SFR));
      __asm("mov %0,d4" : "=d"(SetMask));
      __asm("mov %0,d5" : "=d"(ClearMask));
    #endif
    #elif defined _GNU_C_TRICORE_
    #if (_GNU_C_TRICORE_ == 1U)
      __asm__("mov.aa %0,%%a4" : "=a"(SFR));
      __asm__("mov %0,%%d4" : "=d"(SetMask));
      __asm__("mov %0,%%d5" : "=d"(ClearMask));
    #endif
    #elif defined _DIABDATA_C_TRICORE_
    #if (_DIABDATA_C_TRICORE_ == 1U)

      GET_ADDRESS_REG(a4,TempAddress);
      GET_DATA_REG(d4,SetMask);
      GET_DATA_REG(d5,ClearMask);
      SFR = (uint32 * )TempAddress;

    #endif
    #endif

    Mcal_SVModeExecution(SFR,SetMask,ClearMask,tin);

  }
  else
  #endif
  #endif
  {
    print_f("\nClass 6: System Call Trap occurred\n");
    get_char();
  }

  __asm ("rslcx \n");
  __asm ("rfe \n");
}

/******************************************************************************
** Syntax : void _trap_7( void )                                             **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Sample handler for  class 7 trap                            **
**                                                                           **
*****************************************************************************/

/* Trap class 7 handler. */
void _trap_7( void )
{
  uint32 tin;

  __asm ("svlcx");
  __GETTIN (tin);

  TrapIdentification[7][tin] = 1;
  switch(tin)
   {
     case 0:
          print_f("\nClass 7: Non-Maskable Interrupt Trap occurred\n");
          get_char();

          break;

     default:
          /* Halt the execution if debug mode enabled.*/
          DEBUG();
          break;
   }
  __asm ("rslcx \n");
  __asm ("rfe \n");
}

#if (IFX_MCAL_USED == STD_ON)
#define MCAL_TRAP_STOP_SEC_CODE
#include "MemMap.h"
#else
#define IFX_MCAL_TRAP_STOP_SEC_CODE_ASIL_B
#include "Ifx_MemMap.h"
#endif

#if (IFX_MCAL_USED == STD_ON)
#define MCAL_TRAP_START_SEC_CODE_CPU0_TRAP
#include "MemMap.h"
#else
#define IFX_MCAL_TRAP_START_SEC_CODE_CPU0_TRAP_ASIL_B
#include "Ifx_MemMap.h"
#endif
/******************************************************************************
** Syntax : void cpu0_trap_0 (void)                                          **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Sample handler for  Cpu0 trap                               **
**                                                                           **
*****************************************************************************/

#ifdef __TASKING__

void cpu0_trap_0 (void)
{
  __asm (".align 256");
  /* Class 0, MMU Traps: */
  __asm("j       _trap_0");/*  Jump to the trap handler */

  __asm (".align 32");
    /* Class 1, Internal Protection Traps */
  __asm("j       _trap_1");/*  Jump to the trap handler */

  __asm (".align 32");
  /* Class 2, Instruction Error Traps */
  __asm("j       _trap_2");/*  Jump to the trap handler */

  __asm (".align 32");
  /* Class 3, Context Management Traps */
  __asm("j       _trap_3");/*  Jump to the trap handler   */

  __asm (".align 32");
  /* Class 4, System Bus and Peripheral Error Traps */
  __asm("j       _trap_4");/*  Jump to the trap handler   */

  __asm (".align 32");
  /* Class 5, Assertion Traps */
  __asm("j       _trap_5");/*  Jump to the trap handler     */

  __asm (".align 32");
  /* Class 6, System Call Trap */
  __asm("j       _trap_6");/*  Jump to the trap handler     */

 __asm (".align 32");
  /* Class 7, Non Maskable Interrupt Traps */
  __asm("j       _trap_7");/*  Jump to the trap handler       */
}
#endif /* __TASKING__ */

#ifdef __GNUC__
void cpu0_trap_0 (void)
{
 /* ; Special trap table used during the Trap test: */

  /* ; Class 0, MMU Traps: */
  __asm (".align 8");
  __asm("j       _trap_0"); /*        ; Jump to the trap handler */

  /* ; Class 1, Internal Protection Traps: */
  __asm(".align 5");
  __asm("j       _trap_1"); /*        ; Jump to the trap handler */

  /* ; Class 2, Instruction Error Traps: */
  __asm(".align 5");
  __asm("j       _trap_2"); /*        ; Jump to the trap handler */

  /* ; Class 3, Context Management Traps: */
  __asm(".align 5");
  __asm("j       _trap_3"); /*        ; Jump to the trap handler */

  /* ; Class 4, System Bus and Peripheral Error Traps: */
  __asm(".align 5");
  __asm("j       _trap_4"); /*        ; Jump to the trap handler */

  /* ; Class 5, Assertion Traps: */
  __asm(".align 5");
  __asm("j       _trap_5"); /*        ; Jump to the trap handler */

  /* ; Class 6, System Call Trap: */
  __asm(".align 5");
  __asm("j       _trap_6"); /*        ; Jump to the trap handler */

  /* ; Class 7, Non Maskable Interrupt Traps: */
  __asm(".align 5");
  __asm("j       _trap_7"); /*        ; Jump to the trap handler */

}
#endif /* __GNUC__ */

#ifdef _DIABDATA_C_TRICORE_
void cpu0_trap_0 (void)
{
   /* ; Special trap table used during the Trap test: */

  /* ; Class 0, MMU Traps: */
  __asm (".align 8");
  __asm("j       _trap_0"); /*        ; Jump to the trap handler */

  /* ; Class 1, Internal Protection Traps: */
  __asm(".align 5");
  __asm("j       _trap_1"); /*        ; Jump to the trap handler */

  /* ; Class 2, Instruction Error Traps: */
  __asm(".align 5");
  __asm("j       _trap_2"); /*        ; Jump to the trap handler */

  /* ; Class 3, Context Management Traps: */
  __asm(".align 5");
  __asm("j       _trap_3"); /*        ; Jump to the trap handler */

  /* ; Class 4, System Bus and Peripheral Error Traps: */
  __asm(".align 5");
  __asm("j       _trap_4"); /*        ; Jump to the trap handler */

  /* ; Class 5, Assertion Traps: */
  __asm(".align 5");
  __asm("j       _trap_5"); /*        ; Jump to the trap handler */

  /* ; Class 6, System Call Trap: */
  __asm(".align 5");
  __asm("j       _trap_6"); /*        ; Jump to the trap handler */

  /* ; Class 7, Non Maskable Interrupt Traps: */
  __asm(".align 5");
  __asm("j       _trap_7"); /*        ; Jump to the trap handler */

}

#endif /* _DIABDATA_C_TRICORE_ */


#if (IFX_MCAL_USED == STD_ON)
#define MCAL_TRAP_STOP_SEC_CODE_CPU0_TRAP
#include "MemMap.h"
#else
#define IFX_MCAL_TRAP_STOP_SEC_CODE_CPU0_TRAP_ASIL_B
#include "Ifx_MemMap.h"
#endif

#if (IFX_MCAL_USED == STD_ON)
#define MCAL_TRAP_START_SEC_CODE_CPU1_TRAP
#include "MemMap.h"
#else
#define IFX_MCAL_TRAP_START_SEC_CODE_CPU1_TRAP_ASIL_B
#include "Ifx_MemMap.h"
#endif
/******************************************************************************
** Syntax : void cpu1_trap_0 (void)                                          **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Sample handler for  Cpu1 trap                               **
**                                                                           **
*****************************************************************************/

#ifdef __TASKING__

void cpu1_trap_0 (void)
{
  __asm (".align 256");
  /* Class 0, MMU Traps: */
  __asm("j       _trap_0");/*  Jump to the trap handler */

  __asm (".align 32");
    /* Class 1, Internal Protection Traps */
  __asm("j       _trap_1");/*  Jump to the trap handler */

  __asm (".align 32");
  /* Class 2, Instruction Error Traps */
  __asm("j       _trap_2");/*  Jump to the trap handler */

  __asm (".align 32");
  /* Class 3, Context Management Traps */
  __asm("j       _trap_3");/*  Jump to the trap handler   */

  __asm (".align 32");
  /* Class 4, System Bus and Peripheral Error Traps */
  __asm("j       _trap_4");/*  Jump to the trap handler   */

  __asm (".align 32");
  /* Class 5, Assertion Traps */
  __asm("j       _trap_5");/*  Jump to the trap handler     */

  __asm (".align 32");
  /* Class 6, System Call Trap */
  __asm("j       _trap_6");/*  Jump to the trap handler     */

 __asm (".align 32");
  /* Class 7, Non Maskable Interrupt Traps */
  __asm("j       _trap_7");/*  Jump to the trap handler       */
}
#endif /* __TASKING__ */

#ifdef __GNUC__
void cpu1_trap_0 (void)
{
 /* ; Special trap table used during the Trap test: */

  /* ; Class 0, MMU Traps: */
  __asm (".align 8");
  __asm("j       _trap_0"); /*        ; Jump to the trap handler */

  /* ; Class 1, Internal Protection Traps: */
  __asm(".align 5");
  __asm("j       _trap_1"); /*        ; Jump to the trap handler */

  /* ; Class 2, Instruction Error Traps: */
  __asm(".align 5");
  __asm("j       _trap_2"); /*        ; Jump to the trap handler */

  /* ; Class 3, Context Management Traps: */
  __asm(".align 5");
  __asm("j       _trap_3"); /*        ; Jump to the trap handler */

  /* ; Class 4, System Bus and Peripheral Error Traps: */
  __asm(".align 5");
  __asm("j       _trap_4"); /*        ; Jump to the trap handler */

  /* ; Class 5, Assertion Traps: */
  __asm(".align 5");
  __asm("j       _trap_5"); /*        ; Jump to the trap handler */

  /* ; Class 6, System Call Trap: */
  __asm(".align 5");
  __asm("j       _trap_6"); /*        ; Jump to the trap handler */

  /* ; Class 7, Non Maskable Interrupt Traps: */
  __asm(".align 5");
  __asm("j       _trap_7"); /*        ; Jump to the trap handler */

}
#endif /* __GNUC__ */

#ifdef _DIABDATA_C_TRICORE_
void cpu1_trap_0 (void)
{
   /* ; Special trap table used during the Trap test: */

  /* ; Class 0, MMU Traps: */
  __asm (".align 8");
  __asm("j       _trap_0"); /*        ; Jump to the trap handler */

  /* ; Class 1, Internal Protection Traps: */
  __asm(".align 5");
  __asm("j       _trap_1"); /*        ; Jump to the trap handler */

  /* ; Class 2, Instruction Error Traps: */
  __asm(".align 5");
  __asm("j       _trap_2"); /*        ; Jump to the trap handler */

  /* ; Class 3, Context Management Traps: */
  __asm(".align 5");
  __asm("j       _trap_3"); /*        ; Jump to the trap handler */

  /* ; Class 4, System Bus and Peripheral Error Traps: */
  __asm(".align 5");
  __asm("j       _trap_4"); /*        ; Jump to the trap handler */

  /* ; Class 5, Assertion Traps: */
  __asm(".align 5");
  __asm("j       _trap_5"); /*        ; Jump to the trap handler */

  /* ; Class 6, System Call Trap: */
  __asm(".align 5");
  __asm("j       _trap_6"); /*        ; Jump to the trap handler */

  /* ; Class 7, Non Maskable Interrupt Traps: */
  __asm(".align 5");
  __asm("j       _trap_7"); /*        ; Jump to the trap handler */

}

#endif /* _DIABDATA_C_TRICORE_ */


#if (IFX_MCAL_USED == STD_ON)
#define MCAL_TRAP_STOP_SEC_CODE_CPU1_TRAP
#include "MemMap.h"
#else
#define IFX_MCAL_TRAP_STOP_SEC_CODE_CPU1_TRAP_ASIL_B
#include "Ifx_MemMap.h"
#endif

#if ( MCAL_NO_OF_CORES == 3U )

#if (IFX_MCAL_USED == STD_ON)
#define MCAL_TRAP_START_SEC_CODE_CPU2_TRAP
#include "MemMap.h"
#else
#define IFX_MCAL_TRAP_START_SEC_CODE_CPU2_TRAP_ASIL_B
#include "Ifx_MemMap.h"
#endif
/******************************************************************************
** Syntax : void cpu2_trap_0 (void)                                          **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Sample handler for  Cpu2 trap                               **
**                                                                           **
*****************************************************************************/
#ifdef __TASKING__

void cpu2_trap_0 (void)
{
  __asm (".align 256");
  /* Class 0, MMU Traps: */
  __asm("j       _trap_0");/*  Jump to the trap handler */

  __asm (".align 32");
    /* Class 1, Internal Protection Traps */
  __asm("j       _trap_1");/*  Jump to the trap handler */

  __asm (".align 32");
  /* Class 2, Instruction Error Traps */
  __asm("j       _trap_2");/*  Jump to the trap handler */

  __asm (".align 32");
  /* Class 3, Context Management Traps */
  __asm("j       _trap_3");/*  Jump to the trap handler   */

  __asm (".align 32");
  /* Class 4, System Bus and Peripheral Error Traps */
  __asm("j       _trap_4");/*  Jump to the trap handler   */

  __asm (".align 32");
  /* Class 5, Assertion Traps */
  __asm("j       _trap_5");/*  Jump to the trap handler     */

  __asm (".align 32");
  /* Class 6, System Call Trap */
  __asm("j       _trap_6");/*  Jump to the trap handler     */

 __asm (".align 32");
  /* Class 7, Non Maskable Interrupt Traps */
  __asm("j       _trap_7");/*  Jump to the trap handler       */
}
#endif /* __TASKING__ */

#ifdef __GNUC__
void cpu2_trap_0 (void)
{
 /* ; Special trap table used during the Trap test: */

  /* ; Class 0, MMU Traps: */
  __asm (".align 8");
  __asm("j       _trap_0"); /*        ; Jump to the trap handler */

  /* ; Class 1, Internal Protection Traps: */
  __asm(".align 5");
  __asm("j       _trap_1"); /*        ; Jump to the trap handler */

  /* ; Class 2, Instruction Error Traps: */
  __asm(".align 5");
  __asm("j       _trap_2"); /*        ; Jump to the trap handler */

  /* ; Class 3, Context Management Traps: */
  __asm(".align 5");
  __asm("j       _trap_3"); /*        ; Jump to the trap handler */

  /* ; Class 4, System Bus and Peripheral Error Traps: */
  __asm(".align 5");
  __asm("j       _trap_4"); /*        ; Jump to the trap handler */

  /* ; Class 5, Assertion Traps: */
  __asm(".align 5");
  __asm("j       _trap_5"); /*        ; Jump to the trap handler */

  /* ; Class 6, System Call Trap: */
  __asm(".align 5");
  __asm("j       _trap_6"); /*        ; Jump to the trap handler */

  /* ; Class 7, Non Maskable Interrupt Traps: */
  __asm(".align 5");
  __asm("j       _trap_7"); /*        ; Jump to the trap handler */

}
#endif /* __GNUC__ */

#ifdef _DIABDATA_C_TRICORE_
void cpu2_trap_0 (void)
{
   /* ; Special trap table used during the Trap test: */

  /* ; Class 0, MMU Traps: */
  __asm (".align 8");
  __asm("j       _trap_0"); /*        ; Jump to the trap handler */

  /* ; Class 1, Internal Protection Traps: */
  __asm(".align 5");
  __asm("j       _trap_1"); /*        ; Jump to the trap handler */

  /* ; Class 2, Instruction Error Traps: */
  __asm(".align 5");
  __asm("j       _trap_2"); /*        ; Jump to the trap handler */

  /* ; Class 3, Context Management Traps: */
  __asm(".align 5");
  __asm("j       _trap_3"); /*        ; Jump to the trap handler */

  /* ; Class 4, System Bus and Peripheral Error Traps: */
  __asm(".align 5");
  __asm("j       _trap_4"); /*        ; Jump to the trap handler */

  /* ; Class 5, Assertion Traps: */
  __asm(".align 5");
  __asm("j       _trap_5"); /*        ; Jump to the trap handler */

  /* ; Class 6, System Call Trap: */
  __asm(".align 5");
  __asm("j       _trap_6"); /*        ; Jump to the trap handler */

  /* ; Class 7, Non Maskable Interrupt Traps: */
  __asm(".align 5");
  __asm("j       _trap_7"); /*        ; Jump to the trap handler */

}

#endif /* _DIABDATA_C_TRICORE_ */

#if (IFX_MCAL_USED == STD_ON)
#define MCAL_TRAP_STOP_SEC_CODE_CPU2_TRAP
#include "MemMap.h"
#else
#define IFX_MCAL_TRAP_STOP_SEC_CODE_CPU2_TRAP_ASIL_B
#include "Ifx_MemMap.h"
#endif

#endif /* ( MCAL_NO_OF_CORES == 3U ) */

