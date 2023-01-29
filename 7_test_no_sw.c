#include "TM4C123GH6PM.h"
#include "TM4C123.h"
#include <stdint.h>


#define SYSCTL_RCGCGPIO_R   (*((volatile int *) 0x400FE608))   
#define GPIO_PORTB_DEN_R    (*((volatile int *) 0x4000551C))
#define GPIO_PORTB_DIR_R    (*((volatile int *) 0x40005400))
#define GPIO_PORTB_DATA_R   (*((volatile int *) 0x400053FC))
#define GPIO_PORTB_AMSEL_R  (*((volatile int *) 0x40005528))
#define GPIO_PORTB_AFSEL_R  (*((volatile int *) 0x40005420))
#define GPIO_PORTB_PCTL_R   (*((volatile int *) 0x4000552C))
#define GPIO_PORTB_PUR_R    (*((volatile int *) 0x40005510))1
#define GPIO_PORTB_LOCK_R   (*((volatile int *) 0x40005520))
#define GPIO_PORTB_CR_R     (*((volatile int *) 0x40005524))

#define GPIO_PORTB_CLK_EN  0x02      //enable clock for PORTB

void Delay(unsigned int);
void PORTB_Init(void);

int main(void)
{
	unsigned char digitPattern[] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};  
	volatile unsigned char i;
	PORTB_Init();
	while(1)
	{
		for(i=8;i>0;i--)// (i=0;i<0;i++) to count from 0-8
		{
			GPIO_PORTB_DATA_R = digitPattern[i];   //display digits from 0 to 9 
			Delay(1000);													// delay 1 second between each digit
		}
		
	}
}

void Delay(unsigned int delay)
{
	volatile unsigned int i, counter;
	counter = delay * 4000;  // 1 second (1000 msec) needs 40000000 counter so 4000000/1000 = 4000
	for(i=0;i<counter;i++);
}

void PORTB_Init(void)
{
	SYSCTL_RCGCGPIO_R |= GPIO_PORTB_CLK_EN;           //activate clock for Port B
  Delay(10);           															//Delay 10 msec to allow clock to start on PORTB  
  GPIO_PORTB_DEN_R = 0xFF;        	  							// Enable all pins of PORTB 
  GPIO_PORTB_DIR_R = 0xFF;        	  							// Make all pins of PORTB as ouptut pin
	GPIO_PORTB_PCTL_R &= ~(0xFF) ; 										// Regular GPIO of PORTB
  GPIO_PORTB_AMSEL_R &= ~(0xFF);        						// Disable analog function on all pins of PORTB
	GPIO_PORTB_AFSEL_R &= ~(0xFF);        						// Regular port function
}
