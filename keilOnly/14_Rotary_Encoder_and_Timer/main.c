#include "stm32f10x.h"
uint16_t encodervalue=0;
int main(void)
{
	RCC->APB2ENR |= 1<<3;				// GPIOB clock enable
	GPIOB->CRL = 0x44ffffff;		// pb6,pb7 input float
	
	RCC->APB1ENR |= 1<<2;				// tim4 clock enable
	TIM4->PSC = 0;
	TIM4->ARR = 1320;
	TIM4->CCMR1 |= 1<<8 | 1; 		// cc2 channel TI2 ( TIM4_CH2) & cc1 channel TI1 (TIM4_CH1)
	TIM4->SMCR |= 3;						// TIM SMCR ENCODER MODE TI1, TI2
	TIM4->CR1 |= 1;							// TIMER COUNTER ENABLE
	while(1)
	{
		encodervalue = TIM4->CNT;
	}
}