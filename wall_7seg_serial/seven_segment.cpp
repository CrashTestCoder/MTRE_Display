#include "seven_segment.hpp" 
#include "math.hpp"
#include <avr/io.h>
using namespace seg7;

void seg7::disp(_7_seg_vals val)
{
	PORTB = ~num_map[val];
}

