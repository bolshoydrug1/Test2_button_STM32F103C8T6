#include "stm32f10x.h"
#define SYSCLOCK 72000000U 
#define LED_C13_ON() GPIOC->BSRR |= GPIO_BSRR_BR13; 
#define LED_C13_OFF() GPIOC->BSRR |= GPIO_BSRR_BS13; 
//-----------------------
uint8_t Button_State = 0;
//-----------------------
void PORTC_13_INIT(void);
void PORTB_4_INIT(void);
//-----------------------
int main(void)
{
	PORTC_13_INIT();
	PORTB_4_INIT();
	while(1)
	{
		//Button_State = READ_BIT(GPIOB->IDR, GPIO_IDR_IDR4);
		Button_State = (GPIOB->IDR & GPIO_IDR_IDR4) >> 4;
		if(Button_State == 1)
		{
			LED_C13_OFF()
			//LED_C13_ON()
		}
		else
		{
			LED_C13_ON()
			//LED_C13_OFF()
		}

	}
}

void PORTC_13_INIT(void) //setting up the pin PC13
{
	RCC->APB2ENR |= RCC_APB2ENR_IOPCEN; //setting up the pin timing
	
	GPIOC->CRH &=~ GPIO_CRH_MODE13;
	GPIOC->CRH |= GPIO_CRH_MODE13_1; //setting up the pin operation at a frequency of 2MHz
	GPIOC->CRH &=~ GPIO_CRH_CNF13; //setting up the pin operation in the mode push-pull
}

void PORTB_4_INIT(void) //PB4_input_floating
{
	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN; //timing PORTB
	
	GPIOB->CRL &=~ GPIO_CRL_MODE4_0;
	GPIOB->CRL &=~ GPIO_CRL_MODE4_1; 
	GPIOB->CRL |= GPIO_CRL_CNF4_0;
	GPIOB->CRL &=~ GPIO_CRL_CNF4_1;
}


