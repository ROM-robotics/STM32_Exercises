#include "stm32f10x.h"
void toggle(void);
void toggleDouble(void);
void delay_(void);

int main(void)
{
	RCC->APB2ENR |= 1<<4;      						//   clock for IOPCEN
	GPIOC->CRL = 0x44448833;   						//   PC0,PC1 output, PC2,PC3 input, PC* input float

	GPIOC->ODR |= 1<<2 | 1<<3; 						// 	GPIOC->ODR = 0x0000000C; pull up PC2, PC3
	
	int mode;
	while(1)
	{
		volatile int idr = GPIOC->IDR & 0x0000000C; 	// Mask PC0,PC1,PC4..PC15, filter PC2, PC3
		
		if( idr == 0b1000)									// if PC2 click (0x00000008)
		{
				mode = 0;
		}
		else if( idr == 0b0100)        			// if PC3 click (0x00000004)
		{
				mode = 1;
		}
		else if( idr == 0b0000)   					// if PC2 & PC3 click (0x00000000)
		{
				mode ^= 1;
		}		
			
		if(mode==0)      { toggleDouble(); }
		else if(mode==1) { toggle(); }
	}
	
}

void toggleDouble()
{
	GPIOC->BSRR = 0b11; // on
	delay_();
	GPIOC->BSRR = 1<<16 | 1<<17;
	delay_();
}

void toggle()
{
	GPIOC->BSRR = 1<<16 | 1<<1; // on
	delay_();
	GPIOC->BSRR = 1<<17 | 1;
	delay_();
}

void delay_()
{
	int j=150;
	while(j--)
	{
		for(int i=0;i<11111;i++);
	}	
}
