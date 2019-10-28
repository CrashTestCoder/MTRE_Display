#ifndef _MATH_H_P_P_
#define _MATH_H_P_P_

#include "avr/io.h"

inline uint8_t absval(int8_t val)
{
	if(val < 0) val = -val;
	return val;
}



#endif /* _MATH_H_P_P_ */

