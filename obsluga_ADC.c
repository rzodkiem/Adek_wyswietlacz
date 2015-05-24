#include <avr/io.h>
#include "obsluga_ADC.h"



void ADC_init(){
	ADCSRA |= (1<<ADPS0) | (1<<ADPS1) | (1<<ADPS2) | (1<<ADEN) | (1<<ADSC);
	ADCSRA &= ~(1<<ADIF) & ~(1<<ADIE) & ~(1<<ADFR); //5 oznacza ADFR
	ADMUX |= (1<<REFS0);
}


uint16_t zmierz_prad_bocznik(){ //ADC0
	ADMUX &= ~(1<<MUX0);
	ADCSRA |= (1<<ADSC);
	while(ADCSRA & (1<<ADSC));
	return ADC;
}

uint16_t zmierz_napiecie_silnik(){ //ADC1
	ADMUX |= (1<<MUX0);
	ADCSRA |= (1<<ADSC);
	while(ADCSRA & (1<<ADSC));
	return ADC;
}
