#ifndef _USART_H_P_P_
#define _USART_H_P_P_

#include "avr/interrupt.h"
#include "stdio.h"

namespace Serial {
	typedef enum { sync, async, async2x } Mode;
	extern void begin(uint16_t baudRate, Mode mode = async);
	extern uint8_t send(uint8_t const data);
	extern void send(char const* data);
	extern void sendf(char const* format, ...);
	extern uint8_t read();
}

#endif