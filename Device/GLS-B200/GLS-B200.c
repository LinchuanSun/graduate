#include "GLS-B200.h"
#include "usart.h"

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
    uint16_t i = 0;
    
    while(HAL_UART_Receive_IT(&huart1, pData, Size) != HAL_OK)
    {
//        i++;
//        if(i>10000)
//        {
//            huart1.RxState = HAL_UART_STATE_READY;
//            MX_USART1_UART_Init();
//            //__HAL_UNLOCK(&huart1);
//            i = 0;
//        }
        
    }
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
    


