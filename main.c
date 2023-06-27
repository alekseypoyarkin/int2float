#include <stdio.h>
#include <stm32f0xx.h>

void InitUSART1 (void)
{
	RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
	GPIOA->MODER |= 0x00280000;
	GPIOA->AFR[1] |= 0x00000110;
	GPIOA->OTYPER &= ~GPIO_OTYPER_OT_9;
	GPIOA->PUPDR &= ~GPIO_PUPDR_PUPDR9;
	GPIOA->OSPEEDR |= GPIO_OSPEEDR_OSPEEDR9;
	GPIOA->PUPDR &= ~GPIO_PUPDR_PUPDR10;
	GPIOA->PUPDR |= GPIO_PUPDR_PUPDR10_0;	
	
	USART1->CR1 &= ~USART_CR1_UE;
	USART1->BRR=833; // 9600
	USART1->CR1 = USART_CR1_TE | USART_CR1_RE | USART_CR1_PCE | USART_CR1_PS;
	USART1->CR2 = 10;
	USART1->CR3 = 0;
	USART1->CR1 |= USART_CR1_UE;
}

float int_to_float(int intnum) {
		unsigned int u_intnum = (unsigned int) intnum;		
	  int sign;
		int exponent;
		int mantissa;
		unsigned int result;
	
		if(intnum < 0){
			sign = 1;
			u_intnum = ~u_intnum + 1;
		}
		
		while (u_intnum != 0) {
			exponent++;
			u_intnum >>= 1; // сдвиг вправо на 1 бит
		}
		
		u_intnum = (unsigned int) intnum;
		if (intnum < 0) {
            u_intnum = ~u_intnum + 1;
        }
		mantissa = u_intnum << (24 - exponent);
		mantissa &= 0x7FFFFF;
		
		result = (sign << 31) | ((exponent + 126) << 23) | mantissa;

		return result;
}

int send_number(int number){
	if(number < 10) {
		while((USART1->ISR & USART_ISR_TXE) == 0) {}
			USART1->TDR = number + 48;
	}
	else {
		send_number(number / 10);
	}
}


int main(void) {
		int intnum;
		float result;
		int_to_float(-1);
		
		while(1)
		{
			while((USART1->ISR & USART_ISR_RXNE) == 0) {}
			intnum = (uint8_t)USART1->RDR;
				
			intnum -= 48;
			//int_to_float(intnum);
				
			send_number(result);
		}
}
