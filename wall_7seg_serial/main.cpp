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
    DDRB = 0xff;
	DDRC = 0xff;
	DDRD = (1 << PORTD2);

	Serial::begin(4800,Serial::async);

    {	// Setup Timer 2
		using namespace Timer2;
		//Timer2::setMode(CTC);
	    Timer2::setPrescaler(_32);
		
	    TIMSK2 |= (1 <<TOIE2);
		
		OCR2A = 40;
    }

	
    {
		using namespace Timer1;
		Timer1::setMode(CTC_OCRA);
		Timer1::setPrescaler(_256);
	    	
	    //TIMSK1 |= (1 << OCIE1A);
	    OCR1A = (1 << 12) -191;
    }

	{	// Setup Timer 0
		using namespace Timer0;
		Timer0::setMode(CTC);
		Timer0::setPrescaler(_64);
		
		OCR2A = 194;
	
		TIMSK0 |= (1 << OCIE0A);
	}

	EICRA = 0x01 << 2;
	EIMSK |= (1 << INT1);
	
	sei();
	
	//uint8_t data = 0;
    while (1){
		
	}//Serial::send("test\n");
}

