#include "stm32f10x.h"
#define osc 72e6
#define frequency 500

int main(void)
{
	RCC->APB2ENR |= 1<<2;					// gpioa clock
	GPIOA->CRL = 0xfbffffff;			// pa6 output alternate push pull
	
	RCC->APB1ENR |= 1<<1;
	TIM3->CNT = 0;
	TIM3->CR1 |= 1;
	TIM3->PSC = 72;
	TIM3->ARR = (osc/TIM3->PSC) / frequency;
	
	/* CC output */
	TIM3->CCMR1 |= 6<<4;     // capture compare mode register (for pwm mode)
	TIM3->CCER |= 1;				 // capture compare enable register
	TIM3->CCR1 = TIM3->ARR/2;// capture/compare register 1 for duty cycle
	
	
	while(1)
	{
		
	}
}