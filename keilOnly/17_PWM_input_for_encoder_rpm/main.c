#include "stm32f10x.h"

volatile uint16_t Period = 0, Width = 0;
int rpm = 0, frequency = 0, tim4CNT = 0, cpr = 330;

int calculateRPM(uint16_t p);
int main(void)
{
	RCC->APB1ENR |= 1<<2;					// TIMER4 CLOCK ENABLE
	TIM4->PSC = 72;								// 72Mhz/2 = 1Mhz --> T = 1us
	TIM4->ARR = 65535;
	TIM4->CCMR1|= 2<<8 | 1;
	TIM4->SMCR |= 5<<4 | 4;				// TIMER RESET MODE, 101 FILTER TI1P
	TIM4->CCER |= 1<<5 | 1<<4 | 1;// CC2P ACTIVE,CC2E ACTIVE,CC1E ACTIVE
	TIM4->CR1  |= 1;							// CEN Counter Enable
	
	RCC->APB2ENR |= 1<<3;					// GIPOB clock enable
	GPIOB->CRL = 0x88ffffff;			// pb6,pb7 input pullup
	GPIOB->ODR |= 1<<7 | 1<<6;		// PULL UP
	
	while(1)
	{
		tim4CNT = TIM4->CNT;
		Period = TIM4->CCR1;
		Width  = TIM4->CCR2;
		rpm = calculateRPM(Period);
	}
	
}

int calculateRPM(uint16_t p)
{
	frequency = 1e6/p;
	int rpm_ = ( frequency * 60 ) / cpr;
	// rpm = frequency * 0.1818;
	// rpm = 181818 / p;
	
	return rpm_;
}