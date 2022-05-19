#include "stm32f4xx.h"                  // Device header
#include <stdio.h>
#include <FreeRTOS.h>
#include <task.h>

void Clocks_Init(void);
void GPIOA_Init(void);

void vTask1(void *pvParameters);
void vTask2(void *pvParameters);

int main(void)
{
	Clocks_Init();
	GPIOA_Init();
	
	xTaskCreate(vTask1, "Main Task", 256 , NULL, 1, NULL);
	xTaskCreate(vTask2, "LED Task", 256 , NULL, 1, NULL);
	
	vTaskStartScheduler();
	
	while(1)
	{

	}
}

void Clocks_Init(void)
{
	while((RCC->CR & RCC_CR_HSIRDY) != RCC_CR_HSIRDY);
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
}

void GPIOA_Init(void)
{
	GPIOA->MODER |= GPIO_MODER_MODE5_0;
}

void vTask1(void *pvParameters)
{
	uint8_t i = 0;
	while(1)
	{
		printf("%d", i);
		i++;
		vTaskDelay(pdMS_TO_TICKS(4000));
	}
}
void vTask2(void *pvParameters)
{
	while(1)
	{
		GPIOA->ODR ^= GPIO_ODR_OD5;
		vTaskDelay(pdMS_TO_TICKS(2000));
	}
}
