/**
  ******************************************************************************
  * @file    tim.h 
  * @authors Pablo Fuentes, Joseph Peñafiel
	* @version V1.0.1
  * @date    2019
  * @brief   Timer Library
  ******************************************************************************
*/

#ifndef __TIM_H
#define __TIM_H

#include "stm32l0xx_ll_tim.h"

/** 
 ===============================================================================
              ##### Type #####
 ===============================================================================
 */

typedef volatile uint32_t tick_t;

/** 
 ===============================================================================
              ##### Structure #####
 ===============================================================================
 */

typedef struct
{
  uint32_t period;
  uint32_t prescaler;
} timebase_t;

/** 
 ===============================================================================
              ##### Definitions #####
 ===============================================================================
 */

#define ___TIM_GET_IT_UPD(__TIMX__) ((LL_TIM_ReadReg(__TIMX__, DIER) & LL_TIM_DIER_UIE) == LL_TIM_DIER_UIE)
#define ___TIM_GET_FLAG_UPD(__TIMX__) ((LL_TIM_ReadReg(__TIMX__, SR) & LL_TIM_SR_UIF) == LL_TIM_SR_UIF)

#define IRQ_TIM2()                                                              \
  void __shadow_tim2(void);                                                     \
  void TIM2_IRQHandler(void)                                                    \
  {                                                                             \
    if ((___TIM_GET_IT_UPD(TIM2) != RESET) && (___TIM_GET_FLAG_UPD(TIM2) == 1)) \
    {                                                                           \
      LL_TIM_ClearFlag_UPDATE(TIM2);                                            \
      __shadow_tim2();                                                          \
    }                                                                           \
  }                                                                             \
  void __shadow_tim2(void)

/** 
 ===============================================================================
              ##### Functions #####
 ===============================================================================
 */

/* Timer Clocks */
uint8_t tim_clkEnableAndGetIRQn(TIM_TypeDef *TIMx);
uint32_t tim_getSrcClk(TIM_TypeDef *TIMx);

/* Period and Prescalers from desired frequency, return timer frequency clock */
uint32_t tim_getMinPrescalerAndMaxPeriod(timebase_t *parameter, TIM_TypeDef *TIMx, uint32_t desired_frecuency);

/* Funciones Timer Interrupt */
void tim_interrupt(TIM_TypeDef *TIMx, uint32_t prescaler, uint32_t period);
void tim_interruptMs(TIM_TypeDef *TIMx, uint32_t ms);

#endif
