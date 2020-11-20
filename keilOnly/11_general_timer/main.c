#include "stm32f10x.h"

int main(void)
{
	RCC->APB1ENR |= 1<<2;   // TIMER4 CLOCK ENAGLE
	TIM4->PSC = 71;					// FOSC 72 MHz / t = 1/f 
													// assume = 1 us
													// 1us/13.9ns = 71.9
													// timer overflow = ( 1us x ARR )
													// if 100us = 1us x ARR
													//			ARR = 100
	TIM4->ARR = 100;				// 100us
	TIM4->CNT = 0;					// Clear counter
	TIM4->CR1 |= 1;					// CEN Counter Enable
	TIM4->DIER |= 1;
	NVIC_EnableIRQ(TIM4_IRQn);
	
	while(1)
	{
		
	}
	
}

void TIM4_IRQHandler(void)
{
	if( TIM4->SR & TIM_SR_UIF )
	{
		TIM4->SR &= ~TIM_SR_UIF;
	}
}