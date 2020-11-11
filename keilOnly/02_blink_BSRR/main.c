#include "stm32f10x.h"

int main(void)
{
	RCC->APB2ENR |= 1 << 4;
	GPIOC->CRL = 0x44444433;
	
	while(1)
	{
		//GPIOC->ODR |= 1;
		GPIOC->BSRR = 0x00000003;
		GPIOC->BSRR = 0X00030000;
	}
	
}


	
	