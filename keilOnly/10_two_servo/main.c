#include "stm32f10x.h"

unsigned int systick = 0;
long map(long x, long in_min, long in_max, long out_min, long out_max);
struct Servo{
	unsigned output_state:1;
	uint32_t OnTimePeriod;
	uint32_t OffTimePeriod;
	uint32_t ServoPeriod;
	uint32_t Degree;
};
struct Servo servo1;
struct Servo servo2;

long degreeToServoPeriod(long x)
{
	return (x - 0) * (144000 - 72000) / (144000 - 0) + 72000;
}
uint32_t degree[2];
int main(void)
{

	RCC->APB2ENR |= 1<<4;										// IOPCEN Enable
	GPIOC->CRL = 0xff3388ff;								// pc2,pc3 input pc4,pc5 output
	GPIOC->ODR |= 1<<2 | 1<<3;							// pc2,pc3 pull up
	
	SysTick->LOAD = 720;										// 0.01 milli second
	SysTick->CTRL = 1<<2 | 1<<1 | 1;
	
	int deg[2]={90,180};                           
	
	//for(int i=0;i<180;i++)
	//{
	//	deg[i] = degreeToServoPeriod(i); 
	//}
	int j=0; 
	while(1)
	{
		if(systick)														// every 0.01 milli second
		{						
			systick = 0; 		
			
			if(++servo1.OnTimePeriod >= 2000)// every 20ms servo on 
			{
				servo1.OnTimePeriod = 0;					// reset ontime timer
				servo2.OnTimePeriod = 0;					// reset ontime timer
				GPIOC->BSRR |= 1<<4;							// pc4 high
				GPIOC->BSRR |= 1<<5;							// pc4 high
				servo1.output_state = 1;					// for offtime Servo
				servo2.output_state = 1;					// for offtime Servo
				//j = (j>=180) ? 0 : j+1;
				degree[0] = map(deg[0],0,180,100,200);
				degree[1] = map(deg[1],0,180,100,200);
			}
			if(servo1.output_state)
			{
				if( ++servo1.OffTimePeriod == degree[0] )// 1~2 millis second
				{
					servo1.OffTimePeriod = 0;				// reset offtime timer
					GPIOC->BSRR |= 1<<20;						// pc4 low
					servo1.output_state = 0;
				}
			}
			if(servo2.output_state)
			{
				if( ++servo2.OffTimePeriod == degree[1] )// 1~2 millis second
				{
					servo2.OffTimePeriod = 0;				// reset offtime timer
					GPIOC->BSRR |= 1<<21;						// pc5 low
					servo2.output_state = 0;
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
		systick = 1;
	}
	
}

long map(long x, long in_min, long in_max, long out_min, long out_max)
{
	 return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}


	// map(Degree,0,180,100,300);
	// long map(long x, long in_min, long in_max, long out_min, long out_max);
	// return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;