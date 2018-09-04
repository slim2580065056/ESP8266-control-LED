/**
	*	@breif	delay some time , delay configuration , some us and some ms
	*	@param	nus,some millisecond
	*					ums,some microsecond
	*	@retval	None
	*	@note 	SysTick��һ��24λ��������ʱ��
	*	@mark		temp & 0x01 && (temp & (1<<16)):���������¼�������ѯ��������ǰֵ������ȡ���ļ���ֵtemp��Ϊ0��
	*					��(temp & 0x01)���Ҽ�����־λ(1<<16��CTRL�Ĵ����ĵ�16bit)��Ϊ1ʱ	(!(temp & (1<<16)))������ѭ����
	*/

#include "Delay.h"

static u16 fac_ms;
static u8 fac_us;

void Delay_Config(void)
{	
	/* 	choose clock source and setting correlation param	*/
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);				//ѡ��AHB��8��ƵΪ�δ�ʱ�ӵ�ʱ��Դ��72/8=9MHz
	fac_us=SystemCoreClock/8000000;
	fac_ms=(u16)fac_us*1000; 
}

void Delay_ms(u32 nms)
{
	u32 temp;
	/*	Config SysTick correlation param	*/
	//	SysTick_Config(ticks);				//���µĲ����������ò���
	/* set reload register */	
	SysTick->LOAD  = nms*fac_ms;			//װ��ֵ
	/* Load the SysTick Counter Value */
  SysTick->VAL   = 0x00;								//��ռ�����										
  SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;		//��ʼ����ʱ
	do{
		temp=SysTick->CTRL;

	}while(temp & 0x01 && !(temp & (1<<16)));		//�ȴ�ʱ�䵽��
	SysTick->CTRL	&= ~SysTick_CTRL_ENABLE_Msk;	//�رռ�����
	SysTick->VAL   = 0x00;													//��ռ�����
}

void Delay_us(u32 nus)
{
	u32 temp;
	SysTick->LOAD =	nus*fac_us;					//������ֵ����װ���ֵ�Ĵ���
	SysTick->VAL	=	0x00;									//���ó�ֵΪ0
	SysTick->CTRL|=	SysTick_CTRL_ENABLE_Msk;		//��ʼ������
	do{
		temp=SysTick->CTRL;
	}while(temp & 0x01 && !(temp & (1<<16)));		//�ȴ�����ʱ�䵽��
																							//(1<<16)Ϊ0x0001 0000
	SysTick->CTRL	&= ~SysTick_CTRL_ENABLE_Msk;	//�رռ�����
	SysTick->VAL	=	0x00;														//��ռ�����
}
