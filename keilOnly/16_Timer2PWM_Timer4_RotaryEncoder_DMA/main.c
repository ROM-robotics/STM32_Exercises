#include "stm32f10x.h"

#define prescaler 71
#define frequency 500
#define osc 72e6

uint16_t encodervalue=0;

int main(void)
{
	/* timer2 pwm */
	RCC->APB2ENR |= 1<<2; 			// GPIOA CLOCK ENABLE
	GPIOA->CRL = 0xfffffffb;;       			// PA0 OUTPUT alternate PUSH PULL
	
	RCC->APB1ENR |= 1;
	TIM2->CNT = 0;
	TIM2->PSC = prescaler;
	TIM2->ARR = (osc/	prescaler) / frequency;
	TIM2->DIER|= 1 << 9;				// DMA ENABLE
	TIM2->CCMR1 |= 6<<4;  			// FOR INPUT,OUTPUT AND PWM MODE
	TIM2->CCER |= 1;						// OUTPUT ENABLE
	TIM2->CCR1 = TIM2->ARR /2;  // DUTY CYCLE PERCENTAGE
	TIM2->CR1 |= 1;							// TIMER COUNTER ENABLE
	
	/* timer 4 encoder */
	RCC->APB2ENR |= 1<<3;				// GPIOB clock enable
	GPIOB->CRL = 0x44ffffff;		// pb6,pb7 input float
	
	RCC->APB1ENR |= 1<<2;				// tim4 clock enable
	TIM4->PSC = 0;
	TIM4->ARR = 2028;
	TIM4->CCMR1 |= 1<<8 | 1; 		// cc2 channel TI2 ( TIM4_CH2) & cc1 channel TI1 (TIM4_CH1)
	TIM4->SMCR |= 3;						// TIM SMCR ENCODER MODE TI1, TI2
	TIM4->CR1 |= 1;				
	
	/* DMA */
	RCC->AHBENR |= 1; // dma1 channel clock enable
	DMA1_Channel5->CPAR = (uint32_t) &TIM2->CCR1;
	DMA1_Channel5->CMAR = (uint32_t) &encodervalue;
	DMA1_Channel5->CNDTR = 1;
	
	DMA1_Channel5->CCR = 0 << 14 | // memory to memory disable
											 2 << 12 | // channel priority high
											 1 << 10 | // memory size 16 bits
											 1 << 8  | // peripheral size 16 bits
											 0 << 7  | // memory increment disable
											 0 << 6  | // peripheral increment disable
											 1 << 5  | // circular mode enable
											 1 << 4  | // read from memory
											 0 << 3  | // transfer error interrupt disable
											 0 << 2  | // half transfer interrupt disable
											 0 << 1  | // full transfer interrupt disable
											 1;        // channel enable
	while(1)
	{
		encodervalue = TIM4->CNT;
		
	}
}