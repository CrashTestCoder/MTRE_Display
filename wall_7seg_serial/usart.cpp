#include "usart.hpp"
#include "stdarg.h"
#include "stdlib.h"

#define F_CLK 1000000ULL

static auto getUBRR(uint16_t baudRate, Serial::Mode mode)
{
	switch(mode) 
	{
	case Serial::async:
		return F_CLK/16/baudRate - 1;
	case Serial::async2x:
		return F_CLK/8/baudRate - 1;
	case Serial::sync:
		return F_CLK/2/baudRate - 1;
	}
	return 0ULL;
}

void Serial::begin(uint16_t baudRate, Serial::Mode mode)
{
	uint16_t ubrr = getUBRR(baudRate,mode);
	UBRR0H = (uint8_t)(ubrr >> 8);				// Set Buad Rate
	UBRR0L = (uint8_t)ubrr;
	UCSR0A &= ~(1 << U2X0);						// disable asnyc2x, apparently this can sometimes be necessary
	UCSR0B |= (1 << RXCIE0);					// Enable receiver interrupt
	UCSR0B |= (1 << RXEN0) | (1 << TXEN0);		// Enable RX(receiver) and TX(transmitter)
	UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);	// set frame: 8bit 1stop
	
	sei();
}

uint8_t Serial::send(uint8_t const data)
{
	while( !( UCSR0A & (1 << UDRE0) ) )
		;
	UDR0 = data;
	return data;
}

uint8_t Serial::read()
{
	while( !( UCSR0A & (1 << UDRE0) ) )
		;
	return UDR0;
}

void Serial::send(char* data)
{
	while(*data)
		Serial::send(*data), data++;
}


/** 
 * Note: if the output string is greater than 50 this function calls sprintf twice
 */
void Serial::sendf(char const* format, ...)	// using va_list to minimize program size
{
	int size;
	va_list vl;
	va_start(vl,format);
	char *str = (char*)malloc(30);
	if(!(size = vsnprintf(str, 30, format, vl)))
	{
		free(str);
		str = (char*)malloc(size);
		vsprintf(str, format, vl);
	}
	send(str);
	free(str);
}