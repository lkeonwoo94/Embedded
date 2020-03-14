/*******************************************************************************
**                                                                            **
** Copyright (C) Infineon Technologies (2011)                                 **
**                                                                            **
** All rights reserved.                                                       **
**                                                                            **
** This document contains proprietary information belonging to Infineon       **
** Technologies. Passing on and copying of this document, and communication   **
** of its contents is not permitted without prior written authorization.      **
**                                                                            **
********************************************************************************
**                                                                            **
**  FILENAME  : Dem_PBcfg.h                                                   **
**                                                                            **
**  VERSION   : 1.0.1                                                         **
**                                                                            **
**  DATE, TIME: 2016-05-03, 16:08:40                                          **
**                                                                            **
**  GENERATOR : Build b120625-0327                                            **
**                                                                            **
**  BSW MODULE DESCRIPTION : Dem.xdm                                          **
**                                                                            **
**  VARIANT   : VariantPB                                                     **
**                                                                            **
**  PLATFORM  : Infineon Aurix                                                **
**                                                                            **
**  COMPILER  : Tasking                                                       **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  DESCRIPTION  : DEM configuration generated out of ECU configuration       **
**                 file                                                       **
**                                                                            **
**  SPECIFICATION(S) : AUTOSAR_SWS_DiagnosticEventManager, Release-4.0, 4.1.0 **
**                                                                            **
**  MAY BE CHANGED BY USER [yes/no]: yes                                      **
**                                                                            **
*******************************************************************************/

#ifndef DEM_PBCFG_H
#define DEM_PBCFG_H

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/

/*******************************************************************************
**                      Global Macro Definitions                              **
*******************************************************************************/

/* Assignment of Event Id values for the Symbols */
#define DemConf_DemEventParameter_FLS_COMPARE_ERROR  (Dem_EventIdType)(1U) /* Event Id for FLS_COMPARE_ERROR */
#define DemConf_DemEventParameter_FLS_ERASE_ERROR  (Dem_EventIdType)(2U) /* Event Id for FLS_ERASE_ERROR */
#define DemConf_DemEventParameter_FLS_READ_ERROR  (Dem_EventIdType)(3U) /* Event Id for FLS_READ_ERROR */
#define DemConf_DemEventParameter_FLS_WRITE_ERROR  (Dem_EventIdType)(4U) /* Event Id for FLS_WRITE_ERROR */
#define DemConf_DemEventParameter_CAN_TIMEOUT_ERROR  (Dem_EventIdType)(5U) /* Event Id for CAN_TIMEOUT_ERROR */
#define DemConf_DemEventParameter_FEE_GC_INIT_ERROR  (Dem_EventIdType)(6U) /* Event Id for FEE_GC_INIT_ERROR */
#define DemConf_DemEventParameter_FEE_WRITE_ERROR  (Dem_EventIdType)(7U) /* Event Id for FEE_WRITE_ERROR */
#define DemConf_DemEventParameter_FEE_READ_ERROR  (Dem_EventIdType)(8U) /* Event Id for FEE_READ_ERROR */
#define DemConf_DemEventParameter_FEE_GC_WRITE_ERROR  (Dem_EventIdType)(9U) /* Event Id for FEE_GC_WRITE_ERROR */
#define DemConf_DemEventParameter_FEE_GC_READ_ERROR  (Dem_EventIdType)(10U) /* Event Id for FEE_GC_READ_ERROR */
#define DemConf_DemEventParameter_FEE_GC_ERASE_ERROR  (Dem_EventIdType)(11U) /* Event Id for FEE_GC_ERASE_ERROR */
#define DemConf_DemEventParameter_FEE_INVALIDATE_ERROR  (Dem_EventIdType)(12U) /* Event Id for FEE_INVALIDATE_ERROR */
#define DemConf_DemEventParameter_FEE_WRITE_CYCLES_EXHAUSTED_ERROR  (Dem_EventIdType)(13U) /* Event Id for FEE_WRITE_CYCLES_EXHAUSTED_ERROR */
#define DemConf_DemEventParameter_FEE_GC_TRIG_ERROR  (Dem_EventIdType)(14U) /* Event Id for FEE_GC_TRIG_ERROR */
#define DemConf_DemEventParameter_ETH_E_ACCESS  (Dem_EventIdType)(15U) /* Event Id for ETH_E_ACCESS */
#define DemConf_DemEventParameter_FEE_UNCONFIG_BLK_EXCEEDED_ERROR  (Dem_EventIdType)(16U) /* Event Id for FEE_UNCONFIG_BLK_EXCEEDED_ERROR */
#define DemConf_DemEventParameter_ETH_E_TIMEOUT  (Dem_EventIdType)(17U) /* Event Id for ETH_E_TIMEOUT */


#endif /* end of DEM_PBCFG_H */

