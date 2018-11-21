#ifndef __DS18B20_H
#define __DS18B20_H 
#include "sys.h"   
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//STM32F407VET6
//DS18B20驱动代码	   
//SLC
//
//创建日期:2018/10/7
//版本：V1.0
//版权所有，盗版必究。
//
//All rights reserved										  
//////////////////////////////////////////////////////////////////////////////////

//IO方向设置
#define DS18B20_IO_IN()  {GPIOG->MODER&=~(3<<(9*2));GPIOG->MODER|=0<<9*2;}	//PG9输入模式
#define DS18B20_IO_OUT() {GPIOG->MODER&=~(3<<(9*2));GPIOG->MODER|=1<<9*2;} 	//PG9输出模式
 


////IO操作函数											   
#define	DS18B20_DQ_OUT PGout(9) //数据端口	PG9
#define	DS18B20_DQ_IN  PGin(9)  //数据端口	PG9 
   	
uint8_t DS18B20_Init(void);			//初始化DS18B20
short DS18B20_Get_Temp(void);	//获取温度
void DS18B20_Start(void);		//开始温度转换
void DS18B20_Write_Byte(uint8_t dat);//写入一个字节
uint8_t DS18B20_Read_Byte(void);		//读出一个字节
uint8_t DS18B20_Read_Bit(void);		//读出一个位
uint8_t DS18B20_Check(void);			//检测是否存在DS18B20
void DS18B20_Rst(void);			//复位DS18B20    
#endif


/*
**********************HAL 库*************/
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

