/**
  ******************************************************************************
  * File Name          : TIM.c
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

/* Includes ------------------------------------------------------------------*/
#include "tim.h"

/* USER CODE BEGIN 0 */
int bTime21 = US_STATE_TRIG_END;
int bMeasure = 0;
int mCounter = 0; // counter of TIM21
/* USER CODE END 0 */

TIM_HandleTypeDef htim21;

/* TIM21 init function */
void MX_TIM21_Init(void)
{
  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  htim21.Instance = TIM21;
  htim21.Init.Prescaler = 0;
  htim21.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim21.Init.Period = 0xff;
  htim21.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim21.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  if (HAL_TIM_Base_Init(&htim21) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim21, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim21, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }

}

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef* tim_baseHandle)
{

  if(tim_baseHandle->Instance==TIM21)
  {
  /* USER CODE BEGIN TIM21_MspInit 0 */

  /* USER CODE END TIM21_MspInit 0 */
    /* TIM21 clock enable */
    __HAL_RCC_TIM21_CLK_ENABLE();

    /* TIM21 interrupt Init */
    HAL_NVIC_SetPriority(TIM21_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(TIM21_IRQn);
  /* USER CODE BEGIN TIM21_MspInit 1 */

  /* USER CODE END TIM21_MspInit 1 */
  }
}

void HAL_TIM_Base_MspDeInit(TIM_HandleTypeDef* tim_baseHandle)
{

  if(tim_baseHandle->Instance==TIM21)
  {
  /* USER CODE BEGIN TIM21_MspDeInit 0 */

  /* USER CODE END TIM21_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_TIM21_CLK_DISABLE();

    /* TIM21 interrupt Deinit */
    HAL_NVIC_DisableIRQ(TIM21_IRQn);
  /* USER CODE BEGIN TIM21_MspDeInit 1 */

  /* USER CODE END TIM21_MspDeInit 1 */
  }
} 

/* USER CODE BEGIN 1 */
int __attribute__((optimize("O0"))) get_Ultra_Sonic(){
	// 4194 kHZ MSI clock
	// return n  33ms -> 534
	//  32ms -> 552
	//  14ms -> 221
	// 11.4ms-> 183
	// 8.8ms -> 137
	// 7.4   -> 108
	//  3.4ms-> 50
	//	1.5ms -> 18
	// return -1 abnormal module behavior


	bTime21 = US_STATE_TRIG_START;
	// start the timer
	HAL_TIM_Base_Start_IT(&htim21);
	// raise high level, 34 us, pulse generated trig signal
	on_Trig();
	do{
		;
	}while (bTime21 == US_STATE_TRIG_START) ;

	HAL_TIM_Base_Stop_IT(&htim21);
	off_Trig();

	bMeasure = US_STATE_MEASURE_START;
	mCounter=0;
	// get the distance measuring
	// If ultra-sonic module doesnt respond, it will stuck here!
	HAL_TIM_Base_Start_IT(&htim21);

	while(1){
		if(bMeasure != US_STATE_MEASURE_START){
			break;
		}
		if(mCounter >= (US_STATE_MEASURE_MAX_COUNTER)){
			// so it will jump out if timeout
			return -1;
		}
	}

	// on_LED();
	mCounter = 0;

	while(1){
		if(bMeasure != US_STATE_MEASURE_CONTINUE){
			break;
		}
		if(mCounter >= (US_STATE_MEASURE_MAX_COUNTER)){
			return -1;
		}
	}
	// off_LED();

	HAL_TIM_Base_Stop_IT(&htim21);

	return mCounter;
}
// return ms
float get_TIM21_Dur(){
	int period = 0xff;
	float freq = 4194000.0; //Hz
	float dur = (float)(1/freq) * 1000; // ms
	return period * dur;
}
// return cm

/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
