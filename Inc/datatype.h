#ifndef __DATATYPE_H
#define __DATATYPE_H

#include "stm32f4xx_hal.h"
#include "string.h"
#define DATA_PACK_H_NUM     120
#define DATA_PACK_V_NUM     90

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


 extern DATA_PACK dataAll[DATA_PACK_H_NUM][DATA_PACK_V_NUM]; //数据包

 extern uint32_t data_pack_cnt; 

 extern DATA_PACK dataPack;

 extern uint8_t distanceIsOk;

 extern uint8_t angleDataIsOk;
 
 extern uint8_t directionV;
 
 extern uint8_t directionH;

 extern uint8_t directionC; //激光器盖子

 extern uint8_t initXAngleH ;

 extern uint8_t initYAngleH ;

 extern uint8_t initZAngleH ;

 

#endif
