/**
	*	@brief	config common periph_driver:example GPIO 
	*	@param	None
	*	@retval	None
	*	@periph 
	*******************************************************************************************
	*	@function		void RCC_Config(void);
	*							void NVIC_Config(void);
	*******************************************************************************************
	*/
#include "sys.h"
#include "usart.h"

//===============================================================================================================
void RCC_Config(void)
{
	//Error status variables �������״̬����
	ErrorStatus HSEStartUpStatus;
	
	RCC_DeInit();									//��RCC�Ĵ�����������ΪĬ��ֵ
	
	RCC_HSEConfig(RCC_HSE_ON);		//���ⲿ���پ���
//	while(RCC_WaitForHSEStartUp()==RESET);
	HSEStartUpStatus=RCC_WaitForHSEStartUp();
	if(HSEStartUpStatus==SUCCESS)
	{
		RCC_HCLKConfig(RCC_SYSCLK_Div1);	//HCLKΪSYSCLKʱ��
		RCC_PCLK1Config(RCC_SYSCLK_Div1);	//APB1ΪSYSCLKʱ��2��Ƶ,��������Ϊ2ʱ��SysTick����������⣩
																			//����AHB����ʱ��ΪSYSCLK��һ��Ƶ����PCLK1���֧��36MHz��Ӳ��������ȷ���ͣ�
		RCC_PCLK2Config(RCC_SYSCLK_Div1);	//APB2ΪSYSCLKʱ��1��Ƶ��������⣩
																			//����AHB����ʱ��ΪSYSCLK��һ��Ƶ����PCLK2����ȷ���ͣ�
		/*	ʱ�����У�APB1�ɵ���	1.PCLK1���36MHz��APB1���裻
															2.TIMXCLK��ʱ��2����7�����APB1Ԥ��Ƶϵ��=1����Ƶ�ʲ��䣬����Ƶ��X2��	*/
		
		/*	set PLL clock ,PLLCLK=HSE(8MHz)*9=72MHz;	*/
		RCC_PLLConfig(RCC_PLLSource_HSE_Div1,RCC_PLLMul_9);
		RCC_PLLCmd(ENABLE);												//ʹ��PLLʱ��
		
		while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY)==RESET);		//�ȴ�PLL׼������
		
		RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);					//����PLLΪϵͳʱ��Դ
		
		/* Judge PLLCLK is SYSCLK or not	*/ 
		while(RCC_GetSYSCLKSource()!=0x08);				//0x00:HSI��Ϊϵͳʱ��
																						//0x04:HSE��Ϊϵͳʱ��
																						//0x08:PLL��Ϊϵͳʱ��
	}
}
//===============================================================================================================

//===============================================================================================================
void NVIC_Config(u8 NVIC_PreemptionPriority,u8 NVIC_SubPriority,u8 NVIC_Channel,u8 NVIC_Group)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	
	NVIC_PriorityGroupConfig(NVIC_Group);					//�����ж����ȼ�����
	
	NVIC_InitStructure.NVIC_IRQChannel=NVIC_Channel; 							//�ж�ͨ��
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=NVIC_PreemptionPriority;  //��ռ���ȼ�
  NVIC_InitStructure.NVIC_IRQChannelSubPriority=NVIC_SubPriority;         //�����ȼ�
  NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;  
	
	NVIC_Init(&NVIC_InitStructure);
}
