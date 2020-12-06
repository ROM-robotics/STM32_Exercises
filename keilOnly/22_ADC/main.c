#include "stm32f10x.h"
uint16_t ADCResult = 0;
int main(void)
{
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	GPIOA->CRL = 0xfffffff0;				// PA0 ANALOG INPUT
	
	RCC->CFGR |= 2<<14;							// ADC PRESCALER 72Mhz/6 = 12Mhz
	RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
	
	ADC1->CR2 |= 7<<17 | // EXTI SELECT SWSTART ( SOFTWARE TRIGGER)
							 1<<20;	 // EXTERNAL TRIGGER ENABLE
	ADC1->SMPR2 |= 0;		 // CHANNEL 0 -> 1.5 Cycles sample time
	ADC1->CR2 |= 1;			 // ADC ON ENABLE
	
	while(1)
	{
		ADC1->CR2 |= 1<<22;
		if(ADC1->SR & ADC_SR_EOC)
		{
			ADC1->SR &= ~ADC_SR_EOC;
			ADCResult = ADC1->DR;
		}
	}
}