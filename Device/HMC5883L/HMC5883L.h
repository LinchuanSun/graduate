#ifndef __HMC5883L_H
#define __HMC5883L_H

#include "stm32f4xx_hal.h"
#include "datatype.h"
#define ANGLE_DATA_BUFFER_SIZE   55

typedef struct
{
    uint8_t angleOuptStart[4]; //��ʼ�������
    uint8_t angleOuptStop[4];  //ֹͣ�������
}AngleCntlCmd;
   
extern const AngleCntlCmd  angleCmd;

extern uint8_t angleDataRxBuffer[ANGLE_DATA_BUFFER_SIZE];

extern UART_HandleTypeDef huart2;

/***********************************************************
*            ##### ֡��ʽ #####
* ��ʼ�ֽڣ�0xA7 0x7A
* ֡ �� �ͣ�0x70 ���ٶ�֡
*           0x71 ���ٶ�֡
*           0x72 ��̬֡
*           0x73 �ش�֡
* ֡ �� �ȣ�0x__  ��������ʼ�ֽں�֡����
* У �� �ͣ�0x__   ���Ľ��
* ֡ �� �ݣ���֡�����й�  
* �� ̬ ֡��
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

