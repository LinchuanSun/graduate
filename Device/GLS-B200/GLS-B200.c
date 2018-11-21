#include "GLS-B200.h"


uint8_t pDistanceData[DISTANCE_RECEIVE_BUFFER_SIZE] = {0};
/******************************************
*
*
*
*
*
*
*******************************************/

uint8_t DistanceRead(uint8_t *pData,uint16_t Size)
{
    HAL_UART_Receive_IT(&huart1, pData, Size);
    while(huart1.gState != HAL_UART_STATE_READY);
    return 0;
}
uint8_t DistanceDataHandle(DATA_PACK *data)
{
    
    int i;
    for(i = 0; i < DISTANCE_RECEIVE_BUFFER_SIZE - 3;++i)
    {
        if(pDistanceData[i] == 0xFF && pDistanceData[i+3] == 0xFF) //当中有一组正确数据
        {
            data->distanceM = pDistanceData[i+1];
            data->distance_CM = pDistanceData[i+2];
            //distanceIsOk = 1;
            break;
        }
        
    }
    if(i >= DISTANCE_RECEIVE_BUFFER_SIZE - 3) //没有正确数据
        {
            memset((void *)pDistanceData,0,sizeof(pDistanceData));
            //distanceIsOk  = 0;
            
        }
    
    return i < (DISTANCE_RECEIVE_BUFFER_SIZE - 3) ? 1 : 0;
}
    


