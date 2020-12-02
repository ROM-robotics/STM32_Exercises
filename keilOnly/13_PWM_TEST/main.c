#include "stm32f10x.h"
#define prescaler 71
#define frequency 1000
#define osc 72e6
int ccr_ = 0;
int count = 0;
// TIMER2
int main(void)
{
	RCC->APB2ENR |= 1<<2; 			// GPIOA CLOCK ENABLE
	GPIOA->CRL = 0xfffffffb;;   // PA0 OUTPUT alternate PUSH PULL
	
	RCC->APB1ENR |= 1;
	TIM2->CNT = 0;
	TIM2->PSC = prescaler;
	TIM2->ARR = (osc/	prescaler) / frequency;
	
	
	TIM2->CCMR1 |= 6<<4;  			// FOR INPUT,OUTPUT AND PWM MODE
	TIM2->CCER |= 1;						// OUTPUT ENABLE
	TIM2->CCR1 = TIM2->ARR /2;  // DUTY CYCLE PERCENTAGE
	TIM2->CR1 |= 1;							// TIMER COUNTER ENABLE
	while(1)
	{
		
		/*
		if(count > 100000)
		{
			count = 0;
			ccr_ += 10;
			TIM2->CCR1 = ccr_;
			if(ccr_ >= 2000)
				ccr_ = 0;
		}
		count +=1;
		*/
	}
}