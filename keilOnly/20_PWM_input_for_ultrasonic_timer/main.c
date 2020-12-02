	/* this program has error because use separate timer to produce pwm */ 
#include "stm32f10x.h"
#define frequency 500

volatile uint16_t Period = 0, Width = 0;
volatile uint16_t cm=0,inch=0;
int main(void)
{

	RCC->APB1ENR |= 1<<2;					 // TIMER4 CLOCK ENABLE
	TIM4->CNT = 0;
	TIM4->PSC = 71;								 // 72Mhz/2 = 1Mhz --> T = 1us
	TIM4->ARR = 20000;						 // 20 ms
	TIM4->CCMR1|= 2<<8 | 1;				 // cc2 channel ti2(tim4_ch2) & cc1 channel ti1 (tim4_ch1)
	TIM4->SMCR |= 5<<4 | 4;				 // TIMER RESET MODE, 101 FILTER TI1P  /* error */ 
	TIM4->CCER |= 1<<5 | 1<<4 | 1; // CC2P ACTIVE,CC2E ACTIVE,CC1E ACTIVE		
	TIM4->DIER |= 1<<9;						 // CC1 DE 	
	
	/* PWM TIMER */
	TIM4->CCMR2 |= 6<<4;					 // CHANNEL 3 ->  FOR PWM MODE 1,2 (PB8)
	TIM4->CCR3 = 20; 							 // 20 us
	TIM4->CCER |= 1<<8;						 // CC3E OUTPUT ACTIVE
	TIM4->CR1  |= 1;							 // CEN Counter Enable
	
	RCC->APB2ENR |= 1<<3;					 // GIPOB clock enable
	GPIOB->CRL = 0x88ffffff;			 // pb6,pb7 input pullup
	GPIOB->ODR |= 1<<7 | 1<<6;		 // PULL UP
	GPIOB->CRH = 0xfffffffb;			 // PB8 alternate push pull /* PWM TIMER */
	
	/* DMA */
	RCC->AHBENR |= 1;							 // DMA1 CHANNEL CLOCK ENABLE
	DMA1_Channel1->CPAR = (uint32_t) &TIM4->CCR1;
	DMA1_Channel1->CMAR = (uint32_t) &Period;
	DMA1_Channel1->CNDTR= 1;			 // number of transfer data
	
	DMA1_Channel1->CCR |=0 << 14 | // memory to memory disable
											 2 << 12 | // channel priority high
											 1 << 10 | // memory size 16 bits
											 1 << 8  | // peripheral size 16 bits
											 0 << 7  | // memory increment disable
											 0 << 6  | // peripheral increment disable
											 1 << 5  | // circular mode enable
											 0 << 4  | // read from peripheral
											 0 << 3  | // transfer error interrupt disable
											 0 << 2  | // half transfer interrupt disable
											 0 << 1  | // full transfer interrupt disable
											 1;        // channel enable
	
	
	while(1)
	{
		
		cm = (uint16_t)Period/58;
		inch = (uint16_t)Period/148;
	}
	
}

