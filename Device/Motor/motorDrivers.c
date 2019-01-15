#include "motorDrivers.h"
#include "stm32f4xx_hal.h"
#include "main.h"
/*******************************************************************************
* �� �� ����driver_uln2003_stepmotor
* ��������: ����ָ������Ͳ�����������ULN2003+28�������
* ���������dirc--���ת��0-��ʱ�� 1-˳ʱ�� AD->A->AB->B->BC->C->CD->D
* �� �� ֵ��
* ���÷�����˳ʱ��ת10�������ǣ�driver_uln2003_stepmotor(1,10),��ʱ��ת��driver_uln2003_stepmotor(0,10);
********************************************************************************/
void driver_uln2003_stepmotor(uint8_t dirc,uint16_t step)
{
    //28BYJ-48��������Ĳ����Ϊ5.625/64,���ٱ�Ϊ1:64,��64������5.625��
    //һȦ��Ҫ360/5.625*64=4096������
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
* �� �� ����dirver_l298n_vstepmotor
* ��������: ����ָ������Ͳ�����������L298N+42�������
* ���������dirc--���ת��0-��ʱ�� 1-˳ʱ �������step��ֵΪ������1Ϊ1.2�ȣ����ٱ�Ϊ1:50 7.5*8/50=1.2��
* �� �� ֵ��
* ���÷�����
* ������� ��ɫ�� A+ ��ɫ�� A-  ��ɫ�� B+ ��ɫ�� B- �ֱ��OUT1-OUT4
********************************************************************************/
void dirver_l298n_vstepmotor(uint8_t dirc,uint16_t step)
{
    while(step--)
    {
        if(dirc == 1)//˳ʱ��  
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
        else//��ʱ��
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
* �� �� ����dirver_l298n_hstepmotor
* ��������: ����ָ������Ͳ�����������L298N+42���������7.5���ٱ�1:10�����ּ���34:85��step����1�ýǶ�7.5*8/10*34/85 = 2.4��
* ���������dirc--���ת��0-��ʱ�� 1-˳ʱ 
* �� �� ֵ��
* ���÷�����
* ������� ��ɫ�� A+ ��ɫ�� A-  ��ɫ�� B+ ��ɫ�� B- �ֱ��OUT1-OUT4
********************************************************************************/
void dirver_l298n_hstepmotor(uint8_t dirc,uint16_t step)
{
    while(step--)
    {
        if(dirc == 1)//˳ʱ��  
        {
            //A+ B- 1001 
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
        else//��ʱ��
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
