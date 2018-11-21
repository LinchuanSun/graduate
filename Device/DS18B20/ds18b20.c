#include "ds18b20.h"
#include "delay.h"	
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//STM32F407������
//DS18B20��������	   
//
//
//
//�汾��V1.0
//��Ȩ���У�����ؾ���
//
//All rights reserved										  
//////////////////////////////////////////////////////////////////////////////////
  

//��λDS18B20
void DS18B20_Rst(void)	   
{                 
    DS18B20_IO_OUT(); //SET PG11 OUTPUT
    DS18B20_DQ_OUT=0; //����DQ
    delay_us(750);    //����750us
    DS18B20_DQ_OUT=1; //DQ=1 
	delay_us(15);     //15US
}
//�ȴ�DS18B20�Ļ�Ӧ
//����1:δ��⵽DS18B20�Ĵ���
//����0:����
uint8_t DS18B20_Check(void) 	   
{   
	uint8_t retry=0;
	DS18B20_IO_IN();//SET PG11 INPUT	 
    while (DS18B20_DQ_IN&&retry<200)
	{
		retry++;
		delay_us(1);
	};	 
	if(retry>=200)return 1;
	else retry=0;
    while (!DS18B20_DQ_IN&&retry<240)
	{
		retry++;
		delay_us(1);
	};
	if(retry>=240)return 1;	    
	return 0;
}
//��DS18B20��ȡһ��λ
//����ֵ��1/0
uint8_t DS18B20_Read_Bit(void) 			 // read one bit
{
  uint8_t data;
	DS18B20_IO_OUT();//SET PG11 OUTPUT
  DS18B20_DQ_OUT=0; 
	delay_us(2);
  DS18B20_DQ_OUT=1; 
	DS18B20_IO_IN();//SET PG11 INPUT
	delay_us(12);
	if(DS18B20_DQ_IN)data=1;
  else data=0;	 
  delay_us(50);           
  return data;
}
//��DS18B20��ȡһ���ֽ�
//����ֵ������������
uint8_t DS18B20_Read_Byte(void)    // read one byte
{        
    uint8_t i,j,dat;
    dat=0;
	for (i=1;i<=8;i++) 
	{
        j=DS18B20_Read_Bit();
        dat=(j<<7)|(dat>>1);
    }						    
    return dat;
}
//дһ���ֽڵ�DS18B20
//dat��Ҫд����ֽ�
void DS18B20_Write_Byte(uint8_t dat)     
 {             
    uint8_t j;
    uint8_t testb;
	  DS18B20_IO_OUT();//SET PG11 OUTPUT;
    for (j=1;j<=8;j++) 
	{
        testb=dat&0x01;
        dat=dat>>1;
        if (testb) 
        {
            DS18B20_DQ_OUT=0;// Write 1
            delay_us(2);                            
            DS18B20_DQ_OUT=1;
            delay_us(60);             
        }
        else 
        {
            DS18B20_DQ_OUT=0;// Write 0
            delay_us(60);             
            DS18B20_DQ_OUT=1;
            delay_us(2);                          
        }
    }
}
//��ʼ�¶�ת��
void DS18B20_Start(void)// ds1820 start convert
{   						               
    DS18B20_Rst();	   
	DS18B20_Check();	 
    DS18B20_Write_Byte(0xcc);// skip rom
    DS18B20_Write_Byte(0x44);// convert
} 
//��ʼ��DS18B20��IO�� DQ ͬʱ���DS�Ĵ���
//����1:������
//����0:����    	 
uint8_t DS18B20_Init(void)
{
 /*
  //��cubeMx������
  GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);//ʹ��GPIOGʱ��

  //GPIOG9
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//��ͨ���ģʽ
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//50MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
  GPIO_Init(GPIOG, &GPIO_InitStructure);//��ʼ��
 */
 	DS18B20_Rst();
	return DS18B20_Check();
}  
//��ds18b20�õ��¶�ֵ
//���ȣ�0.1C
//����ֵ���¶�ֵ ��-550~1250�� 
short DS18B20_Get_Temp(void)
{
    uint8_t temp;
    uint8_t TL,TH;
	  short tem;
    DS18B20_Start ();                    // ds1820 start convert
    DS18B20_Rst();
    DS18B20_Check();	 
    DS18B20_Write_Byte(0xcc);// skip rom
    DS18B20_Write_Byte(0xbe);// convert	    
    TL=DS18B20_Read_Byte(); // LSB   
    TH=DS18B20_Read_Byte(); // MSB   
    if(TH>7)
    {
        TH=~TH;
        TL=~TL; 
        temp=0;//�¶�Ϊ��  
    }else temp=1;//�¶�Ϊ��	  	  
    tem=TH; //��ø߰�λ
    tem<<=8;    
    tem+=TL;//��õװ�λ
    tem=(double)tem*0.625;//ת��     
	if(temp)return tem; //�����¶�ֵ
	else return -tem;    
}


// *****************HAl ku********************

///**
//  ******************************************************************************
//  * ????: bsp_DS18B20.c 
//  * ?    ?: ?????????
//  * ?    ?: V1.0
//  * ????: 2015-10-04
//  * ?    ?: DS18B20???????????
//  ******************************************************************************
//  * ??:
//  * ???????stm32???YS-F1Pro???
//  * 
//  * ??:
//  * ??:http://www.ing10bbs.com
//  * ??????????????,?????
//  ******************************************************************************
//  */
///* ????? ----------------------------------------------------------------*/
//#include "DS18B20/bsp_DS18B20.h"

///* ?????? --------------------------------------------------------------*/
///* ????? ----------------------------------------------------------------*/
//#define Delay_ms(x)   HAL_Delay(x)
///* ???? ------------------------------------------------------------------*/
///* ???? ------------------------------------------------------------------*/
///* ?????? --------------------------------------------------------------*/
//static void DS18B20_Mode_IPU(void);
//static void DS18B20_Mode_Out_PP(void);
//static void DS18B20_Rst(void);
//static uint8_t DS18B20_Presence(void);
//static uint8_t DS18B20_ReadBit(void);
//static uint8_t DS18B20_ReadByte(void);
//static void DS18B20_WriteByte(uint8_t dat);
//static void DS18B20_SkipRom(void);
//static void DS18B20_MatchRom(void);

///* ??? --------------------------------------------------------------------*/
///**
//  * ????: 
//  * ????: ?
//  * ? ? ?: ?
//  * ?    ?:?
//  */
//static void DS18B20_Delay(uint16_t time)
//{
//        uint8_t i;

//  while(time)
//  {    
//          for (i = 0; i < 10; i++)
//    {
//      
//    }
//    time--;
//  }
//}

///**
//  * ????: DS18B20 ?????
//  * ????: ?
//  * ? ? ?: ?
//  * ?    ?:?
//  */
//uint8_t DS18B20_Init(void)
//{
//  DS18B20_Dout_GPIO_CLK_ENABLE();
//  
//  DS18B20_Mode_Out_PP();
//        
//        DS18B20_Dout_HIGH();
//        
//        DS18B20_Rst();
//  
//  return DS18B20_Presence ();
//}


///**
//  * ????: ?DS18B20-DATA??????????
//  * ????: ?
//  * ? ? ?: ?
//  * ?    ?:?
//  */
//static void DS18B20_Mode_IPU(void)
//{
//  GPIO_InitTypeDef GPIO_InitStruct;
//  
//  /* ??????GPIO?? */
//  GPIO_InitStruct.Pin   = DS18B20_Dout_PIN;
//  GPIO_InitStruct.Mode  = GPIO_MODE_INPUT;
//  GPIO_InitStruct.Pull  = GPIO_PULLUP;
//  HAL_GPIO_Init(DS18B20_Dout_PORT, &GPIO_InitStruct);
//        
//}

///**
//  * ????: ?DS18B20-DATA??????????
//  * ????: ?
//  * ? ? ?: ?
//  * ?    ?:?
//  */
//static void DS18B20_Mode_Out_PP(void)
//{
//  GPIO_InitTypeDef GPIO_InitStruct;
//  
//  /* ??????GPIO?? */
//  GPIO_InitStruct.Pin = DS18B20_Dout_PIN;
//  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
//  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
//  HAL_GPIO_Init(DS18B20_Dout_PORT, &GPIO_InitStruct);          
//}

///**
//  * ????: ???????????
//  * ????: ?
//  * ? ? ?: ?
//  * ?    ?:?
//  */
//static void DS18B20_Rst(void)
//{
//        /* ????????? */
//        DS18B20_Mode_Out_PP();
//        
//        DS18B20_Dout_LOW();
//  
//        /* ??????480us???????? */
//        DS18B20_Delay(750);
//        
//        /* ??????????,?????? */
//        DS18B20_Dout_HIGH();
//        
//        /*?????????????,??15~60us???????????*/
//        DS18B20_Delay(15);
//}

///**
//  * ????: ??????????????
//  * ????: ?
//  * ? ? ?: 0:??,1:??
//  * ?    ?:?
//  */
//static uint8_t DS18B20_Presence(void)
//{
//        uint8_t pulse_time = 0;
//        
//        /* ????????? */
//        DS18B20_Mode_IPU();
//        
//        /* ?????????,???????60~240us?????? 
//         * ???????????????,?????????????,??15~60us???????????
//         */
//        while( DS18B20_Data_IN() && pulse_time<100 )
//        {
//                pulse_time++;
//                DS18B20_Delay(1);
//        }        
//        /* ??100us?,??????????*/
//        if( pulse_time >=100 )
//                return 1;
//        else
//                pulse_time = 0;
//        
//        /* ??????,??????????240us */
//        while( !DS18B20_Data_IN() && pulse_time<240 )
//        {
//                pulse_time++;
//                DS18B20_Delay(1);
//        }        
//        if( pulse_time >=240 )
//                return 1;
//        else
//                return 0;
//}

///**
//  * ????: ?DS18B20????bit
//  * ????: ?
//  * ? ? ?: ??????
//  * ?    ?:?
//  */
//static uint8_t DS18B20_ReadBit(void)
//{
//        uint8_t dat;
//        
//        /* ?0??1????????60us */        
//        DS18B20_Mode_Out_PP();
//        /* ??????:??????? >1us <15us ?????? */
//        DS18B20_Dout_LOW();
//        DS18B20_Delay(10);
//        
//        /* ?????,????,???????????? */
//        DS18B20_Mode_IPU();
//        //Delay_us(2);
//        
//        if( DS18B20_Data_IN() == SET )
//                dat = 1;
//        else
//                dat = 0;
//        
//        /* ???????????? */
//        DS18B20_Delay(45);
//        
//        return dat;
//}

///**
//  * ????: ?DS18B20?????,????
//  * ????: ?
//  * ? ? ?: ?????
//  * ?    ?:?
//  */
//static uint8_t DS18B20_ReadByte(void)
//{
//        uint8_t i, j, dat = 0;        
//        
//        for(i=0; i<8; i++) 
//        {
//                j = DS18B20_ReadBit();                
//                dat = (dat) | (j<<i);
//        }
//        
//        return dat;
//}

///**
//  * ????: ??????DS18B20,????
//  * ????: dat:?????
//  * ? ? ?: ?
//  * ?    ?:?
//  */
//static void DS18B20_WriteByte(uint8_t dat)
//{
//        uint8_t i, testb;
//        DS18B20_Mode_Out_PP();
//        
//        for( i=0; i<8; i++ )
//        {
//                testb = dat&0x01;
//                dat = dat>>1;                
//                /* ?0??1????????60us */
//                if (testb)
//                {                        
//                        DS18B20_Dout_LOW();
//                        /* 1us < ???? < 15us */
//                        DS18B20_Delay(8);
//                        
//                        DS18B20_Dout_HIGH();
//                        DS18B20_Delay(58);
//                }                
//                else
//                {                        
//                        DS18B20_Dout_LOW();
//                        /* 60us < Tx 0 < 120us */
//                        DS18B20_Delay(70);
//                        
//                        DS18B20_Dout_HIGH();                
//                        /* 1us < Trec(????) < ???*/
//                        DS18B20_Delay(2);
//                }
//        }
//}

///**
//  * ????: ???? DS18B20 ROM
//  * ????: ?
//  * ? ? ?: ?
//  * ?    ?:?
//  */
//static void DS18B20_SkipRom ( void )
//{
//        DS18B20_Rst();                   
//        DS18B20_Presence();                 
//        DS18B20_WriteByte(0XCC);                /* ?? ROM */        
//}

///**
//  * ????: ???? DS18B20 ROM
//  * ????: ?
//  * ? ? ?: ?
//  * ?    ?:?
//  */
//static void DS18B20_MatchRom ( void )
//{
//        DS18B20_Rst();                   
//        DS18B20_Presence();                 
//        DS18B20_WriteByte(0X55);                /* ?? ROM */        
//}


///*
//* ??????16 ???????????????
//* ????12?????,??5????,7????,4????
//*
//*         |---------??----------|-----?? ??? 1/(2^4)=0.0625----|
//* ???  | 2^3 | 2^2 | 2^1 | 2^0 | 2^(-1) | 2^(-2) | 2^(-3) | 2^(-4) |
//*
//*
//*         |-----???:0->?  1->?-------|-----------??-----------|
//* ???  |  s  |  s  |  s  |  s  |    s   |   2^6  |   2^5  |   2^4  |
//*
//* 
//* ?? = ??? + ?? + ??*0.0625
//*/
///**
//  * ????: ????? ROM ????? DS18B20 ??? 
//  * ????: ?
//  * ? ? ?: ???
//  * ?    ?:?
//  */
//float DS18B20_GetTemp_SkipRom ( void )
//{
//        uint8_t tpmsb, tplsb;
//        short s_tem;
//        float f_tem;
//        
//        
//        DS18B20_SkipRom ();
//        DS18B20_WriteByte(0X44);                                /* ???? */
//        
//        
//        DS18B20_SkipRom ();
//  DS18B20_WriteByte(0XBE);                                /* ???? */
//        
//        tplsb = DS18B20_ReadByte();                 
//        tpmsb = DS18B20_ReadByte(); 
//        
//        
//        s_tem = tpmsb<<8;
//        s_tem = s_tem | tplsb;
//        
//        if( s_tem < 0 )                /* ??? */
//                f_tem = (~s_tem+1) * 0.0625;        
//        else
//                f_tem = s_tem * 0.0625;
//        
//        return f_tem;         
//}

///**
//  * ????: ??? ROM ????? DS18B20 ??? 
//  * ????: ds18b20_id:???? DS18B20 ??????????
//  * ? ? ?: ?
//  * ?    ?:?
//  */
//void DS18B20_ReadId ( uint8_t * ds18b20_id )
//{
//        uint8_t uc;
//                
//        DS18B20_WriteByte(0x33);       //?????
//        
//        for ( uc = 0; uc < 8; uc ++ )
//          ds18b20_id [ uc ] = DS18B20_ReadByte();        
//}

///**
//  * ????: ??? ROM ????? DS18B20 ??? 
//  * ????: ds18b20_id:?? DS18B20 ??????????
//  * ? ? ?: ???
//  * ?    ?:?
//  */
//float DS18B20_GetTemp_MatchRom ( uint8_t * ds18b20_id )
//{
//        uint8_t tpmsb, tplsb, i;
//        short s_tem;
//        float f_tem;
//        
//        
//        DS18B20_MatchRom ();            //??ROM
//        
//  for(i=0;i<8;i++)
//                DS18B20_WriteByte ( ds18b20_id [ i ] );        
//        
//        DS18B20_WriteByte(0X44);                                /* ???? */

//        
//        DS18B20_MatchRom ();            //??ROM
//        
//        for(i=0;i<8;i++)
//                DS18B20_WriteByte ( ds18b20_id [ i ] );        
//        
//        DS18B20_WriteByte(0XBE);                                /* ???? */
//        
//        tplsb = DS18B20_ReadByte();                 
//        tpmsb = DS18B20_ReadByte(); 
//        
//        
//        s_tem = tpmsb<<8;
//        s_tem = s_tem | tplsb;
//        
//        if( s_tem < 0 )                /* ??? */
//                f_tem = (~s_tem+1) * 0.0625;        
//        else
//                f_tem = s_tem * 0.0625;
//        
//        return f_tem;                 
//}

///******************* (C) COPYRIGHT 2015-2020 ????????? *****END OF FILE****/












