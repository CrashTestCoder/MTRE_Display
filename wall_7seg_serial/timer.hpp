#ifndef TIMER_H_P_P_
#define TIMER_H_P_P_

#include "usart.hpp"

namespace Timer0 {
	typedef enum {
		Normal			= 0x00,
		PWM_PC_MAX		= 0x01,
		CTC				= 0x02,
		Fast_PWM_MAX	= 0x03,
		PWM_PC_OCRA		= 0x05,
		Fast_PWM_OCRA	= 0x07
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
	
	inline void setMode(Mode mode) {
		Serial::sendf("T0 set mode: 0x%02X\n", mode);
		TCCR0A |=   mode &  ((1 << WGM01) | (1 << WGM00));
		TCCR0A &= ~(mode & ~((1 << WGM01) | (1 << WGM00)));
		
		TCCR0B |=   mode &  (1 << WGM02);
		TCCR0B &= ~(mode & ~(1 << WGM02));
	}
	
	inline void setPrescaler(Prescaler prescaler) {
		Serial::sendf("T0 set prescaler: 0x%02X\n", prescaler);
		TCCR0B |=   prescaler &  ((1 << CS02) | (1 << CS01) | (1 << CS00));
		TCCR0B &= ~(~prescaler & ((1 << CS02) | (1 << CS01) | (1 << CS00)));
	}
}

namespace Timer1 {
	typedef enum {
		Normal			= 0x00,
		PWM_PC_8		= 0x01,
		PWM_PC_9		= 0x02,
		PWM_PC_10		= 0x03,
		CTC_OCRA		= 0x04,
		Fast_PWM_8		= 0x05,
		Fast_PWM_9		= 0x06,
		Fast_PWM_10		= 0x07,
		PWM_PFC_ICR		= 0x08,
		PWM_PFC_OCRA	= 0x09,
		PWM_PC_ICR		= 0x0a,
		PWM_PC_OCRA		= 0x0b,
		CTC_ICR			= 0x0c,
		Fast_PWM_ICR	= 0x0e,
		Fast_PWM_OCRA	= 0x0f
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
	
	inline void setMode(Mode mode) {
		Serial::sendf("T1 set mode: 0x%02X\n", mode);
		TCCR1A |=   mode &  ((1 << WGM11) | (1 << WGM10));
		TCCR1A &= ~(mode & ~((1 << WGM11) | (1 << WGM10)));
		
		TCCR1B |=   mode &  ((1 << WGM13) | (1 << WGM12));
		TCCR1B &= ~(mode & ~((1 << WGM13) | (1 << WGM12)));
	}
	
	inline void setPrescaler(Prescaler prescaler) {
		Serial::sendf("T1 set prescaler: 0x%02X\n", prescaler);
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
		PWM_PC_OCRA		= 0x05,
		Fast_PWM_OCRA	= 0x07
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
	
	inline void setMode(Mode mode) {
		Serial::sendf("T2 set mode: 0x%02X\n", mode);
		TCCR2A |=   mode &  ((1 << WGM21) | (1 << WGM20));
		TCCR2A &= ~(mode & ~((1 << WGM21) | (1 << WGM20)));
			
		TCCR2B |=   mode & (1 << WGM22);
		TCCR2B &= ~(mode & ~(1 << WGM22));
	}
	
	inline void setPrescaler(Prescaler prescaler) {
		Serial::sendf("T2 set prescaler: 0x%02X\n", prescaler);
		TCCR2B |=    prescaler & ((1 << CS22) | (1 << CS21) | (1 << CS20));
		TCCR2B &= ~(~prescaler & ((1 << CS22) | (1 << CS21) | (1 << CS20)));
	}
}

#endif /* TIMER_H_P_P_ */