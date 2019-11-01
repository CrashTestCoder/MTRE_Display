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
volatile uint8_t cycle_start;

ISR(INT0_vect)
{
	cycle_start = TCNT0;
}


constexpr size_t read_size = 8;
uint8_t raw_read[read_size];

ISR(INT1_vect)
{
	uint8_t const cnt = TCNT0 - cycle_start;
	static uint8_t idx = 0;
	idx++;
	idx %= read_size;
	raw_read[idx] = cnt;
	//Serial::sendf("0x%08x\t",raw_read);
	auto const avg_cnt = []{
		float count = 0;
		for(uint8_t i = 0; i < read_size; i++)
		{
			count += (uint8_t)(raw_read[i]);
			//Serial::sendf("%i\t",(uint8_t)(raw_read[i]));
		}
		return count / read_size;
	}();
//Serial::send('\n');
	auto const dist = avg_cnt *343.0f / (2000000.0f / 64) * 1/0.0254f; 
	digit = dist;
	
	uint16_t ocr1b = avg_cnt / 20 *64;
	//if(ocr1b > 64) OCR1B = 128;
	//else OCR1B = ocr1b + 64;
	OCR0B=dist;
	//(avg_cnt / 20 *64 + 64);

	//Serial::sendf("%i\n", (uint32_t)(avg_cnt*10));
}

/**********************************************************************************************/
/*                                     Timer 0 Interrupts                                     */
/**********************************************************************************************/




/**********************************************************************************************/
/*                                     Timer 1 Interrupts                                     */
/**********************************************************************************************/

ISR(TIMER1_COMPA_vect)
{
	PORTD |=  (1 << PORTD4);
	for(volatile int i = 0; i < 0; i++); // wait 13us (measured)
	PORTD &= ~(1 << PORTD4);
	//Serial::send("100\n");
}

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
