/* 
	Pete Hubbard 2017
	Loughborough University
	ELC055 Lab 1
	
	The following 'c' code presents an outline for you to adapt during the laboratory
	
	*/

#include "stm32f3xx.h"                  // Device header


void delay(int a); // prototype for a delay function

int main(void)
{
	// Enable clock on GPIO port E
	RCC->AHBENR |= RCC_AHBENR_GPIOEEN;
	
	// Define mode for each 
	// GPIOE is a structure defined in stm32f303xc.h file
	GPIOE->MODER |= 0x55550000; // Set mode of each pin in port E
	GPIOE->OTYPER &= ~(0x0000FF00); // Set output type for each pin required in Port E
	GPIOE->PUPDR &= ~(0xFFFF0000); // Set Pull up/Pull down resistor configuration for Port E
	
	//The clock pulses are directed to the timer by the following command:
	RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;

	//Set timer attributes
	TIM3->PSC = 799; // prescalor value in Timer 3 as 100
	TIM3->ARR = 9999; // Auto-Reset Register of Timer 3 set to 1000 counts

	//The timer action is set in motion with the ‘enable’ command
	TIM3->CR1 |= TIM_CR1_CEN;

	TIM3->DIER |= TIM_DIER_UIE; // Set DIER register to watch out for an ‘Update’ Interrupt Enable (UIE) – or 0x00000001
	
	NVIC_EnableIRQ(TIM3_IRQn); // Enable Timer 3 interrupt request in NVIC
	
	while(1);

	/*
	while (1)
 	{	
		//Binary counter	


		int myHexAddress=0x00;
		
		for(int x=0; x<255; x++)
		{
			myHexAddress = myHexAddress++;
			
			GPIOE->BSRRH = 0xFF00; //everything off
			GPIOE->BSRRL = myHexAddress*256; //pin 8 on
			delay(1000000);
		}

		
		/*
		//0
		GPIOE->BSRRH = 0x0000; //all off
		delay(500000);
		
		//1
		GPIOE->BSRRL = 0x0100; //pin 8 on
		delay(500000);
		GPIOE->BSRRH = 0xFF00; //everything off
		delay(500000);
		//2
		GPIOE->BSRRL = 0x0200;  //pin 9 on
		delay(500000);
		GPIOE->BSRRH = 0xFF00; //everything off
		delay(500000);
		//3
		GPIOE->BSRRL = 0x0300;  //pins 8 and 9 on
		delay(500000);
		GPIOE->BSRRH = 0xFF00; //everything off
		delay(500000);
		//4
		GPIOE->BSRRL = 0x0400;  //pins 10 on
		delay(500000);
		GPIOE->BSRRH = 0xFF00; //everything off
		delay(500000);
		//5
		GPIOE->BSRRL = 0x0500;  //pins 
		delay(500000);
		GPIOE->BSRRH = 0xFF00; //everything off
		delay(500000);
		//6
		GPIOE->BSRRL = 0x0600;  //pins 
		delay(500000);
		GPIOE->BSRRH = 0xFF00; //everything off
		delay(500000);
		//7
		GPIOE->BSRRL = 0x0700;  //pins 
		delay(500000);
		GPIOE->BSRRH = 0xFF00; //everything off
		delay(500000);
		//8
		GPIOE->BSRRL = 0x0800;  //pins 10 on
		delay(500000);
		GPIOE->BSRRH = 0xFF00; //everything off
		delay(500000);
		//9
		GPIOE->BSRRL = 0x0900;  //pins 10 on
		delay(500000);
		GPIOE->BSRRH = 0xFF00; //everything off
		delay(500000);
		//10
		GPIOE->BSRRL = 0x0A00;  //pins 10 on
		delay(500000);
		GPIOE->BSRRH = 0xFF00; //everything off
		delay(500000);
		//11
		GPIOE->BSRRL = 0x0B00;  //pins 10 on
		delay(500000);
		GPIOE->BSRRH = 0xFF00; //everything off
		delay(500000);
		//12
		GPIOE->BSRRL = 0x0C00;  //pins 10 on
		delay(500000);
		GPIOE->BSRRH = 0xFF00; //everything off
		delay(500000);
		//13
		GPIOE->BSRRL = 0x0D00;  //pins 10 on
		delay(500000);
		GPIOE->BSRRH = 0xFF00; //everything off
		delay(500000);
		//14
		GPIOE->BSRRL = 0x0E00;  //pins 10 on
		delay(500000);
		GPIOE->BSRRH = 0xFF00; //everything off
		delay(500000);
		//15
		GPIOE->BSRRL = 0x0F00;  //pins 10 on
		delay(500000);
		GPIOE->BSRRH = 0xFF00; //everything off
		delay(500000);
		*/
		//return(0);
}
	

//For blinking the LED	
//int myHexAddress = 0xFF00;
/*	
void TIM3_IRQHandler()
{
	if ((TIM3->SR & TIM_SR_UIF) !=0) // Check interrupt source is from the ‘Update’ interrupt flag
	{
		//...INTERRUPT ACTION HERE
		if (myHexAddress == 0xFF00){
			myHexAddress = 0x0100;
			GPIOE->BSRRL = myHexAddress;
		}
		else{
			myHexAddress = 0xFF00;
			GPIOE->BSRRH = myHexAddress;
		}
	}
	TIM3->SR &= ~TIM_SR_UIF; // Reset ‘Update’ interrupt flag in the SR register
}
*/



//For binary LED counter
int counterAddress = 0x00; //global variable used by the interrupt handler to increment address
void TIM3_IRQHandler()
{
	if ((TIM3->SR & TIM_SR_UIF) !=0) // Check interrupt source is from the ‘Update’ interrupt flag
	{
		//...INTERRUPT ACTION HERE		
		GPIOE->BSRRH = 0xFF00;
		counterAddress++;
		GPIOE->BSRRL = counterAddress*256;
	}	
	TIM3->SR &= ~TIM_SR_UIF; // Reset ‘Update’ interrupt flag in the SR register
}


void delay (int a)
{
    volatile int i,j;

    for (i=0 ; i < a ; i++)
    {
        j++;
    }

    return;
}
