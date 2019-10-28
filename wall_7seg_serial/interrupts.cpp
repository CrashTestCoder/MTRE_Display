#include <avr/interrupt.h>

#include "seven_segment.hpp"
#include "math.hpp"
#include "usart.hpp"
#include "stdio.h"
#include "stdlib.h"

using namespace seg7;

volatile int digit = sizeof(float);

/**********************************************************************************************/
/*                                      INT 0 Interrupts                                      */
/**********************************************************************************************/

ISR(INT1_vect)
{
	//Serial::send("INT1\n");
	
	//Serial::send("/INT1\n");
}

/**********************************************************************************************/
/*                                     Timer 0 Interrupts                                     */
/**********************************************************************************************/

ISR(TIMER0_COMPA_vect)
{
	//Serial::send("TIMER0_COMPA_vect\n");
	
	PORTD |=  (1 << PORTD2);
	PORTD &= ~(1 << PORTD2);
	
	//Serial::send("/TIMER0_COMPA_vect\n");
	
}

/**********************************************************************************************/
/*                                     Timer 1 Interrupts                                     */
/**********************************************************************************************/

ISR(TIMER1_COMPA_vect)
{
	//Serial::send('a');
	auto const num = digit;
	Serial::sendf("%d\n",((uint16_t)(num*1000)));
	digit += .001;
	if(digit == 10000) digit = -999;
}

/**********************************************************************************************/
/*                                     Timer 2 Interrupts                                     */
/**********************************************************************************************/


ISR(TIMER2_OVF_vect)
{
	//Serial::send("TIMER2_OVF_vect\n");
	
	static volatile uint8_t dig = 0;
	dig++;
	dig %= 4; // toggle digit
	disp(_off);
	PORTC = 0;
	int const digit_ = digit*1000;
	switch(dig)
	{
		case 0: {
			int i;
			if(digit_ < -99)
				disp(_dash); // show negative sign
			else if((i = digit_/1000))
				disp((_7_seg_vals)absval(i%10));
			//PORTB &= ~dp;
			break;
		}
		case 1: {
			int i;
			if(digit_ < -9 && !(digit_ < -99))
				disp(_dash); // show negative sign
			else if((i = digit_/100))
				disp((_7_seg_vals)absval(i%10));
			break;
		}
		case 2: {
			int i;
			if(digit_ < 0 && !(digit_ < -9))
				disp(_dash); // show negative sign
			else if((i = digit_/10))
				disp((_7_seg_vals)absval(i%10));
			break;
		}
		case 3:
			disp((_7_seg_vals)absval(digit_%10));
			break;
	}

	PORTC = dig_enable[dig];
	TCNT2 = 100;
	//Serial::send("/TIMER2_OVF_vect\n");
}

/************************************************************************/
/*                                USART                                 */
/************************************************************************/

ISR(USART_RX_vect)
{
	const char value = Serial::read();
	digit = atoi(&value);
	Serial::send(digit);
}