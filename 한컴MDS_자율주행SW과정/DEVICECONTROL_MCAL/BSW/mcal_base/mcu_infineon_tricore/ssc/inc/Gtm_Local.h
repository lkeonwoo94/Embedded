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
**  $FILENAME   : Gtm_Local.h $                                              **
**                                                                           **
**  $CC VERSION : \main\10 $                                                 **
**                                                                           **
**  $DATE       : 2015-04-15 $                                               **
**                                                                           **
**  AUTHOR      : DL-AUTOSAR-Engineering                                     **
**                                                                           **
**  VENDOR      : Infineon Technologies                                      **
**                                                                           **
**  DESCRIPTION : This file contains                                         **
**                functionality of <> driver.                                **
**                                                                           **
**  MAY BE CHANGED BY USER [yes/no]: No                                      **
**                                                                           **
******************************************************************************/

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
  /* Include Standard Types */
#include "Std_Types.h"
#include "IfxGtm_regdef.h"

/*******************************************************************************
**                      Private Function Definitions                          **
*******************************************************************************/

extern void Gtm_lAdcConnectionsConfig(void);
extern void Gtm_lTomComplexConfig(void);
extern void Gtm_lAtomComplexConfig(void);
extern void Gtm_lAtomClockSetting(void);
extern void Gtm_lTomClockSetting(void);

#if (GTM_DEINIT_API_ENABLE == STD_ON)

extern void Gtm_lResetGtmSRCReg(void);

#endif

/*******************************************************************************
**                      Global Macro Definitions                              **
*******************************************************************************/

