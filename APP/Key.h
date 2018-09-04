#ifndef __KEY_H__
#define __KEY_H__

#include "stm32f10x.h"
#include "Delay.h"
#include "sys.h"
#include "OLED.h"
#include "usart.h"

void KEY_Config(void);		//外部函数：(extern) 返回函数类型 函数名(形参列表)
static void KEY_GPIO_Config(void);	//内部函数，只能被本文中的函数调用，不能被同一源程序中的其他文件中的函数调用
static void KEY_EXTI_Config(void);
void SET_Screen(void);




#endif
