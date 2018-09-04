/**
	*	breif: Key1 -> PA8 -> Set
	*				 Key2 -> PB0 -> B/N
	**/
#include "Key.h"

u8 SET_Flag=0,BN_Flag=0,S=1;
u16 SPEED_P=360,SPEED_I=3,STAND_P=500,STAND_D=12;
u8 *Control[2]={"BLE ","2.4G"};					//����һ������2��Ԫ�ص�ָ�����飬����ʼ��

void KEY_Config(void)
{
	KEY_GPIO_Config();
	KEY_EXTI_Config();    
}

void KEY_GPIO_Config(void)
{
	/*	����TypeDef���ͱ���(��ͬ����uint x,y;)һ�����ȶ����ʹ��	*/
	GPIO_InitTypeDef GPIO_InitStructure;
	/*	����ʱ��	*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB,ENABLE);
	/*	���ݽṹ���еı�����ֵ��Ӧ��ֵ	*/
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;	//����ƽ����
	/*	��ʼ��IO������ǰ����ΪIO�ڱ�������һ��Ϊָ���IO�ڵ�һ���ṹ��ָ��	*/
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	GPIO_SetBits(GPIOB, GPIO_Pin_0);
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;	//����ƽ����
	/*	��ʼ��IO������ǰ����ΪIO�ڱ�������һ��Ϊָ���IO�ڵ�һ���ṹ��ָ��	*/
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	/*	��Ϊ����Ϊ���������Գ�ʼ��Ϊ�ߵ�ƽ	*/
	GPIO_SetBits(GPIOA, GPIO_Pin_8);		
}

void KEY_EXTI_Config(void)
{
	/*	����TypeDef���ͱ���	*/
	EXTI_InitTypeDef EXTI_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	/*  �ⲿ�ж�ӳ��	*/
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource0);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource8);	
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_EXTI,ENABLE);
	/*	�Խṹ���Ա������ֵ	*/
	EXTI_InitStructure.EXTI_Line=EXTI_Line0|EXTI_Line8;	//PA8 & PB0
	EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;		//interrupt trigger
	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling;//Falling trigger
	EXTI_InitStructure.EXTI_LineCmd=ENABLE;
	/*	��ʼ��EXTI	*/
	EXTI_Init(&EXTI_InitStructure);
}
void SET_Screen(void)
{
	switch(SET_Flag)
	{
		case 1:	OLED_Area_Clear();
						OLED_S8X16(24,36,"<SPEED>");
						OLED_C6X8(48,40,'>');
						OLED_C6X8(48,48,'P');
						OLED_C6X8(56,48,'I');
						OLED_S6X8Num(48,64,SPEED_P,3,1);		//void OLED_S6X8Num(u8 x,u8 y,u32 num,u8 len,u8 mode);
						OLED_S6X8Num(56,64,SPEED_I,3,1);		//void OLED_S6X8Num(u8 x,u8 y,u32 num,u8 len,u8 mode);
			break;
		case 2:
						OLED_C6X8(48,40,' ');
						OLED_C6X8(56,40,'>');
			break;
		case 3:	OLED_Area_Clear();
						OLED_S8X16(24,36,"<STAND>");
						OLED_C6X8(48,40,'>');
						OLED_C6X8(48,48,'P');
						OLED_C6X8(56,48,'D');
						OLED_S6X8Num(48,64,STAND_P,3,1);		//void OLED_S6X8Num(u8 x,u8 y,u32 num,u8 len,u8 mode);
						OLED_S6X8Num(56,64,STAND_D,3,1);		//void OLED_S6X8Num(u8 x,u8 y,u32 num,u8 len,u8 mode);
			break;
		case 4:
						OLED_C6X8(48,40,' ');
						OLED_C6X8(56,40,'>');
			break;
		case 5:	OLED_Area_Clear();
						OLED_S8X16(24,32,"<CONTROL>");
						OLED_C6X8(56,48,'>');
						OLED_S6X8(56,56,Control[S-1]);
			break;
		default:OLED_Area_Clear();		
						OLED_S6X8(24,5,"SPEED");
						OLED_C6X8(24,55,'P');
						OLED_S6X8Num(24,63,SPEED_P,3,1);
						OLED_C6X8(24,95,'I');
						OLED_S6X8Num(24,102,SPEED_I,3,1);
		
						OLED_S6X8(32,5,"STAND");
						OLED_C6X8(32,55,'P');
						OLED_S6X8Num(32,63,STAND_P,3,1);
						OLED_C6X8(32,95,'D');
						OLED_S6X8Num(32,102,STAND_D,3,1);

						OLED_S6X8(40,24,"CONTROL");
						OLED_S6X8(40,80,Control[S-1]);			//Ĭ��Ϊ��������
		
						OLED_S6X8(56,5,"TEMPERATURE");
						OLED_S6X8(56,80,"+22.5");
						OLED_C6X8(56,110,123);		//���ASCII��ֵ(�Զ���)
						OLED_C6X8(56,115,'C');
	}	
}
void BN_Screen(void)
{
	switch(SET_Flag)
	{
		case 1:	SPEED_P=10*BN_Flag;
						BN_Flag==99?BN_Flag=0:BN_Flag;
						OLED_S6X8Num(48,64,SPEED_P,3,1);		//void OLED_S6X8Num(u8 x,u8 y,u32 num,u8 len,u8 mode);
			break;
		case 2:	SPEED_I=BN_Flag;
						BN_Flag==99?BN_Flag=0:BN_Flag;
						OLED_S6X8Num(56,64,SPEED_I,3,1);
			break;
		case 3:	STAND_P=10*BN_Flag;
						BN_Flag==99?BN_Flag=0:BN_Flag;
						OLED_S6X8Num(48,64,STAND_P,3,1);		//void OLED_S6X8Num(u8 x,u8 y,u32 num,u8 len,u8 mode);						
			break;
		case 4:	STAND_D=BN_Flag;
						BN_Flag==99?BN_Flag=0:BN_Flag;
						OLED_S6X8Num(56,64,STAND_D,3,1);		//void OLED_S6X8Num(u8 x,u8 y,u32 num,u8 len,u8 mode);
			break;
		case 5:	S=BN_Flag;
						BN_Flag>=2?BN_Flag=0,S=2:BN_Flag;
						OLED_S6X8(56,56,Control[S-1]);
			break;
		default:
			break;
	}	
}
void EXTI0_IRQHandler(void)			//BN_Key	->PB0
{
	if(EXTI_GetITStatus(EXTI_Line0)==SET)
	{			
		printf("enter interrupt\r\n");
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0)==0)
		{
			Delay_ms(20);
			if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0)==0)
			{				
				while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0)==0);	//�ȴ������ͷ�
				BN_Flag++;
				printf("BN_Flag=%d\r\n",BN_Flag);
				BN_Screen();
				GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_12)==1?GPIO_ResetBits(GPIOA,GPIO_Pin_12):GPIO_SetBits(GPIOA,GPIO_Pin_12);			
			}
		}		
		EXTI_ClearFlag(EXTI_Line0);		
	}
}
void EXTI9_5_IRQHandler(void)			//Key_SET	->PA8
{
	if(EXTI_GetITStatus(EXTI_Line8)==SET)
	{			
		if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8)==0)
		{
			Delay_ms(20);
			if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8)==0)
			{				
				while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8)==0);	//�ȴ������ͷ�
				SET_Flag==6?SET_Flag=0,SET_Flag++:SET_Flag++;
				printf("SET_Flag=%d\r\n",SET_Flag);
				SET_Screen();
				GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_15)==1?GPIO_ResetBits(GPIOA,GPIO_Pin_15):GPIO_SetBits(GPIOA,GPIO_Pin_15);
			}
		}	
		EXTI_ClearFlag(EXTI_Line8);	
	}
}
