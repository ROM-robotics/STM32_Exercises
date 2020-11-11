#include "stm32f10x.h"

void delayMilliSeconds(unsigned int ms);

int main(void)
{
	RCC->APB2ENR |= 1<<4;
	GPIOC->CRL = 0Xffffff33; // PC0 PC1 output , push-pull
	
	while(1)
	{
		GPIOC->ODR |= 1;
		delayMilliSeconds(1000);
		GPIOC->ODR &= 0;
		delayMilliSeconds(1000);
	}
	
}

void delayMilliSeconds(unsigned int ms)
{
	while(ms--)
	{
		for(int i=0;i<18000;i++);
	}
}
