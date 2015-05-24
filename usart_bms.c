#include <avr/io.h>
#include <avr/interrupt.h>
#include "usart_bms.h"
#include "crc.h"
#include "common.h"

#define BAUD 9600
#define BAUDRATE ((F_CPU)/(BAUD*2UL)-1)
extern uint8_t ustaw_znacznik_ncb;



ISR(USART0_RX_vect){
	uint32_t tymczasowy_bufor = receive8bitUSART();
	tymczasowy_bufor = tymczasowy_bufor << (2-(8*znacznik_part_ramki));
	if(znacznik_part_ramki >= 2){
		if(check_crc(tymczasowy_bufor) && check_typ_data(tymczasowy_bufor, znacznik_numer_zapytania))
			tablica_odpowiedzi_bms[znacznik_numer_zapytania] = (uint8_t)(tymczasowy_bufor & 0xff);
			znacznik_numer_zapytania++;
			if(znacznik_numer_zapytania>=36){
				znacznik_numer_zapytania=0;
			}
		else{
			transmit8bitUSART(znacznik_numer_zapytania);
		}
		znacznik_part_ramki=0;
	}
}

void initUSART0(){
	DDRE|=(1<<PE2);															//ja generuje zegar w USARTCIE - Piotrek musi ustawiæ na wejœcie
	UBRR0H = (BAUDRATE>>8);													/* set baudrate */
	UBRR0L = BAUDRATE;												/* set baudrate */
	UCSR0B |= (1<<TXEN0)|(1<<RXEN0);											/* enable receiver and transmitter */
	UCSR0B &= ~(1<<UCSZ02);													/* 8bit data format*/	
	UCSR0C |= (1<<UCSZ00)|(1<<UCSZ01)|(1<<USBS0)|(1<<UMSEL0)|(1<<UCPOL0);	/* UCSZ - 8bit data format. USBS - 2bit stop, tryb asynchroniczny, wybor zboacz przy nadawaniu i odczytywaniu */
	UCSR0C &= ~(1<<UPM00) & ~(1<<UPM01); 									//brak bitu parzystoœci/nieparzystoœcu
	//prepareUSARTFunctions();
}


void transmit8bitUSART(uint8_t data){
	while( !(UCSR0A & (1<<UDRE0) ));
	UDR0 = data;
}

uint8_t receive8bitUSART(){
	while( !(UCSR0A & (1<<RXC0)) );
	uint8_t data = UDR0;
	return data;
}

uint32_t rebuild_frame_from_bms(){
	uint32_t frame = 0;
	for(int i = 2; i >= 0; i--){
		frame += (((uint32_t)receive8bitUSART()) << (i*8));
	}
	return frame;
}

uint8_t check_crc(uint32_t frame){
	if(((uint8_t)(frame >> 20)) != calculate4bitCRC(frame & 0xffffff)){
		return 1;
	}
	else{
		return 0;
	}
}

uint8_t check_typ_data(uint32_t frame, uint8_t typ_data){
	if(((uint8_t)((frame & 0xff000) >> 12)) != typ_data){
		return 1;
	}
	else{
		return 0;
	}
}

uint16_t take_data_from_bmsx(uint8_t typ_data){
	uint32_t frame;
	do{
		transmit8bitUSART(typ_data);
		frame = rebuild_frame_from_bms();
	} 
	while(check_crc(frame) || check_typ_data(frame, typ_data));
	return (frame & 0xfff);
}

uint16_t take_data_from_bms(uint8_t typ_data){
	int i = 0;
	uint32_t frame;
	for(i = 0; ((i<5) && (check_crc(frame) || check_typ_data(frame, typ_data))); i++){
		transmit8bitUSART(typ_data);
		frame = rebuild_frame_from_bms();
	}
	if(i<5){
		return (frame & 0xfff);
	}
	else{
	return 0;
	}
}

	



	

