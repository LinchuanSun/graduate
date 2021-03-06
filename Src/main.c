
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f4xx_hal.h"
#include "dma.h"
#include "i2c.h"
#include "usart.h"
#include "gpio.h"

/* USER CODE BEGIN Includes */
#include "delay.h"
#include "motorDrivers.h"
#include "datatype.h"
#include "GLS-B200.h"
#include "HMC5883L.h"
/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
/************************************* add by slc start ************************/
 int countH = 0 ,countV = 0;
   
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */
  void H_Init(void);
  void V_Init(void);
  void ALL_Init(void);
  
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  *
  * @retval None
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
    delay_init(168);
  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */
 
  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  MX_I2C1_Init();
  MX_USART3_UART_Init();
  MX_UART4_Init();
  /* USER CODE BEGIN 2 */
//   Hmc5883lReadStart(angleDataRxBuffer,ANGLE_DATA_BUFFER_SIZE);
//   DistanceRead(pDistanceData,DISTANCE_RECEIVE_BUFFER_SIZE);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  //ALL_Init();
  
  while (1)
  {

  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */
    int contData = 0;
      
//测量初始角度位置 调试通过
//    while(1)
//    {
//        
//        if(angleDataIsOk == 1)
//        {
//            angleDataIsOk = 0;
//            HAL_NVIC_EnableIRQ(USART2_IRQn);
//            Hmc5883lReadStart(angleDataRxBuffer,ANGLE_DATA_BUFFER_SIZE);

//            
//        }  
//    }        
      
      
////      
//    //测量初始距离 调试成功
//    while(1) 
//    {
//        if(distanceIsOk == 1)
//        {
//            distanceIsOk = 0;
//            HAL_NVIC_EnableIRQ(USART1_IRQn);
//            DistanceRead(pDistanceData,DISTANCE_RECEIVE_BUFFER_SIZE);
//        }      
//    }

      //countH,countV在上面初始化的
      for(countH = 0;countH < DATA_PACK_H_NUM;countH++)
      {
          for(countV = 0;countV < DATA_PACK_V_NUM;countV++)
          {
                //读取距离数据
                while(distanceIsOk == 0)
                {
                    HAL_NVIC_EnableIRQ(USART1_IRQn);
                    DistanceRead(pDistanceData,DISTANCE_RECEIVE_BUFFER_SIZE);
   
                }
                
                
                //读取角度数据
                while( distanceIsOk == 0x01 && angleDataIsOk == 0x00 )
                {
                    HAL_NVIC_EnableIRQ(USART2_IRQn);
                    Hmc5883lReadStart(angleDataRxBuffer,ANGLE_DATA_BUFFER_SIZE);
                }
                
                //数据读取成功，清标记等
                while(distanceIsOk == 0x01 && angleDataIsOk == 0x01)
                {   
        
                    //HAL_Delay(1000);
                    //HAL_UART_Transmit(&huart1, (uint8_t*)(&dataPack), 8,0x100);
                    HAL_UART_Transmit_DMA(&huart4,(uint8_t *)&dataPack,sizeof(dataPack));
                    //存储数据
                    dataAll[countH][countV] = dataPack;
                    memset((void*)(&dataPack.distanceM),0,sizeof(dataPack));
                   
                
                    //清理标志
                    distanceIsOk = 0 ;
                    angleDataIsOk = 0;
                
                    //垂直方向电机旋转
                
                    //
                    dirver_l298n_vstepmotor(directionV,1);//directionV = 0,逆时针
                
                    
        
                }  
            
          }
          
          directionV ^= 0x01;
          //水平方向电机旋转
          
          dirver_l298n_hstepmotor(directionH,1);
          
      }


//      for(contData = 0; contData < DATA_PACK_H_NUM;++contData)
//      {
//          //发送数据
//          HAL_UART_Transmit_DMA(&huart4,(uint8_t *)dataAll[contData],sizeof(dataAll[contData]));
//      }
      while(1);
      

  }
  /* USER CODE END 3 */

}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

    /**Configure the main internal regulator output voltage 
    */
  __HAL_RCC_PWR_CLK_ENABLE();

  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure the Systick interrupt time 
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/8000);

    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK_DIV8);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* USER CODE BEGIN 4 */

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if(huart->Instance == USART1)
    {
        
        if(distanceIsOk == 0 )
        {
            distanceIsOk = DistanceDataHandle(&dataPack); //将距离数据dataPack加入帧
            if(distanceIsOk == 1)
            {
                HAL_NVIC_DisableIRQ(USART1_IRQn);
//                DistanceRead(pDistanceData,DISTANCE_RECEIVE_BUFFER_SIZE);   
//                distanceIsOk = 0;
                memset((void *)pDistanceData,0,sizeof(pDistanceData));
                //HAL_UART_Transmit(huart, (uint8_t*)(&dataPack), 8,0x100);
                
            }
        }
        
        //DistanceRead(pDistanceData,DISTANCE_RECEIVE_BUFFER_SIZE);
        
        
    }
    if(huart->Instance == USART2)
    {
        
        if(angleDataIsOk == 0)
        {
            angleDataIsOk = Hmc5883lDataHandle(&dataPack);
            if(angleDataIsOk == 1)
            {
                //HAL_UART_Transmit(huart, (uint8_t*)(angleDataRxBuffer), sizeof(angleDataRxBuffer),0x100);
                HAL_NVIC_DisableIRQ(USART2_IRQn);
//                Hmc5883lReadStart(angleDataRxBuffer,ANGLE_DATA_BUFFER_SIZE);
//                angleDataIsOk = 0;
                memset((void *)angleDataRxBuffer,0,sizeof(angleDataRxBuffer));
            }
        }
        //Hmc5883lReadStart(angleDataRxBuffer,ANGLE_DATA_BUFFER_SIZE);
    }
    if(huart->Instance == USART3)
    {
        
    }
    
}

void ALL_Init(void)
{
    H_Init();
    V_Init();
    angleDataIsOk = 0;
    distanceIsOk = 0;
    
}
// 水平方向初始化
void H_Init(void)
{
     while(angleDataIsOk == 0)
     {
         HAL_NVIC_EnableIRQ(USART2_IRQn);
         Hmc5883lReadStart(angleDataRxBuffer,ANGLE_DATA_BUFFER_SIZE);
     }
     //读到正确的角度数据,顺时针方向调整
     while( ( ( (dataPack.angleY_H << 8) | dataPack.angleY_L) < initYAngleH ) && angleDataIsOk)
     {
         //旋转电机
         dirver_l298n_hstepmotor(0,1);//逆时针
         //继续读角度数据
         angleDataIsOk = 0;
         while(angleDataIsOk == 0)
        {
            HAL_NVIC_EnableIRQ(USART2_IRQn);
            Hmc5883lReadStart(angleDataRxBuffer,ANGLE_DATA_BUFFER_SIZE);
        }
     }
     //向逆时针方向调整
     while( ( ( (dataPack.angleY_H << 8) | dataPack.angleY_L) > initYAngleH ) && angleDataIsOk)
     {
         //旋转电机
         dirver_l298n_hstepmotor(1,1);//顺时针
         //继续读角度数据
         angleDataIsOk = 0;
         while(angleDataIsOk == 0)
        {
            HAL_NVIC_EnableIRQ(USART2_IRQn);
            Hmc5883lReadStart(angleDataRxBuffer,ANGLE_DATA_BUFFER_SIZE);
        }
     }
}
// 垂直方向初始化
void V_Init(void)
{
     while(angleDataIsOk == 0)
     {
         HAL_NVIC_EnableIRQ(USART2_IRQn);
         Hmc5883lReadStart(angleDataRxBuffer,ANGLE_DATA_BUFFER_SIZE);
     }
     //读到正确的角度数据,顺时针方向调整
     while( ( ( (dataPack.angleX_H << 8) | dataPack.angleX_L) < initYAngleH ) && angleDataIsOk)
     {
         //旋转电机
         dirver_l298n_vstepmotor(0,1);//逆时针转
         //继续读角度数据
         angleDataIsOk = 0;
         while(angleDataIsOk == 0)
        {
            HAL_NVIC_EnableIRQ(USART2_IRQn);
            Hmc5883lReadStart(angleDataRxBuffer,ANGLE_DATA_BUFFER_SIZE);
        }
     }
     //向逆时针方向调整
     while( ( ( (dataPack.angleX_H << 8) | dataPack.angleX_L) > initYAngleH ) && angleDataIsOk)
     {
         //旋转电机
         dirver_l298n_vstepmotor(1,1);//顺时针转
         //继续读角度数据
         angleDataIsOk = 0;
         while(angleDataIsOk == 0)
        {
            HAL_NVIC_EnableIRQ(USART2_IRQn);
            Hmc5883lReadStart(angleDataRxBuffer,ANGLE_DATA_BUFFER_SIZE);
        }
     }
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  file: The file name as string.
  * @param  line: The line in file as a number.
  * @retval None
  */
void _Error_Handler(char *file, int line)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  while(1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
