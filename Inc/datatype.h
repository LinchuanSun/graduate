#ifndef __DATATYPE_H
#define __DATATYPE_H

#include "stm32f4xx_hal.h"
#include "string.h"
#define DATA_PACK_NUM     (120*90)

typedef struct DATA
{
     uint8_t distanceM;
     uint8_t distance_CM;
     uint8_t angleX_L;
     uint8_t angleX_H;
     uint8_t angleY_L;
     uint8_t angleY_H;
     uint8_t angleZ_L;
     uint8_t angleZ_H;
    
}DATA_PACK;


 extern DATA_PACK dataAll[DATA_PACK_NUM];

 extern uint32_t data_pack_cnt;

 extern DATA_PACK dataPack;

 extern uint8_t distanceIsOk;

 extern uint8_t angleDataIsOk;

#endif
