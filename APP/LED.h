#ifndef __LED_H__
#define __LED_H__

#include "stm32f10x.h"
#include "sys.h"
#include "Delay.h"

void LED_Config(void);
void LED_Set(u8 state);

#endif
