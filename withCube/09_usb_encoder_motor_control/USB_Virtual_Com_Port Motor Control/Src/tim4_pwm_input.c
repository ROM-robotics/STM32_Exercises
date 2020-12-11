#include "main.h"

void timer4_pwm_input(void)
{
	RCC->APB1ENR |= 1<<2;//TIMER4 Clock enable
	
	TIM4->PSC = 72;// 72Mhz/72 = 1Mhz - T = 1us
	TIM4->ARR = 65535;
	TIM4->CCMR1 |= 2<<8 | 1; 		
	TIM4->SMCR	|= 5<<4 | 4;//Timer Reset mode , 101 filter TI1P (TIM4 CH1)
	TIM4->CCER |= 1<<5 | 1<<4 | 1;//CC2P active,CC2E active,CC1E active
	TIM4->CR1 |=1;//CEN Counter enable
	
	RCC->APB2ENR |= 1<<3;//IOCB Clock enable
	
	GPIOB->CRL = 0x88ffffff;//PB6 , PB7 input pull up
	GPIOB->ODR |= 1<<7 | 1<<6; //Pull up
	
	/*for forward reverse */
	RCC->APB2ENR |= 1<<4; // iopcen 
	GPIOC->CRL = 0xffffff33; // pc0 pc1 output push pull
	GPIOC->ODR |= 1<<1 | 1;
}