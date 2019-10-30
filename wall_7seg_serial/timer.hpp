#ifndef TIMER_H_P_P_
#define TIMER_H_P_P_

#include "avr/io.h"

namespace Timer0 {
	typedef enum {
		Normal			= 0x00,
		PWM_PC_MAX		= 0x01,
		CTC				= 0x02,
		Fast_PWM_MAX	= 0x03,
		PWM_PC_OCRA		= 0x09,
		Fast_PWM_OCRA	= 0x0B
	} Mode;
	
	typedef enum {
		_0				= 0x00,
		_1				= 0x01,
		_8				= 0x02,
		_64				= 0x03,
		_256			= 0x04,
		_1024			= 0x05,
		T0_fall			= 0x06,
		T0_rise			= 0x07
	} Prescaler;
	
	extern inline void setup(Mode mode, 
							 Prescaler prescaler) 
	{	
		TCCR0A = (mode & ((1 << WGM01) | (1 << WGM00))) |
				 (TCCR0A & 0xf0);

		TCCR0B = (mode & (1 << WGM02)) |
				 (prescaler &  ((1 << CS02) | (1 << CS01) | (1 << CS00))) |
				 (TCCR0B & 0xC0);
	}

	extern inline void setMode(Mode mode) {
		TCCR0A |=   mode & ((1 << WGM01) | (1 << WGM00));
		TCCR0A &= ~(~mode & ((1 << WGM01) | (1 << WGM00)));
		
		TCCR0B |=    mode & (1 << WGM02);
		TCCR0B &= ~(~mode & (1 << WGM02));
	}
	
	extern inline void setPrescaler(Prescaler prescaler) {
		TCCR0B |=   prescaler &  ((1 << CS02) | (1 << CS01) | (1 << CS00));
		TCCR0B &= ~(~prescaler & ((1 << CS02) | (1 << CS01) | (1 << CS00)));
	}
}

namespace Timer1 {
	typedef enum {
		Normal			= 0b00000000,
		PWM_PC_8		= 0b00000001,
		PWM_PC_9		= 0b00000010,
		PWM_PC_10		= 0b00000011,
		CTC_OCRA		= 0b00001000,
		Fast_PWM_8		= 0b00001001,
		Fast_PWM_9		= 0b00001010,
		Fast_PWM_10		= 0b00001011,
		PWM_PFC_ICR		= 0b00010000,
		PWM_PFC_OCRA	= 0b00010001,
		PWM_PC_ICR		= 0b00010010,
		PWM_PC_OCRA		= 0b00010011,
		CTC_ICR			= 0b00011000,
		Fast_PWM_ICR	= 0b00011010,
		Fast_PWM_OCRA	= 0b00011011
	} Mode;
	
	typedef enum {
		_0				= 0x00,
		_1				= 0x01,
		_8				= 0x02,
		_64				= 0x03,
		_256			= 0x04,
		_1024			= 0x05,
		T0_fall			= 0x06,
		T0_rise			= 0x07
	} Prescaler;
	
	extern inline void setup(Mode mode, 
							 Prescaler prescaler) 
	{
		TCCR1A = (mode & ((1 << WGM11) | (1 << WGM10))) |
				 (TCCR1A & 0xf0);

		TCCR1B = (mode & ((1 << WGM13) | (1 << WGM12))) | 
				  (prescaler &  ((1 << CS12) | (1 << CS11) | (1 << CS10))) |
				  (TCCR1B & 0xB0);
	}

	extern inline void setMode(Mode mode) {
		TCCR1A |=   mode &  ((1 << WGM11) | (1 << WGM10));
		TCCR1A &= ~(mode & ~((1 << WGM11) | (1 << WGM10)));
		
		TCCR1B |=    mode & ((1 << WGM13) | (1 << WGM12));
		TCCR1B &= ~(~mode & ((1 << WGM13) | (1 << WGM12)));
	}
	
	extern inline void setPrescaler(Prescaler prescaler) {
		TCCR0B |=   prescaler &  ((1 << CS12) | (1 << CS11) | (1 << CS10));
		TCCR0B &= ~(~prescaler & ((1 << CS12) | (1 << CS11) | (1 << CS10)));
	}
}

namespace Timer2 {
	typedef enum {
		Normal			= 0x00,
		PWM_PC_MAX		= 0x01,
		CTC				= 0x02,
		Fast_PWM_MAX	= 0x03,
		PWM_PC_OCRA		= 0x09,
		Fast_PWM_OCRA	= 0x0B
	} Mode;
	
	typedef enum {
		_0				= 0x00,
		_1				= 0x01,
		_8				= 0x02,
		_32				= 0x03,
		_64				= 0x04,
		_128			= 0x05,
		_256			= 0x06,
		_1024			= 0x07
	} Prescaler;
	
	extern inline void setup(Mode mode, 
							 Prescaler prescaler) 
	{
		TCCR2A = (mode & ((1 << WGM21) | (1 << WGM20))) |
				 (TCCR2A & 0xf0);

		TCCR2B = (mode & (1 << WGM22)) |
				 prescaler |
				 (TCCR2B & 0xB0);
	}

	extern inline void setMode(Mode mode) {
		TCCR2A |=    mode & ((1 << WGM21) | (1 << WGM20));
		TCCR2A &= ~(~mode & ((1 << WGM21) | (1 << WGM20)));
			
		TCCR2B |=    mode & (1 << WGM22);
		TCCR2B &= ~(~mode & (1 << WGM22));
	}
	
	extern inline void setPrescaler(Prescaler prescaler) {
		TCCR2B |=    prescaler & ((1 << CS22) | (1 << CS21) | (1 << CS20));
		TCCR2B &= ~(~prescaler & ((1 << CS22) | (1 << CS21) | (1 << CS20)));
	}
}

#endif /* TIMER_H_P_P_ */