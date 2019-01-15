/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2019 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H__
#define __MAIN_H__

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private define ------------------------------------------------------------*/

#define IN_OUT_485_C_Pin GPIO_PIN_3
#define IN_OUT_485_C_GPIO_Port GPIOC
#define BOOT1_Pin GPIO_PIN_2
#define BOOT1_GPIO_Port GPIOB
#define CH_B_Pin GPIO_PIN_7
#define CH_B_GPIO_Port GPIOE
#define UP_CH_Pin GPIO_PIN_8
#define UP_CH_GPIO_Port GPIOE
#define DW_CH_Pin GPIO_PIN_9
#define DW_CH_GPIO_Port GPIOE
#define OPEN_Pin GPIO_PIN_10
#define OPEN_GPIO_Port GPIOE
#define CLOSE_Pin GPIO_PIN_11
#define CLOSE_GPIO_Port GPIOE
#define UP_LMT_SW_Pin GPIO_PIN_12
#define UP_LMT_SW_GPIO_Port GPIOE
#define DW_LMT_SW_Pin GPIO_PIN_13
#define DW_LMT_SW_GPIO_Port GPIOE
#define OPEN_LMT_SW_Pin GPIO_PIN_14
#define OPEN_LMT_SW_GPIO_Port GPIOE
#define CLOSE_LMT_SW_Pin GPIO_PIN_15
#define CLOSE_LMT_SW_GPIO_Port GPIOE
#define ULN2003_IN4_Pin GPIO_PIN_6
#define ULN2003_IN4_GPIO_Port GPIOC
#define ULN2003_IN3_Pin GPIO_PIN_7
#define ULN2003_IN3_GPIO_Port GPIOC
#define ULN2003_IN2_Pin GPIO_PIN_8
#define ULN2003_IN2_GPIO_Port GPIOC
#define ULN2003_IN1_Pin GPIO_PIN_9
#define ULN2003_IN1_GPIO_Port GPIOC
#define ULN_LMT_SW_Pin GPIO_PIN_8
#define ULN_LMT_SW_GPIO_Port GPIOA
#define H_LMT_SWL_Pin GPIO_PIN_10
#define H_LMT_SWL_GPIO_Port GPIOC
#define H_LMT_SWR_Pin GPIO_PIN_11
#define H_LMT_SWR_GPIO_Port GPIOC
#define V_LMT_SW_Pin GPIO_PIN_12
#define V_LMT_SW_GPIO_Port GPIOC
#define V_INPT1_Pin GPIO_PIN_0
#define V_INPT1_GPIO_Port GPIOD
#define V_INPT2_Pin GPIO_PIN_1
#define V_INPT2_GPIO_Port GPIOD
#define V_INPT3_Pin GPIO_PIN_2
#define V_INPT3_GPIO_Port GPIOD
#define V_INPT4_Pin GPIO_PIN_3
#define V_INPT4_GPIO_Port GPIOD
#define H_INPT1_Pin GPIO_PIN_4
#define H_INPT1_GPIO_Port GPIOD
#define H_INPT2_Pin GPIO_PIN_5
#define H_INPT2_GPIO_Port GPIOD
#define H_INPT3_Pin GPIO_PIN_6
#define H_INPT3_GPIO_Port GPIOD
#define H_INPT4_Pin GPIO_PIN_7
#define H_INPT4_GPIO_Port GPIOD
#define DS18B20_Pin GPIO_PIN_5
#define DS18B20_GPIO_Port GPIOB

/* ########################## Assert Selection ############################## */
/**
  * @brief Uncomment the line below to expanse the "assert_param" macro in the 
  *        HAL drivers code
  */
/* #define USE_FULL_ASSERT    1U */

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
 extern "C" {
#endif
void _Error_Handler(char *, int);

#define Error_Handler() _Error_Handler(__FILE__, __LINE__)
#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
