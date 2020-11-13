#include "stm32f10x.h"


uint8_t Count=0;
char push = 0;
void Delayms(unsigned int ms);
int main(void)
{
		RCC->APB2ENR |= 1<<4;           // clock for IOPCEN
		GPIOC->CRL=0X44448833;  // PC0, PC1 output, PC2, PC3 input
		GPIOC->ODR |= 1<<3 | 1<<2;
		
		while(1)
		{
			int idr = GPIOC->IDR & 0x0000000C; // FILTER PC2, PC3
			
			if(idr == 0x0004) // pc2
			{
				if(push==0)
				{
					push = 1;
					Count++;
				}
			}
			else push = 0; // release
			if(idr == 0x0008) // pc3
			{
				Count--;
			}
			
			
			
			
			//Delayms(1000);
		}
}

void Delayms(unsigned int ms)
{
	while(ms--)
	{
		for(int i=0;i<11111;i++);
	}
}