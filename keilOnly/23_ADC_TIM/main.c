#include "stm32f10x.h"
uint16_t ADCResult = 0;
int main(void)
{
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	GPIOA->CRL = 0xfffffff0;				// PA0 ANALOG INPUT
	
	RCC->CFGR |= 2<<14;							// ADC PRESCALER 72Mhz/6 = 12Mhz
	RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
	
	ADC1->CR2 |= 4<<17 | // EXTI SELECT TIMER3 TRGO ( TIMER3 SPECIAL EVENT TRIGGER )
							 1<<20;	 // EXTERNAL TRIGGER ENABLE
	ADC1->SMPR2 |= 0;		 // CHANNEL 0 -> 1.5 Cycles sample time
	ADC1->CR2 |= 1;			 // ADC ON ENABLE
	
	/* TIMER 3 */
	RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
	TIM3->PSC = 72;
	TIM3->CNT = 0;
	TIM3->ARR = 1000;  // 1 ms timer overflow
	TIM3->CR2 |= 2<<4; // timer trigger event
	TIM3->CR1 |= 1;		 // COUNTER ENABLE
	while(1)
	{
		
		if(ADC1->SR & ADC_SR_EOC)
		{
			ADC1->SR &= ~ADC_SR_EOC;
			ADCResult = ADC1->DR;
		}
	}
}