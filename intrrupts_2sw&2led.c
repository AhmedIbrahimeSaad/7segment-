#include "TM4C123GH6PM.h"
#include "TM4C123.h"
#include <stdint.h>


void Delay (int n);
void printdata(unsigned char data);
int state=0;
int main(){

  SYSCTL->RCGCGPIO = SYSCTL->RCGCGPIO | (1<<5);	/*gpiof clock is enable*/
	SYSCTL->RCGCGPIO = SYSCTL->RCGCGPIO | (1<<1);
	GPIOF->LOCK = 0x4C4F434B;
	GPIOF->CR=0x01;
	GPIOF->DEN =GPIOF->DEN |(1<<0) | (1<<4);
	GPIOF->DIR =GPIOF->DIR &(~(1<<0)) &(~(1<<4));    /*conf p0,4 input*/
	GPIOF->PUR =GPIOF->PUR | (1<<0)| (1<<4);          /*pull up p0,4*/
	GPIOF->IS  =GPIOF->IS  &(~(1<<0))&(~(1<<4));
	GPIOF->IBE =GPIOF->IBE &(~(1<<0))&(~(1<<4));
  GPIOF->IEV =GPIOF->IEV &(~(1<<0))&(~(1<<4));
  GPIOF->IM  =GPIOF->IM  |(1<<0) | (1<<4);
  GPIOF->ICR =GPIOF->ICR |(1<<0) | (1<<4);

	GPIOF->DEN =GPIOF->DEN |(1<<0) | (1<<1)|(1<<2) | (1<<3)|(1<<4) | (1<<5)|(1<<6) ;
	GPIOF->DIR =GPIOF->DIR |(1<<0) | (1<<1)|(1<<2) | (1<<3)|(1<<4) | (1<<5)|(1<<6) ;
	
	NVIC->ISER[0]=NVIC->ISER[0] | (1<<30);
	NVIC->IP[30]=0x60;
	

	while(1)
	{
switch (state){
		case 0:
			printdata(0x3f);
		   Delay(20);
		break;
			case 1:
			printdata(0x06);
		   Delay(20);
		break;
				case 2:
			printdata(0x5B);
		   Delay(20);
		break;
				case 3:
			printdata(0x4F);
		   Delay(20);
		break;
				case 4:
			printdata(0x66);
		   Delay(20);
		break;
			case 5:
			printdata(0x6D);
		   Delay(20);
		break;
				case 6:
			printdata(0x7D);
		   Delay(20);
		break;
				case 7:
			printdata(0x07);
		   Delay(20);;
		break;
						case 8:
			printdata(0x7F);
		   Delay(20);
		break;	
		}
		
}
}
		void GPIOF_Handler(){
		if((GPIOF->MIS &0x10)== 0x10)
		{
			if((state>= 9)){state=0;}	
			state++;
		GPIOF->ICR = GPIOF->ICR | (1<<4);
			
		}
		else if((GPIOF->MIS &0x01)== 0x01)
		 {
			 if((state< 0)){state=0;}
			 state--;
		GPIOF->ICR = GPIOF->ICR | (1<<0); 
		 }
	}
		

void Delay (int n){
int i,j;
	for(i=0;i<n;i++){
	for(j=0;j<3180;j++);
	}
}

void printdata(unsigned char data)
{
if ((data&0x02) ==0x02 ){GPIOB->DATA = GPIOB->DATA |(1<<6);}
else               {GPIOB->DATA = GPIOB->DATA &(~(1<<6));}
if ((data&0x04) ==0x04 ){GPIOB->DATA = GPIOB->DATA |(1<<5);}
else               {GPIOB->DATA = GPIOB->DATA &(~(1<<5));}
if ((data&0x08) ==0x08 ){GPIOB->DATA = GPIOB->DATA |(1<<4);}
else               {GPIOB->DATA = GPIOB->DATA &(~(1<<4));}
if ((data&0x10) ==0x10 ){GPIOB->DATA = GPIOB->DATA |(1<<3);}
else               {GPIOB->DATA = GPIOB->DATA &(~(1<<3));}
if ((data&0x20) ==0x20 ){GPIOB->DATA = GPIOB->DATA |(1<<2);}
else               {GPIOB->DATA = GPIOB->DATA &(~(1<<2));}
if ((data&0x40) ==0x40 ){GPIOB->DATA = GPIOB->DATA |(1<<1);}
else               {GPIOB->DATA = GPIOB->DATA &(~(1<<1));}
if ((data&0x80) ==0x80 ){GPIOB->DATA = GPIOB->DATA |(1<<0);}
else               {GPIOB->DATA = GPIOB->DATA &(~(1<<0));}
}
