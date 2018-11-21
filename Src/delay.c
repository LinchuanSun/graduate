#include "delay.h"
static uint8_t  fac_us=0;									   
static uint16_t fac_ms=0;							

void delay_init(uint8_t SYSCLK)
{
 	
	fac_us=SYSCLK/8;						//??????OS,fac_us?????
	fac_ms=(uint16_t)fac_us*1000;				//?OS?,????ms???systick???   

}				

//延时nus
//nus为延时的us数
//nus的值，不要大于798915us
void delay_us(uint32_t nus)
{		
	uint16_t temp;	    	 
	SysTick->LOAD=nus*fac_us; 				//时间加载	  		 
	SysTick->VAL=0x00;        				//清空计数器
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;//开始道倒数 
	do
	{
		temp=SysTick->CTRL;
	}while((temp&0x01)&&!(temp&(1<<16)));	//等待时间到达
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk; //关闭计数器
	SysTick->VAL =0X00;       				//清空计数器
}
//延时nms
//注意nms的范围
//SysTick->LOAD为24位寄存器，所以，最大延时为
//nms<=0xffffff*8*1000/SYSCLK
//SYSCLK单位为Hz,nms单位为ms
//对168M条件下,nms<=798ms 
void delay_xms(uint16_t nms)
{	 		  	  
	uint32_t temp;		   
	SysTick->LOAD=(uint32_t)nms*fac_ms;			//????(SysTick->LOAD?24bit)
	SysTick->VAL =0x00;           			//?????
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;          //???? 
	do
	{
		temp=SysTick->CTRL;
	}while((temp&0x01)&&!(temp&(1<<16)));	//??????   
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;       //?????
	SysTick->VAL =0X00;     		  		//?????	  	    
} 
//??nms 
//nms:0~65535
void delay_ms(uint16_t nms)
{	 	 
	uint8_t repeat=nms/540;						//???540,??????????????,
											//?????248M???,delay_xms??????541ms???
	uint16_t remain=nms%540;
	while(repeat)
	{
		delay_xms(540);
		repeat--;
	}
	if(remain)delay_xms(remain);
} 
