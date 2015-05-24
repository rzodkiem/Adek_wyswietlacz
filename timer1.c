#include <avr/interrupt.h>
#include "timer1.h"
#include "common.h"


ISR(TIMER1_COMPA_vect) {
	licznik_10ms++;
	licznik_20ms++;
	licznik_1s++;
	licznik_3s++;
}

void timer1_init(){
	OCR1A=624;
	TCNT1=0;
	TCCR1A = 0x00;
	TCCR1B &= ~(1<<WGM13) & ~(1<<CS11) & ~(1<<CS10);
	TCCR1B |= (1<<WGM12) | (1<<CS12);
	TIMSK |= (1<<OCIE1A);
	sei();  
}
