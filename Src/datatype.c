#include "datatype.h"

DATA_PACK dataPack = {0x0,0x0,0x0,0x0,0x0};

DATA_PACK dataAll[DATA_PACK_H_NUM][DATA_PACK_V_NUM] = {0}; 

uint32_t data_pack_cnt = 0; 

uint8_t distanceIsOk = 0;

uint8_t angleDataIsOk = 0;

uint8_t directionV = 0;
 
uint8_t directionH = 0;

uint8_t directionC = 0;

//A7 7A 72 07 03   08 04    B0 01    58 E6 
//                 xl xh    yl yh    zl zh
uint8_t initXAngleH = 0x04;

uint8_t initYAngleH = 0x01;

uint8_t initZAngleH = 0xE6;

