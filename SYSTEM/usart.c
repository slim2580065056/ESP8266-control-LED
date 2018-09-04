/**
  ******************************************************************************
  * @file    my_usart.c
  * @author  LiuSongHu_QQ2580065056
  * @version V1.0.0
  * @date    2016-8-21
  * @brief   This file provides all the my_usart firmware functions. 
  ******************************************************************************
  * @attention
  *
	*	Use USART1 of APB2	
  ******************************************************************************
  */
/**
	*	@brief	Usart Init 
	*	@param	BaudRate
	*	@retval	None
	*/
	
#include "usart.h"
#include "LED.h"

u8 data;

//////////////////////////////////////////////////////////////////
//EN_USART1_RX   //���ʹ���˽���
//����1�жϷ������
//ע��,��ȡUSARTx->SR�ܱ���Ī������Ĵ���   	
u8 USART_RX_BUF[USART_REC_LEN];     //���ջ���,���USART_REC_LEN���ֽ�.
//����״̬
//bit15��	������ɱ�־
//bit14��	���յ�0x0d
//bit13~0��	���յ�����Ч�ֽ���Ŀ
u16 USART_RX_STA=0;       //����״̬���	

void USART1_Config(u32 BaudRate)
{
	/*	GPIO_Init / USART_Init / NVIC_Init Stucture	*/
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	/*	setting Clock of periph APIO and USART enable	*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_USART1,ENABLE);

	/*	set USARTx_TX of GPIO pin/mode/speed	*/
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9;
	/*	USARTx_TX	setting pinmode as alternate pushpull	*/
	GPIO_InitStructure.GPIO_Mode =GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	/*	set USARTx_RX of GPIO pin/mode/speed	*/
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;
	/*	USARTx_TX	setting pinmode as floating	*/
	GPIO_InitStructure.GPIO_Mode =GPIO_Mode_IN_FLOATING;
	//GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	/* USARTx_Init	Config */
	USART_InitStructure.USART_BaudRate=BaudRate;
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;
  USART_InitStructure.USART_StopBits=USART_StopBits_1;
  USART_InitStructure.USART_Parity=USART_Parity_No;
	USART_InitStructure.USART_Mode=USART_Mode_Rx | USART_Mode_Tx;
  USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART_Init(USART1,&USART_InitStructure);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	NVIC_InitStructure.NVIC_IRQChannel=USART1_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1; 
  NVIC_InitStructure.NVIC_IRQChannelSubPriority=3;
  NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;   

	NVIC_Init(&NVIC_InitStructure);
	
	/*	enable USART1	*/
	USART_Cmd(USART1,ENABLE);
	USART_ITConfig(USART1,USART_IT_RXNE, ENABLE);
}  


void USART1_IRQHandler(void)
{
	static uint8_t i;
	if( USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
	{
		if('0'==(u8)USART_ReceiveData(USART1)) {data=1;
		}
		else if('1'==(u8)USART_ReceiveData(USART1)){data=0;
		}
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);	
	}
}


/**
	*	@brief	fputc function redifine
	*	@param	None
	*	@retval	None
	*	@call		printf function
	*/

int fputc(int ch,FILE *f)
{
	/*	content of printf send to usart	*/
	USART_SendData(USART1,(u8) ch);
	//while(!(USART1->SR & USART_FLAG_TXE));
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)!=SET);
	return (ch);	
}

/**
	*	@brief	fgetc function redifine
	*	@param	None
	*	@retval	None
	*	@call		printf function
	*/

int fgetc(FILE *f)
{
	/*	waiting for uart1 input data	*/
	while(USART_GetFlagStatus(USART1,USART_FLAG_RXNE)!=SET);
	return (u32)USART_ReceiveData(USART1);
}
