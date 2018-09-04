/*******************************************************************
*	难点：PA15默认为Jlink下载端口中的JTDI，所以先映射为普通IO，再操作
********************************************************************/

#include "LED.h"
#include "sys.h"

void LED_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_13; 
  GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP; 
	GPIO_Init(GPIOC,&GPIO_InitStructure);
}

void LED_Set(u8 state)
{
	u16 i;
	u8 s=0;
	if(0==state)	PCout(13)=0;
	else if(1==state)	PCout(13)=1;
	else
	{
		if(++i==state)
			(1==s)?(s=0):(s=1);
		PCout(13)=s;
	}
}


