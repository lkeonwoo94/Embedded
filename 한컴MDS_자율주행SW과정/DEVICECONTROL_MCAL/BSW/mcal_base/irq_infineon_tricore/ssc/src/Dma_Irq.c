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
**  $FILENAME   : Dma_Irq.c $                                                **
**                                                                           **
**  $CC VERSION : \main\8 $                                                  **
**                                                                           **
**  $DATE       : 2014-06-25 $                                               **
**                                                                           **
**  AUTHOR      : DL-AUTOSAR-Engineering                                     **
**                                                                           **
**  VENDOR      : Infineon Technologies                                      **
**                                                                           **
**  DESCRIPTION : This file contains                                         **
**                 - functionality of DMA driver.                            **
**                                                                           **
**  MAY BE CHANGED BY USER [yes/no]: Yes                                     **
**                                                                           **
******************************************************************************/

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
/* Global functions like Set/Reset END INIT protection bit,
  Enable/Disable interrupts, Automic write function */
#include "Mcal.h"

/*Include Irq Module*/
#include "Irq.h"

#include "EcuM.h"

#if defined (ECUM_USES_SPI)
#include "Spi.h"
#endif

#if defined (ECUM_USES_ADC)
#include "Adc.h"
#endif
/*******************************************************************************
**                      Imported Compiler Switch Checks                       **
*******************************************************************************/

/*******************************************************************************
**                      Private Macro Definitions                             **
*******************************************************************************/

/*******************************************************************************
**                      Private Type Definitions                              **
*******************************************************************************/

/*******************************************************************************
**                      Private Function Declarations                         **
*******************************************************************************/

/*******************************************************************************
**                      Global Constant Definitions                           **
*******************************************************************************/

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
**                      Private Function Definitions                          **
*******************************************************************************/

/*******************************************************************************
**                      Global Function Definitions                           **
*******************************************************************************/
#define IRQ_START_SEC_CODE
#include "MemMap.h"
/******************************************************************************
** Syntax : void DMAERRSR_ISR(void)                                          **
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
** Description : Service for DMA error interrupts which can be due to Source **
**               ,destination, TCS, RAM or safelinked list checksum error.   **
**                                                                           **
******************************************************************************/
#if((IRQ_DMA_ERR_SR_PRIO > 0U) || (IRQ_DMA_ERR_SR_CAT == IRQ_CAT23))
#if((IRQ_DMA_ERR_SR_PRIO > 0U) && (IRQ_DMA_ERR_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMAERRSR_ISR, 0, IRQ_DMA_ERR_SR_PRIO)
#elif IRQ_DMA_ERR_SR_CAT == IRQ_CAT23
ISR(DMAERRSR_ISR)
#endif
{
  /* Enable Global Interrupts */
  Mcal_EnableAllInterrupts();
}
#endif
#if (IRQ_DMA_CH0TO47_EXIST == STD_ON)
/******************************************************************************
** Syntax : void DMACH0SR_ISR(void)                                        **
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
** Description : Service for DMA Channel0 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if((IRQ_DMA_CHANNEL0_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL0_SR_CAT == IRQ_CAT23))
#if((IRQ_DMA_CHANNEL0_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL0_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH0SR_ISR, 0, IRQ_DMA_CHANNEL0_SR_PRIO)
#elif IRQ_DMA_CHANNEL0_SR_CAT == IRQ_CAT23
ISR(DMACH0SR_ISR)
#endif
{
  #if ((IRQ_DMA_CHANNEL0_USED == IRQ_DMA_USED_MCALSPI_TX) || \
           (IRQ_DMA_CHANNEL0_USED == IRQ_DMA_USED_MCALSPI_RX))
  uint32 DmaErrorstatus;
  #endif
  /* Enable Global Interrupts */
  Mcal_EnableAllInterrupts();

  /* SPI TX interrupt */
  #if (IRQ_DMA_CHANNEL0_USED == IRQ_DMA_USED_MCALSPI_TX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL0_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiTx(IRQ_DMA_CHANNEL0_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL0_PARAM);
  }
  /* SPI RX interrupt */
  #elif (IRQ_DMA_CHANNEL0_USED == IRQ_DMA_USED_MCALSPI_RX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL0_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiRx(IRQ_DMA_CHANNEL0_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL0_PARAM);
  }
  /* ADC interrupt */
  #elif (IRQ_DMA_CHANNEL0_USED == IRQ_DMA_USED_MCALADC)

  #if (ADC_GROUP_EMUX_SCAN == STD_ON)
  Adc_IsrDmaSrn(IRQ_DMA_CHANNEL0_PARAM);
  #endif /*End of ADC_GROUP_EMUX_SCAN == STD_ON*/

  /* DMA CDD interrupt */
  #elif (IRQ_DMA_CHANNEL0_USED == IRQ_DMA_AVAILABLE)
  /* User Code Begins */
  /* Complex DMA driver usage */
  #endif
}
#endif
/******************************************************************************
** Syntax : void DMACH1SR_ISR(void)                                        **
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
** Description : Service for DMA Channel1 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if((IRQ_DMA_CHANNEL1_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL1_SR_CAT == IRQ_CAT23))
#if((IRQ_DMA_CHANNEL1_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL1_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH1SR_ISR, 0, IRQ_DMA_CHANNEL1_SR_PRIO)
#elif IRQ_DMA_CHANNEL1_SR_CAT == IRQ_CAT23
ISR(DMACH1SR_ISR)
#endif
{
  #if ((IRQ_DMA_CHANNEL1_USED == IRQ_DMA_USED_MCALSPI_TX) || \
           (IRQ_DMA_CHANNEL1_USED == IRQ_DMA_USED_MCALSPI_RX))
  uint32 DmaErrorstatus;
  #endif
  /* Enable Global Interrupts */
  Mcal_EnableAllInterrupts();

  /* SPI TX interrupt */
  #if (IRQ_DMA_CHANNEL1_USED == IRQ_DMA_USED_MCALSPI_TX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL1_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiTx(IRQ_DMA_CHANNEL1_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL1_PARAM);
  }
  /* SPI RX interrupt */
  #elif (IRQ_DMA_CHANNEL1_USED == IRQ_DMA_USED_MCALSPI_RX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL1_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiRx(IRQ_DMA_CHANNEL1_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL1_PARAM);
  }
  /* ADC interrupt */
  #elif (IRQ_DMA_CHANNEL1_USED == IRQ_DMA_USED_MCALADC)

  #if (ADC_GROUP_EMUX_SCAN == STD_ON)
  Adc_IsrDmaSrn(IRQ_DMA_CHANNEL1_PARAM);
  #endif /*End of ADC_GROUP_EMUX_SCAN == STD_ON*/

  /* DMA CDD interrupt */
  #elif (IRQ_DMA_CHANNEL1_USED == IRQ_DMA_AVAILABLE)
  /* User Code Begins */
  /* Complex DMA driver usage */
  #endif
}
#endif
/******************************************************************************
** Syntax : void DMACH2SR_ISR(void)                                        **
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
** Description : Service for DMA Channel2 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if((IRQ_DMA_CHANNEL2_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL2_SR_CAT == IRQ_CAT23))
#if((IRQ_DMA_CHANNEL2_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL2_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH2SR_ISR, 0, IRQ_DMA_CHANNEL2_SR_PRIO)
#elif IRQ_DMA_CHANNEL2_SR_CAT == IRQ_CAT23
ISR(DMACH2SR_ISR)
#endif
{
  #if ((IRQ_DMA_CHANNEL2_USED == IRQ_DMA_USED_MCALSPI_TX) || \
           (IRQ_DMA_CHANNEL2_USED == IRQ_DMA_USED_MCALSPI_RX))
  uint32 DmaErrorstatus;
  #endif
  /* Enable Global Interrupts */
  Mcal_EnableAllInterrupts();

  /* SPI TX interrupt */
  #if (IRQ_DMA_CHANNEL2_USED == IRQ_DMA_USED_MCALSPI_TX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL2_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiTx(IRQ_DMA_CHANNEL2_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL2_PARAM);
  }
  /* SPI RX interrupt */
  #elif (IRQ_DMA_CHANNEL2_USED == IRQ_DMA_USED_MCALSPI_RX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL2_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiRx(IRQ_DMA_CHANNEL2_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL2_PARAM);
  }
  /* ADC interrupt */
  #elif (IRQ_DMA_CHANNEL2_USED == IRQ_DMA_USED_MCALADC)

  #if (ADC_GROUP_EMUX_SCAN == STD_ON)
  Adc_IsrDmaSrn(IRQ_DMA_CHANNEL2_PARAM);
  #endif /*End of ADC_GROUP_EMUX_SCAN == STD_ON*/

  /* DMA CDD interrupt */
  #elif (IRQ_DMA_CHANNEL2_USED == IRQ_DMA_AVAILABLE)
  /* User Code Begins */
  /* Complex DMA driver usage */
  #endif
}
#endif
/******************************************************************************
** Syntax : void DMACH3SR_ISR(void)                                        **
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
** Description : Service for DMA Channel3 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if((IRQ_DMA_CHANNEL3_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL3_SR_CAT == IRQ_CAT23))
#if((IRQ_DMA_CHANNEL3_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL3_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH3SR_ISR, 0, IRQ_DMA_CHANNEL3_SR_PRIO)
#elif IRQ_DMA_CHANNEL3_SR_CAT == IRQ_CAT23
ISR(DMACH3SR_ISR)
#endif
{
  #if ((IRQ_DMA_CHANNEL3_USED == IRQ_DMA_USED_MCALSPI_TX) || \
           (IRQ_DMA_CHANNEL3_USED == IRQ_DMA_USED_MCALSPI_RX))
  uint32 DmaErrorstatus;
  #endif
  /* Enable Global Interrupts */
  Mcal_EnableAllInterrupts();

  /* SPI TX interrupt */
  #if (IRQ_DMA_CHANNEL3_USED == IRQ_DMA_USED_MCALSPI_TX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL3_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiTx(IRQ_DMA_CHANNEL3_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL3_PARAM);
  }
  /* SPI RX interrupt */
  #elif (IRQ_DMA_CHANNEL3_USED == IRQ_DMA_USED_MCALSPI_RX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL3_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiRx(IRQ_DMA_CHANNEL3_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL3_PARAM);
  }
  /* ADC interrupt */
  #elif (IRQ_DMA_CHANNEL3_USED == IRQ_DMA_USED_MCALADC)

  #if (ADC_GROUP_EMUX_SCAN == STD_ON)
  Adc_IsrDmaSrn(IRQ_DMA_CHANNEL3_PARAM);
  #endif /*End of ADC_GROUP_EMUX_SCAN == STD_ON*/

  /* DMA CDD interrupt */
  #elif (IRQ_DMA_CHANNEL3_USED == IRQ_DMA_AVAILABLE)
  /* User Code Begins */
  /* Complex DMA driver usage */
  #endif
}
#endif
/******************************************************************************
** Syntax : void DMACH4SR_ISR(void)                                        **
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
** Description : Service for DMA Channel4 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if((IRQ_DMA_CHANNEL4_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL4_SR_CAT == IRQ_CAT23))
#if((IRQ_DMA_CHANNEL4_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL4_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH4SR_ISR, 0, IRQ_DMA_CHANNEL4_SR_PRIO)
#elif IRQ_DMA_CHANNEL4_SR_CAT == IRQ_CAT23
ISR(DMACH4SR_ISR)
#endif
{
  #if ((IRQ_DMA_CHANNEL4_USED == IRQ_DMA_USED_MCALSPI_TX) || \
           (IRQ_DMA_CHANNEL4_USED == IRQ_DMA_USED_MCALSPI_RX))
  uint32 DmaErrorstatus;
  #endif
  /* Enable Global Interrupts */
  Mcal_EnableAllInterrupts();

  /* SPI TX interrupt */
  #if (IRQ_DMA_CHANNEL4_USED == IRQ_DMA_USED_MCALSPI_TX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL4_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiTx(IRQ_DMA_CHANNEL4_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL4_PARAM);
  }
  /* SPI RX interrupt */
  #elif (IRQ_DMA_CHANNEL4_USED == IRQ_DMA_USED_MCALSPI_RX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL4_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiRx(IRQ_DMA_CHANNEL4_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL4_PARAM);
  }
  /* ADC interrupt */
  #elif (IRQ_DMA_CHANNEL4_USED == IRQ_DMA_USED_MCALADC)

  #if (ADC_GROUP_EMUX_SCAN == STD_ON)
  Adc_IsrDmaSrn(IRQ_DMA_CHANNEL4_PARAM);
  #endif /*End of ADC_GROUP_EMUX_SCAN == STD_ON*/

  /* DMA CDD interrupt */
  #elif (IRQ_DMA_CHANNEL4_USED == IRQ_DMA_AVAILABLE)
  /* User Code Begins */
  /* Complex DMA driver usage */
  #endif
}
#endif
/******************************************************************************
** Syntax : void DMACH5SR_ISR(void)                                        **
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
** Description : Service for DMA Channel5 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if((IRQ_DMA_CHANNEL5_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL5_SR_CAT == IRQ_CAT23))
#if((IRQ_DMA_CHANNEL5_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL5_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH5SR_ISR, 0, IRQ_DMA_CHANNEL5_SR_PRIO)
#elif IRQ_DMA_CHANNEL5_SR_CAT == IRQ_CAT23
ISR(DMACH5SR_ISR)
#endif
{
  #if ((IRQ_DMA_CHANNEL5_USED == IRQ_DMA_USED_MCALSPI_TX) || \
           (IRQ_DMA_CHANNEL5_USED == IRQ_DMA_USED_MCALSPI_RX))
  uint32 DmaErrorstatus;
  #endif
  /* Enable Global Interrupts */
  Mcal_EnableAllInterrupts();

  /* SPI TX interrupt */
  #if (IRQ_DMA_CHANNEL5_USED == IRQ_DMA_USED_MCALSPI_TX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL5_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiTx(IRQ_DMA_CHANNEL5_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL5_PARAM);
  }
  /* SPI RX interrupt */
  #elif (IRQ_DMA_CHANNEL5_USED == IRQ_DMA_USED_MCALSPI_RX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL5_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiRx(IRQ_DMA_CHANNEL5_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL5_PARAM);
  }
  /* ADC interrupt */
  #elif (IRQ_DMA_CHANNEL5_USED == IRQ_DMA_USED_MCALADC)

  #if (ADC_GROUP_EMUX_SCAN == STD_ON)
  Adc_IsrDmaSrn(IRQ_DMA_CHANNEL5_PARAM);
  #endif /*End of ADC_GROUP_EMUX_SCAN == STD_ON*/

  /* DMA CDD interrupt */
  #elif (IRQ_DMA_CHANNEL5_USED == IRQ_DMA_AVAILABLE)
  /* User Code Begins */
  /* Complex DMA driver usage */
  #endif
}
#endif
/******************************************************************************
** Syntax : void DMACH6SR_ISR(void)                                        **
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
** Description : Service for DMA Channel6 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if((IRQ_DMA_CHANNEL6_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL6_SR_CAT == IRQ_CAT23))
#if((IRQ_DMA_CHANNEL6_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL6_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH6SR_ISR, 0, IRQ_DMA_CHANNEL6_SR_PRIO)
#elif IRQ_DMA_CHANNEL6_SR_CAT == IRQ_CAT23
ISR(DMACH6SR_ISR)
#endif
{
  #if ((IRQ_DMA_CHANNEL6_USED == IRQ_DMA_USED_MCALSPI_TX) || \
           (IRQ_DMA_CHANNEL6_USED == IRQ_DMA_USED_MCALSPI_RX))
  uint32 DmaErrorstatus;
  #endif
  /* Enable Global Interrupts */
  Mcal_EnableAllInterrupts();

  /* SPI TX interrupt */
  #if (IRQ_DMA_CHANNEL6_USED == IRQ_DMA_USED_MCALSPI_TX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL6_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiTx(IRQ_DMA_CHANNEL6_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL6_PARAM);
  }
  /* SPI RX interrupt */
  #elif (IRQ_DMA_CHANNEL6_USED == IRQ_DMA_USED_MCALSPI_RX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL6_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiRx(IRQ_DMA_CHANNEL6_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL6_PARAM);
  }
  /* ADC interrupt */
  #elif (IRQ_DMA_CHANNEL6_USED == IRQ_DMA_USED_MCALADC)

  #if (ADC_GROUP_EMUX_SCAN == STD_ON)
  Adc_IsrDmaSrn(IRQ_DMA_CHANNEL6_PARAM);
  #endif /*End of ADC_GROUP_EMUX_SCAN == STD_ON*/

  /* DMA CDD interrupt */
  #elif (IRQ_DMA_CHANNEL6_USED == IRQ_DMA_AVAILABLE)
  /* User Code Begins */
  /* Complex DMA driver usage */
  #endif
}
#endif
/******************************************************************************
** Syntax : void DMACH7SR_ISR(void)                                        **
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
** Description : Service for DMA Channel7 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if((IRQ_DMA_CHANNEL7_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL7_SR_CAT == IRQ_CAT23))
#if((IRQ_DMA_CHANNEL7_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL7_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH7SR_ISR, 0, IRQ_DMA_CHANNEL7_SR_PRIO)
#elif IRQ_DMA_CHANNEL7_SR_CAT == IRQ_CAT23
ISR(DMACH7SR_ISR)
#endif
{
  #if ((IRQ_DMA_CHANNEL7_USED == IRQ_DMA_USED_MCALSPI_TX) || \
           (IRQ_DMA_CHANNEL7_USED == IRQ_DMA_USED_MCALSPI_RX))
  uint32 DmaErrorstatus;
  #endif
  /* Enable Global Interrupts */
  Mcal_EnableAllInterrupts();

  /* SPI TX interrupt */
  #if (IRQ_DMA_CHANNEL7_USED == IRQ_DMA_USED_MCALSPI_TX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL7_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiTx(IRQ_DMA_CHANNEL7_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL7_PARAM);
  }
  /* SPI RX interrupt */
  #elif (IRQ_DMA_CHANNEL7_USED == IRQ_DMA_USED_MCALSPI_RX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL7_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiRx(IRQ_DMA_CHANNEL7_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL7_PARAM);
  }
  /* ADC interrupt */
  #elif (IRQ_DMA_CHANNEL7_USED == IRQ_DMA_USED_MCALADC)

  #if (ADC_GROUP_EMUX_SCAN == STD_ON)
  Adc_IsrDmaSrn(IRQ_DMA_CHANNEL7_PARAM);
  #endif /*End of ADC_GROUP_EMUX_SCAN == STD_ON*/

  /* DMA CDD interrupt */
  #elif (IRQ_DMA_CHANNEL7_USED == IRQ_DMA_AVAILABLE)
  /* User Code Begins */
  /* Complex DMA driver usage */
  #endif
}
#endif
/******************************************************************************
** Syntax : void DMACH8SR_ISR(void)                                        **
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
** Description : Service for DMA Channel8 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if((IRQ_DMA_CHANNEL8_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL8_SR_CAT == IRQ_CAT23))
#if((IRQ_DMA_CHANNEL8_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL8_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH8SR_ISR, 0, IRQ_DMA_CHANNEL8_SR_PRIO)
#elif IRQ_DMA_CHANNEL8_SR_CAT == IRQ_CAT23
ISR(DMACH8SR_ISR)
#endif
{
  #if ((IRQ_DMA_CHANNEL8_USED == IRQ_DMA_USED_MCALSPI_TX) || \
           (IRQ_DMA_CHANNEL8_USED == IRQ_DMA_USED_MCALSPI_RX))
  uint32 DmaErrorstatus;
  #endif
  /* Enable Global Interrupts */
  Mcal_EnableAllInterrupts();

  /* SPI TX interrupt */
  #if (IRQ_DMA_CHANNEL8_USED == IRQ_DMA_USED_MCALSPI_TX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL8_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiTx(IRQ_DMA_CHANNEL8_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL8_PARAM);
  }
  /* SPI RX interrupt */
  #elif (IRQ_DMA_CHANNEL8_USED == IRQ_DMA_USED_MCALSPI_RX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL8_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiRx(IRQ_DMA_CHANNEL8_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL8_PARAM);
  }
  /* ADC interrupt */
  #elif (IRQ_DMA_CHANNEL8_USED == IRQ_DMA_USED_MCALADC)

  #if (ADC_GROUP_EMUX_SCAN == STD_ON)
  Adc_IsrDmaSrn(IRQ_DMA_CHANNEL8_PARAM);
  #endif /*End of ADC_GROUP_EMUX_SCAN == STD_ON*/

  /* DMA CDD interrupt */
  #elif (IRQ_DMA_CHANNEL8_USED == IRQ_DMA_AVAILABLE)
  /* User Code Begins */
  /* Complex DMA driver usage */
  #endif
}
#endif
/******************************************************************************
** Syntax : void DMACH9SR_ISR(void)                                        **
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
** Description : Service for DMA Channel9 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if((IRQ_DMA_CHANNEL9_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL9_SR_CAT == IRQ_CAT23))
#if((IRQ_DMA_CHANNEL9_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL9_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH9SR_ISR, 0, IRQ_DMA_CHANNEL9_SR_PRIO)
#elif IRQ_DMA_CHANNEL9_SR_CAT == IRQ_CAT23
ISR(DMACH9SR_ISR)
#endif
{
  #if ((IRQ_DMA_CHANNEL9_USED == IRQ_DMA_USED_MCALSPI_TX) || \
           (IRQ_DMA_CHANNEL9_USED == IRQ_DMA_USED_MCALSPI_RX))
  uint32 DmaErrorstatus;
  #endif
  /* Enable Global Interrupts */
  Mcal_EnableAllInterrupts();

  /* SPI TX interrupt */
  #if (IRQ_DMA_CHANNEL9_USED == IRQ_DMA_USED_MCALSPI_TX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL9_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiTx(IRQ_DMA_CHANNEL9_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL9_PARAM);
  }
  /* SPI RX interrupt */
  #elif (IRQ_DMA_CHANNEL9_USED == IRQ_DMA_USED_MCALSPI_RX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL9_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiRx(IRQ_DMA_CHANNEL9_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL9_PARAM);
  }
  /* ADC interrupt */
  #elif (IRQ_DMA_CHANNEL9_USED == IRQ_DMA_USED_MCALADC)

  #if (ADC_GROUP_EMUX_SCAN == STD_ON)
  Adc_IsrDmaSrn(IRQ_DMA_CHANNEL9_PARAM);
  #endif /*End of ADC_GROUP_EMUX_SCAN == STD_ON*/

  /* DMA CDD interrupt */
  #elif (IRQ_DMA_CHANNEL9_USED == IRQ_DMA_AVAILABLE)
  /* User Code Begins */
  /* Complex DMA driver usage */
  #endif
}
#endif
/******************************************************************************
** Syntax : void DMACH10SR_ISR(void)                                        **
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
** Description : Service for DMA Channel10 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if((IRQ_DMA_CHANNEL10_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL10_SR_CAT == IRQ_CAT23))
#if((IRQ_DMA_CHANNEL10_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL10_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH10SR_ISR, 0, IRQ_DMA_CHANNEL10_SR_PRIO)
#elif IRQ_DMA_CHANNEL10_SR_CAT == IRQ_CAT23
ISR(DMACH10SR_ISR)
#endif
{
  #if ((IRQ_DMA_CHANNEL10_USED == IRQ_DMA_USED_MCALSPI_TX) || \
           (IRQ_DMA_CHANNEL10_USED == IRQ_DMA_USED_MCALSPI_RX))
  uint32 DmaErrorstatus;
  #endif
  /* Enable Global Interrupts */
  Mcal_EnableAllInterrupts();

  /* SPI TX interrupt */
  #if (IRQ_DMA_CHANNEL10_USED == IRQ_DMA_USED_MCALSPI_TX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL10_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiTx(IRQ_DMA_CHANNEL10_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL10_PARAM);
  }
  /* SPI RX interrupt */
  #elif (IRQ_DMA_CHANNEL10_USED == IRQ_DMA_USED_MCALSPI_RX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL10_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiRx(IRQ_DMA_CHANNEL10_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL10_PARAM);
  }
  /* ADC interrupt */
  #elif (IRQ_DMA_CHANNEL10_USED == IRQ_DMA_USED_MCALADC)

  #if (ADC_GROUP_EMUX_SCAN == STD_ON)
  Adc_IsrDmaSrn(IRQ_DMA_CHANNEL10_PARAM);
  #endif /*End of ADC_GROUP_EMUX_SCAN == STD_ON*/

  /* DMA CDD interrupt */
  #elif (IRQ_DMA_CHANNEL10_USED == IRQ_DMA_AVAILABLE)
  /* User Code Begins */
  /* Complex DMA driver usage */
  #endif
}
#endif
/******************************************************************************
** Syntax : void DMACH11SR_ISR(void)                                        **
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
** Description : Service for DMA Channel11 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if((IRQ_DMA_CHANNEL11_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL11_SR_CAT == IRQ_CAT23))
#if((IRQ_DMA_CHANNEL11_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL11_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH11SR_ISR, 0, IRQ_DMA_CHANNEL11_SR_PRIO)
#elif IRQ_DMA_CHANNEL11_SR_CAT == IRQ_CAT23
ISR(DMACH11SR_ISR)
#endif
{
  #if ((IRQ_DMA_CHANNEL11_USED == IRQ_DMA_USED_MCALSPI_TX) || \
           (IRQ_DMA_CHANNEL11_USED == IRQ_DMA_USED_MCALSPI_RX))
  uint32 DmaErrorstatus;
  #endif
  /* Enable Global Interrupts */
  Mcal_EnableAllInterrupts();

  /* SPI TX interrupt */
  #if (IRQ_DMA_CHANNEL11_USED == IRQ_DMA_USED_MCALSPI_TX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL11_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiTx(IRQ_DMA_CHANNEL11_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL11_PARAM);
  }
  /* SPI RX interrupt */
  #elif (IRQ_DMA_CHANNEL11_USED == IRQ_DMA_USED_MCALSPI_RX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL11_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiRx(IRQ_DMA_CHANNEL11_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL11_PARAM);
  }
  /* ADC interrupt */
  #elif (IRQ_DMA_CHANNEL11_USED == IRQ_DMA_USED_MCALADC)

  #if (ADC_GROUP_EMUX_SCAN == STD_ON)
  Adc_IsrDmaSrn(IRQ_DMA_CHANNEL11_PARAM);
  #endif /*End of ADC_GROUP_EMUX_SCAN == STD_ON*/

  /* DMA CDD interrupt */
  #elif (IRQ_DMA_CHANNEL11_USED == IRQ_DMA_AVAILABLE)
  /* User Code Begins */
  /* Complex DMA driver usage */
  #endif
}
#endif
/******************************************************************************
** Syntax : void DMACH12SR_ISR(void)                                        **
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
** Description : Service for DMA Channel12 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if((IRQ_DMA_CHANNEL12_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL12_SR_CAT == IRQ_CAT23))
#if((IRQ_DMA_CHANNEL12_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL12_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH12SR_ISR, 0, IRQ_DMA_CHANNEL12_SR_PRIO)
#elif IRQ_DMA_CHANNEL12_SR_CAT == IRQ_CAT23
ISR(DMACH12SR_ISR)
#endif
{
  #if ((IRQ_DMA_CHANNEL12_USED == IRQ_DMA_USED_MCALSPI_TX) || \
           (IRQ_DMA_CHANNEL12_USED == IRQ_DMA_USED_MCALSPI_RX))
  uint32 DmaErrorstatus;
  #endif
  /* Enable Global Interrupts */
  Mcal_EnableAllInterrupts();

  /* SPI TX interrupt */
  #if (IRQ_DMA_CHANNEL12_USED == IRQ_DMA_USED_MCALSPI_TX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL12_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiTx(IRQ_DMA_CHANNEL12_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL12_PARAM);
  }
  /* SPI RX interrupt */
  #elif (IRQ_DMA_CHANNEL12_USED == IRQ_DMA_USED_MCALSPI_RX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL12_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiRx(IRQ_DMA_CHANNEL12_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL12_PARAM);
  }
  /* ADC interrupt */
  #elif (IRQ_DMA_CHANNEL12_USED == IRQ_DMA_USED_MCALADC)

  #if (ADC_GROUP_EMUX_SCAN == STD_ON)
  Adc_IsrDmaSrn(IRQ_DMA_CHANNEL12_PARAM);
  #endif /*End of ADC_GROUP_EMUX_SCAN == STD_ON*/

  /* DMA CDD interrupt */
  #elif (IRQ_DMA_CHANNEL12_USED == IRQ_DMA_AVAILABLE)
  /* User Code Begins */
  /* Complex DMA driver usage */
  #endif
}
#endif
/******************************************************************************
** Syntax : void DMACH13SR_ISR(void)                                        **
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
** Description : Service for DMA Channel13 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if((IRQ_DMA_CHANNEL13_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL13_SR_CAT == IRQ_CAT23))
#if((IRQ_DMA_CHANNEL13_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL13_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH13SR_ISR, 0, IRQ_DMA_CHANNEL13_SR_PRIO)
#elif IRQ_DMA_CHANNEL13_SR_CAT == IRQ_CAT23
ISR(DMACH13SR_ISR)
#endif
{
  #if ((IRQ_DMA_CHANNEL13_USED == IRQ_DMA_USED_MCALSPI_TX) || \
           (IRQ_DMA_CHANNEL13_USED == IRQ_DMA_USED_MCALSPI_RX))
  uint32 DmaErrorstatus;
  #endif
  /* Enable Global Interrupts */
  Mcal_EnableAllInterrupts();

  /* SPI TX interrupt */
  #if (IRQ_DMA_CHANNEL13_USED == IRQ_DMA_USED_MCALSPI_TX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL13_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiTx(IRQ_DMA_CHANNEL13_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL13_PARAM);
  }
  /* SPI RX interrupt */
  #elif (IRQ_DMA_CHANNEL13_USED == IRQ_DMA_USED_MCALSPI_RX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL13_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiRx(IRQ_DMA_CHANNEL13_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL13_PARAM);
  }
  /* ADC interrupt */
  #elif (IRQ_DMA_CHANNEL13_USED == IRQ_DMA_USED_MCALADC)

  #if (ADC_GROUP_EMUX_SCAN == STD_ON)
  Adc_IsrDmaSrn(IRQ_DMA_CHANNEL13_PARAM);
  #endif /*End of ADC_GROUP_EMUX_SCAN == STD_ON*/

  /* DMA CDD interrupt */
  #elif (IRQ_DMA_CHANNEL13_USED == IRQ_DMA_AVAILABLE)
  /* User Code Begins */
  /* Complex DMA driver usage */
  #endif
}
#endif
/******************************************************************************
** Syntax : void DMACH14SR_ISR(void)                                        **
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
** Description : Service for DMA Channel14 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if((IRQ_DMA_CHANNEL14_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL14_SR_CAT == IRQ_CAT23))
#if((IRQ_DMA_CHANNEL14_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL14_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH14SR_ISR, 0, IRQ_DMA_CHANNEL14_SR_PRIO)
#elif IRQ_DMA_CHANNEL14_SR_CAT == IRQ_CAT23
ISR(DMACH14SR_ISR)
#endif
{
  #if ((IRQ_DMA_CHANNEL14_USED == IRQ_DMA_USED_MCALSPI_TX) || \
           (IRQ_DMA_CHANNEL14_USED == IRQ_DMA_USED_MCALSPI_RX))
  uint32 DmaErrorstatus;
  #endif
  /* Enable Global Interrupts */
  Mcal_EnableAllInterrupts();

  /* SPI TX interrupt */
  #if (IRQ_DMA_CHANNEL14_USED == IRQ_DMA_USED_MCALSPI_TX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL14_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiTx(IRQ_DMA_CHANNEL14_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL14_PARAM);
  }
  /* SPI RX interrupt */
  #elif (IRQ_DMA_CHANNEL14_USED == IRQ_DMA_USED_MCALSPI_RX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL14_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiRx(IRQ_DMA_CHANNEL14_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL14_PARAM);
  }
  /* ADC interrupt */
  #elif (IRQ_DMA_CHANNEL14_USED == IRQ_DMA_USED_MCALADC)

  #if (ADC_GROUP_EMUX_SCAN == STD_ON)
  Adc_IsrDmaSrn(IRQ_DMA_CHANNEL14_PARAM);
  #endif /*End of ADC_GROUP_EMUX_SCAN == STD_ON*/

  /* DMA CDD interrupt */
  #elif (IRQ_DMA_CHANNEL14_USED == IRQ_DMA_AVAILABLE)
  /* User Code Begins */
  /* Complex DMA driver usage */
  #endif
}
#endif
/******************************************************************************
** Syntax : void DMACH15SR_ISR(void)                                        **
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
** Description : Service for DMA Channel15 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if((IRQ_DMA_CHANNEL15_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL15_SR_CAT == IRQ_CAT23))
#if((IRQ_DMA_CHANNEL15_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL15_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH15SR_ISR, 0, IRQ_DMA_CHANNEL15_SR_PRIO)
#elif IRQ_DMA_CHANNEL15_SR_CAT == IRQ_CAT23
ISR(DMACH15SR_ISR)
#endif
{
  #if ((IRQ_DMA_CHANNEL15_USED == IRQ_DMA_USED_MCALSPI_TX) || \
           (IRQ_DMA_CHANNEL15_USED == IRQ_DMA_USED_MCALSPI_RX))
  uint32 DmaErrorstatus;
  #endif
  /* Enable Global Interrupts */
  Mcal_EnableAllInterrupts();

  /* SPI TX interrupt */
  #if (IRQ_DMA_CHANNEL15_USED == IRQ_DMA_USED_MCALSPI_TX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL15_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiTx(IRQ_DMA_CHANNEL15_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL15_PARAM);
  }
  /* SPI RX interrupt */
  #elif (IRQ_DMA_CHANNEL15_USED == IRQ_DMA_USED_MCALSPI_RX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL15_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiRx(IRQ_DMA_CHANNEL15_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL15_PARAM);
  }
  /* ADC interrupt */
  #elif (IRQ_DMA_CHANNEL15_USED == IRQ_DMA_USED_MCALADC)

  #if (ADC_GROUP_EMUX_SCAN == STD_ON)
  Adc_IsrDmaSrn(IRQ_DMA_CHANNEL15_PARAM);
  #endif /*End of ADC_GROUP_EMUX_SCAN == STD_ON*/

  /* DMA CDD interrupt */
  #elif (IRQ_DMA_CHANNEL15_USED == IRQ_DMA_AVAILABLE)
  /* User Code Begins */
  /* Complex DMA driver usage */
  #endif
}
#endif
/******************************************************************************
** Syntax : void DMACH16SR_ISR(void)                                        **
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
** Description : Service for DMA Channel16 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if((IRQ_DMA_CHANNEL16_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL16_SR_CAT == IRQ_CAT23))
#if((IRQ_DMA_CHANNEL16_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL16_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH16SR_ISR, 0, IRQ_DMA_CHANNEL16_SR_PRIO)
#elif IRQ_DMA_CHANNEL16_SR_CAT == IRQ_CAT23
ISR(DMACH16SR_ISR)
#endif
{
  #if ((IRQ_DMA_CHANNEL16_USED == IRQ_DMA_USED_MCALSPI_TX) || \
           (IRQ_DMA_CHANNEL16_USED == IRQ_DMA_USED_MCALSPI_RX))
  uint32 DmaErrorstatus;
  #endif
  /* Enable Global Interrupts */
  Mcal_EnableAllInterrupts();

  /* SPI TX interrupt */
  #if (IRQ_DMA_CHANNEL16_USED == IRQ_DMA_USED_MCALSPI_TX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL16_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiTx(IRQ_DMA_CHANNEL16_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL16_PARAM);
  }
  /* SPI RX interrupt */
  #elif (IRQ_DMA_CHANNEL16_USED == IRQ_DMA_USED_MCALSPI_RX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL16_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiRx(IRQ_DMA_CHANNEL16_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL16_PARAM);
  }
  /* ADC interrupt */
  #elif (IRQ_DMA_CHANNEL16_USED == IRQ_DMA_USED_MCALADC)

  #if (ADC_GROUP_EMUX_SCAN == STD_ON)
  Adc_IsrDmaSrn(IRQ_DMA_CHANNEL16_PARAM);
  #endif /*End of ADC_GROUP_EMUX_SCAN == STD_ON*/

  /* DMA CDD interrupt */
  #elif (IRQ_DMA_CHANNEL16_USED == IRQ_DMA_AVAILABLE)
  /* User Code Begins */
  /* Complex DMA driver usage */
  #endif
}
#endif
/******************************************************************************
** Syntax : void DMACH17SR_ISR(void)                                        **
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
** Description : Service for DMA Channel17 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if((IRQ_DMA_CHANNEL17_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL17_SR_CAT == IRQ_CAT23))
#if((IRQ_DMA_CHANNEL17_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL17_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH17SR_ISR, 0, IRQ_DMA_CHANNEL17_SR_PRIO)
#elif IRQ_DMA_CHANNEL17_SR_CAT == IRQ_CAT23
ISR(DMACH17SR_ISR)
#endif
{
  #if ((IRQ_DMA_CHANNEL17_USED == IRQ_DMA_USED_MCALSPI_TX) || \
           (IRQ_DMA_CHANNEL17_USED == IRQ_DMA_USED_MCALSPI_RX))
  uint32 DmaErrorstatus;
  #endif
  /* Enable Global Interrupts */
  Mcal_EnableAllInterrupts();

  /* SPI TX interrupt */
  #if (IRQ_DMA_CHANNEL17_USED == IRQ_DMA_USED_MCALSPI_TX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL17_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiTx(IRQ_DMA_CHANNEL17_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL17_PARAM);
  }
  /* SPI RX interrupt */
  #elif (IRQ_DMA_CHANNEL17_USED == IRQ_DMA_USED_MCALSPI_RX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL17_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiRx(IRQ_DMA_CHANNEL17_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL17_PARAM);
  }
  /* ADC interrupt */
  #elif (IRQ_DMA_CHANNEL17_USED == IRQ_DMA_USED_MCALADC)

  #if (ADC_GROUP_EMUX_SCAN == STD_ON)
  Adc_IsrDmaSrn(IRQ_DMA_CHANNEL17_PARAM);
  #endif /*End of ADC_GROUP_EMUX_SCAN == STD_ON*/

  /* DMA CDD interrupt */
  #elif (IRQ_DMA_CHANNEL17_USED == IRQ_DMA_AVAILABLE)
  /* User Code Begins */
  /* Complex DMA driver usage */
  #endif
}
#endif
/******************************************************************************
** Syntax : void DMACH18SR_ISR(void)                                        **
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
** Description : Service for DMA Channel18 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if((IRQ_DMA_CHANNEL18_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL18_SR_CAT == IRQ_CAT23))
#if((IRQ_DMA_CHANNEL18_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL18_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH18SR_ISR, 0, IRQ_DMA_CHANNEL18_SR_PRIO)
#elif IRQ_DMA_CHANNEL18_SR_CAT == IRQ_CAT23
ISR(DMACH18SR_ISR)
#endif
{
  #if ((IRQ_DMA_CHANNEL18_USED == IRQ_DMA_USED_MCALSPI_TX) || \
           (IRQ_DMA_CHANNEL18_USED == IRQ_DMA_USED_MCALSPI_RX))
  uint32 DmaErrorstatus;
  #endif
  /* Enable Global Interrupts */
  Mcal_EnableAllInterrupts();

  /* SPI TX interrupt */
  #if (IRQ_DMA_CHANNEL18_USED == IRQ_DMA_USED_MCALSPI_TX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL18_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiTx(IRQ_DMA_CHANNEL18_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL18_PARAM);
  }
  /* SPI RX interrupt */
  #elif (IRQ_DMA_CHANNEL18_USED == IRQ_DMA_USED_MCALSPI_RX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL18_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiRx(IRQ_DMA_CHANNEL18_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL18_PARAM);
  }
  /* ADC interrupt */
  #elif (IRQ_DMA_CHANNEL18_USED == IRQ_DMA_USED_MCALADC)

  #if (ADC_GROUP_EMUX_SCAN == STD_ON)
  Adc_IsrDmaSrn(IRQ_DMA_CHANNEL18_PARAM);
  #endif /*End of ADC_GROUP_EMUX_SCAN == STD_ON*/

  /* DMA CDD interrupt */
  #elif (IRQ_DMA_CHANNEL18_USED == IRQ_DMA_AVAILABLE)
  /* User Code Begins */
  /* Complex DMA driver usage */
  #endif
}
#endif
/******************************************************************************
** Syntax : void DMACH19SR_ISR(void)                                        **
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
** Description : Service for DMA Channel19 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if((IRQ_DMA_CHANNEL19_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL19_SR_CAT == IRQ_CAT23))
#if((IRQ_DMA_CHANNEL19_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL19_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH19SR_ISR, 0, IRQ_DMA_CHANNEL19_SR_PRIO)
#elif IRQ_DMA_CHANNEL19_SR_CAT == IRQ_CAT23
ISR(DMACH19SR_ISR)
#endif
{
  #if ((IRQ_DMA_CHANNEL19_USED == IRQ_DMA_USED_MCALSPI_TX) || \
           (IRQ_DMA_CHANNEL19_USED == IRQ_DMA_USED_MCALSPI_RX))
  uint32 DmaErrorstatus;
  #endif
  /* Enable Global Interrupts */
  Mcal_EnableAllInterrupts();

  /* SPI TX interrupt */
  #if (IRQ_DMA_CHANNEL19_USED == IRQ_DMA_USED_MCALSPI_TX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL19_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiTx(IRQ_DMA_CHANNEL19_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL19_PARAM);
  }
  /* SPI RX interrupt */
  #elif (IRQ_DMA_CHANNEL19_USED == IRQ_DMA_USED_MCALSPI_RX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL19_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiRx(IRQ_DMA_CHANNEL19_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL19_PARAM);
  }
  /* ADC interrupt */
  #elif (IRQ_DMA_CHANNEL19_USED == IRQ_DMA_USED_MCALADC)

  #if (ADC_GROUP_EMUX_SCAN == STD_ON)
  Adc_IsrDmaSrn(IRQ_DMA_CHANNEL19_PARAM);
  #endif /*End of ADC_GROUP_EMUX_SCAN == STD_ON*/

  /* DMA CDD interrupt */
  #elif (IRQ_DMA_CHANNEL19_USED == IRQ_DMA_AVAILABLE)
  /* User Code Begins */
  /* Complex DMA driver usage */
  #endif
}
#endif
/******************************************************************************
** Syntax : void DMACH20SR_ISR(void)                                        **
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
** Description : Service for DMA Channel20 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if((IRQ_DMA_CHANNEL20_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL20_SR_CAT == IRQ_CAT23))
#if((IRQ_DMA_CHANNEL20_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL20_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH20SR_ISR, 0, IRQ_DMA_CHANNEL20_SR_PRIO)
#elif IRQ_DMA_CHANNEL20_SR_CAT == IRQ_CAT23
ISR(DMACH20SR_ISR)
#endif
{
  #if ((IRQ_DMA_CHANNEL20_USED == IRQ_DMA_USED_MCALSPI_TX) || \
           (IRQ_DMA_CHANNEL20_USED == IRQ_DMA_USED_MCALSPI_RX))
  uint32 DmaErrorstatus;
  #endif
  /* Enable Global Interrupts */
  Mcal_EnableAllInterrupts();

  /* SPI TX interrupt */
  #if (IRQ_DMA_CHANNEL20_USED == IRQ_DMA_USED_MCALSPI_TX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL20_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiTx(IRQ_DMA_CHANNEL20_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL20_PARAM);
  }
  /* SPI RX interrupt */
  #elif (IRQ_DMA_CHANNEL20_USED == IRQ_DMA_USED_MCALSPI_RX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL20_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiRx(IRQ_DMA_CHANNEL20_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL20_PARAM);
  }
  /* ADC interrupt */
  #elif (IRQ_DMA_CHANNEL20_USED == IRQ_DMA_USED_MCALADC)

  #if (ADC_GROUP_EMUX_SCAN == STD_ON)
  Adc_IsrDmaSrn(IRQ_DMA_CHANNEL20_PARAM);
  #endif /*End of ADC_GROUP_EMUX_SCAN == STD_ON*/

  /* DMA CDD interrupt */
  #elif (IRQ_DMA_CHANNEL20_USED == IRQ_DMA_AVAILABLE)
  /* User Code Begins */
  /* Complex DMA driver usage */
  #endif
}
#endif
/******************************************************************************
** Syntax : void DMACH21SR_ISR(void)                                        **
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
** Description : Service for DMA Channel21 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if((IRQ_DMA_CHANNEL21_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL21_SR_CAT == IRQ_CAT23))
#if((IRQ_DMA_CHANNEL21_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL21_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH21SR_ISR, 0, IRQ_DMA_CHANNEL21_SR_PRIO)
#elif IRQ_DMA_CHANNEL21_SR_CAT == IRQ_CAT23
ISR(DMACH21SR_ISR)
#endif
{
  #if ((IRQ_DMA_CHANNEL21_USED == IRQ_DMA_USED_MCALSPI_TX) || \
           (IRQ_DMA_CHANNEL21_USED == IRQ_DMA_USED_MCALSPI_RX))
  uint32 DmaErrorstatus;
  #endif
  /* Enable Global Interrupts */
  Mcal_EnableAllInterrupts();

  /* SPI TX interrupt */
  #if (IRQ_DMA_CHANNEL21_USED == IRQ_DMA_USED_MCALSPI_TX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL21_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiTx(IRQ_DMA_CHANNEL21_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL21_PARAM);
  }
  /* SPI RX interrupt */
  #elif (IRQ_DMA_CHANNEL21_USED == IRQ_DMA_USED_MCALSPI_RX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL21_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiRx(IRQ_DMA_CHANNEL21_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL21_PARAM);
  }
  /* ADC interrupt */
  #elif (IRQ_DMA_CHANNEL21_USED == IRQ_DMA_USED_MCALADC)

  #if (ADC_GROUP_EMUX_SCAN == STD_ON)
  Adc_IsrDmaSrn(IRQ_DMA_CHANNEL21_PARAM);
  #endif /*End of ADC_GROUP_EMUX_SCAN == STD_ON*/

  /* DMA CDD interrupt */
  #elif (IRQ_DMA_CHANNEL21_USED == IRQ_DMA_AVAILABLE)
  /* User Code Begins */
  /* Complex DMA driver usage */
  #endif
}
#endif
/******************************************************************************
** Syntax : void DMACH22SR_ISR(void)                                        **
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
** Description : Service for DMA Channel22 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if((IRQ_DMA_CHANNEL22_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL22_SR_CAT == IRQ_CAT23))
#if((IRQ_DMA_CHANNEL22_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL22_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH22SR_ISR, 0, IRQ_DMA_CHANNEL22_SR_PRIO)
#elif IRQ_DMA_CHANNEL22_SR_CAT == IRQ_CAT23
ISR(DMACH22SR_ISR)
#endif
{
  #if ((IRQ_DMA_CHANNEL22_USED == IRQ_DMA_USED_MCALSPI_TX) || \
           (IRQ_DMA_CHANNEL22_USED == IRQ_DMA_USED_MCALSPI_RX))
  uint32 DmaErrorstatus;
  #endif
  /* Enable Global Interrupts */
  Mcal_EnableAllInterrupts();

  /* SPI TX interrupt */
  #if (IRQ_DMA_CHANNEL22_USED == IRQ_DMA_USED_MCALSPI_TX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL22_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiTx(IRQ_DMA_CHANNEL22_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL22_PARAM);
  }
  /* SPI RX interrupt */
  #elif (IRQ_DMA_CHANNEL22_USED == IRQ_DMA_USED_MCALSPI_RX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL22_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiRx(IRQ_DMA_CHANNEL22_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL22_PARAM);
  }
  /* ADC interrupt */
  #elif (IRQ_DMA_CHANNEL22_USED == IRQ_DMA_USED_MCALADC)

  #if (ADC_GROUP_EMUX_SCAN == STD_ON)
  Adc_IsrDmaSrn(IRQ_DMA_CHANNEL22_PARAM);
  #endif /*End of ADC_GROUP_EMUX_SCAN == STD_ON*/

  /* DMA CDD interrupt */
  #elif (IRQ_DMA_CHANNEL22_USED == IRQ_DMA_AVAILABLE)
  /* User Code Begins */
  /* Complex DMA driver usage */
  #endif
}
#endif
/******************************************************************************
** Syntax : void DMACH23SR_ISR(void)                                        **
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
** Description : Service for DMA Channel23 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if((IRQ_DMA_CHANNEL23_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL23_SR_CAT == IRQ_CAT23))
#if((IRQ_DMA_CHANNEL23_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL23_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH23SR_ISR, 0, IRQ_DMA_CHANNEL23_SR_PRIO)
#elif IRQ_DMA_CHANNEL23_SR_CAT == IRQ_CAT23
ISR(DMACH23SR_ISR)
#endif
{
  #if ((IRQ_DMA_CHANNEL23_USED == IRQ_DMA_USED_MCALSPI_TX) || \
           (IRQ_DMA_CHANNEL23_USED == IRQ_DMA_USED_MCALSPI_RX))
  uint32 DmaErrorstatus;
  #endif
  /* Enable Global Interrupts */
  Mcal_EnableAllInterrupts();

  /* SPI TX interrupt */
  #if (IRQ_DMA_CHANNEL23_USED == IRQ_DMA_USED_MCALSPI_TX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL23_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiTx(IRQ_DMA_CHANNEL23_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL23_PARAM);
  }
  /* SPI RX interrupt */
  #elif (IRQ_DMA_CHANNEL23_USED == IRQ_DMA_USED_MCALSPI_RX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL23_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiRx(IRQ_DMA_CHANNEL23_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL23_PARAM);
  }
  /* ADC interrupt */
  #elif (IRQ_DMA_CHANNEL23_USED == IRQ_DMA_USED_MCALADC)

  #if (ADC_GROUP_EMUX_SCAN == STD_ON)
  Adc_IsrDmaSrn(IRQ_DMA_CHANNEL23_PARAM);
  #endif /*End of ADC_GROUP_EMUX_SCAN == STD_ON*/

  /* DMA CDD interrupt */
  #elif (IRQ_DMA_CHANNEL23_USED == IRQ_DMA_AVAILABLE)
  /* User Code Begins */
  /* Complex DMA driver usage */
  #endif
}
#endif
/******************************************************************************
** Syntax : void DMACH24SR_ISR(void)                                        **
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
** Description : Service for DMA Channel24 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if((IRQ_DMA_CHANNEL24_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL24_SR_CAT == IRQ_CAT23))
#if((IRQ_DMA_CHANNEL24_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL24_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH24SR_ISR, 0, IRQ_DMA_CHANNEL24_SR_PRIO)
#elif IRQ_DMA_CHANNEL24_SR_CAT == IRQ_CAT23
ISR(DMACH24SR_ISR)
#endif
{
  #if ((IRQ_DMA_CHANNEL24_USED == IRQ_DMA_USED_MCALSPI_TX) || \
           (IRQ_DMA_CHANNEL24_USED == IRQ_DMA_USED_MCALSPI_RX))
  uint32 DmaErrorstatus;
  #endif
  /* Enable Global Interrupts */
  Mcal_EnableAllInterrupts();

  /* SPI TX interrupt */
  #if (IRQ_DMA_CHANNEL24_USED == IRQ_DMA_USED_MCALSPI_TX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL24_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiTx(IRQ_DMA_CHANNEL24_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL24_PARAM);
  }
  /* SPI RX interrupt */
  #elif (IRQ_DMA_CHANNEL24_USED == IRQ_DMA_USED_MCALSPI_RX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL24_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiRx(IRQ_DMA_CHANNEL24_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL24_PARAM);
  }
  /* ADC interrupt */
  #elif (IRQ_DMA_CHANNEL24_USED == IRQ_DMA_USED_MCALADC)

  #if (ADC_GROUP_EMUX_SCAN == STD_ON)
  Adc_IsrDmaSrn(IRQ_DMA_CHANNEL24_PARAM);
  #endif /*End of ADC_GROUP_EMUX_SCAN == STD_ON*/

  /* DMA CDD interrupt */
  #elif (IRQ_DMA_CHANNEL24_USED == IRQ_DMA_AVAILABLE)
  /* User Code Begins */
  /* Complex DMA driver usage */
  #endif
}
#endif
/******************************************************************************
** Syntax : void DMACH25SR_ISR(void)                                        **
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
** Description : Service for DMA Channel25 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if((IRQ_DMA_CHANNEL25_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL25_SR_CAT == IRQ_CAT23))
#if((IRQ_DMA_CHANNEL25_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL25_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH25SR_ISR, 0, IRQ_DMA_CHANNEL25_SR_PRIO)
#elif IRQ_DMA_CHANNEL25_SR_CAT == IRQ_CAT23
ISR(DMACH25SR_ISR)
#endif
{
  #if ((IRQ_DMA_CHANNEL25_USED == IRQ_DMA_USED_MCALSPI_TX) || \
           (IRQ_DMA_CHANNEL25_USED == IRQ_DMA_USED_MCALSPI_RX))
  uint32 DmaErrorstatus;
  #endif
  /* Enable Global Interrupts */
  Mcal_EnableAllInterrupts();

  /* SPI TX interrupt */
  #if (IRQ_DMA_CHANNEL25_USED == IRQ_DMA_USED_MCALSPI_TX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL25_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiTx(IRQ_DMA_CHANNEL25_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL25_PARAM);
  }
  /* SPI RX interrupt */
  #elif (IRQ_DMA_CHANNEL25_USED == IRQ_DMA_USED_MCALSPI_RX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL25_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiRx(IRQ_DMA_CHANNEL25_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL25_PARAM);
  }
  /* ADC interrupt */
  #elif (IRQ_DMA_CHANNEL25_USED == IRQ_DMA_USED_MCALADC)

  #if (ADC_GROUP_EMUX_SCAN == STD_ON)
  Adc_IsrDmaSrn(IRQ_DMA_CHANNEL25_PARAM);
  #endif /*End of ADC_GROUP_EMUX_SCAN == STD_ON*/

  /* DMA CDD interrupt */
  #elif (IRQ_DMA_CHANNEL25_USED == IRQ_DMA_AVAILABLE)
  /* User Code Begins */
  /* Complex DMA driver usage */
  #endif
}
#endif
/******************************************************************************
** Syntax : void DMACH26SR_ISR(void)                                        **
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
** Description : Service for DMA Channel26 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if((IRQ_DMA_CHANNEL26_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL26_SR_CAT == IRQ_CAT23))
#if((IRQ_DMA_CHANNEL26_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL26_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH26SR_ISR, 0, IRQ_DMA_CHANNEL26_SR_PRIO)
#elif IRQ_DMA_CHANNEL26_SR_CAT == IRQ_CAT23
ISR(DMACH26SR_ISR)
#endif
{
  #if ((IRQ_DMA_CHANNEL26_USED == IRQ_DMA_USED_MCALSPI_TX) || \
           (IRQ_DMA_CHANNEL26_USED == IRQ_DMA_USED_MCALSPI_RX))
  uint32 DmaErrorstatus;
  #endif
  /* Enable Global Interrupts */
  Mcal_EnableAllInterrupts();

  /* SPI TX interrupt */
  #if (IRQ_DMA_CHANNEL26_USED == IRQ_DMA_USED_MCALSPI_TX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL26_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiTx(IRQ_DMA_CHANNEL26_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL26_PARAM);
  }
  /* SPI RX interrupt */
  #elif (IRQ_DMA_CHANNEL26_USED == IRQ_DMA_USED_MCALSPI_RX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL26_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiRx(IRQ_DMA_CHANNEL26_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL26_PARAM);
  }
  /* ADC interrupt */
  #elif (IRQ_DMA_CHANNEL26_USED == IRQ_DMA_USED_MCALADC)

  #if (ADC_GROUP_EMUX_SCAN == STD_ON)
  Adc_IsrDmaSrn(IRQ_DMA_CHANNEL26_PARAM);
  #endif /*End of ADC_GROUP_EMUX_SCAN == STD_ON*/

  /* DMA CDD interrupt */
  #elif (IRQ_DMA_CHANNEL26_USED == IRQ_DMA_AVAILABLE)
  /* User Code Begins */
  /* Complex DMA driver usage */
  #endif
}
#endif
/******************************************************************************
** Syntax : void DMACH27SR_ISR(void)                                        **
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
** Description : Service for DMA Channel27 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if((IRQ_DMA_CHANNEL27_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL27_SR_CAT == IRQ_CAT23))
#if((IRQ_DMA_CHANNEL27_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL27_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH27SR_ISR, 0, IRQ_DMA_CHANNEL27_SR_PRIO)
#elif IRQ_DMA_CHANNEL27_SR_CAT == IRQ_CAT23
ISR(DMACH27SR_ISR)
#endif
{
  #if ((IRQ_DMA_CHANNEL27_USED == IRQ_DMA_USED_MCALSPI_TX) || \
           (IRQ_DMA_CHANNEL27_USED == IRQ_DMA_USED_MCALSPI_RX))
  uint32 DmaErrorstatus;
  #endif
  /* Enable Global Interrupts */
  Mcal_EnableAllInterrupts();

  /* SPI TX interrupt */
  #if (IRQ_DMA_CHANNEL27_USED == IRQ_DMA_USED_MCALSPI_TX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL27_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiTx(IRQ_DMA_CHANNEL27_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL27_PARAM);
  }
  /* SPI RX interrupt */
  #elif (IRQ_DMA_CHANNEL27_USED == IRQ_DMA_USED_MCALSPI_RX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL27_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiRx(IRQ_DMA_CHANNEL27_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL27_PARAM);
  }
  /* ADC interrupt */
  #elif (IRQ_DMA_CHANNEL27_USED == IRQ_DMA_USED_MCALADC)

  #if (ADC_GROUP_EMUX_SCAN == STD_ON)
  Adc_IsrDmaSrn(IRQ_DMA_CHANNEL27_PARAM);
  #endif /*End of ADC_GROUP_EMUX_SCAN == STD_ON*/

  /* DMA CDD interrupt */
  #elif (IRQ_DMA_CHANNEL27_USED == IRQ_DMA_AVAILABLE)
  /* User Code Begins */
  /* Complex DMA driver usage */
  #endif
}
#endif
/******************************************************************************
** Syntax : void DMACH28SR_ISR(void)                                        **
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
** Description : Service for DMA Channel28 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if((IRQ_DMA_CHANNEL28_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL28_SR_CAT == IRQ_CAT23))
#if((IRQ_DMA_CHANNEL28_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL28_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH28SR_ISR, 0, IRQ_DMA_CHANNEL28_SR_PRIO)
#elif IRQ_DMA_CHANNEL28_SR_CAT == IRQ_CAT23
ISR(DMACH28SR_ISR)
#endif
{
  #if ((IRQ_DMA_CHANNEL28_USED == IRQ_DMA_USED_MCALSPI_TX) || \
           (IRQ_DMA_CHANNEL28_USED == IRQ_DMA_USED_MCALSPI_RX))
  uint32 DmaErrorstatus;
  #endif
  /* Enable Global Interrupts */
  Mcal_EnableAllInterrupts();

  /* SPI TX interrupt */
  #if (IRQ_DMA_CHANNEL28_USED == IRQ_DMA_USED_MCALSPI_TX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL28_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiTx(IRQ_DMA_CHANNEL28_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL28_PARAM);
  }
  /* SPI RX interrupt */
  #elif (IRQ_DMA_CHANNEL28_USED == IRQ_DMA_USED_MCALSPI_RX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL28_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiRx(IRQ_DMA_CHANNEL28_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL28_PARAM);
  }
  /* ADC interrupt */
  #elif (IRQ_DMA_CHANNEL28_USED == IRQ_DMA_USED_MCALADC)

  #if (ADC_GROUP_EMUX_SCAN == STD_ON)
  Adc_IsrDmaSrn(IRQ_DMA_CHANNEL28_PARAM);
  #endif /*End of ADC_GROUP_EMUX_SCAN == STD_ON*/

  /* DMA CDD interrupt */
  #elif (IRQ_DMA_CHANNEL28_USED == IRQ_DMA_AVAILABLE)
  /* User Code Begins */
  /* Complex DMA driver usage */
  #endif
}
#endif
/******************************************************************************
** Syntax : void DMACH29SR_ISR(void)                                        **
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
** Description : Service for DMA Channel29 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if((IRQ_DMA_CHANNEL29_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL29_SR_CAT == IRQ_CAT23))
#if((IRQ_DMA_CHANNEL29_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL29_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH29SR_ISR, 0, IRQ_DMA_CHANNEL29_SR_PRIO)
#elif IRQ_DMA_CHANNEL29_SR_CAT == IRQ_CAT23
ISR(DMACH29SR_ISR)
#endif
{
  #if ((IRQ_DMA_CHANNEL29_USED == IRQ_DMA_USED_MCALSPI_TX) || \
           (IRQ_DMA_CHANNEL29_USED == IRQ_DMA_USED_MCALSPI_RX))
  uint32 DmaErrorstatus;
  #endif
  /* Enable Global Interrupts */
  Mcal_EnableAllInterrupts();

  /* SPI TX interrupt */
  #if (IRQ_DMA_CHANNEL29_USED == IRQ_DMA_USED_MCALSPI_TX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL29_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiTx(IRQ_DMA_CHANNEL29_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL29_PARAM);
  }
  /* SPI RX interrupt */
  #elif (IRQ_DMA_CHANNEL29_USED == IRQ_DMA_USED_MCALSPI_RX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL29_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiRx(IRQ_DMA_CHANNEL29_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL29_PARAM);
  }
  /* ADC interrupt */
  #elif (IRQ_DMA_CHANNEL29_USED == IRQ_DMA_USED_MCALADC)

  #if (ADC_GROUP_EMUX_SCAN == STD_ON)
  Adc_IsrDmaSrn(IRQ_DMA_CHANNEL29_PARAM);
  #endif /*End of ADC_GROUP_EMUX_SCAN == STD_ON*/

  /* DMA CDD interrupt */
  #elif (IRQ_DMA_CHANNEL29_USED == IRQ_DMA_AVAILABLE)
  /* User Code Begins */
  /* Complex DMA driver usage */
  #endif
}
#endif
/******************************************************************************
** Syntax : void DMACH30SR_ISR(void)                                        **
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
** Description : Service for DMA Channel30 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if((IRQ_DMA_CHANNEL30_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL30_SR_CAT == IRQ_CAT23))
#if((IRQ_DMA_CHANNEL30_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL30_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH30SR_ISR, 0, IRQ_DMA_CHANNEL30_SR_PRIO)
#elif IRQ_DMA_CHANNEL30_SR_CAT == IRQ_CAT23
ISR(DMACH30SR_ISR)
#endif
{
  #if ((IRQ_DMA_CHANNEL30_USED == IRQ_DMA_USED_MCALSPI_TX) || \
           (IRQ_DMA_CHANNEL30_USED == IRQ_DMA_USED_MCALSPI_RX))
  uint32 DmaErrorstatus;
  #endif
  /* Enable Global Interrupts */
  Mcal_EnableAllInterrupts();

  /* SPI TX interrupt */
  #if (IRQ_DMA_CHANNEL30_USED == IRQ_DMA_USED_MCALSPI_TX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL30_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiTx(IRQ_DMA_CHANNEL30_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL30_PARAM);
  }
  /* SPI RX interrupt */
  #elif (IRQ_DMA_CHANNEL30_USED == IRQ_DMA_USED_MCALSPI_RX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL30_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiRx(IRQ_DMA_CHANNEL30_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL30_PARAM);
  }
  /* ADC interrupt */
  #elif (IRQ_DMA_CHANNEL30_USED == IRQ_DMA_USED_MCALADC)

  #if (ADC_GROUP_EMUX_SCAN == STD_ON)
  Adc_IsrDmaSrn(IRQ_DMA_CHANNEL30_PARAM);
  #endif /*End of ADC_GROUP_EMUX_SCAN == STD_ON*/

  /* DMA CDD interrupt */
  #elif (IRQ_DMA_CHANNEL30_USED == IRQ_DMA_AVAILABLE)
  /* User Code Begins */
  /* Complex DMA driver usage */
  #endif
}
#endif
/******************************************************************************
** Syntax : void DMACH31SR_ISR(void)                                        **
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
** Description : Service for DMA Channel31 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if((IRQ_DMA_CHANNEL31_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL31_SR_CAT == IRQ_CAT23))
#if((IRQ_DMA_CHANNEL31_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL31_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH31SR_ISR, 0, IRQ_DMA_CHANNEL31_SR_PRIO)
#elif IRQ_DMA_CHANNEL31_SR_CAT == IRQ_CAT23
ISR(DMACH31SR_ISR)
#endif
{
  #if ((IRQ_DMA_CHANNEL31_USED == IRQ_DMA_USED_MCALSPI_TX) || \
           (IRQ_DMA_CHANNEL31_USED == IRQ_DMA_USED_MCALSPI_RX))
  uint32 DmaErrorstatus;
  #endif
  /* Enable Global Interrupts */
  Mcal_EnableAllInterrupts();

  /* SPI TX interrupt */
  #if (IRQ_DMA_CHANNEL31_USED == IRQ_DMA_USED_MCALSPI_TX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL31_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiTx(IRQ_DMA_CHANNEL31_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL31_PARAM);
  }
  /* SPI RX interrupt */
  #elif (IRQ_DMA_CHANNEL31_USED == IRQ_DMA_USED_MCALSPI_RX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL31_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiRx(IRQ_DMA_CHANNEL31_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL31_PARAM);
  }
  /* ADC interrupt */
  #elif (IRQ_DMA_CHANNEL31_USED == IRQ_DMA_USED_MCALADC)

  #if (ADC_GROUP_EMUX_SCAN == STD_ON)
  Adc_IsrDmaSrn(IRQ_DMA_CHANNEL31_PARAM);
  #endif /*End of ADC_GROUP_EMUX_SCAN == STD_ON*/

  /* DMA CDD interrupt */
  #elif (IRQ_DMA_CHANNEL31_USED == IRQ_DMA_AVAILABLE)
  /* User Code Begins */
  /* Complex DMA driver usage */
  #endif
}
#endif
/******************************************************************************
** Syntax : void DMACH32SR_ISR(void)                                        **
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
** Description : Service for DMA Channel32 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if((IRQ_DMA_CHANNEL32_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL32_SR_CAT == IRQ_CAT23))
#if((IRQ_DMA_CHANNEL32_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL32_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH32SR_ISR, 0, IRQ_DMA_CHANNEL32_SR_PRIO)
#elif IRQ_DMA_CHANNEL32_SR_CAT == IRQ_CAT23
ISR(DMACH32SR_ISR)
#endif
{
  #if ((IRQ_DMA_CHANNEL32_USED == IRQ_DMA_USED_MCALSPI_TX) || \
           (IRQ_DMA_CHANNEL32_USED == IRQ_DMA_USED_MCALSPI_RX))
  uint32 DmaErrorstatus;
  #endif
  /* Enable Global Interrupts */
  Mcal_EnableAllInterrupts();

  /* SPI TX interrupt */
  #if (IRQ_DMA_CHANNEL32_USED == IRQ_DMA_USED_MCALSPI_TX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL32_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiTx(IRQ_DMA_CHANNEL32_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL32_PARAM);
  }
  /* SPI RX interrupt */
  #elif (IRQ_DMA_CHANNEL32_USED == IRQ_DMA_USED_MCALSPI_RX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL32_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiRx(IRQ_DMA_CHANNEL32_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL32_PARAM);
  }
  /* ADC interrupt */
  #elif (IRQ_DMA_CHANNEL32_USED == IRQ_DMA_USED_MCALADC)

  #if (ADC_GROUP_EMUX_SCAN == STD_ON)
  Adc_IsrDmaSrn(IRQ_DMA_CHANNEL32_PARAM);
  #endif /*End of ADC_GROUP_EMUX_SCAN == STD_ON*/

  /* DMA CDD interrupt */
  #elif (IRQ_DMA_CHANNEL32_USED == IRQ_DMA_AVAILABLE)
  /* User Code Begins */
  /* Complex DMA driver usage */
  #endif
}
#endif
/******************************************************************************
** Syntax : void DMACH33SR_ISR(void)                                        **
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
** Description : Service for DMA Channel33 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if((IRQ_DMA_CHANNEL33_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL33_SR_CAT == IRQ_CAT23))
#if((IRQ_DMA_CHANNEL33_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL33_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH33SR_ISR, 0, IRQ_DMA_CHANNEL33_SR_PRIO)
#elif IRQ_DMA_CHANNEL33_SR_CAT == IRQ_CAT23
ISR(DMACH33SR_ISR)
#endif
{
  #if ((IRQ_DMA_CHANNEL33_USED == IRQ_DMA_USED_MCALSPI_TX) || \
           (IRQ_DMA_CHANNEL33_USED == IRQ_DMA_USED_MCALSPI_RX))
  uint32 DmaErrorstatus;
  #endif
  /* Enable Global Interrupts */
  Mcal_EnableAllInterrupts();

  /* SPI TX interrupt */
  #if (IRQ_DMA_CHANNEL33_USED == IRQ_DMA_USED_MCALSPI_TX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL33_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiTx(IRQ_DMA_CHANNEL33_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL33_PARAM);
  }
  /* SPI RX interrupt */
  #elif (IRQ_DMA_CHANNEL33_USED == IRQ_DMA_USED_MCALSPI_RX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL33_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiRx(IRQ_DMA_CHANNEL33_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL33_PARAM);
  }
  /* ADC interrupt */
  #elif (IRQ_DMA_CHANNEL33_USED == IRQ_DMA_USED_MCALADC)

  #if (ADC_GROUP_EMUX_SCAN == STD_ON)
  Adc_IsrDmaSrn(IRQ_DMA_CHANNEL33_PARAM);
  #endif /*End of ADC_GROUP_EMUX_SCAN == STD_ON*/

  /* DMA CDD interrupt */
  #elif (IRQ_DMA_CHANNEL33_USED == IRQ_DMA_AVAILABLE)
  /* User Code Begins */
  /* Complex DMA driver usage */
  #endif
}
#endif
/******************************************************************************
** Syntax : void DMACH34SR_ISR(void)                                        **
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
** Description : Service for DMA Channel34 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if((IRQ_DMA_CHANNEL34_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL34_SR_CAT == IRQ_CAT23))
#if((IRQ_DMA_CHANNEL34_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL34_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH34SR_ISR, 0, IRQ_DMA_CHANNEL34_SR_PRIO)
#elif IRQ_DMA_CHANNEL34_SR_CAT == IRQ_CAT23
ISR(DMACH34SR_ISR)
#endif
{
  #if ((IRQ_DMA_CHANNEL34_USED == IRQ_DMA_USED_MCALSPI_TX) || \
           (IRQ_DMA_CHANNEL34_USED == IRQ_DMA_USED_MCALSPI_RX))
  uint32 DmaErrorstatus;
  #endif
  /* Enable Global Interrupts */
  Mcal_EnableAllInterrupts();

  /* SPI TX interrupt */
  #if (IRQ_DMA_CHANNEL34_USED == IRQ_DMA_USED_MCALSPI_TX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL34_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiTx(IRQ_DMA_CHANNEL34_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL34_PARAM);
  }
  /* SPI RX interrupt */
  #elif (IRQ_DMA_CHANNEL34_USED == IRQ_DMA_USED_MCALSPI_RX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL34_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiRx(IRQ_DMA_CHANNEL34_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL34_PARAM);
  }
  /* ADC interrupt */
  #elif (IRQ_DMA_CHANNEL34_USED == IRQ_DMA_USED_MCALADC)

  #if (ADC_GROUP_EMUX_SCAN == STD_ON)
  Adc_IsrDmaSrn(IRQ_DMA_CHANNEL34_PARAM);
  #endif /*End of ADC_GROUP_EMUX_SCAN == STD_ON*/

  /* DMA CDD interrupt */
  #elif (IRQ_DMA_CHANNEL34_USED == IRQ_DMA_AVAILABLE)
  /* User Code Begins */
  /* Complex DMA driver usage */
  #endif
}
#endif
/******************************************************************************
** Syntax : void DMACH35SR_ISR(void)                                        **
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
** Description : Service for DMA Channel35 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if((IRQ_DMA_CHANNEL35_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL35_SR_CAT == IRQ_CAT23))
#if((IRQ_DMA_CHANNEL35_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL35_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH35SR_ISR, 0, IRQ_DMA_CHANNEL35_SR_PRIO)
#elif IRQ_DMA_CHANNEL35_SR_CAT == IRQ_CAT23
ISR(DMACH35SR_ISR)
#endif
{
  #if ((IRQ_DMA_CHANNEL35_USED == IRQ_DMA_USED_MCALSPI_TX) || \
           (IRQ_DMA_CHANNEL35_USED == IRQ_DMA_USED_MCALSPI_RX))
  uint32 DmaErrorstatus;
  #endif
  /* Enable Global Interrupts */
  Mcal_EnableAllInterrupts();

  /* SPI TX interrupt */
  #if (IRQ_DMA_CHANNEL35_USED == IRQ_DMA_USED_MCALSPI_TX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL35_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiTx(IRQ_DMA_CHANNEL35_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL35_PARAM);
  }
  /* SPI RX interrupt */
  #elif (IRQ_DMA_CHANNEL35_USED == IRQ_DMA_USED_MCALSPI_RX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL35_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiRx(IRQ_DMA_CHANNEL35_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL35_PARAM);
  }
  /* ADC interrupt */
  #elif (IRQ_DMA_CHANNEL35_USED == IRQ_DMA_USED_MCALADC)

  #if (ADC_GROUP_EMUX_SCAN == STD_ON)
  Adc_IsrDmaSrn(IRQ_DMA_CHANNEL35_PARAM);
  #endif /*End of ADC_GROUP_EMUX_SCAN == STD_ON*/

  /* DMA CDD interrupt */
  #elif (IRQ_DMA_CHANNEL35_USED == IRQ_DMA_AVAILABLE)
  /* User Code Begins */
  /* Complex DMA driver usage */
  #endif
}
#endif
/******************************************************************************
** Syntax : void DMACH36SR_ISR(void)                                        **
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
** Description : Service for DMA Channel36 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if((IRQ_DMA_CHANNEL36_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL36_SR_CAT == IRQ_CAT23))
#if((IRQ_DMA_CHANNEL36_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL36_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH36SR_ISR, 0, IRQ_DMA_CHANNEL36_SR_PRIO)
#elif IRQ_DMA_CHANNEL36_SR_CAT == IRQ_CAT23
ISR(DMACH36SR_ISR)
#endif
{
  #if ((IRQ_DMA_CHANNEL36_USED == IRQ_DMA_USED_MCALSPI_TX) || \
           (IRQ_DMA_CHANNEL36_USED == IRQ_DMA_USED_MCALSPI_RX))
  uint32 DmaErrorstatus;
  #endif
  /* Enable Global Interrupts */
  Mcal_EnableAllInterrupts();

  /* SPI TX interrupt */
  #if (IRQ_DMA_CHANNEL36_USED == IRQ_DMA_USED_MCALSPI_TX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL36_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiTx(IRQ_DMA_CHANNEL36_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL36_PARAM);
  }
  /* SPI RX interrupt */
  #elif (IRQ_DMA_CHANNEL36_USED == IRQ_DMA_USED_MCALSPI_RX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL36_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiRx(IRQ_DMA_CHANNEL36_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL36_PARAM);
  }
  /* ADC interrupt */
  #elif (IRQ_DMA_CHANNEL36_USED == IRQ_DMA_USED_MCALADC)

  #if (ADC_GROUP_EMUX_SCAN == STD_ON)
  Adc_IsrDmaSrn(IRQ_DMA_CHANNEL36_PARAM);
  #endif /*End of ADC_GROUP_EMUX_SCAN == STD_ON*/

  /* DMA CDD interrupt */
  #elif (IRQ_DMA_CHANNEL36_USED == IRQ_DMA_AVAILABLE)
  /* User Code Begins */
  /* Complex DMA driver usage */
  #endif
}
#endif
/******************************************************************************
** Syntax : void DMACH37SR_ISR(void)                                        **
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
** Description : Service for DMA Channel37 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if((IRQ_DMA_CHANNEL37_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL37_SR_CAT == IRQ_CAT23))
#if((IRQ_DMA_CHANNEL37_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL37_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH37SR_ISR, 0, IRQ_DMA_CHANNEL37_SR_PRIO)
#elif IRQ_DMA_CHANNEL37_SR_CAT == IRQ_CAT23
ISR(DMACH37SR_ISR)
#endif
{
  #if ((IRQ_DMA_CHANNEL37_USED == IRQ_DMA_USED_MCALSPI_TX) || \
           (IRQ_DMA_CHANNEL37_USED == IRQ_DMA_USED_MCALSPI_RX))
  uint32 DmaErrorstatus;
  #endif
  /* Enable Global Interrupts */
  Mcal_EnableAllInterrupts();

  /* SPI TX interrupt */
  #if (IRQ_DMA_CHANNEL37_USED == IRQ_DMA_USED_MCALSPI_TX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL37_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiTx(IRQ_DMA_CHANNEL37_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL37_PARAM);
  }
  /* SPI RX interrupt */
  #elif (IRQ_DMA_CHANNEL37_USED == IRQ_DMA_USED_MCALSPI_RX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL37_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiRx(IRQ_DMA_CHANNEL37_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL37_PARAM);
  }
  /* ADC interrupt */
  #elif (IRQ_DMA_CHANNEL37_USED == IRQ_DMA_USED_MCALADC)

  #if (ADC_GROUP_EMUX_SCAN == STD_ON)
  Adc_IsrDmaSrn(IRQ_DMA_CHANNEL37_PARAM);
  #endif /*End of ADC_GROUP_EMUX_SCAN == STD_ON*/

  /* DMA CDD interrupt */
  #elif (IRQ_DMA_CHANNEL37_USED == IRQ_DMA_AVAILABLE)
  /* User Code Begins */
  /* Complex DMA driver usage */
  #endif
}
#endif
/******************************************************************************
** Syntax : void DMACH38SR_ISR(void)                                        **
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
** Description : Service for DMA Channel38 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if((IRQ_DMA_CHANNEL38_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL38_SR_CAT == IRQ_CAT23))
#if((IRQ_DMA_CHANNEL38_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL38_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH38SR_ISR, 0, IRQ_DMA_CHANNEL38_SR_PRIO)
#elif IRQ_DMA_CHANNEL38_SR_CAT == IRQ_CAT23
ISR(DMACH38SR_ISR)
#endif
{
  #if ((IRQ_DMA_CHANNEL38_USED == IRQ_DMA_USED_MCALSPI_TX) || \
           (IRQ_DMA_CHANNEL38_USED == IRQ_DMA_USED_MCALSPI_RX))
  uint32 DmaErrorstatus;
  #endif
  /* Enable Global Interrupts */
  Mcal_EnableAllInterrupts();

  /* SPI TX interrupt */
  #if (IRQ_DMA_CHANNEL38_USED == IRQ_DMA_USED_MCALSPI_TX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL38_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiTx(IRQ_DMA_CHANNEL38_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL38_PARAM);
  }
  /* SPI RX interrupt */
  #elif (IRQ_DMA_CHANNEL38_USED == IRQ_DMA_USED_MCALSPI_RX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL38_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiRx(IRQ_DMA_CHANNEL38_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL38_PARAM);
  }
  /* ADC interrupt */
  #elif (IRQ_DMA_CHANNEL38_USED == IRQ_DMA_USED_MCALADC)

  #if (ADC_GROUP_EMUX_SCAN == STD_ON)
  Adc_IsrDmaSrn(IRQ_DMA_CHANNEL38_PARAM);
  #endif /*End of ADC_GROUP_EMUX_SCAN == STD_ON*/

  /* DMA CDD interrupt */
  #elif (IRQ_DMA_CHANNEL38_USED == IRQ_DMA_AVAILABLE)
  /* User Code Begins */
  /* Complex DMA driver usage */
  #endif
}
#endif
/******************************************************************************
** Syntax : void DMACH39SR_ISR(void)                                        **
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
** Description : Service for DMA Channel39 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if((IRQ_DMA_CHANNEL39_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL39_SR_CAT == IRQ_CAT23))
#if((IRQ_DMA_CHANNEL39_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL39_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH39SR_ISR, 0, IRQ_DMA_CHANNEL39_SR_PRIO)
#elif IRQ_DMA_CHANNEL39_SR_CAT == IRQ_CAT23
ISR(DMACH39SR_ISR)
#endif
{
  #if ((IRQ_DMA_CHANNEL39_USED == IRQ_DMA_USED_MCALSPI_TX) || \
           (IRQ_DMA_CHANNEL39_USED == IRQ_DMA_USED_MCALSPI_RX))
  uint32 DmaErrorstatus;
  #endif
  /* Enable Global Interrupts */
  Mcal_EnableAllInterrupts();

  /* SPI TX interrupt */
  #if (IRQ_DMA_CHANNEL39_USED == IRQ_DMA_USED_MCALSPI_TX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL39_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiTx(IRQ_DMA_CHANNEL39_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL39_PARAM);
  }
  /* SPI RX interrupt */
  #elif (IRQ_DMA_CHANNEL39_USED == IRQ_DMA_USED_MCALSPI_RX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL39_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiRx(IRQ_DMA_CHANNEL39_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL39_PARAM);
  }
  /* ADC interrupt */
  #elif (IRQ_DMA_CHANNEL39_USED == IRQ_DMA_USED_MCALADC)

  #if (ADC_GROUP_EMUX_SCAN == STD_ON)
  Adc_IsrDmaSrn(IRQ_DMA_CHANNEL39_PARAM);
  #endif /*End of ADC_GROUP_EMUX_SCAN == STD_ON*/

  /* DMA CDD interrupt */
  #elif (IRQ_DMA_CHANNEL39_USED == IRQ_DMA_AVAILABLE)
  /* User Code Begins */
  /* Complex DMA driver usage */
  #endif
}
#endif
/******************************************************************************
** Syntax : void DMACH40SR_ISR(void)                                        **
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
** Description : Service for DMA Channel40 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if((IRQ_DMA_CHANNEL40_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL40_SR_CAT == IRQ_CAT23))
#if((IRQ_DMA_CHANNEL40_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL40_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH40SR_ISR, 0, IRQ_DMA_CHANNEL40_SR_PRIO)
#elif IRQ_DMA_CHANNEL40_SR_CAT == IRQ_CAT23
ISR(DMACH40SR_ISR)
#endif
{
  #if ((IRQ_DMA_CHANNEL40_USED == IRQ_DMA_USED_MCALSPI_TX) || \
           (IRQ_DMA_CHANNEL40_USED == IRQ_DMA_USED_MCALSPI_RX))
  uint32 DmaErrorstatus;
  #endif
  /* Enable Global Interrupts */
  Mcal_EnableAllInterrupts();

  /* SPI TX interrupt */
  #if (IRQ_DMA_CHANNEL40_USED == IRQ_DMA_USED_MCALSPI_TX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL40_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiTx(IRQ_DMA_CHANNEL40_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL40_PARAM);
  }
  /* SPI RX interrupt */
  #elif (IRQ_DMA_CHANNEL40_USED == IRQ_DMA_USED_MCALSPI_RX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL40_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiRx(IRQ_DMA_CHANNEL40_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL40_PARAM);
  }
  /* ADC interrupt */
  #elif (IRQ_DMA_CHANNEL40_USED == IRQ_DMA_USED_MCALADC)

  #if (ADC_GROUP_EMUX_SCAN == STD_ON)
  Adc_IsrDmaSrn(IRQ_DMA_CHANNEL40_PARAM);
  #endif /*End of ADC_GROUP_EMUX_SCAN == STD_ON*/

  /* DMA CDD interrupt */
  #elif (IRQ_DMA_CHANNEL40_USED == IRQ_DMA_AVAILABLE)
  /* User Code Begins */
  /* Complex DMA driver usage */
  #endif
}
#endif
/******************************************************************************
** Syntax : void DMACH41SR_ISR(void)                                        **
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
** Description : Service for DMA Channel41 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if((IRQ_DMA_CHANNEL41_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL41_SR_CAT == IRQ_CAT23))
#if((IRQ_DMA_CHANNEL41_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL41_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH41SR_ISR, 0, IRQ_DMA_CHANNEL41_SR_PRIO)
#elif IRQ_DMA_CHANNEL41_SR_CAT == IRQ_CAT23
ISR(DMACH41SR_ISR)
#endif
{
  #if ((IRQ_DMA_CHANNEL41_USED == IRQ_DMA_USED_MCALSPI_TX) || \
           (IRQ_DMA_CHANNEL41_USED == IRQ_DMA_USED_MCALSPI_RX))
  uint32 DmaErrorstatus;
  #endif
  /* Enable Global Interrupts */
  Mcal_EnableAllInterrupts();

  /* SPI TX interrupt */
  #if (IRQ_DMA_CHANNEL41_USED == IRQ_DMA_USED_MCALSPI_TX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL41_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiTx(IRQ_DMA_CHANNEL41_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL41_PARAM);
  }
  /* SPI RX interrupt */
  #elif (IRQ_DMA_CHANNEL41_USED == IRQ_DMA_USED_MCALSPI_RX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL41_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiRx(IRQ_DMA_CHANNEL41_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL41_PARAM);
  }
  /* ADC interrupt */
  #elif (IRQ_DMA_CHANNEL41_USED == IRQ_DMA_USED_MCALADC)

  #if (ADC_GROUP_EMUX_SCAN == STD_ON)
  Adc_IsrDmaSrn(IRQ_DMA_CHANNEL41_PARAM);
  #endif /*End of ADC_GROUP_EMUX_SCAN == STD_ON*/

  /* DMA CDD interrupt */
  #elif (IRQ_DMA_CHANNEL41_USED == IRQ_DMA_AVAILABLE)
  /* User Code Begins */
  /* Complex DMA driver usage */
  #endif
}
#endif
/******************************************************************************
** Syntax : void DMACH42SR_ISR(void)                                        **
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
** Description : Service for DMA Channel42 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if((IRQ_DMA_CHANNEL42_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL42_SR_CAT == IRQ_CAT23))
#if((IRQ_DMA_CHANNEL42_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL42_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH42SR_ISR, 0, IRQ_DMA_CHANNEL42_SR_PRIO)
#elif IRQ_DMA_CHANNEL42_SR_CAT == IRQ_CAT23
ISR(DMACH42SR_ISR)
#endif
{
  #if ((IRQ_DMA_CHANNEL42_USED == IRQ_DMA_USED_MCALSPI_TX) || \
           (IRQ_DMA_CHANNEL42_USED == IRQ_DMA_USED_MCALSPI_RX))
  uint32 DmaErrorstatus;
  #endif
  /* Enable Global Interrupts */
  Mcal_EnableAllInterrupts();

  /* SPI TX interrupt */
  #if (IRQ_DMA_CHANNEL42_USED == IRQ_DMA_USED_MCALSPI_TX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL42_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiTx(IRQ_DMA_CHANNEL42_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL42_PARAM);
  }
  /* SPI RX interrupt */
  #elif (IRQ_DMA_CHANNEL42_USED == IRQ_DMA_USED_MCALSPI_RX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL42_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiRx(IRQ_DMA_CHANNEL42_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL42_PARAM);
  }
  /* ADC interrupt */
  #elif (IRQ_DMA_CHANNEL42_USED == IRQ_DMA_USED_MCALADC)

  #if (ADC_GROUP_EMUX_SCAN == STD_ON)
  Adc_IsrDmaSrn(IRQ_DMA_CHANNEL42_PARAM);
  #endif /*End of ADC_GROUP_EMUX_SCAN == STD_ON*/

  /* DMA CDD interrupt */
  #elif (IRQ_DMA_CHANNEL42_USED == IRQ_DMA_AVAILABLE)
  /* User Code Begins */
  /* Complex DMA driver usage */
  #endif
}
#endif
/******************************************************************************
** Syntax : void DMACH43SR_ISR(void)                                        **
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
** Description : Service for DMA Channel43 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if((IRQ_DMA_CHANNEL43_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL43_SR_CAT == IRQ_CAT23))
#if((IRQ_DMA_CHANNEL43_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL43_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH43SR_ISR, 0, IRQ_DMA_CHANNEL43_SR_PRIO)
#elif IRQ_DMA_CHANNEL43_SR_CAT == IRQ_CAT23
ISR(DMACH43SR_ISR)
#endif
{
  #if ((IRQ_DMA_CHANNEL43_USED == IRQ_DMA_USED_MCALSPI_TX) || \
           (IRQ_DMA_CHANNEL43_USED == IRQ_DMA_USED_MCALSPI_RX))
  uint32 DmaErrorstatus;
  #endif
  /* Enable Global Interrupts */
  Mcal_EnableAllInterrupts();

  /* SPI TX interrupt */
  #if (IRQ_DMA_CHANNEL43_USED == IRQ_DMA_USED_MCALSPI_TX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL43_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiTx(IRQ_DMA_CHANNEL43_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL43_PARAM);
  }
  /* SPI RX interrupt */
  #elif (IRQ_DMA_CHANNEL43_USED == IRQ_DMA_USED_MCALSPI_RX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL43_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiRx(IRQ_DMA_CHANNEL43_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL43_PARAM);
  }
  /* ADC interrupt */
  #elif (IRQ_DMA_CHANNEL43_USED == IRQ_DMA_USED_MCALADC)

  #if (ADC_GROUP_EMUX_SCAN == STD_ON)
  Adc_IsrDmaSrn(IRQ_DMA_CHANNEL43_PARAM);
  #endif /*End of ADC_GROUP_EMUX_SCAN == STD_ON*/

  /* DMA CDD interrupt */
  #elif (IRQ_DMA_CHANNEL43_USED == IRQ_DMA_AVAILABLE)
  /* User Code Begins */
  /* Complex DMA driver usage */
  #endif
}
#endif
/******************************************************************************
** Syntax : void DMACH44SR_ISR(void)                                        **
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
** Description : Service for DMA Channel44 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if((IRQ_DMA_CHANNEL44_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL44_SR_CAT == IRQ_CAT23))
#if((IRQ_DMA_CHANNEL44_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL44_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH44SR_ISR, 0, IRQ_DMA_CHANNEL44_SR_PRIO)
#elif IRQ_DMA_CHANNEL44_SR_CAT == IRQ_CAT23
ISR(DMACH44SR_ISR)
#endif
{
  #if ((IRQ_DMA_CHANNEL44_USED == IRQ_DMA_USED_MCALSPI_TX) || \
           (IRQ_DMA_CHANNEL44_USED == IRQ_DMA_USED_MCALSPI_RX))
  uint32 DmaErrorstatus;
  #endif
  /* Enable Global Interrupts */
  Mcal_EnableAllInterrupts();

  /* SPI TX interrupt */
  #if (IRQ_DMA_CHANNEL44_USED == IRQ_DMA_USED_MCALSPI_TX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL44_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiTx(IRQ_DMA_CHANNEL44_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL44_PARAM);
  }
  /* SPI RX interrupt */
  #elif (IRQ_DMA_CHANNEL44_USED == IRQ_DMA_USED_MCALSPI_RX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL44_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiRx(IRQ_DMA_CHANNEL44_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL44_PARAM);
  }
  /* ADC interrupt */
  #elif (IRQ_DMA_CHANNEL44_USED == IRQ_DMA_USED_MCALADC)

  #if (ADC_GROUP_EMUX_SCAN == STD_ON)
  Adc_IsrDmaSrn(IRQ_DMA_CHANNEL44_PARAM);
  #endif /*End of ADC_GROUP_EMUX_SCAN == STD_ON*/

  /* DMA CDD interrupt */
  #elif (IRQ_DMA_CHANNEL44_USED == IRQ_DMA_AVAILABLE)
  /* User Code Begins */
  /* Complex DMA driver usage */
  #endif
}
#endif
/******************************************************************************
** Syntax : void DMACH45SR_ISR(void)                                        **
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
** Description : Service for DMA Channel45 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if((IRQ_DMA_CHANNEL45_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL45_SR_CAT == IRQ_CAT23))
#if((IRQ_DMA_CHANNEL45_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL45_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH45SR_ISR, 0, IRQ_DMA_CHANNEL45_SR_PRIO)
#elif IRQ_DMA_CHANNEL45_SR_CAT == IRQ_CAT23
ISR(DMACH45SR_ISR)
#endif
{
  #if ((IRQ_DMA_CHANNEL45_USED == IRQ_DMA_USED_MCALSPI_TX) || \
           (IRQ_DMA_CHANNEL45_USED == IRQ_DMA_USED_MCALSPI_RX))
  uint32 DmaErrorstatus;
  #endif
  /* Enable Global Interrupts */
  Mcal_EnableAllInterrupts();

  /* SPI TX interrupt */
  #if (IRQ_DMA_CHANNEL45_USED == IRQ_DMA_USED_MCALSPI_TX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL45_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiTx(IRQ_DMA_CHANNEL45_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL45_PARAM);
  }
  /* SPI RX interrupt */
  #elif (IRQ_DMA_CHANNEL45_USED == IRQ_DMA_USED_MCALSPI_RX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL45_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiRx(IRQ_DMA_CHANNEL45_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL45_PARAM);
  }
  /* ADC interrupt */
  #elif (IRQ_DMA_CHANNEL45_USED == IRQ_DMA_USED_MCALADC)

  #if (ADC_GROUP_EMUX_SCAN == STD_ON)
  Adc_IsrDmaSrn(IRQ_DMA_CHANNEL45_PARAM);
  #endif /*End of ADC_GROUP_EMUX_SCAN == STD_ON*/

  /* DMA CDD interrupt */
  #elif (IRQ_DMA_CHANNEL45_USED == IRQ_DMA_AVAILABLE)
  /* User Code Begins */
  /* Complex DMA driver usage */
  #endif
}
#endif
/******************************************************************************
** Syntax : void DMACH46SR_ISR(void)                                        **
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
** Description : Service for DMA Channel46 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if((IRQ_DMA_CHANNEL46_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL46_SR_CAT == IRQ_CAT23))
#if((IRQ_DMA_CHANNEL46_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL46_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH46SR_ISR, 0, IRQ_DMA_CHANNEL46_SR_PRIO)
#elif IRQ_DMA_CHANNEL46_SR_CAT == IRQ_CAT23
ISR(DMACH46SR_ISR)
#endif
{
  #if ((IRQ_DMA_CHANNEL46_USED == IRQ_DMA_USED_MCALSPI_TX) || \
           (IRQ_DMA_CHANNEL46_USED == IRQ_DMA_USED_MCALSPI_RX))
  uint32 DmaErrorstatus;
  #endif
  /* Enable Global Interrupts */
  Mcal_EnableAllInterrupts();

  /* SPI TX interrupt */
  #if (IRQ_DMA_CHANNEL46_USED == IRQ_DMA_USED_MCALSPI_TX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL46_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiTx(IRQ_DMA_CHANNEL46_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL46_PARAM);
  }
  /* SPI RX interrupt */
  #elif (IRQ_DMA_CHANNEL46_USED == IRQ_DMA_USED_MCALSPI_RX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL46_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiRx(IRQ_DMA_CHANNEL46_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL46_PARAM);
  }
  /* ADC interrupt */
  #elif (IRQ_DMA_CHANNEL46_USED == IRQ_DMA_USED_MCALADC)

  #if (ADC_GROUP_EMUX_SCAN == STD_ON)
  Adc_IsrDmaSrn(IRQ_DMA_CHANNEL46_PARAM);
  #endif /*End of ADC_GROUP_EMUX_SCAN == STD_ON*/

  /* DMA CDD interrupt */
  #elif (IRQ_DMA_CHANNEL46_USED == IRQ_DMA_AVAILABLE)
  /* User Code Begins */
  /* Complex DMA driver usage */
  #endif
}
#endif
/******************************************************************************
** Syntax : void DMACH47SR_ISR(void)                                        **
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
** Description : Service for DMA Channel47 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if((IRQ_DMA_CHANNEL47_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL47_SR_CAT == IRQ_CAT23))
#if((IRQ_DMA_CHANNEL47_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL47_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH47SR_ISR, 0, IRQ_DMA_CHANNEL47_SR_PRIO)
#elif IRQ_DMA_CHANNEL47_SR_CAT == IRQ_CAT23
ISR(DMACH47SR_ISR)
#endif
{
  #if ((IRQ_DMA_CHANNEL47_USED == IRQ_DMA_USED_MCALSPI_TX) || \
           (IRQ_DMA_CHANNEL47_USED == IRQ_DMA_USED_MCALSPI_RX))
  uint32 DmaErrorstatus;
  #endif
  /* Enable Global Interrupts */
  Mcal_EnableAllInterrupts();

  /* SPI TX interrupt */
  #if (IRQ_DMA_CHANNEL47_USED == IRQ_DMA_USED_MCALSPI_TX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL47_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiTx(IRQ_DMA_CHANNEL47_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL47_PARAM);
  }
  /* SPI RX interrupt */
  #elif (IRQ_DMA_CHANNEL47_USED == IRQ_DMA_USED_MCALSPI_RX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL47_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiRx(IRQ_DMA_CHANNEL47_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL47_PARAM);
  }
  /* ADC interrupt */
  #elif (IRQ_DMA_CHANNEL47_USED == IRQ_DMA_USED_MCALADC)

  #if (ADC_GROUP_EMUX_SCAN == STD_ON)
  Adc_IsrDmaSrn(IRQ_DMA_CHANNEL47_PARAM);
  #endif /*End of ADC_GROUP_EMUX_SCAN == STD_ON*/

  /* DMA CDD interrupt */
  #elif (IRQ_DMA_CHANNEL47_USED == IRQ_DMA_AVAILABLE)
  /* User Code Begins */
  /* Complex DMA driver usage */
  #endif
}
#endif
#endif/*end of IRQ_DMA_CH0TO47_EXIST*/

#if (IRQ_DMA_CH48TO63_EXIST == STD_ON)
/******************************************************************************
** Syntax : void DMACH48SR_ISR(void)                                        **
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
** Description : Service for DMA Channel48 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if((IRQ_DMA_CHANNEL48_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL48_SR_CAT == IRQ_CAT23))
#if((IRQ_DMA_CHANNEL48_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL48_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH48SR_ISR, 0, IRQ_DMA_CHANNEL48_SR_PRIO)
#elif IRQ_DMA_CHANNEL48_SR_CAT == IRQ_CAT23
ISR(DMACH48SR_ISR)
#endif
{
  #if ((IRQ_DMA_CHANNEL48_USED == IRQ_DMA_USED_MCALSPI_TX) || \
           (IRQ_DMA_CHANNEL48_USED == IRQ_DMA_USED_MCALSPI_RX))
  uint32 DmaErrorstatus;
  #endif
  /* Enable Global Interrupts */
  Mcal_EnableAllInterrupts();

  /* SPI TX interrupt */
  #if (IRQ_DMA_CHANNEL48_USED == IRQ_DMA_USED_MCALSPI_TX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL48_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiTx(IRQ_DMA_CHANNEL48_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL48_PARAM);
  }
  /* SPI RX interrupt */
  #elif (IRQ_DMA_CHANNEL48_USED == IRQ_DMA_USED_MCALSPI_RX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL48_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiRx(IRQ_DMA_CHANNEL48_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL48_PARAM);
  }
  /* ADC interrupt */
  #elif (IRQ_DMA_CHANNEL48_USED == IRQ_DMA_USED_MCALADC)

  #if (ADC_GROUP_EMUX_SCAN == STD_ON)
  Adc_IsrDmaSrn(IRQ_DMA_CHANNEL48_PARAM);
  #endif /*End of ADC_GROUP_EMUX_SCAN == STD_ON*/

  /* DMA CDD interrupt */
  #elif (IRQ_DMA_CHANNEL48_USED == IRQ_DMA_AVAILABLE)
  /* User Code Begins */
  /* Complex DMA driver usage */
  #endif
}
#endif
/******************************************************************************
** Syntax : void DMACH49SR_ISR(void)                                        **
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
** Description : Service for DMA Channel49 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if((IRQ_DMA_CHANNEL49_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL49_SR_CAT == IRQ_CAT23))
#if((IRQ_DMA_CHANNEL49_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL49_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH49SR_ISR, 0, IRQ_DMA_CHANNEL49_SR_PRIO)
#elif IRQ_DMA_CHANNEL49_SR_CAT == IRQ_CAT23
ISR(DMACH49SR_ISR)
#endif
{
  #if ((IRQ_DMA_CHANNEL49_USED == IRQ_DMA_USED_MCALSPI_TX) || \
           (IRQ_DMA_CHANNEL49_USED == IRQ_DMA_USED_MCALSPI_RX))
  uint32 DmaErrorstatus;
  #endif
  /* Enable Global Interrupts */
  Mcal_EnableAllInterrupts();

  /* SPI TX interrupt */
  #if (IRQ_DMA_CHANNEL49_USED == IRQ_DMA_USED_MCALSPI_TX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL49_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiTx(IRQ_DMA_CHANNEL49_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL49_PARAM);
  }
  /* SPI RX interrupt */
  #elif (IRQ_DMA_CHANNEL49_USED == IRQ_DMA_USED_MCALSPI_RX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL49_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiRx(IRQ_DMA_CHANNEL49_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL49_PARAM);
  }
  /* ADC interrupt */
  #elif (IRQ_DMA_CHANNEL49_USED == IRQ_DMA_USED_MCALADC)

  #if (ADC_GROUP_EMUX_SCAN == STD_ON)
  Adc_IsrDmaSrn(IRQ_DMA_CHANNEL49_PARAM);
  #endif /*End of ADC_GROUP_EMUX_SCAN == STD_ON*/

  /* DMA CDD interrupt */
  #elif (IRQ_DMA_CHANNEL49_USED == IRQ_DMA_AVAILABLE)
  /* User Code Begins */
  /* Complex DMA driver usage */
  #endif
}
#endif
/******************************************************************************
** Syntax : void DMACH50SR_ISR(void)                                        **
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
** Description : Service for DMA Channel50 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if((IRQ_DMA_CHANNEL50_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL50_SR_CAT == IRQ_CAT23))
#if((IRQ_DMA_CHANNEL50_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL50_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH50SR_ISR, 0, IRQ_DMA_CHANNEL50_SR_PRIO)
#elif IRQ_DMA_CHANNEL50_SR_CAT == IRQ_CAT23
ISR(DMACH50SR_ISR)
#endif
{
  #if ((IRQ_DMA_CHANNEL50_USED == IRQ_DMA_USED_MCALSPI_TX) || \
           (IRQ_DMA_CHANNEL50_USED == IRQ_DMA_USED_MCALSPI_RX))
  uint32 DmaErrorstatus;
  #endif
  /* Enable Global Interrupts */
  Mcal_EnableAllInterrupts();

  /* SPI TX interrupt */
  #if (IRQ_DMA_CHANNEL50_USED == IRQ_DMA_USED_MCALSPI_TX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL50_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiTx(IRQ_DMA_CHANNEL50_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL50_PARAM);
  }
  /* SPI RX interrupt */
  #elif (IRQ_DMA_CHANNEL50_USED == IRQ_DMA_USED_MCALSPI_RX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL50_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiRx(IRQ_DMA_CHANNEL50_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL50_PARAM);
  }
  /* ADC interrupt */
  #elif (IRQ_DMA_CHANNEL50_USED == IRQ_DMA_USED_MCALADC)

  #if (ADC_GROUP_EMUX_SCAN == STD_ON)
  Adc_IsrDmaSrn(IRQ_DMA_CHANNEL50_PARAM);
  #endif /*End of ADC_GROUP_EMUX_SCAN == STD_ON*/

  /* DMA CDD interrupt */
  #elif (IRQ_DMA_CHANNEL50_USED == IRQ_DMA_AVAILABLE)
  /* User Code Begins */
  /* Complex DMA driver usage */
  #endif
}
#endif
/******************************************************************************
** Syntax : void DMACH51SR_ISR(void)                                        **
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
** Description : Service for DMA Channel51 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if((IRQ_DMA_CHANNEL51_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL51_SR_CAT == IRQ_CAT23))
#if((IRQ_DMA_CHANNEL51_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL51_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH51SR_ISR, 0, IRQ_DMA_CHANNEL51_SR_PRIO)
#elif IRQ_DMA_CHANNEL51_SR_CAT == IRQ_CAT23
ISR(DMACH51SR_ISR)
#endif
{
  #if ((IRQ_DMA_CHANNEL51_USED == IRQ_DMA_USED_MCALSPI_TX) || \
           (IRQ_DMA_CHANNEL51_USED == IRQ_DMA_USED_MCALSPI_RX))
  uint32 DmaErrorstatus;
  #endif
  /* Enable Global Interrupts */
  Mcal_EnableAllInterrupts();

  /* SPI TX interrupt */
  #if (IRQ_DMA_CHANNEL51_USED == IRQ_DMA_USED_MCALSPI_TX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL51_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiTx(IRQ_DMA_CHANNEL51_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL51_PARAM);
  }
  /* SPI RX interrupt */
  #elif (IRQ_DMA_CHANNEL51_USED == IRQ_DMA_USED_MCALSPI_RX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL51_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiRx(IRQ_DMA_CHANNEL51_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL51_PARAM);
  }
  /* ADC interrupt */
  #elif (IRQ_DMA_CHANNEL51_USED == IRQ_DMA_USED_MCALADC)

  #if (ADC_GROUP_EMUX_SCAN == STD_ON)
  Adc_IsrDmaSrn(IRQ_DMA_CHANNEL51_PARAM);
  #endif /*End of ADC_GROUP_EMUX_SCAN == STD_ON*/

  /* DMA CDD interrupt */
  #elif (IRQ_DMA_CHANNEL51_USED == IRQ_DMA_AVAILABLE)
  /* User Code Begins */
  /* Complex DMA driver usage */
  #endif
}
#endif
/******************************************************************************
** Syntax : void DMACH52SR_ISR(void)                                        **
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
** Description : Service for DMA Channel52 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if((IRQ_DMA_CHANNEL52_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL52_SR_CAT == IRQ_CAT23))
#if((IRQ_DMA_CHANNEL52_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL52_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH52SR_ISR, 0, IRQ_DMA_CHANNEL52_SR_PRIO)
#elif IRQ_DMA_CHANNEL52_SR_CAT == IRQ_CAT23
ISR(DMACH52SR_ISR)
#endif
{
  #if ((IRQ_DMA_CHANNEL52_USED == IRQ_DMA_USED_MCALSPI_TX) || \
           (IRQ_DMA_CHANNEL52_USED == IRQ_DMA_USED_MCALSPI_RX))
  uint32 DmaErrorstatus;
  #endif
  /* Enable Global Interrupts */
  Mcal_EnableAllInterrupts();

  /* SPI TX interrupt */
  #if (IRQ_DMA_CHANNEL52_USED == IRQ_DMA_USED_MCALSPI_TX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL52_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiTx(IRQ_DMA_CHANNEL52_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL52_PARAM);
  }
  /* SPI RX interrupt */
  #elif (IRQ_DMA_CHANNEL52_USED == IRQ_DMA_USED_MCALSPI_RX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL52_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiRx(IRQ_DMA_CHANNEL52_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL52_PARAM);
  }
  /* ADC interrupt */
  #elif (IRQ_DMA_CHANNEL52_USED == IRQ_DMA_USED_MCALADC)

  #if (ADC_GROUP_EMUX_SCAN == STD_ON)
  Adc_IsrDmaSrn(IRQ_DMA_CHANNEL52_PARAM);
  #endif /*End of ADC_GROUP_EMUX_SCAN == STD_ON*/

  /* DMA CDD interrupt */
  #elif (IRQ_DMA_CHANNEL52_USED == IRQ_DMA_AVAILABLE)
  /* User Code Begins */
  /* Complex DMA driver usage */
  #endif
}
#endif
/******************************************************************************
** Syntax : void DMACH53SR_ISR(void)                                        **
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
** Description : Service for DMA Channel53 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if((IRQ_DMA_CHANNEL53_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL53_SR_CAT == IRQ_CAT23))
#if((IRQ_DMA_CHANNEL53_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL53_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH53SR_ISR, 0, IRQ_DMA_CHANNEL53_SR_PRIO)
#elif IRQ_DMA_CHANNEL53_SR_CAT == IRQ_CAT23
ISR(DMACH53SR_ISR)
#endif
{
  #if ((IRQ_DMA_CHANNEL53_USED == IRQ_DMA_USED_MCALSPI_TX) || \
           (IRQ_DMA_CHANNEL53_USED == IRQ_DMA_USED_MCALSPI_RX))
  uint32 DmaErrorstatus;
  #endif
  /* Enable Global Interrupts */
  Mcal_EnableAllInterrupts();

  /* SPI TX interrupt */
  #if (IRQ_DMA_CHANNEL53_USED == IRQ_DMA_USED_MCALSPI_TX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL53_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiTx(IRQ_DMA_CHANNEL53_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL53_PARAM);
  }
  /* SPI RX interrupt */
  #elif (IRQ_DMA_CHANNEL53_USED == IRQ_DMA_USED_MCALSPI_RX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL53_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiRx(IRQ_DMA_CHANNEL53_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL53_PARAM);
  }
  /* ADC interrupt */
  #elif (IRQ_DMA_CHANNEL53_USED == IRQ_DMA_USED_MCALADC)

  #if (ADC_GROUP_EMUX_SCAN == STD_ON)
  Adc_IsrDmaSrn(IRQ_DMA_CHANNEL53_PARAM);
  #endif /*End of ADC_GROUP_EMUX_SCAN == STD_ON*/

  /* DMA CDD interrupt */
  #elif (IRQ_DMA_CHANNEL53_USED == IRQ_DMA_AVAILABLE)
  /* User Code Begins */
  /* Complex DMA driver usage */
  #endif
}
#endif
/******************************************************************************
** Syntax : void DMACH54SR_ISR(void)                                        **
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
** Description : Service for DMA Channel54 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if((IRQ_DMA_CHANNEL54_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL54_SR_CAT == IRQ_CAT23))
#if((IRQ_DMA_CHANNEL54_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL54_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH54SR_ISR, 0, IRQ_DMA_CHANNEL54_SR_PRIO)
#elif IRQ_DMA_CHANNEL54_SR_CAT == IRQ_CAT23
ISR(DMACH54SR_ISR)
#endif
{
  #if ((IRQ_DMA_CHANNEL54_USED == IRQ_DMA_USED_MCALSPI_TX) || \
           (IRQ_DMA_CHANNEL54_USED == IRQ_DMA_USED_MCALSPI_RX))
  uint32 DmaErrorstatus;
  #endif
  /* Enable Global Interrupts */
  Mcal_EnableAllInterrupts();

  /* SPI TX interrupt */
  #if (IRQ_DMA_CHANNEL54_USED == IRQ_DMA_USED_MCALSPI_TX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL54_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiTx(IRQ_DMA_CHANNEL54_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL54_PARAM);
  }
  /* SPI RX interrupt */
  #elif (IRQ_DMA_CHANNEL54_USED == IRQ_DMA_USED_MCALSPI_RX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL54_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiRx(IRQ_DMA_CHANNEL54_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL54_PARAM);
  }
  /* ADC interrupt */
  #elif (IRQ_DMA_CHANNEL54_USED == IRQ_DMA_USED_MCALADC)

  #if (ADC_GROUP_EMUX_SCAN == STD_ON)
  Adc_IsrDmaSrn(IRQ_DMA_CHANNEL54_PARAM);
  #endif /*End of ADC_GROUP_EMUX_SCAN == STD_ON*/

  /* DMA CDD interrupt */
  #elif (IRQ_DMA_CHANNEL54_USED == IRQ_DMA_AVAILABLE)
  /* User Code Begins */
  /* Complex DMA driver usage */
  #endif
}
#endif
/******************************************************************************
** Syntax : void DMACH55SR_ISR(void)                                        **
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
** Description : Service for DMA Channel55 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if((IRQ_DMA_CHANNEL55_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL55_SR_CAT == IRQ_CAT23))
#if((IRQ_DMA_CHANNEL55_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL55_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH55SR_ISR, 0, IRQ_DMA_CHANNEL55_SR_PRIO)
#elif IRQ_DMA_CHANNEL55_SR_CAT == IRQ_CAT23
ISR(DMACH55SR_ISR)
#endif
{
  #if ((IRQ_DMA_CHANNEL55_USED == IRQ_DMA_USED_MCALSPI_TX) || \
           (IRQ_DMA_CHANNEL55_USED == IRQ_DMA_USED_MCALSPI_RX))
  uint32 DmaErrorstatus;
  #endif
  /* Enable Global Interrupts */
  Mcal_EnableAllInterrupts();

  /* SPI TX interrupt */
  #if (IRQ_DMA_CHANNEL55_USED == IRQ_DMA_USED_MCALSPI_TX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL55_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiTx(IRQ_DMA_CHANNEL55_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL55_PARAM);
  }
  /* SPI RX interrupt */
  #elif (IRQ_DMA_CHANNEL55_USED == IRQ_DMA_USED_MCALSPI_RX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL55_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiRx(IRQ_DMA_CHANNEL55_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL55_PARAM);
  }
  /* ADC interrupt */
  #elif (IRQ_DMA_CHANNEL55_USED == IRQ_DMA_USED_MCALADC)

  #if (ADC_GROUP_EMUX_SCAN == STD_ON)
  Adc_IsrDmaSrn(IRQ_DMA_CHANNEL55_PARAM);
  #endif /*End of ADC_GROUP_EMUX_SCAN == STD_ON*/

  /* DMA CDD interrupt */
  #elif (IRQ_DMA_CHANNEL55_USED == IRQ_DMA_AVAILABLE)
  /* User Code Begins */
  /* Complex DMA driver usage */
  #endif
}
#endif
/******************************************************************************
** Syntax : void DMACH56SR_ISR(void)                                        **
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
** Description : Service for DMA Channel56 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if((IRQ_DMA_CHANNEL56_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL56_SR_CAT == IRQ_CAT23))
#if((IRQ_DMA_CHANNEL56_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL56_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH56SR_ISR, 0, IRQ_DMA_CHANNEL56_SR_PRIO)
#elif IRQ_DMA_CHANNEL56_SR_CAT == IRQ_CAT23
ISR(DMACH56SR_ISR)
#endif
{
  #if ((IRQ_DMA_CHANNEL56_USED == IRQ_DMA_USED_MCALSPI_TX) || \
           (IRQ_DMA_CHANNEL56_USED == IRQ_DMA_USED_MCALSPI_RX))
  uint32 DmaErrorstatus;
  #endif
  /* Enable Global Interrupts */
  Mcal_EnableAllInterrupts();

  /* SPI TX interrupt */
  #if (IRQ_DMA_CHANNEL56_USED == IRQ_DMA_USED_MCALSPI_TX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL56_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiTx(IRQ_DMA_CHANNEL56_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL56_PARAM);
  }
  /* SPI RX interrupt */
  #elif (IRQ_DMA_CHANNEL56_USED == IRQ_DMA_USED_MCALSPI_RX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL56_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiRx(IRQ_DMA_CHANNEL56_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL56_PARAM);
  }
  /* ADC interrupt */
  #elif (IRQ_DMA_CHANNEL56_USED == IRQ_DMA_USED_MCALADC)

  #if (ADC_GROUP_EMUX_SCAN == STD_ON)
  Adc_IsrDmaSrn(IRQ_DMA_CHANNEL56_PARAM);
  #endif /*End of ADC_GROUP_EMUX_SCAN == STD_ON*/

  /* DMA CDD interrupt */
  #elif (IRQ_DMA_CHANNEL56_USED == IRQ_DMA_AVAILABLE)
  /* User Code Begins */
  /* Complex DMA driver usage */
  #endif
}
#endif
/******************************************************************************
** Syntax : void DMACH57SR_ISR(void)                                        **
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
** Description : Service for DMA Channel57 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if((IRQ_DMA_CHANNEL57_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL57_SR_CAT == IRQ_CAT23))
#if((IRQ_DMA_CHANNEL57_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL57_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH57SR_ISR, 0, IRQ_DMA_CHANNEL57_SR_PRIO)
#elif IRQ_DMA_CHANNEL57_SR_CAT == IRQ_CAT23
ISR(DMACH57SR_ISR)
#endif
{
  #if ((IRQ_DMA_CHANNEL57_USED == IRQ_DMA_USED_MCALSPI_TX) || \
           (IRQ_DMA_CHANNEL57_USED == IRQ_DMA_USED_MCALSPI_RX))
  uint32 DmaErrorstatus;
  #endif
  /* Enable Global Interrupts */
  Mcal_EnableAllInterrupts();

  /* SPI TX interrupt */
  #if (IRQ_DMA_CHANNEL57_USED == IRQ_DMA_USED_MCALSPI_TX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL57_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiTx(IRQ_DMA_CHANNEL57_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL57_PARAM);
  }
  /* SPI RX interrupt */
  #elif (IRQ_DMA_CHANNEL57_USED == IRQ_DMA_USED_MCALSPI_RX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL57_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiRx(IRQ_DMA_CHANNEL57_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL57_PARAM);
  }
  /* ADC interrupt */
  #elif (IRQ_DMA_CHANNEL57_USED == IRQ_DMA_USED_MCALADC)

  #if (ADC_GROUP_EMUX_SCAN == STD_ON)
  Adc_IsrDmaSrn(IRQ_DMA_CHANNEL57_PARAM);
  #endif /*End of ADC_GROUP_EMUX_SCAN == STD_ON*/

  /* DMA CDD interrupt */
  #elif (IRQ_DMA_CHANNEL57_USED == IRQ_DMA_AVAILABLE)
  /* User Code Begins */
  /* Complex DMA driver usage */
  #endif
}
#endif
/******************************************************************************
** Syntax : void DMACH58SR_ISR(void)                                        **
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
** Description : Service for DMA Channel58 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if((IRQ_DMA_CHANNEL58_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL58_SR_CAT == IRQ_CAT23))
#if((IRQ_DMA_CHANNEL58_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL58_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH58SR_ISR, 0, IRQ_DMA_CHANNEL58_SR_PRIO)
#elif IRQ_DMA_CHANNEL58_SR_CAT == IRQ_CAT23
ISR(DMACH58SR_ISR)
#endif
{
  #if ((IRQ_DMA_CHANNEL58_USED == IRQ_DMA_USED_MCALSPI_TX) || \
           (IRQ_DMA_CHANNEL58_USED == IRQ_DMA_USED_MCALSPI_RX))
  uint32 DmaErrorstatus;
  #endif
  /* Enable Global Interrupts */
  Mcal_EnableAllInterrupts();

  /* SPI TX interrupt */
  #if (IRQ_DMA_CHANNEL58_USED == IRQ_DMA_USED_MCALSPI_TX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL58_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiTx(IRQ_DMA_CHANNEL58_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL58_PARAM);
  }
  /* SPI RX interrupt */
  #elif (IRQ_DMA_CHANNEL58_USED == IRQ_DMA_USED_MCALSPI_RX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL58_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiRx(IRQ_DMA_CHANNEL58_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL58_PARAM);
  }
  /* ADC interrupt */
  #elif (IRQ_DMA_CHANNEL58_USED == IRQ_DMA_USED_MCALADC)

  #if (ADC_GROUP_EMUX_SCAN == STD_ON)
  Adc_IsrDmaSrn(IRQ_DMA_CHANNEL58_PARAM);
  #endif /*End of ADC_GROUP_EMUX_SCAN == STD_ON*/

  /* DMA CDD interrupt */
  #elif (IRQ_DMA_CHANNEL58_USED == IRQ_DMA_AVAILABLE)
  /* User Code Begins */
  /* Complex DMA driver usage */
  #endif
}
#endif
/******************************************************************************
** Syntax : void DMACH59SR_ISR(void)                                        **
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
** Description : Service for DMA Channel59 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if((IRQ_DMA_CHANNEL59_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL59_SR_CAT == IRQ_CAT23))
#if((IRQ_DMA_CHANNEL59_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL59_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH59SR_ISR, 0, IRQ_DMA_CHANNEL59_SR_PRIO)
#elif IRQ_DMA_CHANNEL59_SR_CAT == IRQ_CAT23
ISR(DMACH59SR_ISR)
#endif
{
  #if ((IRQ_DMA_CHANNEL59_USED == IRQ_DMA_USED_MCALSPI_TX) || \
           (IRQ_DMA_CHANNEL59_USED == IRQ_DMA_USED_MCALSPI_RX))
  uint32 DmaErrorstatus;
  #endif
  /* Enable Global Interrupts */
  Mcal_EnableAllInterrupts();

  /* SPI TX interrupt */
  #if (IRQ_DMA_CHANNEL59_USED == IRQ_DMA_USED_MCALSPI_TX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL59_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiTx(IRQ_DMA_CHANNEL59_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL59_PARAM);
  }
  /* SPI RX interrupt */
  #elif (IRQ_DMA_CHANNEL59_USED == IRQ_DMA_USED_MCALSPI_RX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL59_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiRx(IRQ_DMA_CHANNEL59_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL59_PARAM);
  }
  /* ADC interrupt */
  #elif (IRQ_DMA_CHANNEL59_USED == IRQ_DMA_USED_MCALADC)

  #if (ADC_GROUP_EMUX_SCAN == STD_ON)
  Adc_IsrDmaSrn(IRQ_DMA_CHANNEL59_PARAM);
  #endif /*End of ADC_GROUP_EMUX_SCAN == STD_ON*/

  /* DMA CDD interrupt */
  #elif (IRQ_DMA_CHANNEL59_USED == IRQ_DMA_AVAILABLE)
  /* User Code Begins */
  /* Complex DMA driver usage */
  #endif
}
#endif
/******************************************************************************
** Syntax : void DMACH60SR_ISR(void)                                        **
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
** Description : Service for DMA Channel60 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if((IRQ_DMA_CHANNEL60_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL60_SR_CAT == IRQ_CAT23))
#if((IRQ_DMA_CHANNEL60_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL60_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH60SR_ISR, 0, IRQ_DMA_CHANNEL60_SR_PRIO)
#elif IRQ_DMA_CHANNEL60_SR_CAT == IRQ_CAT23
ISR(DMACH60SR_ISR)
#endif
{
  #if ((IRQ_DMA_CHANNEL60_USED == IRQ_DMA_USED_MCALSPI_TX) || \
           (IRQ_DMA_CHANNEL60_USED == IRQ_DMA_USED_MCALSPI_RX))
  uint32 DmaErrorstatus;
  #endif
  /* Enable Global Interrupts */
  Mcal_EnableAllInterrupts();

  /* SPI TX interrupt */
  #if (IRQ_DMA_CHANNEL60_USED == IRQ_DMA_USED_MCALSPI_TX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL60_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiTx(IRQ_DMA_CHANNEL60_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL60_PARAM);
  }
  /* SPI RX interrupt */
  #elif (IRQ_DMA_CHANNEL60_USED == IRQ_DMA_USED_MCALSPI_RX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL60_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiRx(IRQ_DMA_CHANNEL60_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL60_PARAM);
  }
  /* ADC interrupt */
  #elif (IRQ_DMA_CHANNEL60_USED == IRQ_DMA_USED_MCALADC)

  #if (ADC_GROUP_EMUX_SCAN == STD_ON)
  Adc_IsrDmaSrn(IRQ_DMA_CHANNEL60_PARAM);
  #endif /*End of ADC_GROUP_EMUX_SCAN == STD_ON*/

  /* DMA CDD interrupt */
  #elif (IRQ_DMA_CHANNEL60_USED == IRQ_DMA_AVAILABLE)
  /* User Code Begins */
  /* Complex DMA driver usage */
  #endif
}
#endif
/******************************************************************************
** Syntax : void DMACH61SR_ISR(void)                                        **
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
** Description : Service for DMA Channel61 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if((IRQ_DMA_CHANNEL61_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL61_SR_CAT == IRQ_CAT23))
#if((IRQ_DMA_CHANNEL61_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL61_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH61SR_ISR, 0, IRQ_DMA_CHANNEL61_SR_PRIO)
#elif IRQ_DMA_CHANNEL61_SR_CAT == IRQ_CAT23
ISR(DMACH61SR_ISR)
#endif
{
  #if ((IRQ_DMA_CHANNEL61_USED == IRQ_DMA_USED_MCALSPI_TX) || \
           (IRQ_DMA_CHANNEL61_USED == IRQ_DMA_USED_MCALSPI_RX))
  uint32 DmaErrorstatus;
  #endif
  /* Enable Global Interrupts */
  Mcal_EnableAllInterrupts();

  /* SPI TX interrupt */
  #if (IRQ_DMA_CHANNEL61_USED == IRQ_DMA_USED_MCALSPI_TX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL61_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiTx(IRQ_DMA_CHANNEL61_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL61_PARAM);
  }
  /* SPI RX interrupt */
  #elif (IRQ_DMA_CHANNEL61_USED == IRQ_DMA_USED_MCALSPI_RX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL61_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiRx(IRQ_DMA_CHANNEL61_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL61_PARAM);
  }
  /* ADC interrupt */
  #elif (IRQ_DMA_CHANNEL61_USED == IRQ_DMA_USED_MCALADC)

  #if (ADC_GROUP_EMUX_SCAN == STD_ON)
  Adc_IsrDmaSrn(IRQ_DMA_CHANNEL61_PARAM);
  #endif /*End of ADC_GROUP_EMUX_SCAN == STD_ON*/

  /* DMA CDD interrupt */
  #elif (IRQ_DMA_CHANNEL61_USED == IRQ_DMA_AVAILABLE)
  /* User Code Begins */
  /* Complex DMA driver usage */
  #endif
}
#endif
/******************************************************************************
** Syntax : void DMACH62SR_ISR(void)                                        **
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
** Description : Service for DMA Channel62 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if((IRQ_DMA_CHANNEL62_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL62_SR_CAT == IRQ_CAT23))
#if((IRQ_DMA_CHANNEL62_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL62_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH62SR_ISR, 0, IRQ_DMA_CHANNEL62_SR_PRIO)
#elif IRQ_DMA_CHANNEL62_SR_CAT == IRQ_CAT23
ISR(DMACH62SR_ISR)
#endif
{
  #if ((IRQ_DMA_CHANNEL62_USED == IRQ_DMA_USED_MCALSPI_TX) || \
           (IRQ_DMA_CHANNEL62_USED == IRQ_DMA_USED_MCALSPI_RX))
  uint32 DmaErrorstatus;
  #endif
  /* Enable Global Interrupts */
  Mcal_EnableAllInterrupts();

  /* SPI TX interrupt */
  #if (IRQ_DMA_CHANNEL62_USED == IRQ_DMA_USED_MCALSPI_TX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL62_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiTx(IRQ_DMA_CHANNEL62_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL62_PARAM);
  }
  /* SPI RX interrupt */
  #elif (IRQ_DMA_CHANNEL62_USED == IRQ_DMA_USED_MCALSPI_RX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL62_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiRx(IRQ_DMA_CHANNEL62_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL62_PARAM);
  }
  /* ADC interrupt */
  #elif (IRQ_DMA_CHANNEL62_USED == IRQ_DMA_USED_MCALADC)

  #if (ADC_GROUP_EMUX_SCAN == STD_ON)
  Adc_IsrDmaSrn(IRQ_DMA_CHANNEL62_PARAM);
  #endif /*End of ADC_GROUP_EMUX_SCAN == STD_ON*/

  /* DMA CDD interrupt */
  #elif (IRQ_DMA_CHANNEL62_USED == IRQ_DMA_AVAILABLE)
  /* User Code Begins */
  /* Complex DMA driver usage */
  #endif
}
#endif
/******************************************************************************
** Syntax : void DMACH63SR_ISR(void)                                        **
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
** Description : Service for DMA Channel63 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if((IRQ_DMA_CHANNEL63_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL63_SR_CAT == IRQ_CAT23))
#if((IRQ_DMA_CHANNEL63_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL63_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH63SR_ISR, 0, IRQ_DMA_CHANNEL63_SR_PRIO)
#elif IRQ_DMA_CHANNEL63_SR_CAT == IRQ_CAT23
ISR(DMACH63SR_ISR)
#endif
{
  #if ((IRQ_DMA_CHANNEL63_USED == IRQ_DMA_USED_MCALSPI_TX) || \
           (IRQ_DMA_CHANNEL63_USED == IRQ_DMA_USED_MCALSPI_RX))
  uint32 DmaErrorstatus;
  #endif
  /* Enable Global Interrupts */
  Mcal_EnableAllInterrupts();

  /* SPI TX interrupt */
  #if (IRQ_DMA_CHANNEL63_USED == IRQ_DMA_USED_MCALSPI_TX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL63_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiTx(IRQ_DMA_CHANNEL63_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL63_PARAM);
  }
  /* SPI RX interrupt */
  #elif (IRQ_DMA_CHANNEL63_USED == IRQ_DMA_USED_MCALSPI_RX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL63_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiRx(IRQ_DMA_CHANNEL63_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL63_PARAM);
  }
  /* ADC interrupt */
  #elif (IRQ_DMA_CHANNEL63_USED == IRQ_DMA_USED_MCALADC)

  #if (ADC_GROUP_EMUX_SCAN == STD_ON)
  Adc_IsrDmaSrn(IRQ_DMA_CHANNEL63_PARAM);
  #endif /*End of ADC_GROUP_EMUX_SCAN == STD_ON*/

  /* DMA CDD interrupt */
  #elif (IRQ_DMA_CHANNEL63_USED == IRQ_DMA_AVAILABLE)
  /* User Code Begins */
  /* Complex DMA driver usage */
  #endif
}
#endif
#endif/*end of IRQ_DMA_CH48TO63_EXIST*/

#if (IRQ_DMA_CH64TO127_EXIST == STD_ON)
/******************************************************************************
** Syntax : void DMACH64SR_ISR(void)                                        **
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
** Description : Service for DMA Channel64 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if((IRQ_DMA_CHANNEL64_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL64_SR_CAT == IRQ_CAT23))
#if((IRQ_DMA_CHANNEL64_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL64_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH64SR_ISR, 0, IRQ_DMA_CHANNEL64_SR_PRIO)
#elif IRQ_DMA_CHANNEL64_SR_CAT == IRQ_CAT23
ISR(DMACH64SR_ISR)
#endif
{
  #if ((IRQ_DMA_CHANNEL64_USED == IRQ_DMA_USED_MCALSPI_TX) || \
           (IRQ_DMA_CHANNEL64_USED == IRQ_DMA_USED_MCALSPI_RX))
  uint32 DmaErrorstatus;
  #endif
  /* Enable Global Interrupts */
  Mcal_EnableAllInterrupts();

  /* SPI TX interrupt */
  #if (IRQ_DMA_CHANNEL64_USED == IRQ_DMA_USED_MCALSPI_TX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL64_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiTx(IRQ_DMA_CHANNEL64_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL64_PARAM);
  }
  /* SPI RX interrupt */
  #elif (IRQ_DMA_CHANNEL64_USED == IRQ_DMA_USED_MCALSPI_RX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL64_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiRx(IRQ_DMA_CHANNEL64_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL64_PARAM);
  }
  /* ADC interrupt */
  #elif (IRQ_DMA_CHANNEL64_USED == IRQ_DMA_USED_MCALADC)

  #if (ADC_GROUP_EMUX_SCAN == STD_ON)
  Adc_IsrDmaSrn(IRQ_DMA_CHANNEL64_PARAM);
  #endif /*End of ADC_GROUP_EMUX_SCAN == STD_ON*/

  /* DMA CDD interrupt */
  #elif (IRQ_DMA_CHANNEL64_USED == IRQ_DMA_AVAILABLE)
  /* User Code Begins */
  /* Complex DMA driver usage */
  #endif
}
#endif
/******************************************************************************
** Syntax : void DMACH65SR_ISR(void)                                        **
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
** Description : Service for DMA Channel65 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if((IRQ_DMA_CHANNEL65_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL65_SR_CAT == IRQ_CAT23))
#if((IRQ_DMA_CHANNEL65_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL65_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH65SR_ISR, 0, IRQ_DMA_CHANNEL65_SR_PRIO)
#elif IRQ_DMA_CHANNEL65_SR_CAT == IRQ_CAT23
ISR(DMACH65SR_ISR)
#endif
{
  #if ((IRQ_DMA_CHANNEL65_USED == IRQ_DMA_USED_MCALSPI_TX) || \
           (IRQ_DMA_CHANNEL65_USED == IRQ_DMA_USED_MCALSPI_RX))
  uint32 DmaErrorstatus;
  #endif
  /* Enable Global Interrupts */
  Mcal_EnableAllInterrupts();

  /* SPI TX interrupt */
  #if (IRQ_DMA_CHANNEL65_USED == IRQ_DMA_USED_MCALSPI_TX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL65_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiTx(IRQ_DMA_CHANNEL65_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL65_PARAM);
  }
  /* SPI RX interrupt */
  #elif (IRQ_DMA_CHANNEL65_USED == IRQ_DMA_USED_MCALSPI_RX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL65_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiRx(IRQ_DMA_CHANNEL65_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL65_PARAM);
  }
  /* ADC interrupt */
  #elif (IRQ_DMA_CHANNEL65_USED == IRQ_DMA_USED_MCALADC)

  #if (ADC_GROUP_EMUX_SCAN == STD_ON)
  Adc_IsrDmaSrn(IRQ_DMA_CHANNEL65_PARAM);
  #endif /*End of ADC_GROUP_EMUX_SCAN == STD_ON*/

  /* DMA CDD interrupt */
  #elif (IRQ_DMA_CHANNEL65_USED == IRQ_DMA_AVAILABLE)
  /* User Code Begins */
  /* Complex DMA driver usage */
  #endif
}
#endif
/******************************************************************************
** Syntax : void DMACH66SR_ISR(void)                                        **
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
** Description : Service for DMA Channel66 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if((IRQ_DMA_CHANNEL66_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL66_SR_CAT == IRQ_CAT23))
#if((IRQ_DMA_CHANNEL66_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL66_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH66SR_ISR, 0, IRQ_DMA_CHANNEL66_SR_PRIO)
#elif IRQ_DMA_CHANNEL66_SR_CAT == IRQ_CAT23
ISR(DMACH66SR_ISR)
#endif
{
  #if ((IRQ_DMA_CHANNEL66_USED == IRQ_DMA_USED_MCALSPI_TX) || \
           (IRQ_DMA_CHANNEL66_USED == IRQ_DMA_USED_MCALSPI_RX))
  uint32 DmaErrorstatus;
  #endif
  /* Enable Global Interrupts */
  Mcal_EnableAllInterrupts();

  /* SPI TX interrupt */
  #if (IRQ_DMA_CHANNEL66_USED == IRQ_DMA_USED_MCALSPI_TX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL66_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiTx(IRQ_DMA_CHANNEL66_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL66_PARAM);
  }
  /* SPI RX interrupt */
  #elif (IRQ_DMA_CHANNEL66_USED == IRQ_DMA_USED_MCALSPI_RX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL66_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiRx(IRQ_DMA_CHANNEL66_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL66_PARAM);
  }
  /* ADC interrupt */
  #elif (IRQ_DMA_CHANNEL66_USED == IRQ_DMA_USED_MCALADC)

  #if (ADC_GROUP_EMUX_SCAN == STD_ON)
  Adc_IsrDmaSrn(IRQ_DMA_CHANNEL66_PARAM);
  #endif /*End of ADC_GROUP_EMUX_SCAN == STD_ON*/

  /* DMA CDD interrupt */
  #elif (IRQ_DMA_CHANNEL66_USED == IRQ_DMA_AVAILABLE)
  /* User Code Begins */
  /* Complex DMA driver usage */
  #endif
}
#endif
/******************************************************************************
** Syntax : void DMACH67SR_ISR(void)                                        **
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
** Description : Service for DMA Channel67 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if((IRQ_DMA_CHANNEL67_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL67_SR_CAT == IRQ_CAT23))
#if((IRQ_DMA_CHANNEL67_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL67_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH67SR_ISR, 0, IRQ_DMA_CHANNEL67_SR_PRIO)
#elif IRQ_DMA_CHANNEL67_SR_CAT == IRQ_CAT23
ISR(DMACH67SR_ISR)
#endif
{
  #if ((IRQ_DMA_CHANNEL67_USED == IRQ_DMA_USED_MCALSPI_TX) || \
           (IRQ_DMA_CHANNEL67_USED == IRQ_DMA_USED_MCALSPI_RX))
  uint32 DmaErrorstatus;
  #endif
  /* Enable Global Interrupts */
  Mcal_EnableAllInterrupts();

  /* SPI TX interrupt */
  #if (IRQ_DMA_CHANNEL67_USED == IRQ_DMA_USED_MCALSPI_TX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL67_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiTx(IRQ_DMA_CHANNEL67_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL67_PARAM);
  }
  /* SPI RX interrupt */
  #elif (IRQ_DMA_CHANNEL67_USED == IRQ_DMA_USED_MCALSPI_RX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL67_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiRx(IRQ_DMA_CHANNEL67_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL67_PARAM);
  }
  /* ADC interrupt */
  #elif (IRQ_DMA_CHANNEL67_USED == IRQ_DMA_USED_MCALADC)

  #if (ADC_GROUP_EMUX_SCAN == STD_ON)
  Adc_IsrDmaSrn(IRQ_DMA_CHANNEL67_PARAM);
  #endif /*End of ADC_GROUP_EMUX_SCAN == STD_ON*/

  /* DMA CDD interrupt */
  #elif (IRQ_DMA_CHANNEL67_USED == IRQ_DMA_AVAILABLE)
  /* User Code Begins */
  /* Complex DMA driver usage */
  #endif
}
#endif
/******************************************************************************
** Syntax : void DMACH68SR_ISR(void)                                        **
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
** Description : Service for DMA Channel68 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if((IRQ_DMA_CHANNEL68_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL68_SR_CAT == IRQ_CAT23))
#if((IRQ_DMA_CHANNEL68_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL68_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH68SR_ISR, 0, IRQ_DMA_CHANNEL68_SR_PRIO)
#elif IRQ_DMA_CHANNEL68_SR_CAT == IRQ_CAT23
ISR(DMACH68SR_ISR)
#endif
{
  #if ((IRQ_DMA_CHANNEL68_USED == IRQ_DMA_USED_MCALSPI_TX) || \
           (IRQ_DMA_CHANNEL68_USED == IRQ_DMA_USED_MCALSPI_RX))
  uint32 DmaErrorstatus;
  #endif
  /* Enable Global Interrupts */
  Mcal_EnableAllInterrupts();

  /* SPI TX interrupt */
  #if (IRQ_DMA_CHANNEL68_USED == IRQ_DMA_USED_MCALSPI_TX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL68_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiTx(IRQ_DMA_CHANNEL68_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL68_PARAM);
  }
  /* SPI RX interrupt */
  #elif (IRQ_DMA_CHANNEL68_USED == IRQ_DMA_USED_MCALSPI_RX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL68_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiRx(IRQ_DMA_CHANNEL68_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL68_PARAM);
  }
  /* ADC interrupt */
  #elif (IRQ_DMA_CHANNEL68_USED == IRQ_DMA_USED_MCALADC)

  #if (ADC_GROUP_EMUX_SCAN == STD_ON)
  Adc_IsrDmaSrn(IRQ_DMA_CHANNEL68_PARAM);
  #endif /*End of ADC_GROUP_EMUX_SCAN == STD_ON*/

  /* DMA CDD interrupt */
  #elif (IRQ_DMA_CHANNEL68_USED == IRQ_DMA_AVAILABLE)
  /* User Code Begins */
  /* Complex DMA driver usage */
  #endif
}
#endif
/******************************************************************************
** Syntax : void DMACH69SR_ISR(void)                                        **
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
** Description : Service for DMA Channel69 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if((IRQ_DMA_CHANNEL69_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL69_SR_CAT == IRQ_CAT23))
#if((IRQ_DMA_CHANNEL69_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL69_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH69SR_ISR, 0, IRQ_DMA_CHANNEL69_SR_PRIO)
#elif IRQ_DMA_CHANNEL69_SR_CAT == IRQ_CAT23
ISR(DMACH69SR_ISR)
#endif
{
  #if ((IRQ_DMA_CHANNEL69_USED == IRQ_DMA_USED_MCALSPI_TX) || \
           (IRQ_DMA_CHANNEL69_USED == IRQ_DMA_USED_MCALSPI_RX))
  uint32 DmaErrorstatus;
  #endif
  /* Enable Global Interrupts */
  Mcal_EnableAllInterrupts();

  /* SPI TX interrupt */
  #if (IRQ_DMA_CHANNEL69_USED == IRQ_DMA_USED_MCALSPI_TX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL69_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiTx(IRQ_DMA_CHANNEL69_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL69_PARAM);
  }
  /* SPI RX interrupt */
  #elif (IRQ_DMA_CHANNEL69_USED == IRQ_DMA_USED_MCALSPI_RX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL69_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiRx(IRQ_DMA_CHANNEL69_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL69_PARAM);
  }
  /* ADC interrupt */
  #elif (IRQ_DMA_CHANNEL69_USED == IRQ_DMA_USED_MCALADC)

  #if (ADC_GROUP_EMUX_SCAN == STD_ON)
  Adc_IsrDmaSrn(IRQ_DMA_CHANNEL69_PARAM);
  #endif /*End of ADC_GROUP_EMUX_SCAN == STD_ON*/

  /* DMA CDD interrupt */
  #elif (IRQ_DMA_CHANNEL69_USED == IRQ_DMA_AVAILABLE)
  /* User Code Begins */
  /* Complex DMA driver usage */
  #endif
}
#endif
/******************************************************************************
** Syntax : void DMACH70SR_ISR(void)                                        **
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
** Description : Service for DMA Channel70 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if((IRQ_DMA_CHANNEL70_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL70_SR_CAT == IRQ_CAT23))
#if((IRQ_DMA_CHANNEL70_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL70_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH70SR_ISR, 0, IRQ_DMA_CHANNEL70_SR_PRIO)
#elif IRQ_DMA_CHANNEL70_SR_CAT == IRQ_CAT23
ISR(DMACH70SR_ISR)
#endif
{
  #if ((IRQ_DMA_CHANNEL70_USED == IRQ_DMA_USED_MCALSPI_TX) || \
           (IRQ_DMA_CHANNEL70_USED == IRQ_DMA_USED_MCALSPI_RX))
  uint32 DmaErrorstatus;
  #endif
  /* Enable Global Interrupts */
  Mcal_EnableAllInterrupts();

  /* SPI TX interrupt */
  #if (IRQ_DMA_CHANNEL70_USED == IRQ_DMA_USED_MCALSPI_TX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL70_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiTx(IRQ_DMA_CHANNEL70_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL70_PARAM);
  }
  /* SPI RX interrupt */
  #elif (IRQ_DMA_CHANNEL70_USED == IRQ_DMA_USED_MCALSPI_RX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL70_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiRx(IRQ_DMA_CHANNEL70_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL70_PARAM);
  }
  /* ADC interrupt */
  #elif (IRQ_DMA_CHANNEL70_USED == IRQ_DMA_USED_MCALADC)

  #if (ADC_GROUP_EMUX_SCAN == STD_ON)
  Adc_IsrDmaSrn(IRQ_DMA_CHANNEL70_PARAM);
  #endif /*End of ADC_GROUP_EMUX_SCAN == STD_ON*/

  /* DMA CDD interrupt */
  #elif (IRQ_DMA_CHANNEL70_USED == IRQ_DMA_AVAILABLE)
  /* User Code Begins */
  /* Complex DMA driver usage */
  #endif
}
#endif
/******************************************************************************
** Syntax : void DMACH71SR_ISR(void)                                        **
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
** Description : Service for DMA Channel71 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if((IRQ_DMA_CHANNEL71_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL71_SR_CAT == IRQ_CAT23))
#if((IRQ_DMA_CHANNEL71_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL71_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH71SR_ISR, 0, IRQ_DMA_CHANNEL71_SR_PRIO)
#elif IRQ_DMA_CHANNEL71_SR_CAT == IRQ_CAT23
ISR(DMACH71SR_ISR)
#endif
{
  #if ((IRQ_DMA_CHANNEL71_USED == IRQ_DMA_USED_MCALSPI_TX) || \
           (IRQ_DMA_CHANNEL71_USED == IRQ_DMA_USED_MCALSPI_RX))
  uint32 DmaErrorstatus;
  #endif
  /* Enable Global Interrupts */
  Mcal_EnableAllInterrupts();

  /* SPI TX interrupt */
  #if (IRQ_DMA_CHANNEL71_USED == IRQ_DMA_USED_MCALSPI_TX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL71_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiTx(IRQ_DMA_CHANNEL71_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL71_PARAM);
  }
  /* SPI RX interrupt */
  #elif (IRQ_DMA_CHANNEL71_USED == IRQ_DMA_USED_MCALSPI_RX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL71_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiRx(IRQ_DMA_CHANNEL71_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL71_PARAM);
  }
  /* ADC interrupt */
  #elif (IRQ_DMA_CHANNEL71_USED == IRQ_DMA_USED_MCALADC)

  #if (ADC_GROUP_EMUX_SCAN == STD_ON)
  Adc_IsrDmaSrn(IRQ_DMA_CHANNEL71_PARAM);
  #endif /*End of ADC_GROUP_EMUX_SCAN == STD_ON*/

  /* DMA CDD interrupt */
  #elif (IRQ_DMA_CHANNEL71_USED == IRQ_DMA_AVAILABLE)
  /* User Code Begins */
  /* Complex DMA driver usage */
  #endif
}
#endif
/******************************************************************************
** Syntax : void DMACH72SR_ISR(void)                                        **
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
** Description : Service for DMA Channel72 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if((IRQ_DMA_CHANNEL72_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL72_SR_CAT == IRQ_CAT23))
#if((IRQ_DMA_CHANNEL72_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL72_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH72SR_ISR, 0, IRQ_DMA_CHANNEL72_SR_PRIO)
#elif IRQ_DMA_CHANNEL72_SR_CAT == IRQ_CAT23
ISR(DMACH72SR_ISR)
#endif
{
  #if ((IRQ_DMA_CHANNEL72_USED == IRQ_DMA_USED_MCALSPI_TX) || \
           (IRQ_DMA_CHANNEL72_USED == IRQ_DMA_USED_MCALSPI_RX))
  uint32 DmaErrorstatus;
  #endif
  /* Enable Global Interrupts */
  Mcal_EnableAllInterrupts();

  /* SPI TX interrupt */
  #if (IRQ_DMA_CHANNEL72_USED == IRQ_DMA_USED_MCALSPI_TX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL72_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiTx(IRQ_DMA_CHANNEL72_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL72_PARAM);
  }
  /* SPI RX interrupt */
  #elif (IRQ_DMA_CHANNEL72_USED == IRQ_DMA_USED_MCALSPI_RX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL72_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiRx(IRQ_DMA_CHANNEL72_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL72_PARAM);
  }
  /* ADC interrupt */
  #elif (IRQ_DMA_CHANNEL72_USED == IRQ_DMA_USED_MCALADC)

  #if (ADC_GROUP_EMUX_SCAN == STD_ON)
  Adc_IsrDmaSrn(IRQ_DMA_CHANNEL72_PARAM);
  #endif /*End of ADC_GROUP_EMUX_SCAN == STD_ON*/

  /* DMA CDD interrupt */
  #elif (IRQ_DMA_CHANNEL72_USED == IRQ_DMA_AVAILABLE)
  /* User Code Begins */
  /* Complex DMA driver usage */
  #endif
}
#endif
/******************************************************************************
** Syntax : void DMACH73SR_ISR(void)                                        **
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
** Description : Service for DMA Channel73 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if((IRQ_DMA_CHANNEL73_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL73_SR_CAT == IRQ_CAT23))
#if((IRQ_DMA_CHANNEL73_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL73_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH73SR_ISR, 0, IRQ_DMA_CHANNEL73_SR_PRIO)
#elif IRQ_DMA_CHANNEL73_SR_CAT == IRQ_CAT23
ISR(DMACH73SR_ISR)
#endif
{
  #if ((IRQ_DMA_CHANNEL73_USED == IRQ_DMA_USED_MCALSPI_TX) || \
           (IRQ_DMA_CHANNEL73_USED == IRQ_DMA_USED_MCALSPI_RX))
  uint32 DmaErrorstatus;
  #endif
  /* Enable Global Interrupts */
  Mcal_EnableAllInterrupts();

  /* SPI TX interrupt */
  #if (IRQ_DMA_CHANNEL73_USED == IRQ_DMA_USED_MCALSPI_TX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL73_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiTx(IRQ_DMA_CHANNEL73_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL73_PARAM);
  }
  /* SPI RX interrupt */
  #elif (IRQ_DMA_CHANNEL73_USED == IRQ_DMA_USED_MCALSPI_RX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL73_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiRx(IRQ_DMA_CHANNEL73_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL73_PARAM);
  }
  /* ADC interrupt */
  #elif (IRQ_DMA_CHANNEL73_USED == IRQ_DMA_USED_MCALADC)

  #if (ADC_GROUP_EMUX_SCAN == STD_ON)
  Adc_IsrDmaSrn(IRQ_DMA_CHANNEL73_PARAM);
  #endif /*End of ADC_GROUP_EMUX_SCAN == STD_ON*/

  /* DMA CDD interrupt */
  #elif (IRQ_DMA_CHANNEL73_USED == IRQ_DMA_AVAILABLE)
  /* User Code Begins */
  /* Complex DMA driver usage */
  #endif
}
#endif
/******************************************************************************
** Syntax : void DMACH74SR_ISR(void)                                        **
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
** Description : Service for DMA Channel74 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if((IRQ_DMA_CHANNEL74_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL74_SR_CAT == IRQ_CAT23))
#if((IRQ_DMA_CHANNEL74_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL74_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH74SR_ISR, 0, IRQ_DMA_CHANNEL74_SR_PRIO)
#elif IRQ_DMA_CHANNEL74_SR_CAT == IRQ_CAT23
ISR(DMACH74SR_ISR)
#endif
{
  #if ((IRQ_DMA_CHANNEL74_USED == IRQ_DMA_USED_MCALSPI_TX) || \
           (IRQ_DMA_CHANNEL74_USED == IRQ_DMA_USED_MCALSPI_RX))
  uint32 DmaErrorstatus;
  #endif
  /* Enable Global Interrupts */
  Mcal_EnableAllInterrupts();

  /* SPI TX interrupt */
  #if (IRQ_DMA_CHANNEL74_USED == IRQ_DMA_USED_MCALSPI_TX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL74_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiTx(IRQ_DMA_CHANNEL74_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL74_PARAM);
  }
  /* SPI RX interrupt */
  #elif (IRQ_DMA_CHANNEL74_USED == IRQ_DMA_USED_MCALSPI_RX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL74_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiRx(IRQ_DMA_CHANNEL74_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL74_PARAM);
  }
  /* ADC interrupt */
  #elif (IRQ_DMA_CHANNEL74_USED == IRQ_DMA_USED_MCALADC)

  #if (ADC_GROUP_EMUX_SCAN == STD_ON)
  Adc_IsrDmaSrn(IRQ_DMA_CHANNEL74_PARAM);
  #endif /*End of ADC_GROUP_EMUX_SCAN == STD_ON*/

  /* DMA CDD interrupt */
  #elif (IRQ_DMA_CHANNEL74_USED == IRQ_DMA_AVAILABLE)
  /* User Code Begins */
  /* Complex DMA driver usage */
  #endif
}
#endif
/******************************************************************************
** Syntax : void DMACH75SR_ISR(void)                                        **
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
** Description : Service for DMA Channel75 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if((IRQ_DMA_CHANNEL75_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL75_SR_CAT == IRQ_CAT23))
#if((IRQ_DMA_CHANNEL75_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL75_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH75SR_ISR, 0, IRQ_DMA_CHANNEL75_SR_PRIO)
#elif IRQ_DMA_CHANNEL75_SR_CAT == IRQ_CAT23
ISR(DMACH75SR_ISR)
#endif
{
  #if ((IRQ_DMA_CHANNEL75_USED == IRQ_DMA_USED_MCALSPI_TX) || \
           (IRQ_DMA_CHANNEL75_USED == IRQ_DMA_USED_MCALSPI_RX))
  uint32 DmaErrorstatus;
  #endif
  /* Enable Global Interrupts */
  Mcal_EnableAllInterrupts();

  /* SPI TX interrupt */
  #if (IRQ_DMA_CHANNEL75_USED == IRQ_DMA_USED_MCALSPI_TX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL75_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiTx(IRQ_DMA_CHANNEL75_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL75_PARAM);
  }
  /* SPI RX interrupt */
  #elif (IRQ_DMA_CHANNEL75_USED == IRQ_DMA_USED_MCALSPI_RX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL75_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiRx(IRQ_DMA_CHANNEL75_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL75_PARAM);
  }
  /* ADC interrupt */
  #elif (IRQ_DMA_CHANNEL75_USED == IRQ_DMA_USED_MCALADC)

  #if (ADC_GROUP_EMUX_SCAN == STD_ON)
  Adc_IsrDmaSrn(IRQ_DMA_CHANNEL75_PARAM);
  #endif /*End of ADC_GROUP_EMUX_SCAN == STD_ON*/

  /* DMA CDD interrupt */
  #elif (IRQ_DMA_CHANNEL75_USED == IRQ_DMA_AVAILABLE)
  /* User Code Begins */
  /* Complex DMA driver usage */
  #endif
}
#endif
/******************************************************************************
** Syntax : void DMACH76SR_ISR(void)                                        **
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
** Description : Service for DMA Channel76 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if((IRQ_DMA_CHANNEL76_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL76_SR_CAT == IRQ_CAT23))
#if((IRQ_DMA_CHANNEL76_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL76_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH76SR_ISR, 0, IRQ_DMA_CHANNEL76_SR_PRIO)
#elif IRQ_DMA_CHANNEL76_SR_CAT == IRQ_CAT23
ISR(DMACH76SR_ISR)
#endif
{
  #if ((IRQ_DMA_CHANNEL76_USED == IRQ_DMA_USED_MCALSPI_TX) || \
           (IRQ_DMA_CHANNEL76_USED == IRQ_DMA_USED_MCALSPI_RX))
  uint32 DmaErrorstatus;
  #endif
  /* Enable Global Interrupts */
  Mcal_EnableAllInterrupts();

  /* SPI TX interrupt */
  #if (IRQ_DMA_CHANNEL76_USED == IRQ_DMA_USED_MCALSPI_TX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL76_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiTx(IRQ_DMA_CHANNEL76_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL76_PARAM);
  }
  /* SPI RX interrupt */
  #elif (IRQ_DMA_CHANNEL76_USED == IRQ_DMA_USED_MCALSPI_RX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL76_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiRx(IRQ_DMA_CHANNEL76_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL76_PARAM);
  }
  /* ADC interrupt */
  #elif (IRQ_DMA_CHANNEL76_USED == IRQ_DMA_USED_MCALADC)

  #if (ADC_GROUP_EMUX_SCAN == STD_ON)
  Adc_IsrDmaSrn(IRQ_DMA_CHANNEL76_PARAM);
  #endif /*End of ADC_GROUP_EMUX_SCAN == STD_ON*/

  /* DMA CDD interrupt */
  #elif (IRQ_DMA_CHANNEL76_USED == IRQ_DMA_AVAILABLE)
  /* User Code Begins */
  /* Complex DMA driver usage */
  #endif
}
#endif
/******************************************************************************
** Syntax : void DMACH77SR_ISR(void)                                        **
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
** Description : Service for DMA Channel77 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if((IRQ_DMA_CHANNEL77_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL77_SR_CAT == IRQ_CAT23))
#if((IRQ_DMA_CHANNEL77_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL77_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH77SR_ISR, 0, IRQ_DMA_CHANNEL77_SR_PRIO)
#elif IRQ_DMA_CHANNEL77_SR_CAT == IRQ_CAT23
ISR(DMACH77SR_ISR)
#endif
{
  #if ((IRQ_DMA_CHANNEL77_USED == IRQ_DMA_USED_MCALSPI_TX) || \
           (IRQ_DMA_CHANNEL77_USED == IRQ_DMA_USED_MCALSPI_RX))
  uint32 DmaErrorstatus;
  #endif
  /* Enable Global Interrupts */
  Mcal_EnableAllInterrupts();

  /* SPI TX interrupt */
  #if (IRQ_DMA_CHANNEL77_USED == IRQ_DMA_USED_MCALSPI_TX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL77_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiTx(IRQ_DMA_CHANNEL77_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL77_PARAM);
  }
  /* SPI RX interrupt */
  #elif (IRQ_DMA_CHANNEL77_USED == IRQ_DMA_USED_MCALSPI_RX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL77_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiRx(IRQ_DMA_CHANNEL77_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL77_PARAM);
  }
  /* ADC interrupt */
  #elif (IRQ_DMA_CHANNEL77_USED == IRQ_DMA_USED_MCALADC)

  #if (ADC_GROUP_EMUX_SCAN == STD_ON)
  Adc_IsrDmaSrn(IRQ_DMA_CHANNEL77_PARAM);
  #endif /*End of ADC_GROUP_EMUX_SCAN == STD_ON*/

  /* DMA CDD interrupt */
  #elif (IRQ_DMA_CHANNEL77_USED == IRQ_DMA_AVAILABLE)
  /* User Code Begins */
  /* Complex DMA driver usage */
  #endif
}
#endif
/******************************************************************************
** Syntax : void DMACH78SR_ISR(void)                                        **
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
** Description : Service for DMA Channel78 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if((IRQ_DMA_CHANNEL78_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL78_SR_CAT == IRQ_CAT23))
#if((IRQ_DMA_CHANNEL78_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL78_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH78SR_ISR, 0, IRQ_DMA_CHANNEL78_SR_PRIO)
#elif IRQ_DMA_CHANNEL78_SR_CAT == IRQ_CAT23
ISR(DMACH78SR_ISR)
#endif
{
  #if ((IRQ_DMA_CHANNEL78_USED == IRQ_DMA_USED_MCALSPI_TX) || \
           (IRQ_DMA_CHANNEL78_USED == IRQ_DMA_USED_MCALSPI_RX))
  uint32 DmaErrorstatus;
  #endif
  /* Enable Global Interrupts */
  Mcal_EnableAllInterrupts();

  /* SPI TX interrupt */
  #if (IRQ_DMA_CHANNEL78_USED == IRQ_DMA_USED_MCALSPI_TX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL78_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiTx(IRQ_DMA_CHANNEL78_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL78_PARAM);
  }
  /* SPI RX interrupt */
  #elif (IRQ_DMA_CHANNEL78_USED == IRQ_DMA_USED_MCALSPI_RX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL78_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiRx(IRQ_DMA_CHANNEL78_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL78_PARAM);
  }
  /* ADC interrupt */
  #elif (IRQ_DMA_CHANNEL78_USED == IRQ_DMA_USED_MCALADC)

  #if (ADC_GROUP_EMUX_SCAN == STD_ON)
  Adc_IsrDmaSrn(IRQ_DMA_CHANNEL78_PARAM);
  #endif /*End of ADC_GROUP_EMUX_SCAN == STD_ON*/

  /* DMA CDD interrupt */
  #elif (IRQ_DMA_CHANNEL78_USED == IRQ_DMA_AVAILABLE)
  /* User Code Begins */
  /* Complex DMA driver usage */
  #endif
}
#endif
/******************************************************************************
** Syntax : void DMACH79SR_ISR(void)                                        **
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
** Description : Service for DMA Channel79 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if((IRQ_DMA_CHANNEL79_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL79_SR_CAT == IRQ_CAT23))
#if((IRQ_DMA_CHANNEL79_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL79_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH79SR_ISR, 0, IRQ_DMA_CHANNEL79_SR_PRIO)
#elif IRQ_DMA_CHANNEL79_SR_CAT == IRQ_CAT23
ISR(DMACH79SR_ISR)
#endif
{
  #if ((IRQ_DMA_CHANNEL79_USED == IRQ_DMA_USED_MCALSPI_TX) || \
           (IRQ_DMA_CHANNEL79_USED == IRQ_DMA_USED_MCALSPI_RX))
  uint32 DmaErrorstatus;
  #endif
  /* Enable Global Interrupts */
  Mcal_EnableAllInterrupts();

  /* SPI TX interrupt */
  #if (IRQ_DMA_CHANNEL79_USED == IRQ_DMA_USED_MCALSPI_TX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL79_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiTx(IRQ_DMA_CHANNEL79_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL79_PARAM);
  }
  /* SPI RX interrupt */
  #elif (IRQ_DMA_CHANNEL79_USED == IRQ_DMA_USED_MCALSPI_RX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL79_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiRx(IRQ_DMA_CHANNEL79_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL79_PARAM);
  }
  /* ADC interrupt */
  #elif (IRQ_DMA_CHANNEL79_USED == IRQ_DMA_USED_MCALADC)

  #if (ADC_GROUP_EMUX_SCAN == STD_ON)
  Adc_IsrDmaSrn(IRQ_DMA_CHANNEL79_PARAM);
  #endif /*End of ADC_GROUP_EMUX_SCAN == STD_ON*/

  /* DMA CDD interrupt */
  #elif (IRQ_DMA_CHANNEL79_USED == IRQ_DMA_AVAILABLE)
  /* User Code Begins */
  /* Complex DMA driver usage */
  #endif
}
#endif
/******************************************************************************
** Syntax : void DMACH80SR_ISR(void)                                        **
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
** Description : Service for DMA Channel80 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if((IRQ_DMA_CHANNEL80_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL80_SR_CAT == IRQ_CAT23))
#if((IRQ_DMA_CHANNEL80_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL80_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH80SR_ISR, 0, IRQ_DMA_CHANNEL80_SR_PRIO)
#elif IRQ_DMA_CHANNEL80_SR_CAT == IRQ_CAT23
ISR(DMACH80SR_ISR)
#endif
{
  #if ((IRQ_DMA_CHANNEL80_USED == IRQ_DMA_USED_MCALSPI_TX) || \
           (IRQ_DMA_CHANNEL80_USED == IRQ_DMA_USED_MCALSPI_RX))
  uint32 DmaErrorstatus;
  #endif
  /* Enable Global Interrupts */
  Mcal_EnableAllInterrupts();

  /* SPI TX interrupt */
  #if (IRQ_DMA_CHANNEL80_USED == IRQ_DMA_USED_MCALSPI_TX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL80_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiTx(IRQ_DMA_CHANNEL80_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL80_PARAM);
  }
  /* SPI RX interrupt */
  #elif (IRQ_DMA_CHANNEL80_USED == IRQ_DMA_USED_MCALSPI_RX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL80_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiRx(IRQ_DMA_CHANNEL80_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL80_PARAM);
  }
  /* ADC interrupt */
  #elif (IRQ_DMA_CHANNEL80_USED == IRQ_DMA_USED_MCALADC)

  #if (ADC_GROUP_EMUX_SCAN == STD_ON)
  Adc_IsrDmaSrn(IRQ_DMA_CHANNEL80_PARAM);
  #endif /*End of ADC_GROUP_EMUX_SCAN == STD_ON*/

  /* DMA CDD interrupt */
  #elif (IRQ_DMA_CHANNEL80_USED == IRQ_DMA_AVAILABLE)
  /* User Code Begins */
  /* Complex DMA driver usage */
  #endif
}
#endif
/******************************************************************************
** Syntax : void DMACH81SR_ISR(void)                                        **
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
** Description : Service for DMA Channel81 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if((IRQ_DMA_CHANNEL81_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL81_SR_CAT == IRQ_CAT23))
#if((IRQ_DMA_CHANNEL81_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL81_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH81SR_ISR, 0, IRQ_DMA_CHANNEL81_SR_PRIO)
#elif IRQ_DMA_CHANNEL81_SR_CAT == IRQ_CAT23
ISR(DMACH81SR_ISR)
#endif
{
  #if ((IRQ_DMA_CHANNEL81_USED == IRQ_DMA_USED_MCALSPI_TX) || \
           (IRQ_DMA_CHANNEL81_USED == IRQ_DMA_USED_MCALSPI_RX))
  uint32 DmaErrorstatus;
  #endif
  /* Enable Global Interrupts */
  Mcal_EnableAllInterrupts();

  /* SPI TX interrupt */
  #if (IRQ_DMA_CHANNEL81_USED == IRQ_DMA_USED_MCALSPI_TX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL81_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiTx(IRQ_DMA_CHANNEL81_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL81_PARAM);
  }
  /* SPI RX interrupt */
  #elif (IRQ_DMA_CHANNEL81_USED == IRQ_DMA_USED_MCALSPI_RX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL81_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiRx(IRQ_DMA_CHANNEL81_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL81_PARAM);
  }
  /* ADC interrupt */
  #elif (IRQ_DMA_CHANNEL81_USED == IRQ_DMA_USED_MCALADC)

  #if (ADC_GROUP_EMUX_SCAN == STD_ON)
  Adc_IsrDmaSrn(IRQ_DMA_CHANNEL81_PARAM);
  #endif /*End of ADC_GROUP_EMUX_SCAN == STD_ON*/

  /* DMA CDD interrupt */
  #elif (IRQ_DMA_CHANNEL81_USED == IRQ_DMA_AVAILABLE)
  /* User Code Begins */
  /* Complex DMA driver usage */
  #endif
}
#endif
/******************************************************************************
** Syntax : void DMACH82SR_ISR(void)                                        **
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
** Description : Service for DMA Channel82 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if((IRQ_DMA_CHANNEL82_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL82_SR_CAT == IRQ_CAT23))
#if((IRQ_DMA_CHANNEL82_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL82_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH82SR_ISR, 0, IRQ_DMA_CHANNEL82_SR_PRIO)
#elif IRQ_DMA_CHANNEL82_SR_CAT == IRQ_CAT23
ISR(DMACH82SR_ISR)
#endif
{
  #if ((IRQ_DMA_CHANNEL82_USED == IRQ_DMA_USED_MCALSPI_TX) || \
           (IRQ_DMA_CHANNEL82_USED == IRQ_DMA_USED_MCALSPI_RX))
  uint32 DmaErrorstatus;
  #endif
  /* Enable Global Interrupts */
  Mcal_EnableAllInterrupts();

  /* SPI TX interrupt */
  #if (IRQ_DMA_CHANNEL82_USED == IRQ_DMA_USED_MCALSPI_TX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL82_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiTx(IRQ_DMA_CHANNEL82_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL82_PARAM);
  }
  /* SPI RX interrupt */
  #elif (IRQ_DMA_CHANNEL82_USED == IRQ_DMA_USED_MCALSPI_RX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL82_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiRx(IRQ_DMA_CHANNEL82_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL82_PARAM);
  }
  /* ADC interrupt */
  #elif (IRQ_DMA_CHANNEL82_USED == IRQ_DMA_USED_MCALADC)

  #if (ADC_GROUP_EMUX_SCAN == STD_ON)
  Adc_IsrDmaSrn(IRQ_DMA_CHANNEL82_PARAM);
  #endif /*End of ADC_GROUP_EMUX_SCAN == STD_ON*/

  /* DMA CDD interrupt */
  #elif (IRQ_DMA_CHANNEL82_USED == IRQ_DMA_AVAILABLE)
  /* User Code Begins */
  /* Complex DMA driver usage */
  #endif
}
#endif
/******************************************************************************
** Syntax : void DMACH83SR_ISR(void)                                        **
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
** Description : Service for DMA Channel83 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if((IRQ_DMA_CHANNEL83_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL83_SR_CAT == IRQ_CAT23))
#if((IRQ_DMA_CHANNEL83_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL83_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH83SR_ISR, 0, IRQ_DMA_CHANNEL83_SR_PRIO)
#elif IRQ_DMA_CHANNEL83_SR_CAT == IRQ_CAT23
ISR(DMACH83SR_ISR)
#endif
{
  #if ((IRQ_DMA_CHANNEL83_USED == IRQ_DMA_USED_MCALSPI_TX) || \
           (IRQ_DMA_CHANNEL83_USED == IRQ_DMA_USED_MCALSPI_RX))
  uint32 DmaErrorstatus;
  #endif
  /* Enable Global Interrupts */
  Mcal_EnableAllInterrupts();

  /* SPI TX interrupt */
  #if (IRQ_DMA_CHANNEL83_USED == IRQ_DMA_USED_MCALSPI_TX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL83_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiTx(IRQ_DMA_CHANNEL83_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL83_PARAM);
  }
  /* SPI RX interrupt */
  #elif (IRQ_DMA_CHANNEL83_USED == IRQ_DMA_USED_MCALSPI_RX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL83_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiRx(IRQ_DMA_CHANNEL83_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL83_PARAM);
  }
  /* ADC interrupt */
  #elif (IRQ_DMA_CHANNEL83_USED == IRQ_DMA_USED_MCALADC)

  #if (ADC_GROUP_EMUX_SCAN == STD_ON)
  Adc_IsrDmaSrn(IRQ_DMA_CHANNEL83_PARAM);
  #endif /*End of ADC_GROUP_EMUX_SCAN == STD_ON*/

  /* DMA CDD interrupt */
  #elif (IRQ_DMA_CHANNEL83_USED == IRQ_DMA_AVAILABLE)
  /* User Code Begins */
  /* Complex DMA driver usage */
  #endif
}
#endif
/******************************************************************************
** Syntax : void DMACH84SR_ISR(void)                                        **
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
** Description : Service for DMA Channel84 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if((IRQ_DMA_CHANNEL84_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL84_SR_CAT == IRQ_CAT23))
#if((IRQ_DMA_CHANNEL84_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL84_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH84SR_ISR, 0, IRQ_DMA_CHANNEL84_SR_PRIO)
#elif IRQ_DMA_CHANNEL84_SR_CAT == IRQ_CAT23
ISR(DMACH84SR_ISR)
#endif
{
  #if ((IRQ_DMA_CHANNEL84_USED == IRQ_DMA_USED_MCALSPI_TX) || \
           (IRQ_DMA_CHANNEL84_USED == IRQ_DMA_USED_MCALSPI_RX))
  uint32 DmaErrorstatus;
  #endif
  /* Enable Global Interrupts */
  Mcal_EnableAllInterrupts();

  /* SPI TX interrupt */
  #if (IRQ_DMA_CHANNEL84_USED == IRQ_DMA_USED_MCALSPI_TX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL84_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiTx(IRQ_DMA_CHANNEL84_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL84_PARAM);
  }
  /* SPI RX interrupt */
  #elif (IRQ_DMA_CHANNEL84_USED == IRQ_DMA_USED_MCALSPI_RX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL84_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiRx(IRQ_DMA_CHANNEL84_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL84_PARAM);
  }
  /* ADC interrupt */
  #elif (IRQ_DMA_CHANNEL84_USED == IRQ_DMA_USED_MCALADC)

  #if (ADC_GROUP_EMUX_SCAN == STD_ON)
  Adc_IsrDmaSrn(IRQ_DMA_CHANNEL84_PARAM);
  #endif /*End of ADC_GROUP_EMUX_SCAN == STD_ON*/

  /* DMA CDD interrupt */
  #elif (IRQ_DMA_CHANNEL84_USED == IRQ_DMA_AVAILABLE)
  /* User Code Begins */
  /* Complex DMA driver usage */
  #endif
}
#endif
/******************************************************************************
** Syntax : void DMACH85SR_ISR(void)                                        **
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
** Description : Service for DMA Channel85 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if((IRQ_DMA_CHANNEL85_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL85_SR_CAT == IRQ_CAT23))
#if((IRQ_DMA_CHANNEL85_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL85_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH85SR_ISR, 0, IRQ_DMA_CHANNEL85_SR_PRIO)
#elif IRQ_DMA_CHANNEL85_SR_CAT == IRQ_CAT23
ISR(DMACH85SR_ISR)
#endif
{
  #if ((IRQ_DMA_CHANNEL85_USED == IRQ_DMA_USED_MCALSPI_TX) || \
           (IRQ_DMA_CHANNEL85_USED == IRQ_DMA_USED_MCALSPI_RX))
  uint32 DmaErrorstatus;
  #endif
  /* Enable Global Interrupts */
  Mcal_EnableAllInterrupts();

  /* SPI TX interrupt */
  #if (IRQ_DMA_CHANNEL85_USED == IRQ_DMA_USED_MCALSPI_TX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL85_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiTx(IRQ_DMA_CHANNEL85_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL85_PARAM);
  }
  /* SPI RX interrupt */
  #elif (IRQ_DMA_CHANNEL85_USED == IRQ_DMA_USED_MCALSPI_RX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL85_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiRx(IRQ_DMA_CHANNEL85_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL85_PARAM);
  }
  /* ADC interrupt */
  #elif (IRQ_DMA_CHANNEL85_USED == IRQ_DMA_USED_MCALADC)

  #if (ADC_GROUP_EMUX_SCAN == STD_ON)
  Adc_IsrDmaSrn(IRQ_DMA_CHANNEL85_PARAM);
  #endif /*End of ADC_GROUP_EMUX_SCAN == STD_ON*/

  /* DMA CDD interrupt */
  #elif (IRQ_DMA_CHANNEL85_USED == IRQ_DMA_AVAILABLE)
  /* User Code Begins */
  /* Complex DMA driver usage */
  #endif
}
#endif
/******************************************************************************
** Syntax : void DMACH86SR_ISR(void)                                        **
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
** Description : Service for DMA Channel86 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if((IRQ_DMA_CHANNEL86_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL86_SR_CAT == IRQ_CAT23))
#if((IRQ_DMA_CHANNEL86_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL86_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH86SR_ISR, 0, IRQ_DMA_CHANNEL86_SR_PRIO)
#elif IRQ_DMA_CHANNEL86_SR_CAT == IRQ_CAT23
ISR(DMACH86SR_ISR)
#endif
{
  #if ((IRQ_DMA_CHANNEL86_USED == IRQ_DMA_USED_MCALSPI_TX) || \
           (IRQ_DMA_CHANNEL86_USED == IRQ_DMA_USED_MCALSPI_RX))
  uint32 DmaErrorstatus;
  #endif
  /* Enable Global Interrupts */
  Mcal_EnableAllInterrupts();

  /* SPI TX interrupt */
  #if (IRQ_DMA_CHANNEL86_USED == IRQ_DMA_USED_MCALSPI_TX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL86_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiTx(IRQ_DMA_CHANNEL86_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL86_PARAM);
  }
  /* SPI RX interrupt */
  #elif (IRQ_DMA_CHANNEL86_USED == IRQ_DMA_USED_MCALSPI_RX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL86_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiRx(IRQ_DMA_CHANNEL86_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL86_PARAM);
  }
  /* ADC interrupt */
  #elif (IRQ_DMA_CHANNEL86_USED == IRQ_DMA_USED_MCALADC)

  #if (ADC_GROUP_EMUX_SCAN == STD_ON)
  Adc_IsrDmaSrn(IRQ_DMA_CHANNEL86_PARAM);
  #endif /*End of ADC_GROUP_EMUX_SCAN == STD_ON*/

  /* DMA CDD interrupt */
  #elif (IRQ_DMA_CHANNEL86_USED == IRQ_DMA_AVAILABLE)
  /* User Code Begins */
  /* Complex DMA driver usage */
  #endif
}
#endif
/******************************************************************************
** Syntax : void DMACH87SR_ISR(void)                                        **
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
** Description : Service for DMA Channel87 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if((IRQ_DMA_CHANNEL87_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL87_SR_CAT == IRQ_CAT23))
#if((IRQ_DMA_CHANNEL87_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL87_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH87SR_ISR, 0, IRQ_DMA_CHANNEL87_SR_PRIO)
#elif IRQ_DMA_CHANNEL87_SR_CAT == IRQ_CAT23
ISR(DMACH87SR_ISR)
#endif
{
  #if ((IRQ_DMA_CHANNEL87_USED == IRQ_DMA_USED_MCALSPI_TX) || \
           (IRQ_DMA_CHANNEL87_USED == IRQ_DMA_USED_MCALSPI_RX))
  uint32 DmaErrorstatus;
  #endif
  /* Enable Global Interrupts */
  Mcal_EnableAllInterrupts();

  /* SPI TX interrupt */
  #if (IRQ_DMA_CHANNEL87_USED == IRQ_DMA_USED_MCALSPI_TX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL87_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiTx(IRQ_DMA_CHANNEL87_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL87_PARAM);
  }
  /* SPI RX interrupt */
  #elif (IRQ_DMA_CHANNEL87_USED == IRQ_DMA_USED_MCALSPI_RX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL87_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiRx(IRQ_DMA_CHANNEL87_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL87_PARAM);
  }
  /* ADC interrupt */
  #elif (IRQ_DMA_CHANNEL87_USED == IRQ_DMA_USED_MCALADC)

  #if (ADC_GROUP_EMUX_SCAN == STD_ON)
  Adc_IsrDmaSrn(IRQ_DMA_CHANNEL87_PARAM);
  #endif /*End of ADC_GROUP_EMUX_SCAN == STD_ON*/

  /* DMA CDD interrupt */
  #elif (IRQ_DMA_CHANNEL87_USED == IRQ_DMA_AVAILABLE)
  /* User Code Begins */
  /* Complex DMA driver usage */
  #endif
}
#endif
/******************************************************************************
** Syntax : void DMACH88SR_ISR(void)                                        **
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
** Description : Service for DMA Channel88 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if((IRQ_DMA_CHANNEL88_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL88_SR_CAT == IRQ_CAT23))
#if((IRQ_DMA_CHANNEL88_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL88_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH88SR_ISR, 0, IRQ_DMA_CHANNEL88_SR_PRIO)
#elif IRQ_DMA_CHANNEL88_SR_CAT == IRQ_CAT23
ISR(DMACH88SR_ISR)
#endif
{
  #if ((IRQ_DMA_CHANNEL88_USED == IRQ_DMA_USED_MCALSPI_TX) || \
           (IRQ_DMA_CHANNEL88_USED == IRQ_DMA_USED_MCALSPI_RX))
  uint32 DmaErrorstatus;
  #endif
  /* Enable Global Interrupts */
  Mcal_EnableAllInterrupts();

  /* SPI TX interrupt */
  #if (IRQ_DMA_CHANNEL88_USED == IRQ_DMA_USED_MCALSPI_TX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL88_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiTx(IRQ_DMA_CHANNEL88_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL88_PARAM);
  }
  /* SPI RX interrupt */
  #elif (IRQ_DMA_CHANNEL88_USED == IRQ_DMA_USED_MCALSPI_RX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL88_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiRx(IRQ_DMA_CHANNEL88_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL88_PARAM);
  }
  /* ADC interrupt */
  #elif (IRQ_DMA_CHANNEL88_USED == IRQ_DMA_USED_MCALADC)

  #if (ADC_GROUP_EMUX_SCAN == STD_ON)
  Adc_IsrDmaSrn(IRQ_DMA_CHANNEL88_PARAM);
  #endif /*End of ADC_GROUP_EMUX_SCAN == STD_ON*/

  /* DMA CDD interrupt */
  #elif (IRQ_DMA_CHANNEL88_USED == IRQ_DMA_AVAILABLE)
  /* User Code Begins */
  /* Complex DMA driver usage */
  #endif
}
#endif
/******************************************************************************
** Syntax : void DMACH89SR_ISR(void)                                        **
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
** Description : Service for DMA Channel89 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if((IRQ_DMA_CHANNEL89_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL89_SR_CAT == IRQ_CAT23))
#if((IRQ_DMA_CHANNEL89_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL89_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH89SR_ISR, 0, IRQ_DMA_CHANNEL89_SR_PRIO)
#elif IRQ_DMA_CHANNEL89_SR_CAT == IRQ_CAT23
ISR(DMACH89SR_ISR)
#endif
{
  #if ((IRQ_DMA_CHANNEL89_USED == IRQ_DMA_USED_MCALSPI_TX) || \
           (IRQ_DMA_CHANNEL89_USED == IRQ_DMA_USED_MCALSPI_RX))
  uint32 DmaErrorstatus;
  #endif
  /* Enable Global Interrupts */
  Mcal_EnableAllInterrupts();

  /* SPI TX interrupt */
  #if (IRQ_DMA_CHANNEL89_USED == IRQ_DMA_USED_MCALSPI_TX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL89_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiTx(IRQ_DMA_CHANNEL89_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL89_PARAM);
  }
  /* SPI RX interrupt */
  #elif (IRQ_DMA_CHANNEL89_USED == IRQ_DMA_USED_MCALSPI_RX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL89_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiRx(IRQ_DMA_CHANNEL89_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL89_PARAM);
  }
  /* ADC interrupt */
  #elif (IRQ_DMA_CHANNEL89_USED == IRQ_DMA_USED_MCALADC)

  #if (ADC_GROUP_EMUX_SCAN == STD_ON)
  Adc_IsrDmaSrn(IRQ_DMA_CHANNEL89_PARAM);
  #endif /*End of ADC_GROUP_EMUX_SCAN == STD_ON*/

  /* DMA CDD interrupt */
  #elif (IRQ_DMA_CHANNEL89_USED == IRQ_DMA_AVAILABLE)
  /* User Code Begins */
  /* Complex DMA driver usage */
  #endif
}
#endif
/******************************************************************************
** Syntax : void DMACH90SR_ISR(void)                                        **
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
** Description : Service for DMA Channel90 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if((IRQ_DMA_CHANNEL90_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL90_SR_CAT == IRQ_CAT23))
#if((IRQ_DMA_CHANNEL90_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL90_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH90SR_ISR, 0, IRQ_DMA_CHANNEL90_SR_PRIO)
#elif IRQ_DMA_CHANNEL90_SR_CAT == IRQ_CAT23
ISR(DMACH90SR_ISR)
#endif
{
  #if ((IRQ_DMA_CHANNEL90_USED == IRQ_DMA_USED_MCALSPI_TX) || \
           (IRQ_DMA_CHANNEL90_USED == IRQ_DMA_USED_MCALSPI_RX))
  uint32 DmaErrorstatus;
  #endif
  /* Enable Global Interrupts */
  Mcal_EnableAllInterrupts();

  /* SPI TX interrupt */
  #if (IRQ_DMA_CHANNEL90_USED == IRQ_DMA_USED_MCALSPI_TX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL90_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiTx(IRQ_DMA_CHANNEL90_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL90_PARAM);
  }
  /* SPI RX interrupt */
  #elif (IRQ_DMA_CHANNEL90_USED == IRQ_DMA_USED_MCALSPI_RX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL90_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiRx(IRQ_DMA_CHANNEL90_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL90_PARAM);
  }
  /* ADC interrupt */
  #elif (IRQ_DMA_CHANNEL90_USED == IRQ_DMA_USED_MCALADC)

  #if (ADC_GROUP_EMUX_SCAN == STD_ON)
  Adc_IsrDmaSrn(IRQ_DMA_CHANNEL90_PARAM);
  #endif /*End of ADC_GROUP_EMUX_SCAN == STD_ON*/

  /* DMA CDD interrupt */
  #elif (IRQ_DMA_CHANNEL90_USED == IRQ_DMA_AVAILABLE)
  /* User Code Begins */
  /* Complex DMA driver usage */
  #endif
}
#endif
/******************************************************************************
** Syntax : void DMACH91SR_ISR(void)                                        **
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
** Description : Service for DMA Channel91 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if((IRQ_DMA_CHANNEL91_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL91_SR_CAT == IRQ_CAT23))
#if((IRQ_DMA_CHANNEL91_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL91_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH91SR_ISR, 0, IRQ_DMA_CHANNEL91_SR_PRIO)
#elif IRQ_DMA_CHANNEL91_SR_CAT == IRQ_CAT23
ISR(DMACH91SR_ISR)
#endif
{
  #if ((IRQ_DMA_CHANNEL91_USED == IRQ_DMA_USED_MCALSPI_TX) || \
           (IRQ_DMA_CHANNEL91_USED == IRQ_DMA_USED_MCALSPI_RX))
  uint32 DmaErrorstatus;
  #endif
  /* Enable Global Interrupts */
  Mcal_EnableAllInterrupts();

  /* SPI TX interrupt */
  #if (IRQ_DMA_CHANNEL91_USED == IRQ_DMA_USED_MCALSPI_TX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL91_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiTx(IRQ_DMA_CHANNEL91_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL91_PARAM);
  }
  /* SPI RX interrupt */
  #elif (IRQ_DMA_CHANNEL91_USED == IRQ_DMA_USED_MCALSPI_RX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL91_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiRx(IRQ_DMA_CHANNEL91_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL91_PARAM);
  }
  /* ADC interrupt */
  #elif (IRQ_DMA_CHANNEL91_USED == IRQ_DMA_USED_MCALADC)

  #if (ADC_GROUP_EMUX_SCAN == STD_ON)
  Adc_IsrDmaSrn(IRQ_DMA_CHANNEL91_PARAM);
  #endif /*End of ADC_GROUP_EMUX_SCAN == STD_ON*/

  /* DMA CDD interrupt */
  #elif (IRQ_DMA_CHANNEL91_USED == IRQ_DMA_AVAILABLE)
  /* User Code Begins */
  /* Complex DMA driver usage */
  #endif
}
#endif
/******************************************************************************
** Syntax : void DMACH92SR_ISR(void)                                        **
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
** Description : Service for DMA Channel92 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if((IRQ_DMA_CHANNEL92_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL92_SR_CAT == IRQ_CAT23))
#if((IRQ_DMA_CHANNEL92_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL92_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH92SR_ISR, 0, IRQ_DMA_CHANNEL92_SR_PRIO)
#elif IRQ_DMA_CHANNEL92_SR_CAT == IRQ_CAT23
ISR(DMACH92SR_ISR)
#endif
{
  #if ((IRQ_DMA_CHANNEL92_USED == IRQ_DMA_USED_MCALSPI_TX) || \
           (IRQ_DMA_CHANNEL92_USED == IRQ_DMA_USED_MCALSPI_RX))
  uint32 DmaErrorstatus;
  #endif
  /* Enable Global Interrupts */
  Mcal_EnableAllInterrupts();

  /* SPI TX interrupt */
  #if (IRQ_DMA_CHANNEL92_USED == IRQ_DMA_USED_MCALSPI_TX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL92_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiTx(IRQ_DMA_CHANNEL92_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL92_PARAM);
  }
  /* SPI RX interrupt */
  #elif (IRQ_DMA_CHANNEL92_USED == IRQ_DMA_USED_MCALSPI_RX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL92_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiRx(IRQ_DMA_CHANNEL92_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL92_PARAM);
  }
  /* ADC interrupt */
  #elif (IRQ_DMA_CHANNEL92_USED == IRQ_DMA_USED_MCALADC)

  #if (ADC_GROUP_EMUX_SCAN == STD_ON)
  Adc_IsrDmaSrn(IRQ_DMA_CHANNEL92_PARAM);
  #endif /*End of ADC_GROUP_EMUX_SCAN == STD_ON*/

  /* DMA CDD interrupt */
  #elif (IRQ_DMA_CHANNEL92_USED == IRQ_DMA_AVAILABLE)
  /* User Code Begins */
  /* Complex DMA driver usage */
  #endif
}
#endif
/******************************************************************************
** Syntax : void DMACH93SR_ISR(void)                                        **
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
** Description : Service for DMA Channel93 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if((IRQ_DMA_CHANNEL93_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL93_SR_CAT == IRQ_CAT23))
#if((IRQ_DMA_CHANNEL93_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL93_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH93SR_ISR, 0, IRQ_DMA_CHANNEL93_SR_PRIO)
#elif IRQ_DMA_CHANNEL93_SR_CAT == IRQ_CAT23
ISR(DMACH93SR_ISR)
#endif
{
  #if ((IRQ_DMA_CHANNEL93_USED == IRQ_DMA_USED_MCALSPI_TX) || \
           (IRQ_DMA_CHANNEL93_USED == IRQ_DMA_USED_MCALSPI_RX))
  uint32 DmaErrorstatus;
  #endif
  /* Enable Global Interrupts */
  Mcal_EnableAllInterrupts();

  /* SPI TX interrupt */
  #if (IRQ_DMA_CHANNEL93_USED == IRQ_DMA_USED_MCALSPI_TX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL93_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiTx(IRQ_DMA_CHANNEL93_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL93_PARAM);
  }
  /* SPI RX interrupt */
  #elif (IRQ_DMA_CHANNEL93_USED == IRQ_DMA_USED_MCALSPI_RX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL93_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiRx(IRQ_DMA_CHANNEL93_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL93_PARAM);
  }
  /* ADC interrupt */
  #elif (IRQ_DMA_CHANNEL93_USED == IRQ_DMA_USED_MCALADC)

  #if (ADC_GROUP_EMUX_SCAN == STD_ON)
  Adc_IsrDmaSrn(IRQ_DMA_CHANNEL93_PARAM);
  #endif /*End of ADC_GROUP_EMUX_SCAN == STD_ON*/

  /* DMA CDD interrupt */
  #elif (IRQ_DMA_CHANNEL93_USED == IRQ_DMA_AVAILABLE)
  /* User Code Begins */
  /* Complex DMA driver usage */
  #endif
}
#endif
/******************************************************************************
** Syntax : void DMACH94SR_ISR(void)                                        **
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
** Description : Service for DMA Channel94 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if((IRQ_DMA_CHANNEL94_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL94_SR_CAT == IRQ_CAT23))
#if((IRQ_DMA_CHANNEL94_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL94_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH94SR_ISR, 0, IRQ_DMA_CHANNEL94_SR_PRIO)
#elif IRQ_DMA_CHANNEL94_SR_CAT == IRQ_CAT23
ISR(DMACH94SR_ISR)
#endif
{
  #if ((IRQ_DMA_CHANNEL94_USED == IRQ_DMA_USED_MCALSPI_TX) || \
           (IRQ_DMA_CHANNEL94_USED == IRQ_DMA_USED_MCALSPI_RX))
  uint32 DmaErrorstatus;
  #endif
  /* Enable Global Interrupts */
  Mcal_EnableAllInterrupts();

  /* SPI TX interrupt */
  #if (IRQ_DMA_CHANNEL94_USED == IRQ_DMA_USED_MCALSPI_TX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL94_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiTx(IRQ_DMA_CHANNEL94_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL94_PARAM);
  }
  /* SPI RX interrupt */
  #elif (IRQ_DMA_CHANNEL94_USED == IRQ_DMA_USED_MCALSPI_RX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL94_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiRx(IRQ_DMA_CHANNEL94_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL94_PARAM);
  }
  /* ADC interrupt */
  #elif (IRQ_DMA_CHANNEL94_USED == IRQ_DMA_USED_MCALADC)

  #if (ADC_GROUP_EMUX_SCAN == STD_ON)
  Adc_IsrDmaSrn(IRQ_DMA_CHANNEL94_PARAM);
  #endif /*End of ADC_GROUP_EMUX_SCAN == STD_ON*/

  /* DMA CDD interrupt */
  #elif (IRQ_DMA_CHANNEL94_USED == IRQ_DMA_AVAILABLE)
  /* User Code Begins */
  /* Complex DMA driver usage */
  #endif
}
#endif
/******************************************************************************
** Syntax : void DMACH95SR_ISR(void)                                        **
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
** Description : Service for DMA Channel95 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if((IRQ_DMA_CHANNEL95_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL95_SR_CAT == IRQ_CAT23))
#if((IRQ_DMA_CHANNEL95_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL95_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH95SR_ISR, 0, IRQ_DMA_CHANNEL95_SR_PRIO)
#elif IRQ_DMA_CHANNEL95_SR_CAT == IRQ_CAT23
ISR(DMACH95SR_ISR)
#endif
{
  #if ((IRQ_DMA_CHANNEL95_USED == IRQ_DMA_USED_MCALSPI_TX) || \
           (IRQ_DMA_CHANNEL95_USED == IRQ_DMA_USED_MCALSPI_RX))
  uint32 DmaErrorstatus;
  #endif
  /* Enable Global Interrupts */
  Mcal_EnableAllInterrupts();

  /* SPI TX interrupt */
  #if (IRQ_DMA_CHANNEL95_USED == IRQ_DMA_USED_MCALSPI_TX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL95_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiTx(IRQ_DMA_CHANNEL95_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL95_PARAM);
  }
  /* SPI RX interrupt */
  #elif (IRQ_DMA_CHANNEL95_USED == IRQ_DMA_USED_MCALSPI_RX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL95_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiRx(IRQ_DMA_CHANNEL95_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL95_PARAM);
  }
  /* ADC interrupt */
  #elif (IRQ_DMA_CHANNEL95_USED == IRQ_DMA_USED_MCALADC)

  #if (ADC_GROUP_EMUX_SCAN == STD_ON)
  Adc_IsrDmaSrn(IRQ_DMA_CHANNEL95_PARAM);
  #endif /*End of ADC_GROUP_EMUX_SCAN == STD_ON*/

  /* DMA CDD interrupt */
  #elif (IRQ_DMA_CHANNEL95_USED == IRQ_DMA_AVAILABLE)
  /* User Code Begins */
  /* Complex DMA driver usage */
  #endif
}
#endif
/******************************************************************************
** Syntax : void DMACH96SR_ISR(void)                                        **
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
** Description : Service for DMA Channel96 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if((IRQ_DMA_CHANNEL96_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL96_SR_CAT == IRQ_CAT23))
#if((IRQ_DMA_CHANNEL96_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL96_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH96SR_ISR, 0, IRQ_DMA_CHANNEL96_SR_PRIO)
#elif IRQ_DMA_CHANNEL96_SR_CAT == IRQ_CAT23
ISR(DMACH96SR_ISR)
#endif
{
  #if ((IRQ_DMA_CHANNEL96_USED == IRQ_DMA_USED_MCALSPI_TX) || \
           (IRQ_DMA_CHANNEL96_USED == IRQ_DMA_USED_MCALSPI_RX))
  uint32 DmaErrorstatus;
  #endif
  /* Enable Global Interrupts */
  Mcal_EnableAllInterrupts();

  /* SPI TX interrupt */
  #if (IRQ_DMA_CHANNEL96_USED == IRQ_DMA_USED_MCALSPI_TX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL96_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiTx(IRQ_DMA_CHANNEL96_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL96_PARAM);
  }
  /* SPI RX interrupt */
  #elif (IRQ_DMA_CHANNEL96_USED == IRQ_DMA_USED_MCALSPI_RX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL96_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiRx(IRQ_DMA_CHANNEL96_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL96_PARAM);
  }
  /* ADC interrupt */
  #elif (IRQ_DMA_CHANNEL96_USED == IRQ_DMA_USED_MCALADC)

  #if (ADC_GROUP_EMUX_SCAN == STD_ON)
  Adc_IsrDmaSrn(IRQ_DMA_CHANNEL96_PARAM);
  #endif /*End of ADC_GROUP_EMUX_SCAN == STD_ON*/

  /* DMA CDD interrupt */
  #elif (IRQ_DMA_CHANNEL96_USED == IRQ_DMA_AVAILABLE)
  /* User Code Begins */
  /* Complex DMA driver usage */
  #endif
}
#endif
/******************************************************************************
** Syntax : void DMACH97SR_ISR(void)                                        **
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
** Description : Service for DMA Channel97 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if((IRQ_DMA_CHANNEL97_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL97_SR_CAT == IRQ_CAT23))
#if((IRQ_DMA_CHANNEL97_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL97_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH97SR_ISR, 0, IRQ_DMA_CHANNEL97_SR_PRIO)
#elif IRQ_DMA_CHANNEL97_SR_CAT == IRQ_CAT23
ISR(DMACH97SR_ISR)
#endif
{
  #if ((IRQ_DMA_CHANNEL97_USED == IRQ_DMA_USED_MCALSPI_TX) || \
           (IRQ_DMA_CHANNEL97_USED == IRQ_DMA_USED_MCALSPI_RX))
  uint32 DmaErrorstatus;
  #endif
  /* Enable Global Interrupts */
  Mcal_EnableAllInterrupts();

  /* SPI TX interrupt */
  #if (IRQ_DMA_CHANNEL97_USED == IRQ_DMA_USED_MCALSPI_TX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL97_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiTx(IRQ_DMA_CHANNEL97_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL97_PARAM);
  }
  /* SPI RX interrupt */
  #elif (IRQ_DMA_CHANNEL97_USED == IRQ_DMA_USED_MCALSPI_RX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL97_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiRx(IRQ_DMA_CHANNEL97_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL97_PARAM);
  }
  /* ADC interrupt */
  #elif (IRQ_DMA_CHANNEL97_USED == IRQ_DMA_USED_MCALADC)

  #if (ADC_GROUP_EMUX_SCAN == STD_ON)
  Adc_IsrDmaSrn(IRQ_DMA_CHANNEL97_PARAM);
  #endif /*End of ADC_GROUP_EMUX_SCAN == STD_ON*/

  /* DMA CDD interrupt */
  #elif (IRQ_DMA_CHANNEL97_USED == IRQ_DMA_AVAILABLE)
  /* User Code Begins */
  /* Complex DMA driver usage */
  #endif
}
#endif
/******************************************************************************
** Syntax : void DMACH98SR_ISR(void)                                        **
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
** Description : Service for DMA Channel98 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if((IRQ_DMA_CHANNEL98_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL98_SR_CAT == IRQ_CAT23))
#if((IRQ_DMA_CHANNEL98_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL98_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH98SR_ISR, 0, IRQ_DMA_CHANNEL98_SR_PRIO)
#elif IRQ_DMA_CHANNEL98_SR_CAT == IRQ_CAT23
ISR(DMACH98SR_ISR)
#endif
{
  #if ((IRQ_DMA_CHANNEL98_USED == IRQ_DMA_USED_MCALSPI_TX) || \
           (IRQ_DMA_CHANNEL98_USED == IRQ_DMA_USED_MCALSPI_RX))
  uint32 DmaErrorstatus;
  #endif
  /* Enable Global Interrupts */
  Mcal_EnableAllInterrupts();

  /* SPI TX interrupt */
  #if (IRQ_DMA_CHANNEL98_USED == IRQ_DMA_USED_MCALSPI_TX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL98_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiTx(IRQ_DMA_CHANNEL98_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL98_PARAM);
  }
  /* SPI RX interrupt */
  #elif (IRQ_DMA_CHANNEL98_USED == IRQ_DMA_USED_MCALSPI_RX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL98_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiRx(IRQ_DMA_CHANNEL98_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL98_PARAM);
  }
  /* ADC interrupt */
  #elif (IRQ_DMA_CHANNEL98_USED == IRQ_DMA_USED_MCALADC)

  #if (ADC_GROUP_EMUX_SCAN == STD_ON)
  Adc_IsrDmaSrn(IRQ_DMA_CHANNEL98_PARAM);
  #endif /*End of ADC_GROUP_EMUX_SCAN == STD_ON*/

  /* DMA CDD interrupt */
  #elif (IRQ_DMA_CHANNEL98_USED == IRQ_DMA_AVAILABLE)
  /* User Code Begins */
  /* Complex DMA driver usage */
  #endif
}
#endif
/******************************************************************************
** Syntax : void DMACH99SR_ISR(void)                                        **
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
** Description : Service for DMA Channel99 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if((IRQ_DMA_CHANNEL99_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL99_SR_CAT == IRQ_CAT23))
#if((IRQ_DMA_CHANNEL99_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL99_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH99SR_ISR, 0, IRQ_DMA_CHANNEL99_SR_PRIO)
#elif IRQ_DMA_CHANNEL99_SR_CAT == IRQ_CAT23
ISR(DMACH99SR_ISR)
#endif
{
  #if ((IRQ_DMA_CHANNEL99_USED == IRQ_DMA_USED_MCALSPI_TX) || \
           (IRQ_DMA_CHANNEL99_USED == IRQ_DMA_USED_MCALSPI_RX))
  uint32 DmaErrorstatus;
  #endif
  /* Enable Global Interrupts */
  Mcal_EnableAllInterrupts();

  /* SPI TX interrupt */
  #if (IRQ_DMA_CHANNEL99_USED == IRQ_DMA_USED_MCALSPI_TX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL99_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiTx(IRQ_DMA_CHANNEL99_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL99_PARAM);
  }
  /* SPI RX interrupt */
  #elif (IRQ_DMA_CHANNEL99_USED == IRQ_DMA_USED_MCALSPI_RX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL99_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiRx(IRQ_DMA_CHANNEL99_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL99_PARAM);
  }
  /* ADC interrupt */
  #elif (IRQ_DMA_CHANNEL99_USED == IRQ_DMA_USED_MCALADC)

  #if (ADC_GROUP_EMUX_SCAN == STD_ON)
  Adc_IsrDmaSrn(IRQ_DMA_CHANNEL99_PARAM);
  #endif /*End of ADC_GROUP_EMUX_SCAN == STD_ON*/

  /* DMA CDD interrupt */
  #elif (IRQ_DMA_CHANNEL99_USED == IRQ_DMA_AVAILABLE)
  /* User Code Begins */
  /* Complex DMA driver usage */
  #endif
}
#endif
/******************************************************************************
** Syntax : void DMACH100SR_ISR(void)                                        **
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
** Description : Service for DMA Channel100 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if((IRQ_DMA_CHANNEL100_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL100_SR_CAT == IRQ_CAT23))
#if((IRQ_DMA_CHANNEL100_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL100_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH100SR_ISR, 0, IRQ_DMA_CHANNEL100_SR_PRIO)
#elif IRQ_DMA_CHANNEL100_SR_CAT == IRQ_CAT23
ISR(DMACH100SR_ISR)
#endif
{
  #if ((IRQ_DMA_CHANNEL100_USED == IRQ_DMA_USED_MCALSPI_TX) || \
           (IRQ_DMA_CHANNEL100_USED == IRQ_DMA_USED_MCALSPI_RX))
  uint32 DmaErrorstatus;
  #endif
  /* Enable Global Interrupts */
  Mcal_EnableAllInterrupts();

  /* SPI TX interrupt */
  #if (IRQ_DMA_CHANNEL100_USED == IRQ_DMA_USED_MCALSPI_TX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL100_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiTx(IRQ_DMA_CHANNEL100_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL100_PARAM);
  }
  /* SPI RX interrupt */
  #elif (IRQ_DMA_CHANNEL100_USED == IRQ_DMA_USED_MCALSPI_RX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL100_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiRx(IRQ_DMA_CHANNEL100_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL100_PARAM);
  }
  /* ADC interrupt */
  #elif (IRQ_DMA_CHANNEL100_USED == IRQ_DMA_USED_MCALADC)

  #if (ADC_GROUP_EMUX_SCAN == STD_ON)
  Adc_IsrDmaSrn(IRQ_DMA_CHANNEL100_PARAM);
  #endif /*End of ADC_GROUP_EMUX_SCAN == STD_ON*/

  /* DMA CDD interrupt */
  #elif (IRQ_DMA_CHANNEL100_USED == IRQ_DMA_AVAILABLE)
  /* User Code Begins */
  /* Complex DMA driver usage */
  #endif
}
#endif
/******************************************************************************
** Syntax : void DMACH101SR_ISR(void)                                        **
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
** Description : Service for DMA Channel101 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if((IRQ_DMA_CHANNEL101_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL101_SR_CAT == IRQ_CAT23))
#if((IRQ_DMA_CHANNEL101_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL101_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH101SR_ISR, 0, IRQ_DMA_CHANNEL101_SR_PRIO)
#elif IRQ_DMA_CHANNEL101_SR_CAT == IRQ_CAT23
ISR(DMACH101SR_ISR)
#endif
{
  #if ((IRQ_DMA_CHANNEL101_USED == IRQ_DMA_USED_MCALSPI_TX) || \
           (IRQ_DMA_CHANNEL101_USED == IRQ_DMA_USED_MCALSPI_RX))
  uint32 DmaErrorstatus;
  #endif
  /* Enable Global Interrupts */
  Mcal_EnableAllInterrupts();

  /* SPI TX interrupt */
  #if (IRQ_DMA_CHANNEL101_USED == IRQ_DMA_USED_MCALSPI_TX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL101_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiTx(IRQ_DMA_CHANNEL101_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL101_PARAM);
  }
  /* SPI RX interrupt */
  #elif (IRQ_DMA_CHANNEL101_USED == IRQ_DMA_USED_MCALSPI_RX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL101_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiRx(IRQ_DMA_CHANNEL101_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL101_PARAM);
  }
  /* ADC interrupt */
  #elif (IRQ_DMA_CHANNEL101_USED == IRQ_DMA_USED_MCALADC)

  #if (ADC_GROUP_EMUX_SCAN == STD_ON)
  Adc_IsrDmaSrn(IRQ_DMA_CHANNEL101_PARAM);
  #endif /*End of ADC_GROUP_EMUX_SCAN == STD_ON*/

  /* DMA CDD interrupt */
  #elif (IRQ_DMA_CHANNEL101_USED == IRQ_DMA_AVAILABLE)
  /* User Code Begins */
  /* Complex DMA driver usage */
  #endif
}
#endif
/******************************************************************************
** Syntax : void DMACH102SR_ISR(void)                                        **
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
** Description : Service for DMA Channel102 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if((IRQ_DMA_CHANNEL102_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL102_SR_CAT == IRQ_CAT23))
#if((IRQ_DMA_CHANNEL102_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL102_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH102SR_ISR, 0, IRQ_DMA_CHANNEL102_SR_PRIO)
#elif IRQ_DMA_CHANNEL102_SR_CAT == IRQ_CAT23
ISR(DMACH102SR_ISR)
#endif
{
  #if ((IRQ_DMA_CHANNEL102_USED == IRQ_DMA_USED_MCALSPI_TX) || \
           (IRQ_DMA_CHANNEL102_USED == IRQ_DMA_USED_MCALSPI_RX))
  uint32 DmaErrorstatus;
  #endif
  /* Enable Global Interrupts */
  Mcal_EnableAllInterrupts();

  /* SPI TX interrupt */
  #if (IRQ_DMA_CHANNEL102_USED == IRQ_DMA_USED_MCALSPI_TX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL102_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiTx(IRQ_DMA_CHANNEL102_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL102_PARAM);
  }
  /* SPI RX interrupt */
  #elif (IRQ_DMA_CHANNEL102_USED == IRQ_DMA_USED_MCALSPI_RX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL102_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiRx(IRQ_DMA_CHANNEL102_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL102_PARAM);
  }
  /* ADC interrupt */
  #elif (IRQ_DMA_CHANNEL102_USED == IRQ_DMA_USED_MCALADC)

  #if (ADC_GROUP_EMUX_SCAN == STD_ON)
  Adc_IsrDmaSrn(IRQ_DMA_CHANNEL102_PARAM);
  #endif /*End of ADC_GROUP_EMUX_SCAN == STD_ON*/

  /* DMA CDD interrupt */
  #elif (IRQ_DMA_CHANNEL102_USED == IRQ_DMA_AVAILABLE)
  /* User Code Begins */
  /* Complex DMA driver usage */
  #endif
}
#endif
/******************************************************************************
** Syntax : void DMACH103SR_ISR(void)                                        **
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
** Description : Service for DMA Channel103 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if((IRQ_DMA_CHANNEL103_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL103_SR_CAT == IRQ_CAT23))
#if((IRQ_DMA_CHANNEL103_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL103_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH103SR_ISR, 0, IRQ_DMA_CHANNEL103_SR_PRIO)
#elif IRQ_DMA_CHANNEL103_SR_CAT == IRQ_CAT23
ISR(DMACH103SR_ISR)
#endif
{
  #if ((IRQ_DMA_CHANNEL103_USED == IRQ_DMA_USED_MCALSPI_TX) || \
           (IRQ_DMA_CHANNEL103_USED == IRQ_DMA_USED_MCALSPI_RX))
  uint32 DmaErrorstatus;
  #endif
  /* Enable Global Interrupts */
  Mcal_EnableAllInterrupts();

  /* SPI TX interrupt */
  #if (IRQ_DMA_CHANNEL103_USED == IRQ_DMA_USED_MCALSPI_TX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL103_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiTx(IRQ_DMA_CHANNEL103_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL103_PARAM);
  }
  /* SPI RX interrupt */
  #elif (IRQ_DMA_CHANNEL103_USED == IRQ_DMA_USED_MCALSPI_RX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL103_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiRx(IRQ_DMA_CHANNEL103_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL103_PARAM);
  }
  /* ADC interrupt */
  #elif (IRQ_DMA_CHANNEL103_USED == IRQ_DMA_USED_MCALADC)

  #if (ADC_GROUP_EMUX_SCAN == STD_ON)
  Adc_IsrDmaSrn(IRQ_DMA_CHANNEL103_PARAM);
  #endif /*End of ADC_GROUP_EMUX_SCAN == STD_ON*/

  /* DMA CDD interrupt */
  #elif (IRQ_DMA_CHANNEL103_USED == IRQ_DMA_AVAILABLE)
  /* User Code Begins */
  /* Complex DMA driver usage */
  #endif
}
#endif
/******************************************************************************
** Syntax : void DMACH104SR_ISR(void)                                        **
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
** Description : Service for DMA Channel104 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if((IRQ_DMA_CHANNEL104_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL104_SR_CAT == IRQ_CAT23))
#if((IRQ_DMA_CHANNEL104_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL104_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH104SR_ISR, 0, IRQ_DMA_CHANNEL104_SR_PRIO)
#elif IRQ_DMA_CHANNEL104_SR_CAT == IRQ_CAT23
ISR(DMACH104SR_ISR)
#endif
{
  #if ((IRQ_DMA_CHANNEL104_USED == IRQ_DMA_USED_MCALSPI_TX) || \
           (IRQ_DMA_CHANNEL104_USED == IRQ_DMA_USED_MCALSPI_RX))
  uint32 DmaErrorstatus;
  #endif
  /* Enable Global Interrupts */
  Mcal_EnableAllInterrupts();

  /* SPI TX interrupt */
  #if (IRQ_DMA_CHANNEL104_USED == IRQ_DMA_USED_MCALSPI_TX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL104_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiTx(IRQ_DMA_CHANNEL104_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL104_PARAM);
  }
  /* SPI RX interrupt */
  #elif (IRQ_DMA_CHANNEL104_USED == IRQ_DMA_USED_MCALSPI_RX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL104_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiRx(IRQ_DMA_CHANNEL104_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL104_PARAM);
  }
  /* ADC interrupt */
  #elif (IRQ_DMA_CHANNEL104_USED == IRQ_DMA_USED_MCALADC)

  #if (ADC_GROUP_EMUX_SCAN == STD_ON)
  Adc_IsrDmaSrn(IRQ_DMA_CHANNEL104_PARAM);
  #endif /*End of ADC_GROUP_EMUX_SCAN == STD_ON*/

  /* DMA CDD interrupt */
  #elif (IRQ_DMA_CHANNEL104_USED == IRQ_DMA_AVAILABLE)
  /* User Code Begins */
  /* Complex DMA driver usage */
  #endif
}
#endif
/******************************************************************************
** Syntax : void DMACH105SR_ISR(void)                                        **
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
** Description : Service for DMA Channel105 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if((IRQ_DMA_CHANNEL105_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL105_SR_CAT == IRQ_CAT23))
#if((IRQ_DMA_CHANNEL105_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL105_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH105SR_ISR, 0, IRQ_DMA_CHANNEL105_SR_PRIO)
#elif IRQ_DMA_CHANNEL105_SR_CAT == IRQ_CAT23
ISR(DMACH105SR_ISR)
#endif
{
  #if ((IRQ_DMA_CHANNEL105_USED == IRQ_DMA_USED_MCALSPI_TX) || \
           (IRQ_DMA_CHANNEL105_USED == IRQ_DMA_USED_MCALSPI_RX))
  uint32 DmaErrorstatus;
  #endif
  /* Enable Global Interrupts */
  Mcal_EnableAllInterrupts();

  /* SPI TX interrupt */
  #if (IRQ_DMA_CHANNEL105_USED == IRQ_DMA_USED_MCALSPI_TX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL105_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiTx(IRQ_DMA_CHANNEL105_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL105_PARAM);
  }
  /* SPI RX interrupt */
  #elif (IRQ_DMA_CHANNEL105_USED == IRQ_DMA_USED_MCALSPI_RX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL105_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiRx(IRQ_DMA_CHANNEL105_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL105_PARAM);
  }
  /* ADC interrupt */
  #elif (IRQ_DMA_CHANNEL105_USED == IRQ_DMA_USED_MCALADC)

  #if (ADC_GROUP_EMUX_SCAN == STD_ON)
  Adc_IsrDmaSrn(IRQ_DMA_CHANNEL105_PARAM);
  #endif /*End of ADC_GROUP_EMUX_SCAN == STD_ON*/

  /* DMA CDD interrupt */
  #elif (IRQ_DMA_CHANNEL105_USED == IRQ_DMA_AVAILABLE)
  /* User Code Begins */
  /* Complex DMA driver usage */
  #endif
}
#endif
/******************************************************************************
** Syntax : void DMACH106SR_ISR(void)                                        **
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
** Description : Service for DMA Channel106 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if((IRQ_DMA_CHANNEL106_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL106_SR_CAT == IRQ_CAT23))
#if((IRQ_DMA_CHANNEL106_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL106_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH106SR_ISR, 0, IRQ_DMA_CHANNEL106_SR_PRIO)
#elif IRQ_DMA_CHANNEL106_SR_CAT == IRQ_CAT23
ISR(DMACH106SR_ISR)
#endif
{
  #if ((IRQ_DMA_CHANNEL106_USED == IRQ_DMA_USED_MCALSPI_TX) || \
           (IRQ_DMA_CHANNEL106_USED == IRQ_DMA_USED_MCALSPI_RX))
  uint32 DmaErrorstatus;
  #endif
  /* Enable Global Interrupts */
  Mcal_EnableAllInterrupts();

  /* SPI TX interrupt */
  #if (IRQ_DMA_CHANNEL106_USED == IRQ_DMA_USED_MCALSPI_TX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL106_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiTx(IRQ_DMA_CHANNEL106_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL106_PARAM);
  }
  /* SPI RX interrupt */
  #elif (IRQ_DMA_CHANNEL106_USED == IRQ_DMA_USED_MCALSPI_RX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL106_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiRx(IRQ_DMA_CHANNEL106_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL106_PARAM);
  }
  /* ADC interrupt */
  #elif (IRQ_DMA_CHANNEL106_USED == IRQ_DMA_USED_MCALADC)

  #if (ADC_GROUP_EMUX_SCAN == STD_ON)
  Adc_IsrDmaSrn(IRQ_DMA_CHANNEL106_PARAM);
  #endif /*End of ADC_GROUP_EMUX_SCAN == STD_ON*/

  /* DMA CDD interrupt */
  #elif (IRQ_DMA_CHANNEL106_USED == IRQ_DMA_AVAILABLE)
  /* User Code Begins */
  /* Complex DMA driver usage */
  #endif
}
#endif
/******************************************************************************
** Syntax : void DMACH107SR_ISR(void)                                        **
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
** Description : Service for DMA Channel107 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if((IRQ_DMA_CHANNEL107_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL107_SR_CAT == IRQ_CAT23))
#if((IRQ_DMA_CHANNEL107_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL107_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH107SR_ISR, 0, IRQ_DMA_CHANNEL107_SR_PRIO)
#elif IRQ_DMA_CHANNEL107_SR_CAT == IRQ_CAT23
ISR(DMACH107SR_ISR)
#endif
{
  #if ((IRQ_DMA_CHANNEL107_USED == IRQ_DMA_USED_MCALSPI_TX) || \
           (IRQ_DMA_CHANNEL107_USED == IRQ_DMA_USED_MCALSPI_RX))
  uint32 DmaErrorstatus;
  #endif
  /* Enable Global Interrupts */
  Mcal_EnableAllInterrupts();

  /* SPI TX interrupt */
  #if (IRQ_DMA_CHANNEL107_USED == IRQ_DMA_USED_MCALSPI_TX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL107_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiTx(IRQ_DMA_CHANNEL107_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL107_PARAM);
  }
  /* SPI RX interrupt */
  #elif (IRQ_DMA_CHANNEL107_USED == IRQ_DMA_USED_MCALSPI_RX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL107_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiRx(IRQ_DMA_CHANNEL107_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL107_PARAM);
  }
  /* ADC interrupt */
  #elif (IRQ_DMA_CHANNEL107_USED == IRQ_DMA_USED_MCALADC)

  #if (ADC_GROUP_EMUX_SCAN == STD_ON)
  Adc_IsrDmaSrn(IRQ_DMA_CHANNEL107_PARAM);
  #endif /*End of ADC_GROUP_EMUX_SCAN == STD_ON*/

  /* DMA CDD interrupt */
  #elif (IRQ_DMA_CHANNEL107_USED == IRQ_DMA_AVAILABLE)
  /* User Code Begins */
  /* Complex DMA driver usage */
  #endif
}
#endif
/******************************************************************************
** Syntax : void DMACH108SR_ISR(void)                                        **
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
** Description : Service for DMA Channel108 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if((IRQ_DMA_CHANNEL108_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL108_SR_CAT == IRQ_CAT23))
#if((IRQ_DMA_CHANNEL108_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL108_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH108SR_ISR, 0, IRQ_DMA_CHANNEL108_SR_PRIO)
#elif IRQ_DMA_CHANNEL108_SR_CAT == IRQ_CAT23
ISR(DMACH108SR_ISR)
#endif
{
  #if ((IRQ_DMA_CHANNEL108_USED == IRQ_DMA_USED_MCALSPI_TX) || \
           (IRQ_DMA_CHANNEL108_USED == IRQ_DMA_USED_MCALSPI_RX))
  uint32 DmaErrorstatus;
  #endif
  /* Enable Global Interrupts */
  Mcal_EnableAllInterrupts();

  /* SPI TX interrupt */
  #if (IRQ_DMA_CHANNEL108_USED == IRQ_DMA_USED_MCALSPI_TX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL108_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiTx(IRQ_DMA_CHANNEL108_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL108_PARAM);
  }
  /* SPI RX interrupt */
  #elif (IRQ_DMA_CHANNEL108_USED == IRQ_DMA_USED_MCALSPI_RX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL108_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiRx(IRQ_DMA_CHANNEL108_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL108_PARAM);
  }
  /* ADC interrupt */
  #elif (IRQ_DMA_CHANNEL108_USED == IRQ_DMA_USED_MCALADC)

  #if (ADC_GROUP_EMUX_SCAN == STD_ON)
  Adc_IsrDmaSrn(IRQ_DMA_CHANNEL108_PARAM);
  #endif /*End of ADC_GROUP_EMUX_SCAN == STD_ON*/

  /* DMA CDD interrupt */
  #elif (IRQ_DMA_CHANNEL108_USED == IRQ_DMA_AVAILABLE)
  /* User Code Begins */
  /* Complex DMA driver usage */
  #endif
}
#endif
/******************************************************************************
** Syntax : void DMACH109SR_ISR(void)                                        **
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
** Description : Service for DMA Channel109 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if((IRQ_DMA_CHANNEL109_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL109_SR_CAT == IRQ_CAT23))
#if((IRQ_DMA_CHANNEL109_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL109_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH109SR_ISR, 0, IRQ_DMA_CHANNEL109_SR_PRIO)
#elif IRQ_DMA_CHANNEL109_SR_CAT == IRQ_CAT23
ISR(DMACH109SR_ISR)
#endif
{
  #if ((IRQ_DMA_CHANNEL109_USED == IRQ_DMA_USED_MCALSPI_TX) || \
           (IRQ_DMA_CHANNEL109_USED == IRQ_DMA_USED_MCALSPI_RX))
  uint32 DmaErrorstatus;
  #endif
  /* Enable Global Interrupts */
  Mcal_EnableAllInterrupts();

  /* SPI TX interrupt */
  #if (IRQ_DMA_CHANNEL109_USED == IRQ_DMA_USED_MCALSPI_TX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL109_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiTx(IRQ_DMA_CHANNEL109_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL109_PARAM);
  }
  /* SPI RX interrupt */
  #elif (IRQ_DMA_CHANNEL109_USED == IRQ_DMA_USED_MCALSPI_RX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL109_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiRx(IRQ_DMA_CHANNEL109_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL109_PARAM);
  }
  /* ADC interrupt */
  #elif (IRQ_DMA_CHANNEL109_USED == IRQ_DMA_USED_MCALADC)

  #if (ADC_GROUP_EMUX_SCAN == STD_ON)
  Adc_IsrDmaSrn(IRQ_DMA_CHANNEL109_PARAM);
  #endif /*End of ADC_GROUP_EMUX_SCAN == STD_ON*/

  /* DMA CDD interrupt */
  #elif (IRQ_DMA_CHANNEL109_USED == IRQ_DMA_AVAILABLE)
  /* User Code Begins */
  /* Complex DMA driver usage */
  #endif
}
#endif
/******************************************************************************
** Syntax : void DMACH110SR_ISR(void)                                        **
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
** Description : Service for DMA Channel110 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if((IRQ_DMA_CHANNEL110_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL110_SR_CAT == IRQ_CAT23))
#if((IRQ_DMA_CHANNEL110_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL110_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH110SR_ISR, 0, IRQ_DMA_CHANNEL110_SR_PRIO)
#elif IRQ_DMA_CHANNEL110_SR_CAT == IRQ_CAT23
ISR(DMACH110SR_ISR)
#endif
{
  #if ((IRQ_DMA_CHANNEL110_USED == IRQ_DMA_USED_MCALSPI_TX) || \
           (IRQ_DMA_CHANNEL110_USED == IRQ_DMA_USED_MCALSPI_RX))
  uint32 DmaErrorstatus;
  #endif
  /* Enable Global Interrupts */
  Mcal_EnableAllInterrupts();

  /* SPI TX interrupt */
  #if (IRQ_DMA_CHANNEL110_USED == IRQ_DMA_USED_MCALSPI_TX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL110_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiTx(IRQ_DMA_CHANNEL110_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL110_PARAM);
  }
  /* SPI RX interrupt */
  #elif (IRQ_DMA_CHANNEL110_USED == IRQ_DMA_USED_MCALSPI_RX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL110_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiRx(IRQ_DMA_CHANNEL110_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL110_PARAM);
  }
  /* ADC interrupt */
  #elif (IRQ_DMA_CHANNEL110_USED == IRQ_DMA_USED_MCALADC)

  #if (ADC_GROUP_EMUX_SCAN == STD_ON)
  Adc_IsrDmaSrn(IRQ_DMA_CHANNEL110_PARAM);
  #endif /*End of ADC_GROUP_EMUX_SCAN == STD_ON*/

  /* DMA CDD interrupt */
  #elif (IRQ_DMA_CHANNEL110_USED == IRQ_DMA_AVAILABLE)
  /* User Code Begins */
  /* Complex DMA driver usage */
  #endif
}
#endif
/******************************************************************************
** Syntax : void DMACH111SR_ISR(void)                                        **
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
** Description : Service for DMA Channel111 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if((IRQ_DMA_CHANNEL111_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL111_SR_CAT == IRQ_CAT23))
#if((IRQ_DMA_CHANNEL111_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL111_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH111SR_ISR, 0, IRQ_DMA_CHANNEL111_SR_PRIO)
#elif IRQ_DMA_CHANNEL111_SR_CAT == IRQ_CAT23
ISR(DMACH111SR_ISR)
#endif
{
  #if ((IRQ_DMA_CHANNEL111_USED == IRQ_DMA_USED_MCALSPI_TX) || \
           (IRQ_DMA_CHANNEL111_USED == IRQ_DMA_USED_MCALSPI_RX))
  uint32 DmaErrorstatus;
  #endif
  /* Enable Global Interrupts */
  Mcal_EnableAllInterrupts();

  /* SPI TX interrupt */
  #if (IRQ_DMA_CHANNEL111_USED == IRQ_DMA_USED_MCALSPI_TX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL111_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiTx(IRQ_DMA_CHANNEL111_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL111_PARAM);
  }
  /* SPI RX interrupt */
  #elif (IRQ_DMA_CHANNEL111_USED == IRQ_DMA_USED_MCALSPI_RX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL111_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiRx(IRQ_DMA_CHANNEL111_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL111_PARAM);
  }
  /* ADC interrupt */
  #elif (IRQ_DMA_CHANNEL111_USED == IRQ_DMA_USED_MCALADC)

  #if (ADC_GROUP_EMUX_SCAN == STD_ON)
  Adc_IsrDmaSrn(IRQ_DMA_CHANNEL111_PARAM);
  #endif /*End of ADC_GROUP_EMUX_SCAN == STD_ON*/

  /* DMA CDD interrupt */
  #elif (IRQ_DMA_CHANNEL111_USED == IRQ_DMA_AVAILABLE)
  /* User Code Begins */
  /* Complex DMA driver usage */
  #endif
}
#endif
/******************************************************************************
** Syntax : void DMACH112SR_ISR(void)                                        **
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
** Description : Service for DMA Channel112 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if((IRQ_DMA_CHANNEL112_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL112_SR_CAT == IRQ_CAT23))
#if((IRQ_DMA_CHANNEL112_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL112_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH112SR_ISR, 0, IRQ_DMA_CHANNEL112_SR_PRIO)
#elif IRQ_DMA_CHANNEL112_SR_CAT == IRQ_CAT23
ISR(DMACH112SR_ISR)
#endif
{
  #if ((IRQ_DMA_CHANNEL112_USED == IRQ_DMA_USED_MCALSPI_TX) || \
           (IRQ_DMA_CHANNEL112_USED == IRQ_DMA_USED_MCALSPI_RX))
  uint32 DmaErrorstatus;
  #endif
  /* Enable Global Interrupts */
  Mcal_EnableAllInterrupts();

  /* SPI TX interrupt */
  #if (IRQ_DMA_CHANNEL112_USED == IRQ_DMA_USED_MCALSPI_TX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL112_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiTx(IRQ_DMA_CHANNEL112_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL112_PARAM);
  }
  /* SPI RX interrupt */
  #elif (IRQ_DMA_CHANNEL112_USED == IRQ_DMA_USED_MCALSPI_RX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL112_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiRx(IRQ_DMA_CHANNEL112_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL112_PARAM);
  }
  /* ADC interrupt */
  #elif (IRQ_DMA_CHANNEL112_USED == IRQ_DMA_USED_MCALADC)

  #if (ADC_GROUP_EMUX_SCAN == STD_ON)
  Adc_IsrDmaSrn(IRQ_DMA_CHANNEL112_PARAM);
  #endif /*End of ADC_GROUP_EMUX_SCAN == STD_ON*/

  /* DMA CDD interrupt */
  #elif (IRQ_DMA_CHANNEL112_USED == IRQ_DMA_AVAILABLE)
  /* User Code Begins */
  /* Complex DMA driver usage */
  #endif
}
#endif
/******************************************************************************
** Syntax : void DMACH113SR_ISR(void)                                        **
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
** Description : Service for DMA Channel113 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if((IRQ_DMA_CHANNEL113_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL113_SR_CAT == IRQ_CAT23))
#if((IRQ_DMA_CHANNEL113_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL113_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH113SR_ISR, 0, IRQ_DMA_CHANNEL113_SR_PRIO)
#elif IRQ_DMA_CHANNEL113_SR_CAT == IRQ_CAT23
ISR(DMACH113SR_ISR)
#endif
{
  #if ((IRQ_DMA_CHANNEL113_USED == IRQ_DMA_USED_MCALSPI_TX) || \
           (IRQ_DMA_CHANNEL113_USED == IRQ_DMA_USED_MCALSPI_RX))
  uint32 DmaErrorstatus;
  #endif
  /* Enable Global Interrupts */
  Mcal_EnableAllInterrupts();

  /* SPI TX interrupt */
  #if (IRQ_DMA_CHANNEL113_USED == IRQ_DMA_USED_MCALSPI_TX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL113_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiTx(IRQ_DMA_CHANNEL113_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL113_PARAM);
  }
  /* SPI RX interrupt */
  #elif (IRQ_DMA_CHANNEL113_USED == IRQ_DMA_USED_MCALSPI_RX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL113_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiRx(IRQ_DMA_CHANNEL113_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL113_PARAM);
  }
  /* ADC interrupt */
  #elif (IRQ_DMA_CHANNEL113_USED == IRQ_DMA_USED_MCALADC)

  #if (ADC_GROUP_EMUX_SCAN == STD_ON)
  Adc_IsrDmaSrn(IRQ_DMA_CHANNEL113_PARAM);
  #endif /*End of ADC_GROUP_EMUX_SCAN == STD_ON*/

  /* DMA CDD interrupt */
  #elif (IRQ_DMA_CHANNEL113_USED == IRQ_DMA_AVAILABLE)
  /* User Code Begins */
  /* Complex DMA driver usage */
  #endif
}
#endif
/******************************************************************************
** Syntax : void DMACH114SR_ISR(void)                                        **
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
** Description : Service for DMA Channel114 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if((IRQ_DMA_CHANNEL114_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL114_SR_CAT == IRQ_CAT23))
#if((IRQ_DMA_CHANNEL114_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL114_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH114SR_ISR, 0, IRQ_DMA_CHANNEL114_SR_PRIO)
#elif IRQ_DMA_CHANNEL114_SR_CAT == IRQ_CAT23
ISR(DMACH114SR_ISR)
#endif
{
  #if ((IRQ_DMA_CHANNEL114_USED == IRQ_DMA_USED_MCALSPI_TX) || \
           (IRQ_DMA_CHANNEL114_USED == IRQ_DMA_USED_MCALSPI_RX))
  uint32 DmaErrorstatus;
  #endif
  /* Enable Global Interrupts */
  Mcal_EnableAllInterrupts();

  /* SPI TX interrupt */
  #if (IRQ_DMA_CHANNEL114_USED == IRQ_DMA_USED_MCALSPI_TX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL114_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiTx(IRQ_DMA_CHANNEL114_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL114_PARAM);
  }
  /* SPI RX interrupt */
  #elif (IRQ_DMA_CHANNEL114_USED == IRQ_DMA_USED_MCALSPI_RX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL114_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiRx(IRQ_DMA_CHANNEL114_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL114_PARAM);
  }
  /* ADC interrupt */
  #elif (IRQ_DMA_CHANNEL114_USED == IRQ_DMA_USED_MCALADC)

  #if (ADC_GROUP_EMUX_SCAN == STD_ON)
  Adc_IsrDmaSrn(IRQ_DMA_CHANNEL114_PARAM);
  #endif /*End of ADC_GROUP_EMUX_SCAN == STD_ON*/

  /* DMA CDD interrupt */
  #elif (IRQ_DMA_CHANNEL114_USED == IRQ_DMA_AVAILABLE)
  /* User Code Begins */
  /* Complex DMA driver usage */
  #endif
}
#endif
/******************************************************************************
** Syntax : void DMACH115SR_ISR(void)                                        **
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
** Description : Service for DMA Channel115 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if((IRQ_DMA_CHANNEL115_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL115_SR_CAT == IRQ_CAT23))
#if((IRQ_DMA_CHANNEL115_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL115_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH115SR_ISR, 0, IRQ_DMA_CHANNEL115_SR_PRIO)
#elif IRQ_DMA_CHANNEL115_SR_CAT == IRQ_CAT23
ISR(DMACH115SR_ISR)
#endif
{
  #if ((IRQ_DMA_CHANNEL115_USED == IRQ_DMA_USED_MCALSPI_TX) || \
           (IRQ_DMA_CHANNEL115_USED == IRQ_DMA_USED_MCALSPI_RX))
  uint32 DmaErrorstatus;
  #endif
  /* Enable Global Interrupts */
  Mcal_EnableAllInterrupts();

  /* SPI TX interrupt */
  #if (IRQ_DMA_CHANNEL115_USED == IRQ_DMA_USED_MCALSPI_TX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL115_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiTx(IRQ_DMA_CHANNEL115_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL115_PARAM);
  }
  /* SPI RX interrupt */
  #elif (IRQ_DMA_CHANNEL115_USED == IRQ_DMA_USED_MCALSPI_RX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL115_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiRx(IRQ_DMA_CHANNEL115_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL115_PARAM);
  }
  /* ADC interrupt */
  #elif (IRQ_DMA_CHANNEL115_USED == IRQ_DMA_USED_MCALADC)

  #if (ADC_GROUP_EMUX_SCAN == STD_ON)
  Adc_IsrDmaSrn(IRQ_DMA_CHANNEL115_PARAM);
  #endif /*End of ADC_GROUP_EMUX_SCAN == STD_ON*/

  /* DMA CDD interrupt */
  #elif (IRQ_DMA_CHANNEL115_USED == IRQ_DMA_AVAILABLE)
  /* User Code Begins */
  /* Complex DMA driver usage */
  #endif
}
#endif
/******************************************************************************
** Syntax : void DMACH116SR_ISR(void)                                        **
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
** Description : Service for DMA Channel116 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if((IRQ_DMA_CHANNEL116_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL116_SR_CAT == IRQ_CAT23))
#if((IRQ_DMA_CHANNEL116_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL116_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH116SR_ISR, 0, IRQ_DMA_CHANNEL116_SR_PRIO)
#elif IRQ_DMA_CHANNEL116_SR_CAT == IRQ_CAT23
ISR(DMACH116SR_ISR)
#endif
{
  #if ((IRQ_DMA_CHANNEL116_USED == IRQ_DMA_USED_MCALSPI_TX) || \
           (IRQ_DMA_CHANNEL116_USED == IRQ_DMA_USED_MCALSPI_RX))
  uint32 DmaErrorstatus;
  #endif
  /* Enable Global Interrupts */
  Mcal_EnableAllInterrupts();

  /* SPI TX interrupt */
  #if (IRQ_DMA_CHANNEL116_USED == IRQ_DMA_USED_MCALSPI_TX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL116_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiTx(IRQ_DMA_CHANNEL116_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL116_PARAM);
  }
  /* SPI RX interrupt */
  #elif (IRQ_DMA_CHANNEL116_USED == IRQ_DMA_USED_MCALSPI_RX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL116_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiRx(IRQ_DMA_CHANNEL116_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL116_PARAM);
  }
  /* ADC interrupt */
  #elif (IRQ_DMA_CHANNEL116_USED == IRQ_DMA_USED_MCALADC)

  #if (ADC_GROUP_EMUX_SCAN == STD_ON)
  Adc_IsrDmaSrn(IRQ_DMA_CHANNEL116_PARAM);
  #endif /*End of ADC_GROUP_EMUX_SCAN == STD_ON*/

  /* DMA CDD interrupt */
  #elif (IRQ_DMA_CHANNEL116_USED == IRQ_DMA_AVAILABLE)
  /* User Code Begins */
  /* Complex DMA driver usage */
  #endif
}
#endif
/******************************************************************************
** Syntax : void DMACH117SR_ISR(void)                                        **
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
** Description : Service for DMA Channel117 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if((IRQ_DMA_CHANNEL117_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL117_SR_CAT == IRQ_CAT23))
#if((IRQ_DMA_CHANNEL117_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL117_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH117SR_ISR, 0, IRQ_DMA_CHANNEL117_SR_PRIO)
#elif IRQ_DMA_CHANNEL117_SR_CAT == IRQ_CAT23
ISR(DMACH117SR_ISR)
#endif
{
  #if ((IRQ_DMA_CHANNEL117_USED == IRQ_DMA_USED_MCALSPI_TX) || \
           (IRQ_DMA_CHANNEL117_USED == IRQ_DMA_USED_MCALSPI_RX))
  uint32 DmaErrorstatus;
  #endif
  /* Enable Global Interrupts */
  Mcal_EnableAllInterrupts();

  /* SPI TX interrupt */
  #if (IRQ_DMA_CHANNEL117_USED == IRQ_DMA_USED_MCALSPI_TX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL117_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiTx(IRQ_DMA_CHANNEL117_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL117_PARAM);
  }
  /* SPI RX interrupt */
  #elif (IRQ_DMA_CHANNEL117_USED == IRQ_DMA_USED_MCALSPI_RX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL117_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiRx(IRQ_DMA_CHANNEL117_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL117_PARAM);
  }
  /* ADC interrupt */
  #elif (IRQ_DMA_CHANNEL117_USED == IRQ_DMA_USED_MCALADC)

  #if (ADC_GROUP_EMUX_SCAN == STD_ON)
  Adc_IsrDmaSrn(IRQ_DMA_CHANNEL117_PARAM);
  #endif /*End of ADC_GROUP_EMUX_SCAN == STD_ON*/

  /* DMA CDD interrupt */
  #elif (IRQ_DMA_CHANNEL117_USED == IRQ_DMA_AVAILABLE)
  /* User Code Begins */
  /* Complex DMA driver usage */
  #endif
}
#endif
/******************************************************************************
** Syntax : void DMACH118SR_ISR(void)                                        **
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
** Description : Service for DMA Channel118 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if((IRQ_DMA_CHANNEL118_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL118_SR_CAT == IRQ_CAT23))
#if((IRQ_DMA_CHANNEL118_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL118_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH118SR_ISR, 0, IRQ_DMA_CHANNEL118_SR_PRIO)
#elif IRQ_DMA_CHANNEL118_SR_CAT == IRQ_CAT23
ISR(DMACH118SR_ISR)
#endif
{
  #if ((IRQ_DMA_CHANNEL118_USED == IRQ_DMA_USED_MCALSPI_TX) || \
           (IRQ_DMA_CHANNEL118_USED == IRQ_DMA_USED_MCALSPI_RX))
  uint32 DmaErrorstatus;
  #endif
  /* Enable Global Interrupts */
  Mcal_EnableAllInterrupts();

  /* SPI TX interrupt */
  #if (IRQ_DMA_CHANNEL118_USED == IRQ_DMA_USED_MCALSPI_TX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL118_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiTx(IRQ_DMA_CHANNEL118_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL118_PARAM);
  }
  /* SPI RX interrupt */
  #elif (IRQ_DMA_CHANNEL118_USED == IRQ_DMA_USED_MCALSPI_RX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL118_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiRx(IRQ_DMA_CHANNEL118_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL118_PARAM);
  }
  /* ADC interrupt */
  #elif (IRQ_DMA_CHANNEL118_USED == IRQ_DMA_USED_MCALADC)

  #if (ADC_GROUP_EMUX_SCAN == STD_ON)
  Adc_IsrDmaSrn(IRQ_DMA_CHANNEL118_PARAM);
  #endif /*End of ADC_GROUP_EMUX_SCAN == STD_ON*/

  /* DMA CDD interrupt */
  #elif (IRQ_DMA_CHANNEL118_USED == IRQ_DMA_AVAILABLE)
  /* User Code Begins */
  /* Complex DMA driver usage */
  #endif
}
#endif
/******************************************************************************
** Syntax : void DMACH119SR_ISR(void)                                        **
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
** Description : Service for DMA Channel119 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if((IRQ_DMA_CHANNEL119_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL119_SR_CAT == IRQ_CAT23))
#if((IRQ_DMA_CHANNEL119_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL119_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH119SR_ISR, 0, IRQ_DMA_CHANNEL119_SR_PRIO)
#elif IRQ_DMA_CHANNEL119_SR_CAT == IRQ_CAT23
ISR(DMACH119SR_ISR)
#endif
{
  #if ((IRQ_DMA_CHANNEL119_USED == IRQ_DMA_USED_MCALSPI_TX) || \
           (IRQ_DMA_CHANNEL119_USED == IRQ_DMA_USED_MCALSPI_RX))
  uint32 DmaErrorstatus;
  #endif
  /* Enable Global Interrupts */
  Mcal_EnableAllInterrupts();

  /* SPI TX interrupt */
  #if (IRQ_DMA_CHANNEL119_USED == IRQ_DMA_USED_MCALSPI_TX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL119_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiTx(IRQ_DMA_CHANNEL119_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL119_PARAM);
  }
  /* SPI RX interrupt */
  #elif (IRQ_DMA_CHANNEL119_USED == IRQ_DMA_USED_MCALSPI_RX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL119_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiRx(IRQ_DMA_CHANNEL119_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL119_PARAM);
  }
  /* ADC interrupt */
  #elif (IRQ_DMA_CHANNEL119_USED == IRQ_DMA_USED_MCALADC)

  #if (ADC_GROUP_EMUX_SCAN == STD_ON)
  Adc_IsrDmaSrn(IRQ_DMA_CHANNEL119_PARAM);
  #endif /*End of ADC_GROUP_EMUX_SCAN == STD_ON*/

  /* DMA CDD interrupt */
  #elif (IRQ_DMA_CHANNEL119_USED == IRQ_DMA_AVAILABLE)
  /* User Code Begins */
  /* Complex DMA driver usage */
  #endif
}
#endif
/******************************************************************************
** Syntax : void DMACH120SR_ISR(void)                                        **
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
** Description : Service for DMA Channel120 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if((IRQ_DMA_CHANNEL120_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL120_SR_CAT == IRQ_CAT23))
#if((IRQ_DMA_CHANNEL120_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL120_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH120SR_ISR, 0, IRQ_DMA_CHANNEL120_SR_PRIO)
#elif IRQ_DMA_CHANNEL120_SR_CAT == IRQ_CAT23
ISR(DMACH120SR_ISR)
#endif
{
  #if ((IRQ_DMA_CHANNEL120_USED == IRQ_DMA_USED_MCALSPI_TX) || \
           (IRQ_DMA_CHANNEL120_USED == IRQ_DMA_USED_MCALSPI_RX))
  uint32 DmaErrorstatus;
  #endif
  /* Enable Global Interrupts */
  Mcal_EnableAllInterrupts();

  /* SPI TX interrupt */
  #if (IRQ_DMA_CHANNEL120_USED == IRQ_DMA_USED_MCALSPI_TX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL120_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiTx(IRQ_DMA_CHANNEL120_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL120_PARAM);
  }
  /* SPI RX interrupt */
  #elif (IRQ_DMA_CHANNEL120_USED == IRQ_DMA_USED_MCALSPI_RX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL120_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiRx(IRQ_DMA_CHANNEL120_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL120_PARAM);
  }
  /* ADC interrupt */
  #elif (IRQ_DMA_CHANNEL120_USED == IRQ_DMA_USED_MCALADC)

  #if (ADC_GROUP_EMUX_SCAN == STD_ON)
  Adc_IsrDmaSrn(IRQ_DMA_CHANNEL120_PARAM);
  #endif /*End of ADC_GROUP_EMUX_SCAN == STD_ON*/

  /* DMA CDD interrupt */
  #elif (IRQ_DMA_CHANNEL120_USED == IRQ_DMA_AVAILABLE)
  /* User Code Begins */
  /* Complex DMA driver usage */
  #endif
}
#endif
/******************************************************************************
** Syntax : void DMACH121SR_ISR(void)                                        **
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
** Description : Service for DMA Channel121 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if((IRQ_DMA_CHANNEL121_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL121_SR_CAT == IRQ_CAT23))
#if((IRQ_DMA_CHANNEL121_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL121_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH121SR_ISR, 0, IRQ_DMA_CHANNEL121_SR_PRIO)
#elif IRQ_DMA_CHANNEL121_SR_CAT == IRQ_CAT23
ISR(DMACH121SR_ISR)
#endif
{
  #if ((IRQ_DMA_CHANNEL121_USED == IRQ_DMA_USED_MCALSPI_TX) || \
           (IRQ_DMA_CHANNEL121_USED == IRQ_DMA_USED_MCALSPI_RX))
  uint32 DmaErrorstatus;
  #endif
  /* Enable Global Interrupts */
  Mcal_EnableAllInterrupts();

  /* SPI TX interrupt */
  #if (IRQ_DMA_CHANNEL121_USED == IRQ_DMA_USED_MCALSPI_TX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL121_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiTx(IRQ_DMA_CHANNEL121_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL121_PARAM);
  }
  /* SPI RX interrupt */
  #elif (IRQ_DMA_CHANNEL121_USED == IRQ_DMA_USED_MCALSPI_RX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL121_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiRx(IRQ_DMA_CHANNEL121_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL121_PARAM);
  }
  /* ADC interrupt */
  #elif (IRQ_DMA_CHANNEL121_USED == IRQ_DMA_USED_MCALADC)

  #if (ADC_GROUP_EMUX_SCAN == STD_ON)
  Adc_IsrDmaSrn(IRQ_DMA_CHANNEL121_PARAM);
  #endif /*End of ADC_GROUP_EMUX_SCAN == STD_ON*/

  /* DMA CDD interrupt */
  #elif (IRQ_DMA_CHANNEL121_USED == IRQ_DMA_AVAILABLE)
  /* User Code Begins */
  /* Complex DMA driver usage */
  #endif
}
#endif
/******************************************************************************
** Syntax : void DMACH122SR_ISR(void)                                        **
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
** Description : Service for DMA Channel122 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if((IRQ_DMA_CHANNEL122_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL122_SR_CAT == IRQ_CAT23))
#if((IRQ_DMA_CHANNEL122_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL122_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH122SR_ISR, 0, IRQ_DMA_CHANNEL122_SR_PRIO)
#elif IRQ_DMA_CHANNEL122_SR_CAT == IRQ_CAT23
ISR(DMACH122SR_ISR)
#endif
{
  #if ((IRQ_DMA_CHANNEL122_USED == IRQ_DMA_USED_MCALSPI_TX) || \
           (IRQ_DMA_CHANNEL122_USED == IRQ_DMA_USED_MCALSPI_RX))
  uint32 DmaErrorstatus;
  #endif
  /* Enable Global Interrupts */
  Mcal_EnableAllInterrupts();

  /* SPI TX interrupt */
  #if (IRQ_DMA_CHANNEL122_USED == IRQ_DMA_USED_MCALSPI_TX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL122_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiTx(IRQ_DMA_CHANNEL122_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL122_PARAM);
  }
  /* SPI RX interrupt */
  #elif (IRQ_DMA_CHANNEL122_USED == IRQ_DMA_USED_MCALSPI_RX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL122_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiRx(IRQ_DMA_CHANNEL122_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL122_PARAM);
  }
  /* ADC interrupt */
  #elif (IRQ_DMA_CHANNEL122_USED == IRQ_DMA_USED_MCALADC)

  #if (ADC_GROUP_EMUX_SCAN == STD_ON)
  Adc_IsrDmaSrn(IRQ_DMA_CHANNEL122_PARAM);
  #endif /*End of ADC_GROUP_EMUX_SCAN == STD_ON*/

  /* DMA CDD interrupt */
  #elif (IRQ_DMA_CHANNEL122_USED == IRQ_DMA_AVAILABLE)
  /* User Code Begins */
  /* Complex DMA driver usage */
  #endif
}
#endif
/******************************************************************************
** Syntax : void DMACH123SR_ISR(void)                                        **
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
** Description : Service for DMA Channel123 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if((IRQ_DMA_CHANNEL123_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL123_SR_CAT == IRQ_CAT23))
#if((IRQ_DMA_CHANNEL123_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL123_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH123SR_ISR, 0, IRQ_DMA_CHANNEL123_SR_PRIO)
#elif IRQ_DMA_CHANNEL123_SR_CAT == IRQ_CAT23
ISR(DMACH123SR_ISR)
#endif
{
  #if ((IRQ_DMA_CHANNEL123_USED == IRQ_DMA_USED_MCALSPI_TX) || \
           (IRQ_DMA_CHANNEL123_USED == IRQ_DMA_USED_MCALSPI_RX))
  uint32 DmaErrorstatus;
  #endif
  /* Enable Global Interrupts */
  Mcal_EnableAllInterrupts();

  /* SPI TX interrupt */
  #if (IRQ_DMA_CHANNEL123_USED == IRQ_DMA_USED_MCALSPI_TX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL123_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiTx(IRQ_DMA_CHANNEL123_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL123_PARAM);
  }
  /* SPI RX interrupt */
  #elif (IRQ_DMA_CHANNEL123_USED == IRQ_DMA_USED_MCALSPI_RX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL123_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiRx(IRQ_DMA_CHANNEL123_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL123_PARAM);
  }
  /* ADC interrupt */
  #elif (IRQ_DMA_CHANNEL123_USED == IRQ_DMA_USED_MCALADC)

  #if (ADC_GROUP_EMUX_SCAN == STD_ON)
  Adc_IsrDmaSrn(IRQ_DMA_CHANNEL123_PARAM);
  #endif /*End of ADC_GROUP_EMUX_SCAN == STD_ON*/

  /* DMA CDD interrupt */
  #elif (IRQ_DMA_CHANNEL123_USED == IRQ_DMA_AVAILABLE)
  /* User Code Begins */
  /* Complex DMA driver usage */
  #endif
}
#endif
/******************************************************************************
** Syntax : void DMACH124SR_ISR(void)                                        **
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
** Description : Service for DMA Channel124 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if((IRQ_DMA_CHANNEL124_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL124_SR_CAT == IRQ_CAT23))
#if((IRQ_DMA_CHANNEL124_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL124_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH124SR_ISR, 0, IRQ_DMA_CHANNEL124_SR_PRIO)
#elif IRQ_DMA_CHANNEL124_SR_CAT == IRQ_CAT23
ISR(DMACH124SR_ISR)
#endif
{
  #if ((IRQ_DMA_CHANNEL124_USED == IRQ_DMA_USED_MCALSPI_TX) || \
           (IRQ_DMA_CHANNEL124_USED == IRQ_DMA_USED_MCALSPI_RX))
  uint32 DmaErrorstatus;
  #endif
  /* Enable Global Interrupts */
  Mcal_EnableAllInterrupts();

  /* SPI TX interrupt */
  #if (IRQ_DMA_CHANNEL124_USED == IRQ_DMA_USED_MCALSPI_TX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL124_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiTx(IRQ_DMA_CHANNEL124_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL124_PARAM);
  }
  /* SPI RX interrupt */
  #elif (IRQ_DMA_CHANNEL124_USED == IRQ_DMA_USED_MCALSPI_RX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL124_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiRx(IRQ_DMA_CHANNEL124_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL124_PARAM);
  }
  /* ADC interrupt */
  #elif (IRQ_DMA_CHANNEL124_USED == IRQ_DMA_USED_MCALADC)

  #if (ADC_GROUP_EMUX_SCAN == STD_ON)
  Adc_IsrDmaSrn(IRQ_DMA_CHANNEL124_PARAM);
  #endif /*End of ADC_GROUP_EMUX_SCAN == STD_ON*/

  /* DMA CDD interrupt */
  #elif (IRQ_DMA_CHANNEL124_USED == IRQ_DMA_AVAILABLE)
  /* User Code Begins */
  /* Complex DMA driver usage */
  #endif
}
#endif
/******************************************************************************
** Syntax : void DMACH125SR_ISR(void)                                        **
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
** Description : Service for DMA Channel125 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if((IRQ_DMA_CHANNEL125_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL125_SR_CAT == IRQ_CAT23))
#if((IRQ_DMA_CHANNEL125_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL125_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH125SR_ISR, 0, IRQ_DMA_CHANNEL125_SR_PRIO)
#elif IRQ_DMA_CHANNEL125_SR_CAT == IRQ_CAT23
ISR(DMACH125SR_ISR)
#endif
{
  #if ((IRQ_DMA_CHANNEL125_USED == IRQ_DMA_USED_MCALSPI_TX) || \
           (IRQ_DMA_CHANNEL125_USED == IRQ_DMA_USED_MCALSPI_RX))
  uint32 DmaErrorstatus;
  #endif
  /* Enable Global Interrupts */
  Mcal_EnableAllInterrupts();

  /* SPI TX interrupt */
  #if (IRQ_DMA_CHANNEL125_USED == IRQ_DMA_USED_MCALSPI_TX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL125_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiTx(IRQ_DMA_CHANNEL125_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL125_PARAM);
  }
  /* SPI RX interrupt */
  #elif (IRQ_DMA_CHANNEL125_USED == IRQ_DMA_USED_MCALSPI_RX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL125_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiRx(IRQ_DMA_CHANNEL125_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL125_PARAM);
  }
  /* ADC interrupt */
  #elif (IRQ_DMA_CHANNEL125_USED == IRQ_DMA_USED_MCALADC)

  #if (ADC_GROUP_EMUX_SCAN == STD_ON)
  Adc_IsrDmaSrn(IRQ_DMA_CHANNEL125_PARAM);
  #endif /*End of ADC_GROUP_EMUX_SCAN == STD_ON*/

  /* DMA CDD interrupt */
  #elif (IRQ_DMA_CHANNEL125_USED == IRQ_DMA_AVAILABLE)
  /* User Code Begins */
  /* Complex DMA driver usage */
  #endif
}
#endif
/******************************************************************************
** Syntax : void DMACH126SR_ISR(void)                                        **
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
** Description : Service for DMA Channel126 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if((IRQ_DMA_CHANNEL126_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL126_SR_CAT == IRQ_CAT23))
#if((IRQ_DMA_CHANNEL126_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL126_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH126SR_ISR, 0, IRQ_DMA_CHANNEL126_SR_PRIO)
#elif IRQ_DMA_CHANNEL126_SR_CAT == IRQ_CAT23
ISR(DMACH126SR_ISR)
#endif
{
  #if ((IRQ_DMA_CHANNEL126_USED == IRQ_DMA_USED_MCALSPI_TX) || \
           (IRQ_DMA_CHANNEL126_USED == IRQ_DMA_USED_MCALSPI_RX))
  uint32 DmaErrorstatus;
  #endif
  /* Enable Global Interrupts */
  Mcal_EnableAllInterrupts();

  /* SPI TX interrupt */
  #if (IRQ_DMA_CHANNEL126_USED == IRQ_DMA_USED_MCALSPI_TX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL126_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiTx(IRQ_DMA_CHANNEL126_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL126_PARAM);
  }
  /* SPI RX interrupt */
  #elif (IRQ_DMA_CHANNEL126_USED == IRQ_DMA_USED_MCALSPI_RX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL126_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiRx(IRQ_DMA_CHANNEL126_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL126_PARAM);
  }
  /* ADC interrupt */
  #elif (IRQ_DMA_CHANNEL126_USED == IRQ_DMA_USED_MCALADC)

  #if (ADC_GROUP_EMUX_SCAN == STD_ON)
  Adc_IsrDmaSrn(IRQ_DMA_CHANNEL126_PARAM);
  #endif /*End of ADC_GROUP_EMUX_SCAN == STD_ON*/

  /* DMA CDD interrupt */
  #elif (IRQ_DMA_CHANNEL126_USED == IRQ_DMA_AVAILABLE)
  /* User Code Begins */
  /* Complex DMA driver usage */
  #endif
}
#endif
/******************************************************************************
** Syntax : void DMACH127SR_ISR(void)                                        **
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
** Description : Service for DMA Channel127 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if((IRQ_DMA_CHANNEL127_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL127_SR_CAT == IRQ_CAT23))
#if((IRQ_DMA_CHANNEL127_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL127_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH127SR_ISR, 0, IRQ_DMA_CHANNEL127_SR_PRIO)
#elif IRQ_DMA_CHANNEL127_SR_CAT == IRQ_CAT23
ISR(DMACH127SR_ISR)
#endif
{
  #if ((IRQ_DMA_CHANNEL127_USED == IRQ_DMA_USED_MCALSPI_TX) || \
           (IRQ_DMA_CHANNEL127_USED == IRQ_DMA_USED_MCALSPI_RX))
  uint32 DmaErrorstatus;
  #endif
  /* Enable Global Interrupts */
  Mcal_EnableAllInterrupts();

  /* SPI TX interrupt */
  #if (IRQ_DMA_CHANNEL127_USED == IRQ_DMA_USED_MCALSPI_TX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL127_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiTx(IRQ_DMA_CHANNEL127_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL127_PARAM);
  }
  /* SPI RX interrupt */
  #elif (IRQ_DMA_CHANNEL127_USED == IRQ_DMA_USED_MCALSPI_RX)

  DmaErrorstatus  = Spi_IsrCheckDmaError(IRQ_DMA_CHANNEL127_PARAM);
  if (DmaErrorstatus == 0U)
  {
    Spi_IsrDmaQspiRx(IRQ_DMA_CHANNEL127_PARAM);
  }
  else
  {
    Spi_IsrDmaError(IRQ_DMA_CHANNEL127_PARAM);
  }
  /* ADC interrupt */
  #elif (IRQ_DMA_CHANNEL127_USED == IRQ_DMA_USED_MCALADC)

  #if (ADC_GROUP_EMUX_SCAN == STD_ON)
  Adc_IsrDmaSrn(IRQ_DMA_CHANNEL127_PARAM);
  #endif /*End of ADC_GROUP_EMUX_SCAN == STD_ON*/

  /* DMA CDD interrupt */
  #elif (IRQ_DMA_CHANNEL127_USED == IRQ_DMA_AVAILABLE)
  /* User Code Begins */
  /* Complex DMA driver usage */
  #endif
}
#endif
#endif/*end of IRQ_DMA_CH64TO127_EXIST*/

#define IRQ_STOP_SEC_CODE
#include "MemMap.h"
