#include "ds18b20.h"
#include "delay.h"	
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//STM32F407开发板
//DS18B20驱动代码	   
//
//
//
//版本：V1.0
//版权所有，盗版必究。
//
//All rights reserved										  
//////////////////////////////////////////////////////////////////////////////////
  

//复位DS18B20
void DS18B20_Rst(void)	   
{                 
    DS18B20_IO_OUT(); //SET PG11 OUTPUT
    DS18B20_DQ_OUT=0; //拉低DQ
    delay_us(750);    //拉低750us
    DS18B20_DQ_OUT=1; //DQ=1 
	delay_us(15);     //15US
}
//等待DS18B20的回应
//返回1:未检测到DS18B20的存在
//返回0:存在
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
//从DS18B20读取一个位
//返回值：1/0
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
//从DS18B20读取一个字节
//返回值：读到的数据
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
//写一个字节到DS18B20
//dat：要写入的字节
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
//开始温度转换
void DS18B20_Start(void)// ds1820 start convert
{   						               
    DS18B20_Rst();	   
	DS18B20_Check();	 
    DS18B20_Write_Byte(0xcc);// skip rom
    DS18B20_Write_Byte(0x44);// convert
} 
//初始化DS18B20的IO口 DQ 同时检测DS的存在
//返回1:不存在
//返回0:存在    	 
uint8_t DS18B20_Init(void)
{
 /*
  //在cubeMx中配置
  GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);//使能GPIOG时钟

  //GPIOG9
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//50MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init(GPIOG, &GPIO_InitStructure);//初始化
 */
 	DS18B20_Rst();
	return DS18B20_Check();
}  
//从ds18b20得到温度值
//精度：0.1C
//返回值：温度值 （-550~1250） 
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
        temp=0;//温度为负  
    }else temp=1;//温度为正	  	  
    tem=TH; //获得高八位
    tem<<=8;    
    tem+=TL;//获得底八位
    tem=(double)tem*0.625;//转换     
	if(temp)return tem; //返回温度值
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












