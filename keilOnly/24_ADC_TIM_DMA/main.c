#include "stm32f10x.h"
uint32_t ADCResult = 0;
int main(void)
{
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	GPIOA->CRL = 0xfffffff0;				// PA0 ANALOG INPUT
	
	RCC->CFGR |= 2<<14;							// ADC PRESCALER 72Mhz/6 = 12Mhz
	RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
	
	ADC1->CR2 |= 4<<17 | // EXTI SELECT TIMER3 TRGO ( TIMER3 SPECIAL EVENT TRIGGER )
							 1<<20 | // EXTERNAL TRIGGER ENABLE
						   1<<8;   //---------------------------------------------------------------DMA MODE
	ADC1->SMPR2 |= 0;		 // CHANNEL 0 -> 1.5 Cycles sample time
	ADC1->CR2 |= 1;			 // ADC ON ENABLE
	
	/* TIMER 3 */
	RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
	TIM3->PSC = 72;
	TIM3->CNT = 0;
	TIM3->ARR = 1000;  // 1 ms timer overflow
	TIM3->CR2 |= 2<<4; // timer trigger event
	TIM3->CR1 |= 1;		 // COUNTER ENABLE
	
	RCC->AHBENR |= RCC_AHBENR_DMA1EN;
	DMA1_Channel1->CPAR = (uint32_t) &ADC1->DR;
	DMA1_Channel1->CMAR = (uint32_t) &ADCResult;
	DMA1_Channel1->CNDTR = 1;
	DMA1_Channel1->CCR |= 0<<14 | 
												2<<12 |
												1<<10 |
												1<<8	|
												0<<7	| //MEMORY INCREMENT
												0<<6	|
												1<<5	|
												0<<4	|
												0<<3	|
												0<<2	|
												0<<1	|
												1;			// DMA ENABLE
	while(1)
	{
		
		
	}
}