#include "stm32f10x.h"
#define OSC 72e6
#define FREQUENCY 500

int main(void)
{
	RCC->APB2ENR |= 1<<2;			// GPIOA CLK
	GPIOA->CRL = 0xf8ffffff;	// pa6 input pull up
	GPIOA->CRH = 0xfffffffb;	// pa8 alternate push pull
	GPIOA->ODR|= 1<<6;			
	
	AFIO->MAPR |= 1<<6;				// PARTIAL REMAP
	
	RCC->APB2ENR |= 1<<11;		// TIM1 CLK ENABLE
	TIM1->CNT = 0;
	TIM1->PSC = 71;						// PSC = 72e6 / 72 = 1Mhz ( T = 1us )
	TIM1->ARR = (OSC/TIM1->PSC)/ FREQUENCY;
	
	/* Capture & PWM Output */
	TIM1->CCMR1 |= 7<<4;			// CCMR1 PWM mode 1
	TIM1->CCER	|= 1;					// CCIE enable (PWM CH1 - TIM3 CH1)
	TIM1->CCR1  = TIM1->ARR/2;// 50% DUTY CYCLE
	TIM1->BDTR  |= 1<< 15	|		// MOE Enable
								 1<<12;		  // BKE Enable
	TIM1->CR1 	|= 1;					// TIME Counter Enable
	while(1)
	{
		
	}
}