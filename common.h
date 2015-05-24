#ifndef COMMON_H
#define COMMON_H

#include <stdint.h>

#define czerwony PORTB = (PORTB & ~(1<<PB6)) | (1<<PB7)
#define zielony PORTB = (PORTB & ~(1<<PB7)) | (1<<PB6)

uint16_t licznik_10ms;
uint16_t licznik_20ms;
uint16_t licznik_1s;
uint16_t licznik_3s;

uint8_t tablica_odpowiedzi_bms[36];
uint8_t znacznik_part_ramki;
uint8_t znacznik_numer_zapytania;
uint32_t bufor_data_bms;
uint16_t napiecie_srednie_cela;
float napiecie_srednie_cela_liczba;

uint16_t napiecie_silnik;
uint16_t prad_bocznik;
uint8_t napiecie_silnik_liczba;
uint8_t prad_bocznik_liczba;

uint8_t temp_bms;
uint8_t temp_chl;

uint8_t predkosc;
uint8_t max_predkosc;

uint8_t szerokosc_paska_predkosci;
uint8_t szerokosc_paska_prad_bocznik;
uint8_t szerokosc_paska_napiecia_cela_real;
uint8_t szerokosc_paska_napiecia_cela_teor;




#endif
