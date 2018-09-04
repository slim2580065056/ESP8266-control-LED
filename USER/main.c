#include "stm32f10x.h"
#include "usart.h"
#include "sys.h"
#include "Delay.h"
#include "LED.h"


extern const u8 KISS[];
extern u8 data;


void ESP_Init(void);

int main(void)
{
//	u8 flag;
	RCC_Config();
	Delay_Config();
	USART1_Config(115200);
	LED_Config();
	
	ESP_Init();
	while(1)
	{
		
		(0==data)?LED_Set(1):LED_Set(0);
		Delay_ms(50);
//		LED_Set(0);
//		Delay_ms(500);
//		LED_Set(1);
//		Delay_ms(500);
	}
}

void ESP_Init(void)
{
	printf("AT+RST\r\n");
	Delay_ms(5000);
	printf("AT+CWMODE=2\r\n");
	Delay_ms(6000);
	printf("AT+RST\r\n");
	Delay_ms(6000);
	printf("AT+CIPMUX=1\r\n");
	Delay_ms(6000);
	printf("AT+CIPSERVER=1,8080\r\n");
	Delay_ms(6000);
}

