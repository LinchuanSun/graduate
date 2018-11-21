#include "motorDrivers.h"
#include "stm32f4xx_hal.h"
#include "main.h"
/*******************************************************************************
* 函 数 名：driver_uln2003_stepmotor
* 功能描述: 安照指定方向和步进角数驱动ULN2003+28步进电机
* 输入参数：dirc--电机转向，0-逆时针 1-顺时针 AD->A->AB->B->BC->C->CD->D
* 返 回 值：
* 调用方法：顺时针转10个步进角，driver_uln2003_stepmotor(1,10),逆时针转，driver_uln2003_stepmotor(0,10);
********************************************************************************/
void driver_uln2003_stepmotor(uint8_t dirc,uint16_t step)
{
    //28BYJ-48步进电机的步距角为5.625/64,减速比为1:64,即64个脉冲5.625度
    //一圈需要360/5.625*64=4096个脉冲
    int i ;
    for(i = 0; i < step ; ++i)
    { 
        if(dirc == 1)//DA->A->AB->B->BC->C->CD->D
        {   
            
            //A
            HAL_GPIO_WritePin(ULN2003_IN1_GPIO_Port,ULN2003_IN1_Pin,GPIO_PIN_SET);
            HAL_GPIO_WritePin(ULN2003_IN2_GPIO_Port,ULN2003_IN2_Pin,GPIO_PIN_RESET);
            HAL_GPIO_WritePin(ULN2003_IN3_GPIO_Port,ULN2003_IN3_Pin,GPIO_PIN_RESET);
            HAL_GPIO_WritePin(ULN2003_IN4_GPIO_Port,ULN2003_IN4_Pin,GPIO_PIN_RESET);
            HAL_Delay(STEPMOTOR_SPEED);
            
            //AB
            HAL_GPIO_WritePin(ULN2003_IN1_GPIO_Port,ULN2003_IN1_Pin,GPIO_PIN_SET);
            HAL_GPIO_WritePin(ULN2003_IN2_GPIO_Port,ULN2003_IN2_Pin,GPIO_PIN_SET);
            HAL_GPIO_WritePin(ULN2003_IN3_GPIO_Port,ULN2003_IN3_Pin,GPIO_PIN_RESET);
            HAL_GPIO_WritePin(ULN2003_IN4_GPIO_Port,ULN2003_IN4_Pin,GPIO_PIN_RESET);
            HAL_Delay(STEPMOTOR_SPEED);
            
            //B
            HAL_GPIO_WritePin(ULN2003_IN1_GPIO_Port,ULN2003_IN1_Pin,GPIO_PIN_RESET);
            HAL_GPIO_WritePin(ULN2003_IN2_GPIO_Port,ULN2003_IN2_Pin,GPIO_PIN_SET);
            HAL_GPIO_WritePin(ULN2003_IN3_GPIO_Port,ULN2003_IN3_Pin,GPIO_PIN_RESET);
            HAL_GPIO_WritePin(ULN2003_IN4_GPIO_Port,ULN2003_IN4_Pin,GPIO_PIN_RESET);
            HAL_Delay(STEPMOTOR_SPEED);
            
            //BC
            HAL_GPIO_WritePin(ULN2003_IN1_GPIO_Port,ULN2003_IN1_Pin,GPIO_PIN_RESET);
            HAL_GPIO_WritePin(ULN2003_IN2_GPIO_Port,ULN2003_IN2_Pin,GPIO_PIN_SET);
            HAL_GPIO_WritePin(ULN2003_IN3_GPIO_Port,ULN2003_IN3_Pin,GPIO_PIN_SET);
            HAL_GPIO_WritePin(ULN2003_IN4_GPIO_Port,ULN2003_IN4_Pin,GPIO_PIN_RESET);
            HAL_Delay(STEPMOTOR_SPEED);
            
            //C
            HAL_GPIO_WritePin(ULN2003_IN1_GPIO_Port,ULN2003_IN1_Pin,GPIO_PIN_RESET);
            HAL_GPIO_WritePin(ULN2003_IN2_GPIO_Port,ULN2003_IN2_Pin,GPIO_PIN_RESET);
            HAL_GPIO_WritePin(ULN2003_IN3_GPIO_Port,ULN2003_IN3_Pin,GPIO_PIN_SET);
            HAL_GPIO_WritePin(ULN2003_IN4_GPIO_Port,ULN2003_IN4_Pin,GPIO_PIN_RESET);
            HAL_Delay(STEPMOTOR_SPEED);
            
            //CD
            HAL_GPIO_WritePin(ULN2003_IN1_GPIO_Port,ULN2003_IN1_Pin,GPIO_PIN_RESET);
            HAL_GPIO_WritePin(ULN2003_IN2_GPIO_Port,ULN2003_IN2_Pin,GPIO_PIN_RESET);
            HAL_GPIO_WritePin(ULN2003_IN3_GPIO_Port,ULN2003_IN3_Pin,GPIO_PIN_SET);
            HAL_GPIO_WritePin(ULN2003_IN4_GPIO_Port,ULN2003_IN4_Pin,GPIO_PIN_SET);
            HAL_Delay(STEPMOTOR_SPEED);
            
            //D
            HAL_GPIO_WritePin(ULN2003_IN1_GPIO_Port,ULN2003_IN1_Pin,GPIO_PIN_RESET);
            HAL_GPIO_WritePin(ULN2003_IN2_GPIO_Port,ULN2003_IN2_Pin,GPIO_PIN_RESET);
            HAL_GPIO_WritePin(ULN2003_IN3_GPIO_Port,ULN2003_IN3_Pin,GPIO_PIN_RESET);
            HAL_GPIO_WritePin(ULN2003_IN4_GPIO_Port,ULN2003_IN4_Pin,GPIO_PIN_SET);
            HAL_Delay(STEPMOTOR_SPEED);
            
            //DA
            HAL_GPIO_WritePin(ULN2003_IN1_GPIO_Port,ULN2003_IN1_Pin,GPIO_PIN_SET);
            HAL_GPIO_WritePin(ULN2003_IN2_GPIO_Port,ULN2003_IN2_Pin,GPIO_PIN_RESET);
            HAL_GPIO_WritePin(ULN2003_IN3_GPIO_Port,ULN2003_IN3_Pin,GPIO_PIN_RESET);
            HAL_GPIO_WritePin(ULN2003_IN4_GPIO_Port,ULN2003_IN4_Pin,GPIO_PIN_SET);
            HAL_Delay(STEPMOTOR_SPEED);
        }
        else//D->DC->C->CB->B->BA->A->AD
        {
             //AD
            HAL_GPIO_WritePin(ULN2003_IN1_GPIO_Port,ULN2003_IN1_Pin,GPIO_PIN_SET);
            HAL_GPIO_WritePin(ULN2003_IN2_GPIO_Port,ULN2003_IN2_Pin,GPIO_PIN_RESET);
            HAL_GPIO_WritePin(ULN2003_IN3_GPIO_Port,ULN2003_IN3_Pin,GPIO_PIN_RESET);
            HAL_GPIO_WritePin(ULN2003_IN4_GPIO_Port,ULN2003_IN4_Pin,GPIO_PIN_SET);
            
            //D
            HAL_GPIO_WritePin(ULN2003_IN1_GPIO_Port,ULN2003_IN1_Pin,GPIO_PIN_RESET);
            HAL_GPIO_WritePin(ULN2003_IN2_GPIO_Port,ULN2003_IN2_Pin,GPIO_PIN_RESET);
            HAL_GPIO_WritePin(ULN2003_IN3_GPIO_Port,ULN2003_IN3_Pin,GPIO_PIN_RESET);
            HAL_GPIO_WritePin(ULN2003_IN4_GPIO_Port,ULN2003_IN4_Pin,GPIO_PIN_SET);
            HAL_Delay(STEPMOTOR_SPEED);
    
            //DC
            HAL_GPIO_WritePin(ULN2003_IN1_GPIO_Port,ULN2003_IN1_Pin,GPIO_PIN_RESET);
            HAL_GPIO_WritePin(ULN2003_IN2_GPIO_Port,ULN2003_IN2_Pin,GPIO_PIN_RESET);
            HAL_GPIO_WritePin(ULN2003_IN3_GPIO_Port,ULN2003_IN3_Pin,GPIO_PIN_SET);
            HAL_GPIO_WritePin(ULN2003_IN4_GPIO_Port,ULN2003_IN4_Pin,GPIO_PIN_SET);
    
            //C
            HAL_GPIO_WritePin(ULN2003_IN1_GPIO_Port,ULN2003_IN1_Pin,GPIO_PIN_RESET);
            HAL_GPIO_WritePin(ULN2003_IN1_GPIO_Port,ULN2003_IN2_Pin,GPIO_PIN_RESET);
            HAL_GPIO_WritePin(ULN2003_IN1_GPIO_Port,ULN2003_IN3_Pin,GPIO_PIN_SET);
            HAL_GPIO_WritePin(ULN2003_IN1_GPIO_Port,ULN2003_IN4_Pin,GPIO_PIN_RESET);
            HAL_Delay(STEPMOTOR_SPEED);
    
            //CB
            HAL_GPIO_WritePin(ULN2003_IN1_GPIO_Port,ULN2003_IN1_Pin,GPIO_PIN_RESET);
            HAL_GPIO_WritePin(ULN2003_IN2_GPIO_Port,ULN2003_IN2_Pin,GPIO_PIN_SET);
            HAL_GPIO_WritePin(ULN2003_IN3_GPIO_Port,ULN2003_IN3_Pin,GPIO_PIN_SET);
            HAL_GPIO_WritePin(ULN2003_IN4_GPIO_Port,ULN2003_IN4_Pin,GPIO_PIN_RESET);
    
            //B
            HAL_GPIO_WritePin(ULN2003_IN1_GPIO_Port,ULN2003_IN1_Pin,GPIO_PIN_RESET);
            HAL_GPIO_WritePin(ULN2003_IN1_GPIO_Port,ULN2003_IN2_Pin,GPIO_PIN_SET);
            HAL_GPIO_WritePin(ULN2003_IN1_GPIO_Port,ULN2003_IN3_Pin,GPIO_PIN_RESET);
            HAL_GPIO_WritePin(ULN2003_IN1_GPIO_Port,ULN2003_IN4_Pin,GPIO_PIN_RESET);
            HAL_Delay(STEPMOTOR_SPEED);
    
            //BA
            HAL_GPIO_WritePin(ULN2003_IN1_GPIO_Port,ULN2003_IN1_Pin,GPIO_PIN_SET);
            HAL_GPIO_WritePin(ULN2003_IN2_GPIO_Port,ULN2003_IN2_Pin,GPIO_PIN_SET);
            HAL_GPIO_WritePin(ULN2003_IN3_GPIO_Port,ULN2003_IN3_Pin,GPIO_PIN_RESET);
            HAL_GPIO_WritePin(ULN2003_IN4_GPIO_Port,ULN2003_IN4_Pin,GPIO_PIN_RESET);
    
            //A
            HAL_GPIO_WritePin(ULN2003_IN1_GPIO_Port,ULN2003_IN1_Pin,GPIO_PIN_SET);
            HAL_GPIO_WritePin(ULN2003_IN1_GPIO_Port,ULN2003_IN2_Pin,GPIO_PIN_RESET);
            HAL_GPIO_WritePin(ULN2003_IN1_GPIO_Port,ULN2003_IN3_Pin,GPIO_PIN_RESET);
            HAL_GPIO_WritePin(ULN2003_IN1_GPIO_Port,ULN2003_IN4_Pin,GPIO_PIN_RESET);
            HAL_Delay(STEPMOTOR_SPEED);
    
           
            
        }
    }
    HAL_GPIO_WritePin(ULN2003_IN1_GPIO_Port,ULN2003_IN1_Pin|ULN2003_IN2_Pin|ULN2003_IN3_Pin|ULN2003_IN4_Pin,GPIO_PIN_RESET);
}

/*******************************************************************************
* 函 数 名：dirver_l298n_vstepmotor
* 功能描述: 安照指定方向和步进角数驱动L298N+42步进电机
* 输入参数：dirc--电机转向，0-逆时针 1-顺时 
* 返 回 值：
* 调用方法：
* 步进电机 红色线 A+ 棕色线 A-  黄色线 B+ 绿色线 B- 分别接OUT1-OUT4
********************************************************************************/
void dirver_l298n_vstepmotor(uint8_t dirc,uint16_t step)
{
    while(step--)
    {
        if(dirc == 1)//顺时针  
        {
            //A+ B- 1001
            HAL_GPIO_WritePin(V_INPT1_GPIO_Port,V_INPT1_Pin,GPIO_PIN_SET);
            HAL_GPIO_WritePin(V_INPT2_GPIO_Port,V_INPT2_Pin,GPIO_PIN_RESET);
            HAL_GPIO_WritePin(V_INPT3_GPIO_Port,V_INPT3_Pin,GPIO_PIN_RESET);
            HAL_GPIO_WritePin(V_INPT4_GPIO_Port,V_INPT4_Pin,GPIO_PIN_SET);
            HAL_Delay(STEPMOTOR_SPEED_V);
            
            //B-  0001
            HAL_GPIO_WritePin(V_INPT1_GPIO_Port,V_INPT1_Pin,GPIO_PIN_RESET);
            HAL_GPIO_WritePin(V_INPT2_GPIO_Port,V_INPT2_Pin,GPIO_PIN_RESET);
            HAL_GPIO_WritePin(V_INPT3_GPIO_Port,V_INPT3_Pin,GPIO_PIN_RESET);
            HAL_GPIO_WritePin(V_INPT4_GPIO_Port,V_INPT4_Pin,GPIO_PIN_SET);
            HAL_Delay(STEPMOTOR_SPEED_V);
            
            //A-B-0101
            HAL_GPIO_WritePin(V_INPT1_GPIO_Port,V_INPT1_Pin,GPIO_PIN_RESET);
            HAL_GPIO_WritePin(V_INPT2_GPIO_Port,V_INPT2_Pin,GPIO_PIN_SET);
            HAL_GPIO_WritePin(V_INPT3_GPIO_Port,V_INPT3_Pin,GPIO_PIN_RESET);
            HAL_GPIO_WritePin(V_INPT4_GPIO_Port,V_INPT4_Pin,GPIO_PIN_SET);
            HAL_Delay(STEPMOTOR_SPEED_V);
            
            //A-   0100
            HAL_GPIO_WritePin(V_INPT1_GPIO_Port,V_INPT1_Pin,GPIO_PIN_RESET);
            HAL_GPIO_WritePin(V_INPT2_GPIO_Port,V_INPT2_Pin,GPIO_PIN_SET);
            HAL_GPIO_WritePin(V_INPT3_GPIO_Port,V_INPT3_Pin,GPIO_PIN_RESET);
            HAL_GPIO_WritePin(V_INPT4_GPIO_Port,V_INPT4_Pin,GPIO_PIN_RESET);
            HAL_Delay(STEPMOTOR_SPEED_V);
            
            //A-B+   0110
            HAL_GPIO_WritePin(V_INPT1_GPIO_Port,V_INPT1_Pin,GPIO_PIN_RESET);
            HAL_GPIO_WritePin(V_INPT2_GPIO_Port,V_INPT2_Pin,GPIO_PIN_SET);
            HAL_GPIO_WritePin(V_INPT3_GPIO_Port,V_INPT3_Pin,GPIO_PIN_RESET);
            HAL_GPIO_WritePin(V_INPT4_GPIO_Port,V_INPT4_Pin,GPIO_PIN_SET);
            HAL_Delay(STEPMOTOR_SPEED_V);
            
            //B+   0010
            HAL_GPIO_WritePin(V_INPT1_GPIO_Port,V_INPT1_Pin,GPIO_PIN_RESET);
            HAL_GPIO_WritePin(V_INPT2_GPIO_Port,V_INPT2_Pin,GPIO_PIN_RESET);
            HAL_GPIO_WritePin(V_INPT3_GPIO_Port,V_INPT3_Pin,GPIO_PIN_SET);
            HAL_GPIO_WritePin(V_INPT4_GPIO_Port,V_INPT4_Pin,GPIO_PIN_RESET);
            HAL_Delay(STEPMOTOR_SPEED_V);
            
            //A+B+ 1010
            HAL_GPIO_WritePin(V_INPT1_GPIO_Port,V_INPT1_Pin,GPIO_PIN_SET);
            HAL_GPIO_WritePin(V_INPT2_GPIO_Port,V_INPT2_Pin,GPIO_PIN_RESET);
            HAL_GPIO_WritePin(V_INPT3_GPIO_Port,V_INPT3_Pin,GPIO_PIN_SET);
            HAL_GPIO_WritePin(V_INPT4_GPIO_Port,V_INPT4_Pin,GPIO_PIN_RESET);
            HAL_Delay(STEPMOTOR_SPEED_V);
            
            //A+  1000
            HAL_GPIO_WritePin(V_INPT1_GPIO_Port,V_INPT1_Pin,GPIO_PIN_SET);
            HAL_GPIO_WritePin(V_INPT2_GPIO_Port,V_INPT2_Pin,GPIO_PIN_RESET);
            HAL_GPIO_WritePin(V_INPT3_GPIO_Port,V_INPT3_Pin,GPIO_PIN_RESET);
            HAL_GPIO_WritePin(V_INPT4_GPIO_Port,V_INPT4_Pin,GPIO_PIN_RESET);
            HAL_Delay(STEPMOTOR_SPEED_V);
        }
        else//逆时针
        {
            //A+  1000
            HAL_GPIO_WritePin(V_INPT1_GPIO_Port,V_INPT1_Pin,GPIO_PIN_SET);
            HAL_GPIO_WritePin(V_INPT2_GPIO_Port,V_INPT2_Pin,GPIO_PIN_RESET);
            HAL_GPIO_WritePin(V_INPT3_GPIO_Port,V_INPT3_Pin,GPIO_PIN_RESET);
            HAL_GPIO_WritePin(V_INPT4_GPIO_Port,V_INPT4_Pin,GPIO_PIN_RESET);
            HAL_Delay(STEPMOTOR_SPEED_V);
            
            //A+B+ 1010
            HAL_GPIO_WritePin(V_INPT1_GPIO_Port,V_INPT1_Pin,GPIO_PIN_SET);
            HAL_GPIO_WritePin(V_INPT2_GPIO_Port,V_INPT2_Pin,GPIO_PIN_RESET);
            HAL_GPIO_WritePin(V_INPT3_GPIO_Port,V_INPT3_Pin,GPIO_PIN_SET);
            HAL_GPIO_WritePin(V_INPT4_GPIO_Port,V_INPT4_Pin,GPIO_PIN_RESET);
            HAL_Delay(STEPMOTOR_SPEED_V);
            
            //B+   0010
            HAL_GPIO_WritePin(V_INPT1_GPIO_Port,V_INPT1_Pin,GPIO_PIN_RESET);
            HAL_GPIO_WritePin(V_INPT2_GPIO_Port,V_INPT2_Pin,GPIO_PIN_RESET);
            HAL_GPIO_WritePin(V_INPT3_GPIO_Port,V_INPT3_Pin,GPIO_PIN_SET);
            HAL_GPIO_WritePin(V_INPT4_GPIO_Port,V_INPT4_Pin,GPIO_PIN_RESET);
            HAL_Delay(STEPMOTOR_SPEED_V);
            
            //A-B+   0110
            HAL_GPIO_WritePin(V_INPT1_GPIO_Port,V_INPT1_Pin,GPIO_PIN_RESET);
            HAL_GPIO_WritePin(V_INPT2_GPIO_Port,V_INPT2_Pin,GPIO_PIN_SET);
            HAL_GPIO_WritePin(V_INPT3_GPIO_Port,V_INPT3_Pin,GPIO_PIN_RESET);
            HAL_GPIO_WritePin(V_INPT4_GPIO_Port,V_INPT4_Pin,GPIO_PIN_SET);
            HAL_Delay(STEPMOTOR_SPEED_V);
            
            //A-   0100
            HAL_GPIO_WritePin(V_INPT1_GPIO_Port,V_INPT1_Pin,GPIO_PIN_RESET);
            HAL_GPIO_WritePin(V_INPT2_GPIO_Port,V_INPT2_Pin,GPIO_PIN_SET);
            HAL_GPIO_WritePin(V_INPT3_GPIO_Port,V_INPT3_Pin,GPIO_PIN_RESET);
            HAL_GPIO_WritePin(V_INPT4_GPIO_Port,V_INPT4_Pin,GPIO_PIN_RESET);
            HAL_Delay(STEPMOTOR_SPEED_V);
            
            //A-B-0101
            HAL_GPIO_WritePin(V_INPT1_GPIO_Port,V_INPT1_Pin,GPIO_PIN_RESET);
            HAL_GPIO_WritePin(V_INPT2_GPIO_Port,V_INPT2_Pin,GPIO_PIN_SET);
            HAL_GPIO_WritePin(V_INPT3_GPIO_Port,V_INPT3_Pin,GPIO_PIN_RESET);
            HAL_GPIO_WritePin(V_INPT4_GPIO_Port,V_INPT4_Pin,GPIO_PIN_SET);
            HAL_Delay(STEPMOTOR_SPEED_V);
            
            //B-  0001
            HAL_GPIO_WritePin(V_INPT1_GPIO_Port,V_INPT1_Pin,GPIO_PIN_RESET);
            HAL_GPIO_WritePin(V_INPT2_GPIO_Port,V_INPT2_Pin,GPIO_PIN_RESET);
            HAL_GPIO_WritePin(V_INPT3_GPIO_Port,V_INPT3_Pin,GPIO_PIN_RESET);
            HAL_GPIO_WritePin(V_INPT4_GPIO_Port,V_INPT4_Pin,GPIO_PIN_SET);
            HAL_Delay(STEPMOTOR_SPEED_V);
            
            //A+ B- 1001
            HAL_GPIO_WritePin(V_INPT1_GPIO_Port,V_INPT1_Pin,GPIO_PIN_SET);
            HAL_GPIO_WritePin(V_INPT2_GPIO_Port,V_INPT2_Pin,GPIO_PIN_RESET);
            HAL_GPIO_WritePin(V_INPT3_GPIO_Port,V_INPT3_Pin,GPIO_PIN_RESET);
            HAL_GPIO_WritePin(V_INPT4_GPIO_Port,V_INPT4_Pin,GPIO_PIN_SET);
            HAL_Delay(STEPMOTOR_SPEED_V);
           
        }
    }
    HAL_GPIO_WritePin(V_INPT1_GPIO_Port,V_INPT1_Pin|V_INPT2_Pin|V_INPT3_Pin|V_INPT4_Pin,GPIO_PIN_RESET);
}
/*******************************************************************************
* 函 数 名：dirver_l298n_hstepmotor
* 功能描述: 安照指定方向和步进角数驱动L298N+42步进电机
* 输入参数：dirc--电机转向，0-逆时针 1-顺时 
* 返 回 值：
* 调用方法：
* 步进电机 红色线 A+ 棕色线 A-  黄色线 B+ 绿色线 B- 分别接OUT1-OUT4
********************************************************************************/
void dirver_l298n_hstepmotor(uint8_t dirc,uint16_t step)
{
    while(step--)
    {
        if(dirc == 1)//顺时针  
        {
            //A+ B- 1001
            HAL_GPIO_WritePin(H_INPT1_GPIO_Port,H_INPT1_Pin,GPIO_PIN_SET);
            HAL_GPIO_WritePin(H_INPT2_GPIO_Port,H_INPT2_Pin,GPIO_PIN_RESET);
            HAL_GPIO_WritePin(H_INPT3_GPIO_Port,H_INPT3_Pin,GPIO_PIN_RESET);
            HAL_GPIO_WritePin(H_INPT4_GPIO_Port,H_INPT4_Pin,GPIO_PIN_SET);
            HAL_Delay(STEPMOTOR_SPEED_H);
            
            //B-  0001
            HAL_GPIO_WritePin(H_INPT1_GPIO_Port,H_INPT1_Pin,GPIO_PIN_RESET);
            HAL_GPIO_WritePin(H_INPT2_GPIO_Port,H_INPT2_Pin,GPIO_PIN_RESET);
            HAL_GPIO_WritePin(H_INPT3_GPIO_Port,H_INPT3_Pin,GPIO_PIN_RESET);
            HAL_GPIO_WritePin(H_INPT4_GPIO_Port,H_INPT4_Pin,GPIO_PIN_SET);
            HAL_Delay(STEPMOTOR_SPEED_H);
            
            //A-B-0101
            HAL_GPIO_WritePin(H_INPT1_GPIO_Port,H_INPT1_Pin,GPIO_PIN_RESET);
            HAL_GPIO_WritePin(H_INPT2_GPIO_Port,H_INPT2_Pin,GPIO_PIN_SET);
            HAL_GPIO_WritePin(H_INPT3_GPIO_Port,H_INPT3_Pin,GPIO_PIN_RESET);
            HAL_GPIO_WritePin(H_INPT4_GPIO_Port,H_INPT4_Pin,GPIO_PIN_SET);
            HAL_Delay(STEPMOTOR_SPEED_H);
            
            //A-   0100
            HAL_GPIO_WritePin(H_INPT1_GPIO_Port,H_INPT1_Pin,GPIO_PIN_RESET);
            HAL_GPIO_WritePin(H_INPT2_GPIO_Port,H_INPT2_Pin,GPIO_PIN_SET);
            HAL_GPIO_WritePin(H_INPT3_GPIO_Port,H_INPT3_Pin,GPIO_PIN_RESET);
            HAL_GPIO_WritePin(H_INPT4_GPIO_Port,H_INPT4_Pin,GPIO_PIN_RESET);
            HAL_Delay(STEPMOTOR_SPEED_H);
            
            //A-B+   0110
            HAL_GPIO_WritePin(H_INPT1_GPIO_Port,H_INPT1_Pin,GPIO_PIN_RESET);
            HAL_GPIO_WritePin(H_INPT2_GPIO_Port,H_INPT2_Pin,GPIO_PIN_SET);
            HAL_GPIO_WritePin(H_INPT3_GPIO_Port,H_INPT3_Pin,GPIO_PIN_RESET);
            HAL_GPIO_WritePin(H_INPT4_GPIO_Port,H_INPT4_Pin,GPIO_PIN_SET);
            HAL_Delay(STEPMOTOR_SPEED_H);
            
            //B+   0010
            HAL_GPIO_WritePin(H_INPT1_GPIO_Port,H_INPT1_Pin,GPIO_PIN_RESET);
            HAL_GPIO_WritePin(H_INPT2_GPIO_Port,H_INPT2_Pin,GPIO_PIN_RESET);
            HAL_GPIO_WritePin(H_INPT3_GPIO_Port,H_INPT3_Pin,GPIO_PIN_SET);
            HAL_GPIO_WritePin(H_INPT4_GPIO_Port,H_INPT4_Pin,GPIO_PIN_RESET);
            HAL_Delay(STEPMOTOR_SPEED_H);
            
            //A+B+ 1010
            HAL_GPIO_WritePin(H_INPT1_GPIO_Port,H_INPT1_Pin,GPIO_PIN_SET);
            HAL_GPIO_WritePin(H_INPT2_GPIO_Port,H_INPT2_Pin,GPIO_PIN_RESET);
            HAL_GPIO_WritePin(H_INPT3_GPIO_Port,H_INPT3_Pin,GPIO_PIN_SET);
            HAL_GPIO_WritePin(H_INPT4_GPIO_Port,H_INPT4_Pin,GPIO_PIN_RESET);
            HAL_Delay(STEPMOTOR_SPEED_H);
            
            //A+  1000
            HAL_GPIO_WritePin(H_INPT1_GPIO_Port,H_INPT1_Pin,GPIO_PIN_SET);
            HAL_GPIO_WritePin(H_INPT2_GPIO_Port,H_INPT2_Pin,GPIO_PIN_RESET);
            HAL_GPIO_WritePin(H_INPT3_GPIO_Port,H_INPT3_Pin,GPIO_PIN_RESET);
            HAL_GPIO_WritePin(H_INPT4_GPIO_Port,H_INPT4_Pin,GPIO_PIN_RESET);
            HAL_Delay(STEPMOTOR_SPEED_H);
        }
        else//逆时针
        {
            //A+  1000
            HAL_GPIO_WritePin(H_INPT1_GPIO_Port,H_INPT1_Pin,GPIO_PIN_SET);
            HAL_GPIO_WritePin(H_INPT2_GPIO_Port,H_INPT2_Pin,GPIO_PIN_RESET);
            HAL_GPIO_WritePin(H_INPT3_GPIO_Port,H_INPT3_Pin,GPIO_PIN_RESET);
            HAL_GPIO_WritePin(H_INPT4_GPIO_Port,H_INPT4_Pin,GPIO_PIN_RESET);
            HAL_Delay(STEPMOTOR_SPEED_H);
            
            //A+B+ 1010
            HAL_GPIO_WritePin(H_INPT1_GPIO_Port,H_INPT1_Pin,GPIO_PIN_SET);
            HAL_GPIO_WritePin(H_INPT2_GPIO_Port,H_INPT2_Pin,GPIO_PIN_RESET);
            HAL_GPIO_WritePin(H_INPT3_GPIO_Port,H_INPT3_Pin,GPIO_PIN_SET);
            HAL_GPIO_WritePin(H_INPT4_GPIO_Port,H_INPT4_Pin,GPIO_PIN_RESET);
            HAL_Delay(STEPMOTOR_SPEED_H);
            
            //B+   0010
            HAL_GPIO_WritePin(H_INPT1_GPIO_Port,H_INPT1_Pin,GPIO_PIN_RESET);
            HAL_GPIO_WritePin(H_INPT2_GPIO_Port,H_INPT2_Pin,GPIO_PIN_RESET);
            HAL_GPIO_WritePin(H_INPT3_GPIO_Port,H_INPT3_Pin,GPIO_PIN_SET);
            HAL_GPIO_WritePin(H_INPT4_GPIO_Port,H_INPT4_Pin,GPIO_PIN_RESET);
            HAL_Delay(STEPMOTOR_SPEED_H);
            
            //A-B+   0110
            HAL_GPIO_WritePin(H_INPT1_GPIO_Port,H_INPT1_Pin,GPIO_PIN_RESET);
            HAL_GPIO_WritePin(H_INPT2_GPIO_Port,H_INPT2_Pin,GPIO_PIN_SET);
            HAL_GPIO_WritePin(H_INPT3_GPIO_Port,H_INPT3_Pin,GPIO_PIN_RESET);
            HAL_GPIO_WritePin(H_INPT4_GPIO_Port,H_INPT4_Pin,GPIO_PIN_SET);
            HAL_Delay(STEPMOTOR_SPEED_H);
            
            //A-   0100
            HAL_GPIO_WritePin(H_INPT1_GPIO_Port,H_INPT1_Pin,GPIO_PIN_RESET);
            HAL_GPIO_WritePin(H_INPT2_GPIO_Port,H_INPT2_Pin,GPIO_PIN_SET);
            HAL_GPIO_WritePin(H_INPT3_GPIO_Port,H_INPT3_Pin,GPIO_PIN_RESET);
            HAL_GPIO_WritePin(H_INPT4_GPIO_Port,H_INPT4_Pin,GPIO_PIN_RESET);
            HAL_Delay(STEPMOTOR_SPEED_H);
            
            //A-B-0101
            HAL_GPIO_WritePin(H_INPT1_GPIO_Port,H_INPT1_Pin,GPIO_PIN_RESET);
            HAL_GPIO_WritePin(H_INPT2_GPIO_Port,H_INPT2_Pin,GPIO_PIN_SET);
            HAL_GPIO_WritePin(H_INPT3_GPIO_Port,H_INPT3_Pin,GPIO_PIN_RESET);
            HAL_GPIO_WritePin(H_INPT4_GPIO_Port,H_INPT4_Pin,GPIO_PIN_SET);
            HAL_Delay(STEPMOTOR_SPEED_H);
            
            //B-  0001
            HAL_GPIO_WritePin(H_INPT1_GPIO_Port,H_INPT1_Pin,GPIO_PIN_RESET);
            HAL_GPIO_WritePin(H_INPT2_GPIO_Port,H_INPT2_Pin,GPIO_PIN_RESET);
            HAL_GPIO_WritePin(H_INPT3_GPIO_Port,H_INPT3_Pin,GPIO_PIN_RESET);
            HAL_GPIO_WritePin(H_INPT4_GPIO_Port,H_INPT4_Pin,GPIO_PIN_SET);
            HAL_Delay(STEPMOTOR_SPEED_H);
            
            //A+ B- 1001
            HAL_GPIO_WritePin(H_INPT1_GPIO_Port,H_INPT1_Pin,GPIO_PIN_SET);
            HAL_GPIO_WritePin(H_INPT2_GPIO_Port,H_INPT2_Pin,GPIO_PIN_RESET);
            HAL_GPIO_WritePin(H_INPT3_GPIO_Port,H_INPT3_Pin,GPIO_PIN_RESET);
            HAL_GPIO_WritePin(H_INPT4_GPIO_Port,H_INPT4_Pin,GPIO_PIN_SET);
            HAL_Delay(STEPMOTOR_SPEED_H);
           
        }
    }
    HAL_GPIO_WritePin(H_INPT1_GPIO_Port,H_INPT1_Pin|H_INPT2_Pin|H_INPT3_Pin|H_INPT4_Pin,GPIO_PIN_RESET);
    
}
