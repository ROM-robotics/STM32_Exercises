#include "stm32f10x.h"

#define prescaler 71
#define frequency 500
#define osc 72e6

uint16_t encodervalue=0;

int main(void)
{
	/* timer2 pwm */
	RCC->APB2ENR |= 1<<2; 			// GPIOA CLOCK ENABLE
	GPIOA->CRL = 0xfffffffb;  	// PA0 OUTPUT alternate PUSH PULL
	
	RCC->APB1ENR |= 1;
	TIM2->CNT = 0;
	TIM2->PSC = prescaler;
	TIM2->ARR = (osc/	prescaler) / frequency;
	TIM2->CR1 |= 1;							// TIMER COUNTER ENABLE
	
	TIM2->CCMR1 |= 6<<4;  			// FOR INPUT,OUTPUT AND PWM MODE
	TIM2->CCER |= 1;						// OUTPUT ENABLE
	//TIM2->CCR1 = TIM2->ARR /2;  // DUTY CYCLE PERCENTAGE
	
	/* timer 4 encoder */
	RCC->APB2ENR |= 1<<3;				// GPIOB clock enable
	GPIOB->CRL = 0x44ffffff;		// pb6,pb7 input float
	
	RCC->APB1ENR |= 1<<2;				// tim4 clock enable
	TIM4->PSC = 0;
	TIM4->ARR = 2028;
	TIM4->CCMR1 |= 1<<8 | 1; 		// cc2 channel TI2 ( TIM4_CH2) & cc1 channel TI1 (TIM4_CH1)
	TIM4->SMCR |= 3;						// TIM SMCR ENCODER MODE TI1, TI2
	TIM4->CR1 |= 1;				
	
	while(1)
	{
		encodervalue = TIM4->CNT;
		TIM2->CCR1 = encodervalue;
	}
}