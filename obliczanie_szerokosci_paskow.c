#include <math.h>
#include <stdint.h>
#include "obliczanie_szerokosci_paskow.h"
#include "common.h"


uint8_t oblicz_napiecie_silnik(uint16_t data){
	if((data > 511) && (data<1024)){
		uint8_t napiecie = (float)(data-512)*60.0/512.0;
		return napiecie;
	}
	else if(data <= 511){
		return 0;																//min paska
	}
	else{
		return 60;																//max paska
	}
}


uint8_t oblicz_prad_bocznik(uint16_t data){
	if((data > 511) && (data<1024)){
		uint8_t napiecie = (float)(data-512)*200.0/512.0;
		return napiecie;
	}
	else if(data <= 511){
		return 0;																//min paska
	}
	else{
		return 200;																//max paska
	}
}


uint8_t oblicz_predkosc(uint8_t data_nap, uint8_t data_pr){
	uint8_t predkosc = (0.76*data_nap - 0.01152*data_pr)*0.353*0.87*3.6;
	if((predkosc > 0) && (predkosc < 70)){
		return predkosc;
	}
	else{
		return 0;
	}
}


uint16_t oblicz_napiecie_srednie_cela(){
	uint16_t suma_napiecia=0;
	uint16_t srednie_napiecie;
	uint8_t i = 0;
	for (i = 0; i < 6; i++){
		suma_napiecia = suma_napiecia + tablica_odpowiedzi_bms[i];
	}
	for (i = 13; i < 17; i++){
		suma_napiecia = (suma_napiecia + tablica_odpowiedzi_bms[i]);
	}
	for (i = 25; i < 29; i++){
		suma_napiecia = (suma_napiecia + tablica_odpowiedzi_bms[i]);
	}
	srednie_napiecie = suma_napiecia/0x0D;
	return srednie_napiecie;
}


float oblicz_napiecie_srednie_cela_liczba(){
	float srednie = (float)(napiecie_srednie_cela)*4.0/4096.0+1;
	return srednie;
}


uint8_t oblicz_szerokosc_paska_prad_bocznika(uint16_t data){
	if((data > 511) && (data<1024)){
		return (float)(data-512)/7.76;
	}
	else if(data <= 511){
		return 0;																//min paska
	}
	else{
		return 66;																//max paska
	}
}


uint8_t oblicz_szerokosc_paska_predkosc(uint8_t data){
	return data;
}


uint8_t oblicz_szerokosc_paska_napiecie_cela_real(uint16_t data){
	uint8_t szerokosc;
	if(((data - 2053) > 0) && ((data - 2053) < 1024)){
		szerokosc = (uint8_t)((float)(data - 2053)*66.0/1024.0);
		return szerokosc;
	}
	else if((data - 2053) > 0){
		return 66;
	}
	else{
		return 0;
	}
}















	
