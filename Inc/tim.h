/**
  ******************************************************************************
  * File Name          : TIM.h
  * Description        : This file provides code for the configuration
  *                      of the TIM instances.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __tim_H
#define __tim_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */
#include "gpio.h"
/* USER CODE END Includes */

extern TIM_HandleTypeDef htim21;

/* USER CODE BEGIN Private defines */
#define US_STATE_TRIG_START      0x10
#define US_STATE_TRIG_END        0x11
#define US_STATE_MEASURE_START     0x20
#define US_STATE_MEASURE_CONTINUE  0x21
#define US_STATE_MEASURE_END       0x22
#define US_STATE_MEASURE_MAX_COUNTER  0x1FFF

/* USER CODE END Private defines */

void MX_TIM21_Init(void);

/* USER CODE BEGIN Prototypes */
int get_Ultra_Sonic();
float get_TIM21_Dur();
float get_Distance(int steps);
/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__ tim_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
