#include "stm32f10x.h"

void delayMilliSec(unsigned int ms);
uint32_t Delay = 0;
int main(void)
{
		RCC->APB2ENR |= 1<<4;           // clock for IOPCEN
		GPIOC->CRL=0X44444433;  // PC0, PC1 output, PC2, PC3 input
			
		SysTick->LOAD = 72000;
		SysTick->CTRL = 1<<2 | 1<<1 | 1;
		
		while(1)
		{
			delayMilliSec(200);
		}
}

void SysTick_Handler (void)
{
	if(SysTick->CTRL & SysTick_CTRL_COUNTFLAG)
	{
		SysTick->CTRL &= ~SysTick_CTRL_COUNTFLAG;
		if(Delay)
			--Delay;
		
	}
}

void delayMilliSec(unsigned int ms)
{
	Delay = ms;
	while(Delay)
	{
		
	}
}