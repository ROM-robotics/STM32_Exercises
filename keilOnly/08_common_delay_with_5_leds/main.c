#include "stm32f10x.h"

void delayMilliSec(unsigned int ms);

uint32_t Delay=0;
uint32_t t[6]={0,0,0,0,0,0};
uint32_t centi_sec[6] = {5,15,25,35,45,55}; // {.1,.3,.5,.7,.9,1.1} seconds
char push[6] = {0,0,0,0,0,0};

int main(void)
{
		RCC->APB2ENR |= 1<<2;           // clock for IOPAEN
		GPIOA->CRL=0X44333333;  	      // PA0,1,2,3,4,5 OUTPUT
			
		SysTick->LOAD = 72000;
		SysTick->CTRL = 1<<2 | 1<<1 | 1;
		
		while(1)
		{
			delayMilliSec(10);
			
			for(int i=0;i<6;i++)
			{
				if(++t[i] >= centi_sec[i])
				{
					if( push[i] == 0)
					{
						push[i] = 1;
						GPIOA->BSRR |= 1<<i;
					}
					else
					{
						push[i] = 0;
						int j = i+16;
						GPIOA->BSRR |= 1<<j;
					}					
					t[i]=0;
				}
			}	// end for loop
		
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
	while(Delay){}
}