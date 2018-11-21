#ifndef __HMC5883L_H
#define __HMC5883L_H

#include "stm32f4xx_hal.h"
#include "datatype.h"
#define ANGLE_DATA_BUFFER_SIZE   55

typedef struct
{
    uint8_t angleOuptStart[4]; //开始输出数据
    uint8_t angleOuptStop[4];  //停止输出数据
}AngleCntlCmd;
   
extern const AngleCntlCmd  angleCmd;

extern uint8_t angleDataRxBuffer[ANGLE_DATA_BUFFER_SIZE];

extern UART_HandleTypeDef huart2;

/***********************************************************
*            ##### 帧格式 #####
* 起始字节：0xA7 0x7A
* 帧 类 型：0x70 角速度帧
*           0x71 加速度帧
*           0x72 姿态帧
*           0x73 地磁帧
* 帧 长 度：0x__  不包括起始字节和帧类型
* 校 验 和：0x__   异或的结果
* 帧 内 容：与帧类型有关  
* 姿 态 帧：
*          0xA7 0x7A 0x72 0x07 0x__
*          AngleX_L  AngleX_H
*          AngleY_L  AngleY_H
*          AngleZ_L  AngleZ_H
* 
* AngleX  = (int16_t)((AngleX_H << 8) | AngleX_L);
*
*
*
************************************************************/

uint8_t Hmc5883lReadStart(uint8_t *pData,uint16_t Size);
uint8_t Hmc5883lDataHandle(DATA_PACK *data);

#endif

