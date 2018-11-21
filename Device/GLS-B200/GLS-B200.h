#ifndef __GLS_B200_H
#define __GLS_B200_H

//#include "usart.h"
#include "datatype.h"


#define DISTANCE_RECEIVE_BUFFER_SIZE   12
extern UART_HandleTypeDef huart1;
extern uint8_t pDistanceData[DISTANCE_RECEIVE_BUFFER_SIZE];
/******************************************
*
*
*
*
*
*
*******************************************/

uint8_t DistanceRead(uint8_t *pData,uint16_t Size);
uint8_t DistanceDataHandle(DATA_PACK *data);




#endif
