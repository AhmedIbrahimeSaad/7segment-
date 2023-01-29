#define PORT_P(1U)
void GPIO_PORTA_SET_INPUT(int input_pin);
void GPIO_PORTB_SET_OUTPUT(int output_pin);
void GPIO_SW1_LED_UPDATE(void);




void GPIO_PORTA_SET_INPUT(int input_pin){

SIM->SCGC5 |=SIM_SCGC5_PORTA_MASK;
	PORTA->PCR[input_pin]=PORT_PCR_MUX(0x01)|PORT_PCR_IRQC(0xA)|PORT_PCR_PE_MASK |PORT_PCR_PS_MASK;
	PTA->PDDR&=~(PORT_PCR_IRQC<<input_pin);
	NVIC_ENABLEIRQ(PORTA_IRQn);





}