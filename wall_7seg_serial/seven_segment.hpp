#ifndef _SEVEN_SEGMENT_H_P_P_
#define _SEVEN_SEGMENT_H_P_P_

#include "avr/io.h"

namespace seg7 {
	typedef enum {
		_0 = 0x00, _1, _2, _3, _4, _5, _6, _7, _8, _9, _a, _b, _c, _d, _e, _f, _dash, _off
	} _7_seg_vals;
	
	/**
	 * ____a____
	 * |       |
	 * |f      |b
	 * |___g___|
	 * |       |
	 * |e      |c
	 * |___d___|  dp
	 */

	typedef enum {
		a  = 0b00100000,
		b  = 0b00000001,
		c  = 0b00001000,
		d  = 0b00000100,
		e  = 0b00000010,
		f  = 0b01000000,
		g  = 0b10000000,
		dp = 0b00010000
	} _7_seg_map;


	/** 
	 * Used to set the order that the digits are displayed
	 */
	constexpr uint8_t dig_enable[] = {
		1 << 4,
		1 << 5,
		1 << 0,
		1 << 1
	};

	constexpr uint8_t num_map[] = {
		[_0] = a|b|c|d|e|f,
		[_1] =   b|c,
		[_2] = a|b|  d|e|  g,
		[_3] = a|b|c|d|    g,
		[_4] =   b|c|    f|g,
		[_5] = a|  c|d|  f|g,
		[_6] = a|  c|d|e|f|g,
		[_7] = a|b|c,
		[_8] = a|b|c|d|e|f|g,
		[_9] = a|b|c|    f|g,
		[_a] = a|b|c|  e|f|g,
		[_b] =     c|d|e|f|g,
		[_c] =       d|e|  g,
		[_d] =   b|c|d|e|  g,
		[_e] = a|    d|e|f|g,
		[_f] = a|      e|f|g,
		[_dash] = g,
		[_off] = 0
	};

	extern void disp(_7_seg_vals val);
}
#endif /* _SEVEN_SEGMENT_H_P_P_ */