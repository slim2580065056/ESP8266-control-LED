#ifndef __KEY_H__
#define __KEY_H__

#include "stm32f10x.h"
#include "Delay.h"
#include "sys.h"
#include "OLED.h"
#include "usart.h"

void KEY_Config(void);		//�ⲿ������(extern) ���غ������� ������(�β��б�)
static void KEY_GPIO_Config(void);	//�ڲ�������ֻ�ܱ������еĺ������ã����ܱ�ͬһԴ�����е������ļ��еĺ�������
static void KEY_EXTI_Config(void);
void SET_Screen(void);




#endif
