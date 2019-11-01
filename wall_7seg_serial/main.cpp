/*
 * MCU3.c
 *
 * Created: 10/18/2019 4:24:11 PM
 * Author : mrrya
 */

unsigned long long const F_CLK = 8000000ULL;

#include "avr/io.h"
#include "avr/interrupt.h"
#include "usart.hpp"
#include "timer.hpp"

extern volatile float digit;

int main(void)
{
	TCCR1B = 1;
    DDRB = 0xff;
	DDRC = 0xff;
	DDRD =  (1 << PORTD4) | 
			(1 << PORTD5);

	PORTD =~(1 << PORTD5);
	Serial::begin(4800,Serial::async);

    {	// Setup Timer 2
		using namespace Timer2;
		Timer2::setMode(CTC);
	    Timer2::setPrescaler(_64);
		
	    TIMSK2 = (1 <<OCIE2A);
		
		OCR2A = 203;
    }

	{	// Setup Timer 1
		using namespace Timer1;
		Timer1::setup(CTC_OCRA,_8);
	
		OCR1A = 8000;
	
		TIMSK1 = (1 << OCIE1A);
	}

	{	// Setup Timer 0
		using namespace Timer0;
		
		TCCR0A = (1 << COM0B1) | 3;
		TCCR0B = (1 << WGM02) | (1 << CS01) | (1 << CS00);
		OCR0A = 194;
	
		//OCR0B = 1;
		//TIMSK0 = (1 << OCIE0A);
	}

	EICRA = (1 << ISC01) | (1 << ISC11) | (1 << ISC00);
	EIMSK |= (1 << INT1) | (1 << INT0);
	
	sei();
    while (1);
}

