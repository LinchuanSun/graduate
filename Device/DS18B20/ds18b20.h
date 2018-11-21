#ifndef __DS18B20_H
#define __DS18B20_H 
#include "sys.h"   
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//STM32F407VET6
//DS18B20��������	   
//SLC
//
//��������:2018/10/7
//�汾��V1.0
//��Ȩ���У�����ؾ���
//
//All rights reserved										  
//////////////////////////////////////////////////////////////////////////////////

//IO��������
#define DS18B20_IO_IN()  {GPIOG->MODER&=~(3<<(9*2));GPIOG->MODER|=0<<9*2;}	//PG9����ģʽ
#define DS18B20_IO_OUT() {GPIOG->MODER&=~(3<<(9*2));GPIOG->MODER|=1<<9*2;} 	//PG9���ģʽ
 


////IO��������											   
#define	DS18B20_DQ_OUT PGout(9) //���ݶ˿�	PG9
#define	DS18B20_DQ_IN  PGin(9)  //���ݶ˿�	PG9 
   	
uint8_t DS18B20_Init(void);			//��ʼ��DS18B20
short DS18B20_Get_Temp(void);	//��ȡ�¶�
void DS18B20_Start(void);		//��ʼ�¶�ת��
void DS18B20_Write_Byte(uint8_t dat);//д��һ���ֽ�
uint8_t DS18B20_Read_Byte(void);		//����һ���ֽ�
uint8_t DS18B20_Read_Bit(void);		//����һ��λ
uint8_t DS18B20_Check(void);			//����Ƿ����DS18B20
void DS18B20_Rst(void);			//��λDS18B20    
#endif


/*
**********************HAL ��*************/
//#ifndef __ONEWIRE_DS18B20_H__
//#define        __ONEWIRE_DS18B20_H__
///* ????? ----------------------------------------------------------------*/
//#include "stm32f1xx_hal.h"

///* ???? ------------------------------------------------------------------*/
///* ??? -------------------------------------------------------------------*/
///***********************   DS18B20 ??????  **************************/
//#define DS18B20_Dout_GPIO_CLK_ENABLE()              __HAL_RCC_GPIOD_CLK_ENABLE()
//#define DS18B20_Dout_PORT                           GPIOD
//#define DS18B20_Dout_PIN                            GPIO_PIN_3

///***********************   DS18B20 ?????  ****************************/
//#define DS18B20_Dout_LOW()                          HAL_GPIO_WritePin(DS18B20_Dout_PORT,DS18B20_Dout_PIN,GPIO_PIN_RESET) 
//#define DS18B20_Dout_HIGH()                         HAL_GPIO_WritePin(DS18B20_Dout_PORT,DS18B20_Dout_PIN,GPIO_PIN_SET)
//#define DS18B20_Data_IN()                                  HAL_GPIO_ReadPin(DS18B20_Dout_PORT,DS18B20_Dout_PIN)

///* ???? ------------------------------------------------------------------*/
///* ???? ------------------------------------------------------------------*/
//uint8_t DS18B20_Init(void);
//void DS18B20_ReadId( uint8_t * ds18b20_id);
//float DS18B20_GetTemp_SkipRom(void);
//float DS18B20_GetTemp_MatchRom(uint8_t *ds18b20_id);

//#endif /* __ONEWIRE_DS18B20_H__ */
/******************* (C) COPYRIGHT 2015-2020 ????????? *****END OF FILE****/

