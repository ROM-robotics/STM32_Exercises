#include "stm32f10x.h"

int main(void)
{
	RCC->APB2ENR |= 1 << 4;
	GPIOC->CRL = 0x44448833;
	GPIOC->ODR |= 1<<3 | 1<<2;



	while(1)
	{
		int idr = GPIOC->IDR & 0x000C;
		
		
		
		
	}
}