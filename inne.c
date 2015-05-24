#include <avr/io.h>
#include <avr/interrupt.h>
#include <math.h>
#include "inne.h"
#include "usart_bms.h"
#include "obsluga_eeprom.h"
#include "graphic.h"
#include "S1D15705.h"
 #include <stdlib.h>
//#include "common.h"

extern uint8_t ustaw_znacznik_ncb;
extern uint16_t pradu_bufor;
extern uint16_t napiecia_bufor;
extern uint16_t czas_20s;
volatile uint8_t licznik;
extern uint16_t srednie_napiecie;
extern uint16_t srednia_temperatura;
extern enum stany { rozladowywanie, bierne, ladowanie };
enum stany battery_state;
extern uint16_t tablica[36];
extern uint16_t czas;
extern uint8_t  aktual_speed;
extern uint8_t max_speed;
extern uint8_t tablica_alarmow[7];
extern uint8_t wspolrzedna_bledu_x[7];
extern uint8_t wspolrzedna_bledu_y[7];
extern uint8_t tablica_alarm_tekst[5][4];

void timer1_init(){
	OCR1A=1249;
	TCNT1=0;
	TCCR1A = 0x00;
	TCCR1B &= ~(1<<WGM13) & ~(1<<CS11) & ~(1<<CS10);
	TCCR1B |= (1<<WGM12) | (1<<CS12);
	TIMSK |= (1<<OCIE1A);
	sei();  
}

void ADC_init(){
	ADCSRA |= (1<<ADPS0) | (1<<ADPS1) | (1<<ADPS2) | (1<<ADEN) | (1<<ADSC);
	ADCSRA &= ~(1<<ADIF) & ~(1<<ADIE) & ~(1<<5); //5 oznacza ADFR
	ADMUX |= (1<<REFS0);
}

void zmierz_prad_bocznik(){ //ADC0
	ADMUX &= ~(1<<MUX0);
	ADCSRA |= (1<<ADSC);
	while(ADCSRA & (1<<ADSC));
	pradu_bufor = ADC;
}

void zmierz_napiecie_silnik(){ //ADC1
	ADMUX |= (1<<MUX0);
	ADCSRA |= (1<<ADSC);
	while(ADCSRA & (1<<ADSC));
	napiecia_bufor = ADC;
}

float napiecie(uint16_t napieciex){
	float napiecie1;
	if(napieciex > 512){
		napiecie1 = (float)napieciex*5.0/1024.0 - 2.5;
		return napiecie1*60.0/2.5;
	}
	else{
		napiecie1 = 0;
		return napiecie1;
	}		
}

float prad(uint32_t pradx){
	float prad1;
	if(pradx > 512){
		prad1 = (float)pradx*5.0/1024.0 - 2.5;
		return prad1*200.0/2.5;
	}
	else{
		prad1=0;
		return prad1;
	}
}

uint8_t speed(uint32_t pradx, uint16_t napieciex){
	uint8_t predkosc = (0.76*napiecie(napieciex) - 0.01152*prad(pradx))*0.33*0.8*3.6;
	return predkosc;
}
	
void take_all_data_from_bms(){
	
	tablica[0] = take_data_from_bms(0);
	if (!(tablica[0] == 0)){
		for( uint8_t i = 1; i < 36; i++){
			tablica[i] = take_data_from_bms(i);
		}
	}
}

void oblicz_srednie_napiecie(){
	uint16_t suma_napiecia=0;
	uint8_t i = 0;
	for (i = 0; i < 6; i++){
		suma_napiecia = (suma_napiecia + tablica[i]);
	}
	for (i = 13; i < 17; i++){
		suma_napiecia = (suma_napiecia + tablica[i]);
	}
	for (i = 25; i < 29; i++){
		suma_napiecia = (suma_napiecia + tablica[i]);
	}
	srednie_napiecie = suma_napiecia;///0x0D;
}

void wyznacz_stan_baterii(){
	uint16_t nap_20s_temu = EEPROM_read_word_2byte(last_voltage_adress);
	if(srednie_napiecie < nap_20s_temu){
		battery_state =	rozladowywanie;
		EEPROM_write_word_2byte(last_voltage_adress, srednie_napiecie);
		GLCD_WriteStringXY(70, 5, "Ro");
	}
	else if(srednie_napiecie == nap_20s_temu){
		battery_state = bierne;
		GLCD_WriteStringXY(70, 5, "B");
	}
	else{
		battery_state = ladowanie;
		EEPROM_write_word_2byte(last_voltage_adress, srednie_napiecie);
		czas = 0;
		GLCD_WriteStringXY(70, 5, "L");
	}
}

void paski_po_lewej(){

	if (battery_state == rozladowywanie){
		uint16_t v_bat = EEPROM_read_word_2byte(bateria_volt_adress);
		uint16_t v_nal = EEPROM_read_word_2byte(v_naladowania_adress);
		EEPROM_write_word_2byte(czas_zapisany_adress, czas);
		uint16_t szer = v_nal/3277*66/-czas*66/180; //powinno byc /1800 !!!
		v_bat = (float)szer*49.65;
		EEPROM_write_word_2byte(bateria_volt_adress, v_bat);
		if(szer>0){
			gruba_pozioma(2, 25, szer);
		}
	}
	if (battery_state == bierne){
		uint16_t v_bat = EEPROM_read_word_2byte(bateria_volt_adress);
		if(v_bat*66/3277 > 0){
			gruba_pozioma(2, 25, v_bat*66/3277); //powinno byc /1800
		}
	}
	if (battery_state == ladowanie){
		EEPROM_write_word_2byte(v_naladowania_adress, srednie_napiecie);
		EEPROM_write_word_2byte(bateria_volt_adress, srednie_napiecie);
		if((((srednie_napiecie-2253)>0) && (srednie_napiecie<3277) ) > 0){
			gruba_pozioma(2, 25, ((srednie_napiecie-2253)*66/1024));
		}
		else if((((srednie_napiecie-2253)>0) && (srednie_napiecie>3277) ) > 0){
			gruba_pozioma(2, 25, 66);
		}

	}
	if((srednie_napiecie-2253) > 0){
		gruba_pozioma(2, 9, (srednie_napiecie-2253)*66/1024);
	}
}

void sprawdz_max_speed(){
	max_speed =  EEPROM_read_byte(max_speed_adress);
	if((aktual_speed > max_speed) && (aktual_speed != 0xff)){
		EEPROM_write_byte(max_speed_adress, aktual_speed);	
		max_speed=aktual_speed;
	}
	char b[2];
	itoa(max_speed, b, 10);
	GLCD_WriteStringXY(136, 0,b);
}

uint8_t alarm_prog_napiecia(uint16_t srednie_napiecie){
	if(srednie_napiecie > 2653){	//ponizej 3,6V wlacza alarm = 1
		return 0;
	}
	else{
		return 1;
	}
}

uint8_t alarm_nap_cela(){
	for(int i = 1; i <= 5; i++){
		if (abs(tablica[i] - srednie_napiecie) > 10){
			return 1;
		}
	}
	for(int i = 13;i <= 16;i++){
		if (abs(tablica[i] - srednie_napiecie) > 10){
			return 1;
		}
	}
	for(int i = 25;i <= 28;i++){
		if (abs(tablica[i] - srednie_napiecie) > 10){
			return 1;
		}
	}
	return 0;
}

uint8_t alarm_no_communication_bms(){
	if(tablica[0] == 0){
		return 1;
	}
	return 0;
}

void wypelnij_tab_alarm(){
	tablica_alarmow[0] = alarm_nap_cela();
	tablica_alarmow[1] = alarm_prog_napiecia(srednie_napiecie);
	tablica_alarmow[2] = alarm_no_communication_bms();
}

void ustaw_symbole_alarmow(){
	int i = 0;
	int j=0;
	for( i = 0; i < 3; i++){
		if(tablica_alarmow[i] == 1){
			GLCD_WriteStringXY(wspolrzedna_bledu_x[j],wspolrzedna_bledu_y[j],tablica_alarm_tekst[i]);
			czerwony;
			j++;
		}
	}
	if(j==0){
		GLCD_WriteStringXY(wspolrzedna_bledu_x[0],wspolrzedna_bledu_y[0],"OK");
		zielony;
	}
		
}



void ustaw_kolor_wyswietlacza(){
	for(int i = 0; i < 3; i++){
		if(tablica_alarmow[i] == 1){
			czerwony;
		}
		else{
			zielony;
		}
	}
}



