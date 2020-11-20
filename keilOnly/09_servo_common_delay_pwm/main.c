#include "stm32f10x.h"
struct {
	unsigned systick:1;
	unsigned output_state:1;
} Flag;
uint32_t OnTimePeriod=0, OffTimePeriod=0;
uint32_t ServoPeriod=200, Degree = 100;

long map(long x, long in_min, long in_max, long out_min, long out_max);

int main(void)
{

	RCC->APB2ENR |= 1<<4;										// IOPCEN Enable
	GPIOC->CRL = 0xff3388ff;								// pc2,pc3 input pc4,pc5 output
	GPIOC->ODR |= 1<<2 | 1<<3;							// pc2,pc3 pull up
	
	SysTick->LOAD = 720;										// 0.01 milli second
	SysTick->CTRL = 1<<2 | 1<<1 | 1;
	//while(!1);
	while(1)
	{
		if(Flag.systick)											// every 0.01 milli second
		{
			Flag.systick = 0; 									
			if(++OnTimePeriod >= 1570)					// every 20ms servo on 
			{
				OnTimePeriod = 0;									// reset ontime timer
				GPIOC->BSRR |= 1<<4;							// pc4 high
				Flag.output_state = 1;						// for offtime flag
				//ServoPeriod = map(Degree,0,180,100,300);				
			}
			if(Flag.output_state)
			{
				if(++OffTimePeriod == ServoPeriod)// 1~2 millis second
				{
					OffTimePeriod = 0;							// reset offtime timer
					GPIOC->BSRR |= 1<<20;						// pc4 low
					Flag.output_state = 0;
				}
			}
			
		}// end 0.01 milli sec loops 
	}// end while 
}//end main

void SysTick_Handler(void)
{
	if(SysTick->CTRL & SysTick_CTRL_COUNTFLAG)
	{
		SysTick->CTRL &= ~SysTick_CTRL_COUNTFLAG;		
		Flag.systick = 1;
	}
	
}

long map(long x, long in_min, long in_max, long out_min, long out_max)
{
	 return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}