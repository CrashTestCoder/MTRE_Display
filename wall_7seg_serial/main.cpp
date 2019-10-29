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
	DDRD = (1 << PORTD4);

	Serial::begin(4800,Serial::async);
	Serial::send("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");

    {	// Setup Timer 2
		using namespace Timer2;
		Timer2::setMode(CTC);
	    Timer2::setPrescaler(_64);
		
	    TIMSK2 |= (1 <<OCIE2A);
		
		OCR2A = 203;
    }

	
    {
		using namespace Timer1;
		//Timer1::setMode(CTC_OCRA);
		//Timer1::setMode(CTC_OCRA);
		Timer1::setPrescaler(_64);
	    	
	    //TIMSK1 |= (1 << OCIE1A);
	    //OCR1A = (1 << 12) -191;
		OCR1A = 0xfee;
    }

	{	// Setup Timer 0
		using namespace Timer0;
		Timer0::setMode(CTC);
		//Timer0::setPrescaler(Timer0::_256);
		TCCR0B = 4;
		Serial::sendf("%i\n",TCCR0B);
		
		OCR0A = 194;
	
		TIMSK0 |= (1 << OCIE0A);
	}

	EICRA = (1 << ISC01) | (1 << ISC11) | (1 << ISC00);
	EIMSK |= (1 << INT1) | (1 << INT0);
	
	sei();
	
	Serial::sendf("0x%08x\n",53.2f);
	
	//uint8_t data = 0;
    while (1){
		
	}//Serial::send("test\n");
}

