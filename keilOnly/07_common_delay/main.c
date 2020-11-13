#include "stm32f10x.h"

void delayMilliSec(unsigned int ms);

uint32_t Delay=0;
uint32_t t1=0, t2=0;
char push1=0, push2=0;

int main(void)
{
		RCC->APB2ENR |= 1<<4;           // clock for IOPCEN
		GPIOC->CRL=0X44444433;  // PC0, PC1 output, PC2, PC3 input
			
		SysTick->LOAD = 72000;
		SysTick->CTRL = 1<<2 | 1<<1 | 1;
		
		/*
		while(1)
		{  THIS IS ERROR BECAUSE WE USE SUPER LOOP METHOD
			GPIOC->BSRR |= 1;
			delayMilliSec(1000);
			GPIOC->BSRR |= 1<<16;
			
			GPIOC->BSRR |= 1<<1;
			delayMilliSec(3000);
			GPIOC->BSRR |= 1<<17;
			delayMilliSec(3000);
			WE SHOULD USE COMMON DELAY FOR TIME SLICING 			
		} 
		*/
	
		/* THIS IS NO ERROR BECAUSE WE USE COMMON DELAY */
		while(1)
		{
			delayMilliSec(100);
			
			if(++t1 >= 5)
			{
				if( push1==0 ) 
				{	
					push1 = 1;
					GPIOC->BSRR |= 1;
				}
				else 
				{	
					push1= 0;
					GPIOC->BSRR |= 1<<16;
				}				
				t1 = 0;
			}
			
			if(++t2 >= 15)
			{
				if( push2==0 )
				{
					push2=1;
					GPIOC->BSRR |= 1<<1;
				}
				else
				{
					push2=0;
					GPIOC->BSRR |= 1<<17;
				}
				t2 = 0;
			}
		}
		/* USE IN PLC */
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
	while(Delay){}
}