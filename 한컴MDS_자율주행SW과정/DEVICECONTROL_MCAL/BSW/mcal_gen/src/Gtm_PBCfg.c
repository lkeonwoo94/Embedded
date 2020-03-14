/*******************************************************************************
**                                                                            **
** Copyright (C) Infineon Technologies (2013)                                 **
**                                                                            **
** All rights reserved.                                                       **
**                                                                            **
** This document contains proprietary information belonging to Infineon       **
** Technologies. Passing on and copying of this document, and communication   **
** of its contents is not permitted without prior written authorization.      **
**                                                                            **
********************************************************************************
**                                                                            **
**  FILENAME  : Gtm_PBCfg.c                                                   **
**                                                                            **
**  $CC VERSION : \main\75 $                                                 **
**                                                                            **
**  DATE, TIME: 2016-05-14, 11:31:14                                          **
**                                                                            **
**  GENERATOR : Build b120625-0327                                            **
**                                                                            **
**  BSW MODULE DECRIPTION : Mcu.bmd                                           **
**                                                                            **
**  VARIANT   : VariantPB                                                     **
**                                                                            **
**  PLATFORM  : Infineon Aurix                                                **
**                                                                            **
**  COMPILER  : Tasking/GNU/Diab                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  DESCRIPTION  : GTM configuration generated out of ECU configuration      **
**                 file                                                       **
**                                                                            **
**  SPECIFICATION(S) : complex driver implementation                          **
**                                                                            **
**  MAY BE CHANGED BY USER [yes/no]: no                                       **
**                                                                            **
*******************************************************************************/
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
**  FILENAME  : Gtm.m                                                        **
**                                                                           **
**  $CC VERSION : \main\53 $                                                 **
**                                                                           **
**  DATE, TIME: 2016-05-14, 11:31:14                                         **
**                                                                           **
**  GENERATOR : Build b120625-0327                                           **
**                                                                           **
**  AUTHOR    : DL-AUTOSAR-Engineering                                       **
**                                                                           **
**  VENDOR    : Infineon Technologies                                        **
**                                                                           **
**  DESCRIPTION  : GTM configuration generated out of ECU configuration      **
**                 file (Mcu.bmd/.xdm)                                       **
**                                                                           **
**  MAY BE CHANGED BY USER [yes/no]: No                                      **
**                                                                           **
******************************************************************************/
/*******************************************************************************
**                                                                            **
*******************************************************************************/




/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/

/* Own header file, this includes own configuration file also */
#include "Gtm.h"



/*******************************************************************************
**                      Global Macro Definitions                              **
*******************************************************************************/
/* Note:
The user can configure the parameters with the tag Configuration:
The user should not change anything under the tag Configuration Options:
*/

/*******************************************************************************
**                      Private Macro Definitions                             **
*******************************************************************************/
#define GTM_INTERRUPT_LEVEL_MODE          (0U)
#define GTM_INTERRUPT_PULSE_MODE          (1U)
#define GTM_INTERRUPT_PULSE_NOTIFY_MODE   (2U) 
#define GTM_INTERRUPT_SINGLE_PULSE_MODE   (3U)

#define TSPP1_SUBUNIT_OUTPUT 5

/* For Tbu */
#define BITS_0_TO_23   (0U)
#define BITS_3_TO_26   (1U)
#define FREE_RUNNING_COUNTER_MODE      (0)
#define FORWARD_BACKWARD_COUNTER_MODE  (1)

/*IFX_MISRA_RULE_19_07_STATUS= Function like macros used for simplifacation of
        configuration generation and increase the readability of config file */
#define Gtm_lTbuBuildControl(Bit0, Bit123, Bit5)                              \
 (0x00U | (uint8)(Bit0) | (uint8)((uint8)(Bit123) << 1) |                     \
                                                 (uint8)((uint8)(Bit5) << 5))
                                                 
/*IFX_MISRA_RULE_19_07_STATUS=Function like macros used for simplifacation of
        configuration generation and increase the readability of config file*/
#define Gtm_lTimerCtrlValue(Word, ClockValue)                                 \
                        ((uint32)(Word) | (uint32)((uint32)(ClockValue) << 12))
                        
/*IFX_MISRA_RULE_19_07_STATUS=Function like macros used for simplifacation of
        configuration generation and increase the readability of config file*/
#define Gtm_TimbuildReg(Word, ClockValue)                                     \
                         ((uint32)(Word)| (uint32)((uint32)(ClockValue) << 24))
                         
/*IFX_MISRA_RULE_19_07_STATUS=Function like macros used for simplifacation of
        configuration generation and increase the readability of config file*/
#define Gtm_TimTduBuildReg(Word, ClockValue)                                  \
                        ((uint32)(Word) | (uint32)((uint32)(ClockValue) << 28))
                        
/*IFX_MISRA_RULE_19_07_STATUS=Function like macros used for simplifacation of
        configuration generation and increase the readability of config file*/
#define Gtm_MapBuildReg(Word, ClockValue)                                     \
                         ((uint32)(Word) | (uint32)((uint32)(ClockValue) << 1))

/*IFX_MISRA_RULE_19_07_STATUS=Function like macros used for simplifacation of
        configuration generation and increase the readability of config file*/
#define Gtm_lMoveCcuTo8Bit(Ccu1,Ccu0)                                        \
                             (((uint16)(Ccu0))| (uint16)((uint16)(Ccu1) << 8))

/* For Interrupt Mode Appending */
/*IFX_MISRA_RULE_19_07_STATUS=Function like macros used for simplifacation of
        configuration generation and increase the readability of config file*/
#define Gtm_lIncludeIntMode8Bit(Bytevalue, IrqMode)                           \
                          ((uint8)(Bytevalue) | (uint8)((uint8)(IrqMode) << 6))
                          
/*IFX_MISRA_RULE_19_07_STATUS=Function like macros used for simplifacation of
        configuration generation and increase the readability of config file*/
#define Gtm_lIncludeIntMode16Bit(Intvalue, IrqMode)                           \
                       ((uint16)(Intvalue) | (uint16)((uint16)(IrqMode) << 14))
/*IFX_MISRA_RULE_19_07_STATUS=Function like macros used for simplifacation of
        configuration generation and increase the readability of config file*/
        
#define Gtm_lIncludeIntMode32Bit(Wordvalue, IrqMode)                          \
                      ((uint32)(Wordvalue) | (uint32)((uint32)(IrqMode) << 30))

/*******************************************************************************
**                      Private Type Definitions                              **
*******************************************************************************/


/*******************************************************************************
**                      Private Function Declarations                         **
*******************************************************************************/


/*******************************************************************************
**                      Global Funtion Declarations                           **
*******************************************************************************/

/*******************************************************************************
**                      Global Constant Definitions                           **
*******************************************************************************/
#define MCU_START_SEC_POSTBUILDCFG
/*IFX_MISRA_RULE_19_01_STATUS=File inclusion after pre-processor directives is 
 allowed only for MemMap.h*/
#include "MemMap.h"


static const Gtm_GeneralConfigType Gtm_kGeneralConfig0 =
{
  0x0001U,
  Gtm_lIncludeIntMode8Bit(0U,GTM_INTERRUPT_LEVEL_MODE)
  };






static const Gtm_ModUsageConfigType Gtm_kModUsage0 =
{  
  { /*TIM Module Usage */
    
     /*TIM0 Module Usage*/   {
      GTM_TIM_CH_NOT_USEDBY_ICU,
      GTM_TIM_CH_NOT_USEDBY_ICU,
      GTM_TIM_CH_NOT_USEDBY_ICU,
      GTM_TIM_CH_NOT_USEDBY_ICU,
      GTM_TIM_CH_NOT_USEDBY_ICU,
      GTM_TIM_CH_NOT_USEDBY_ICU,
      GTM_TIM_CH_NOT_USEDBY_ICU,
      GTM_TIM_CH_NOT_USEDBY_ICU,
   },
     /*TIM1 Module Usage*/
   {
      GTM_TIM_CH_NOT_USEDBY_ICU,
      GTM_TIM_CH_NOT_USEDBY_ICU,
      GTM_TIM_CH_NOT_USEDBY_ICU,
      GTM_TIM_CH_NOT_USEDBY_ICU,
      GTM_TIM_CH_NOT_USEDBY_ICU,
      GTM_TIM_CH_NOT_USEDBY_ICU,
      GTM_TIM_CH_NOT_USEDBY_ICU,
      GTM_TIM_CH_NOT_USEDBY_ICU,
   },
     /*TIM2 Module Usage*/
   {
      GTM_TIM_CH_NOT_USEDBY_ICU,
      GTM_TIM_CH_NOT_USEDBY_ICU,
      GTM_TIM_CH_NOT_USEDBY_ICU,
      GTM_TIM_CH_NOT_USEDBY_ICU,
      GTM_TIM_CH_NOT_USEDBY_ICU,
      GTM_TIM_CH_NOT_USEDBY_ICU,
      GTM_TIM_CH_NOT_USEDBY_ICU,
      GTM_TIM_CH_NOT_USEDBY_ICU,
   },
     /*TIM3 Module Usage*/
   {
      GTM_TIM_CH_NOT_USEDBY_ICU,
      GTM_TIM_CH_NOT_USEDBY_ICU,
      GTM_TIM_CH_NOT_USEDBY_ICU,
      GTM_TIM_CH_NOT_USEDBY_ICU,
      GTM_TIM_CH_NOT_USEDBY_ICU,
      GTM_TIM_CH_NOT_USEDBY_ICU,
      GTM_TIM_CH_NOT_USEDBY_ICU,
      GTM_TIM_CH_NOT_USEDBY_ICU,
   },
  },
  {   /*TOM module Usage */
     /*TOM Module 0 Usage*/    {
      GTM_TOM_CH_NOT_USEDBY_GPT_PWM,
      GTM_TOM_CH_NOT_USEDBY_GPT_PWM,
      GTM_TOM_CH_NOT_USEDBY_GPT_PWM,
      GTM_TOM_CH_NOT_USEDBY_GPT_PWM,
      GTM_TOM_CH_NOT_USEDBY_GPT_PWM,
      GTM_TOM_CH_NOT_USEDBY_GPT_PWM,
      GTM_TOM_CH_NOT_USEDBY_GPT_PWM,
      GTM_TOM_CH_NOT_USEDBY_GPT_PWM,
      GTM_TOM_CH_NOT_USEDBY_GPT_PWM,
      GTM_TOM_CH_NOT_USEDBY_GPT_PWM,
      GTM_TOM_CH_NOT_USEDBY_GPT_PWM,
      GTM_TOM_CH_NOT_USEDBY_GPT_PWM,
      GTM_TOM_CH_NOT_USEDBY_GPT_PWM,
      GTM_TOM_CH_NOT_USEDBY_GPT_PWM,
      GTM_TOM_CH_NOT_USEDBY_GPT_PWM,
      GTM_TOM_CH_NOT_USEDBY_GPT_PWM,
    },
     /*TOM Module 1 Usage*/
    {
      GTM_TOM_CH_NOT_USEDBY_GPT_PWM,
      GTM_TOM_CH_NOT_USEDBY_GPT_PWM,
      GTM_TOM_CH_NOT_USEDBY_GPT_PWM,
      GTM_TOM_CH_NOT_USEDBY_GPT_PWM,
      GTM_TOM_CH_NOT_USEDBY_GPT_PWM,
      GTM_TOM_CH_NOT_USEDBY_GPT_PWM,
      GTM_TOM_CH_NOT_USEDBY_GPT_PWM,
      GTM_TOM_CH_NOT_USEDBY_GPT_PWM,
      GTM_TOM_CH_NOT_USEDBY_GPT_PWM,
      GTM_TOM_CH_NOT_USEDBY_GPT_PWM,
      GTM_TOM_CH_NOT_USEDBY_GPT_PWM,
      GTM_TOM_CH_NOT_USEDBY_GPT_PWM,
      GTM_TOM_CH_NOT_USEDBY_GPT_PWM,
      GTM_TOM_CH_NOT_USEDBY_GPT_PWM,
      GTM_TOM_CH_NOT_USEDBY_GPT_PWM,
      GTM_TOM_CH_NOT_USEDBY_GPT_PWM,
    },
     /*TOM Module 2 Usage*/
    {
      GTM_TOM_CH_NOT_USEDBY_GPT_PWM,
      GTM_TOM_CH_NOT_USEDBY_GPT_PWM,
      GTM_TOM_CH_NOT_USEDBY_GPT_PWM,
      GTM_TOM_CH_NOT_USEDBY_GPT_PWM,
      GTM_TOM_CH_NOT_USEDBY_GPT_PWM,
      GTM_TOM_CH_NOT_USEDBY_GPT_PWM,
      GTM_TOM_CH_NOT_USEDBY_GPT_PWM,
      GTM_TOM_CH_NOT_USEDBY_GPT_PWM,
      GTM_TOM_CH_NOT_USEDBY_GPT_PWM,
      GTM_TOM_CH_NOT_USEDBY_GPT_PWM,
      GTM_TOM_CH_NOT_USEDBY_GPT_PWM,
      GTM_TOM_CH_NOT_USEDBY_GPT_PWM,
      GTM_TOM_CH_NOT_USEDBY_GPT_PWM,
      GTM_TOM_CH_NOT_USEDBY_GPT_PWM,
      GTM_TOM_CH_NOT_USEDBY_GPT_PWM,
      GTM_TOM_CH_NOT_USEDBY_GPT_PWM,
    },
  },  {     /*ATOM module Usage */


     /*ATOM Module 0 Usage*/
   {
      GTM_ATOM_CH_NOT_USEDBY_GPT_PWM,
      GTM_ATOM_CH_NOT_USEDBY_GPT_PWM,
      GTM_ATOM_CH_NOT_USEDBY_GPT_PWM,
      GTM_ATOM_CH_NOT_USEDBY_GPT_PWM,
      GTM_ATOM_CH_NOT_USEDBY_GPT_PWM,
      GTM_ATOM_CH_NOT_USEDBY_GPT_PWM,
      GTM_ATOM_CH_NOT_USEDBY_GPT_PWM,
      GTM_ATOM_CH_NOT_USEDBY_GPT_PWM,
    },
     /*ATOM Module 1 Usage*/
   {
      GTM_ATOM_CH_NOT_USEDBY_GPT_PWM,
      GTM_ATOM_CH_NOT_USEDBY_GPT_PWM,
      GTM_ATOM_CH_NOT_USEDBY_GPT_PWM,
      GTM_ATOM_CH_NOT_USEDBY_GPT_PWM,
      GTM_ATOM_CH_NOT_USEDBY_GPT_PWM,
      GTM_ATOM_CH_NOT_USEDBY_GPT_PWM,
      GTM_ATOM_CH_NOT_USEDBY_GPT_PWM,
      GTM_ATOM_CH_NOT_USEDBY_GPT_PWM,
    },
     /*ATOM Module 2 Usage*/
   {
      GTM_ATOM_CH_NOT_USEDBY_GPT_PWM,
      GTM_ATOM_CH_NOT_USEDBY_GPT_PWM,
      GTM_ATOM_CH_NOT_USEDBY_GPT_PWM,
      GTM_ATOM_CH_NOT_USEDBY_GPT_PWM,
      GTM_ATOM_CH_NOT_USEDBY_GPT_PWM,
      GTM_ATOM_CH_NOT_USEDBY_GPT_PWM,
      GTM_ATOM_CH_NOT_USEDBY_GPT_PWM,
      GTM_ATOM_CH_NOT_USEDBY_GPT_PWM,
    },
     /*ATOM Module 3 Usage*/
   {
      GTM_ATOM_CH_NOT_USEDBY_GPT_PWM,
      GTM_ATOM_CH_NOT_USEDBY_GPT_PWM,
      GTM_ATOM_CH_NOT_USEDBY_GPT_PWM,
      GTM_ATOM_CH_NOT_USEDBY_GPT_PWM,
      GTM_ATOM_CH_NOT_USEDBY_GPT_PWM,
      GTM_ATOM_CH_NOT_USEDBY_GPT_PWM,
      GTM_ATOM_CH_NOT_USEDBY_GPT_PWM,
      GTM_ATOM_CH_NOT_USEDBY_GPT_PWM,
    },

   /*ATOM Module 4 Usage*/
   {
      GTM_ATOM_CH_NOT_USEDBY_GPT_PWM,
      GTM_ATOM_CH_NOT_USEDBY_GPT_PWM,
      GTM_ATOM_CH_NOT_USEDBY_GPT_PWM,
      GTM_ATOM_CH_NOT_USEDBY_GPT_PWM,
      GTM_ATOM_CH_NOT_USEDBY_GPT_PWM,
      GTM_ATOM_CH_NOT_USEDBY_GPT_PWM,
      GTM_ATOM_CH_NOT_USEDBY_GPT_PWM,
      GTM_ATOM_CH_NOT_USEDBY_GPT_PWM,
    },
  }

};



static const Gtm_ModuleConfigType Gtm_kModuleConfig0 =
{
  0x00U | (uint8)((uint8)1U << 5),  /* ARU Configuration */
  GTM_SETUNUSED8,  /* Mcfg Configuration*/
  GTM_SLEEP_ENABLE,  /* Module Sleep Mode */
  1U,  /* Global Clock Configuration - Numerator */
  1U,/* Global Clock Configuration - Denominator */
  0xFFFFFFFFU,  /* Access Enable 0 */
  0UL,  /* Access Enable 1 */
  {0U,0U},
  {0U},  /* TIM Usage */  
  NULL_PTR,  /* TIM Configuration Pointer */
  {0U},  /* TOM TGC Usage */
  NULL_PTR,  /* TOM TGC Configuration Pointer */
  {  0U,  0U,  0U,},  
  {
  0U,  0U,
  },  /* TOM Usage */
  NULL_PTR,  /* TOM Configuration Pointer */  
  {0U},  /* ATOM AGC Usage */
  NULL_PTR,  /* ATOM AGC Configuration Pointer */
  {  0U,  0U,  0U,},  
  
  {
  0U,  0U,  },  /* ATOM Usage */
  NULL_PTR,  /* ATOM Configuration Pointer */   
    

  &Gtm_kModUsage0, /* Configuration for GTM Usage by other modules */
  &Gtm_kGeneralConfig0,  /* GTM General Configuration */
  NULL_PTR,  /* TBU Configuration Pointer */
  NULL_PTR,  /* BRC Configuration Pointer*/
  NULL_PTR,  /* Fifo Configuration Pointer*/
  NULL_PTR,  /* F2a Configuration Pointer*/
  NULL_PTR,  /* Mcs Configuration Pointer*/
  GTM_SETUNUSED32,  /* Map Configuration*/
  NULL_PTR,  /* Dpll Configuration Pointer*/
  { /* Spe Configurations*/
    NULL_PTR,  /* Spe Configuration Pointer*/
    NULL_PTR,  /* Spe Configuration Pointer*/
  },
  NULL_PTR,  /* Cmp Configuration Pointer*/
  NULL_PTR,  /* Msc Connections Configuration Pointer*/
  NULL_PTR,  /* Dsadc Connections Configuration Pointer*/
  NULL_PTR,  /* Adc Connections Configuration Pointer*/
  {
    0x00000000U,  /* Ttcan Connections Configuration*/
  },
  0x00000000U,  /* Psi5 Connections Configuration Pointer*/
  0x00000000U  /* Psi5S Connections Configuration Pointer*/
};

const Gtm_ConfigType Gtm_ConfigRoot[]  =
{
  {
    /*  GTM Module Clock Settings  */
    NULL_PTR, 
    /*  Pointer to Gtm Configuration structure  */
    NULL_PTR,
    &Gtm_kModuleConfig0,
  },
};
#define MCU_STOP_SEC_POSTBUILDCFG
/*IFX_MISRA_RULE_19_01_STATUS=File inclusion after pre-processor directives is 
 allowed only for MemMap.h*/
#include "MemMap.h"




/*******************************************************************************
**                      Global Variable Definitions                           **
*******************************************************************************/


/*******************************************************************************
**                      Private Constant Definitions                          **
*******************************************************************************/


/*******************************************************************************
**                      Private Variable Definitions                          **
*******************************************************************************/


/*******************************************************************************
**                      Global Function Definitions                           **
*******************************************************************************/


/*******************************************************************************
**                      Private Function Definitions                          **
*******************************************************************************/

