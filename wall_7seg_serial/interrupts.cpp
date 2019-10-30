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
ISR(INT0_vect)
{
	TCNT0 = 0;
}

ISR(INT1_vect)
{
	auto const cnt = TCNT0;
	static uint64_t raw_read = 0;
	raw_read <<= 8 * sizeof(cnt);
	raw_read |= cnt;
	//Serial::sendf("0x%08x\t",raw_read);
	auto const avg_cnt = []{
		float count = 0;
		for(uint8_t i = 0; i < sizeof(raw_read); i++)
		{
			count += (uint8_t)(raw_read >> (i*8));
			//Serial::sendf("%i\t",(uint8_t)(raw_read >> (i*8)));
		}
		return count / sizeof(raw_read);
	}();
	auto const dist = avg_cnt *343.0f / (2000000.0f / 256) * 1/0.0254f; 
	digit = dist;
	OCR0B = 2*avg_cnt;
	//Serial::sendf("dist: %i\n", (uint32_t)(avg_cnt));
}

/**********************************************************************************************/
/*                                     Timer 0 Interrupts                                     */
/**********************************************************************************************/

ISR(TIMER0_COMPA_vect)
{
	PORTD |=  (1 << PORTD4);
	for(volatile int i = 0; i < 0; i++); // wait 13us (measured)
	PORTD &= ~(1 << PORTD4);
	
	PORTD |= (1 << PORTD7);
	
}

ISR(TIMER0_COMPB_vect)
{
	PORTD &= ~(1 << PORTD7);
}

/**********************************************************************************************/
/*                                     Timer 1 Interrupts                                     */
/**********************************************************************************************/

//ISR(TIMER1_COMPA_vect)
//{
	////Serial::send('a');
	//auto const num = digit;
	//Serial::sendf("%d\n",((uint16_t)(num*1000)));
	//digit += .001;
	//if(digit == 10000) digit = -999;
//}

/**********************************************************************************************/
/*                                     Timer 2 Interrupts                                     */
/**********************************************************************************************/


ISR(TIMER2_COMPA_vect)
{
	//Serial::send("TIMER2_OVF_vect\n");
	
	//PORTD |=  (1 << PORTD4);
	//PORTD &= ~(1 << PORTD4);
	static volatile uint8_t dig = 0;
	dig++;
	dig %= 4; // toggle digit
	disp(_off);
	PORTC = 0;
	int const digit_ = digit;
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
