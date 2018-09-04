/**
  ******************************************************************************
  * @file    my_usart.h
  * @author  LiuSongHu_QQ2580065056
  * @version V1.0.0
  * @date    20116-8-21
  * @brief   This file contains all the functions prototypes for the my_usart 
  *          firmware library.
  ******************************************************************************
  * @attention
  *
	*	Use USART1 of APB2	
	*********************************************************************************
	*	1.�޸���USART_RX_STA,ʹ�ô����������ֽ���Ϊ2��14�η�
	*	2.������USART_REC_LEN,���ڶ��崮�����������յ��ֽ���(������2��14�η�)	
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef	__USART_H__
#define __USART_H__

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include <stdio.h>


#define USART_REC_LEN  			200  	//�����������ֽ��� 200
#define EN_USART1_RX 			1		//ʹ�ܣ�1��/��ֹ��0������1����
	  	
extern u8  USART_RX_BUF[USART_REC_LEN]; //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
extern u16 USART_RX_STA;         		//����״̬���	

void USART1_Config(u32);

#endif
