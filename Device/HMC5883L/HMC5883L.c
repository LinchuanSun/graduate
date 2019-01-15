#include "HMC5883L.h"
#include "usart.h"
const AngleCntlCmd  angleCmd ={
                                {0xD6,0X6D,0x08,0x08},
                                {0xD6,0X6D,0x09,0x09}
                              };

uint8_t angleDataRxBuffer[ANGLE_DATA_BUFFER_SIZE] = {0};


uint8_t Hmc5883lReadStart(uint8_t *pData,uint16_t Size)
{
    uint16_t i =0;
    while(HAL_UART_Receive_IT(&huart2, pData, Size) != HAL_OK)
    {
//        i++;
//        if(i>10000)
//        {
//            huart2.RxState = HAL_UART_STATE_READY;
//            //MX_USART2_UART_Init();
//            __HAL_UNLOCK(&huart2);
//            i = 0;
//        }
        
    }
    return 0;
}
uint8_t Hmc5883lDataHandle(DATA_PACK *data)
{
    int i ;
    for(i = 0 ; i < ANGLE_DATA_BUFFER_SIZE - 10 ; ++i)
    {
        if(0xA7 == angleDataRxBuffer[i] && 0x7A == angleDataRxBuffer[i+1] && \
           0x72 == angleDataRxBuffer[i+2] && 0x07 == angleDataRxBuffer[i+3]) 
        {
            if(angleDataRxBuffer[i+4] == (angleDataRxBuffer[i+5] ^ angleDataRxBuffer[i+6] ^ \
                                          angleDataRxBuffer[i+7] ^ angleDataRxBuffer[i+8] ^ \
                                          angleDataRxBuffer[i+9] ^ angleDataRxBuffer[i+10]))
            {
                data->angleX_L = angleDataRxBuffer[i+5];
                data->angleX_H = angleDataRxBuffer[i+6];
                data->angleY_L = angleDataRxBuffer[i+7];
                data->angleY_H = angleDataRxBuffer[i+8];
                data->angleZ_L = angleDataRxBuffer[i+9];
                data->angleZ_H = angleDataRxBuffer[i+10];
                //angleDataIsOk = 1;
                break;
           
            }
        }
    }
    if(i >= (ANGLE_DATA_BUFFER_SIZE - 10))
    {
        memset((void *)angleDataRxBuffer,0,sizeof(angleDataRxBuffer));
    }
   
   
   
    return i < (ANGLE_DATA_BUFFER_SIZE - 10) ? 1 : 0;
}

