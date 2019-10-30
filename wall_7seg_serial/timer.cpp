//  #include "timer.hpp"
 //  
 //  void Timer0::setMode(Timer0::Mode mode) {
 //  	TCCR0A |=   mode & ((1 << WGM01) | (1 << WGM00));
 //  	TCCR0A &= ~(~mode & ((1 << WGM01) | (1 << WGM00)));
 //  	
 //  	TCCR0B |=    mode & (1 << WGM02);
 //  	TCCR0B &= ~(~mode & (1 << WGM02));
 //  }
 //  
 //  void Timer0::setPrescaler(Timer0::Prescaler prescaler) {
 //  	TCCR0B |=   prescaler &  ((1 << CS02) | (1 << CS01) | (1 << CS00));
 //  	TCCR0B &= ~(~prescaler & ((1 << CS02) | (1 << CS01) | (1 << CS00)));
 //  }
 //  
 //  void Timer1::setMode(Timer1::Mode mode) {
 //  	TCCR1A |=   mode &  ((1 << WGM11) | (1 << WGM10));
 //  	TCCR1A &= ~(mode & ~((1 << WGM11) | (1 << WGM10)));
 //  	
 //  	TCCR1B |=    mode & ((1 << WGM13) | (1 << WGM12));
 //  	TCCR1B &= ~(~mode & ((1 << WGM13) | (1 << WGM12)));
 //  }
 //  
 //  void Timer1::setPrescaler(Timer1::Prescaler prescaler) {
 //  	TCCR0B |=   prescaler &  ((1 << CS12) | (1 << CS11) | (1 << CS10));
 //  	TCCR0B &= ~(~prescaler & ((1 << CS12) | (1 << CS11) | (1 << CS10)));
 //  }
 //  
 //  void Timer2::setMode(Timer2::Mode mode) {
 //  	TCCR2A |=    mode & ((1 << WGM21) | (1 << WGM20));
 //  	TCCR2A &= ~(~mode & ((1 << WGM21) | (1 << WGM20)));
 //  	
 //  	TCCR2B |=    mode & (1 << WGM22);
 //  	TCCR2B &= ~(~mode & (1 << WGM22));
 //  }
 //  
 //  void Timer2::setPrescaler(Timer2::Prescaler prescaler) {
 //  	TCCR2B |=    prescaler & ((1 << CS22) | (1 << CS21) | (1 << CS20));
 //  	TCCR2B &= ~(~prescaler & ((1 << CS22) | (1 << CS21) | (1 << CS20)));
 //  }