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
**  $FILENAME   : EcuM_Cbk.h $                                               **
**                                                                           **
**  $CC VERSION : \main\4 $                                                  **
**                                                                           **
**  $DATE       : 2013-06-27 $                                               **
**                                                                           **
**  AUTHOR      : DL-AUTOSAR-Engineering                                     **
**                                                                           **
**  VENDOR      : Infineon Technologies                                      **
**                                                                           **
**  DESCRIPTION  : This file provides ECUM callback/callout declarations     **
**                 This file is for Evaluation Purpose Only                  **
**                                                                           **
**  MAY BE CHANGED BY USER [yes/no]: Yes                                     **
**                                                                           **
******************************************************************************/
 
#ifndef ECUMCBK_H
#define ECUMCBK_H

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
 
/*******************************************************************************
**                      Global Macro Definitions                              **
*******************************************************************************/

/*******************************************************************************
**                      Global Type Definitions                               **
*******************************************************************************/
/* Used in Gpt, Icu Modules */
typedef uint32 EcuM_WakeupSourceType;

/*******************************************************************************
**                      Global Constant Declarations                          **
*******************************************************************************/

/*******************************************************************************
**                      Global Variable Declarations                          **
*******************************************************************************/

/*******************************************************************************
**                      Global Function Declarations                          **
*******************************************************************************/

/* Wake Up Related APIs. Used in Gpt,Icu, Can Drivers */

extern void EcuM_SetWakeupEvent
(
      EcuM_WakeupSourceType events
);

extern void EcuM_ValidateWakeupEvent
(
      EcuM_WakeupSourceType events
);

extern void EcuM_CheckWakeup
(
      EcuM_WakeupSourceType wakeupSource
);
#endif   /* #ifndef ECUMCBK_H  */
