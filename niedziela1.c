#include <avr/io.h>
#include "usart_bms.h"
#include "common.h"
#include "timer1.h"
#include "S1D15705.h"
#include "obliczanie_szerokosci_paskow.h"
#include "obsluga_ADC.h"
#include "obsluga_eeprom.h"
#include "wyglad_wyswietlacza.h"



int main(){

EEPROM_write_byte(max_speed_adress, 0);

	for(int i = 0; i < 36; i++){
		tablica_odpowiedzi_bms[i] = 0;
	}

	licznik_10ms = 0;
	licznik_20ms = 0;
	licznik_1s = 0;
	licznik_3s = 0;

	znacznik_numer_zapytania = 0;
	bufor_data_bms = 0;
	znacznik_part_ramki = 0;

	napiecie_silnik = 0;
	prad_bocznik = 0;
	napiecie_silnik_liczba=0;
	prad_bocznik_liczba=0;
	napiecie_srednie_cela = 0;

	temp_bms=0;
	temp_chl=0;

	predkosc = 0;
	max_predkosc = EEPROM_read_byte(max_speed_adress);

	napiecie_srednie_cela = 0;
	napiecie_srednie_cela_liczba = 0;

	szerokosc_paska_prad_bocznik = 0;
	szerokosc_paska_predkosci = 0;
	szerokosc_paska_napiecia_cela_real = 0;
	szerokosc_paska_napiecia_cela_teor = 0;

	DDRB = 0xff;
	zielony;
	
	timer1_init();
	initUSART0();
	GLCD_Initialize();
	GLCD_Clear();
	ADC_init();

	

	//pobranie z EEPROMu max_speedu i przechowywanie go w zmiennej.



	while(1){
		if(licznik_10ms >= 3){
			licznik_10ms = 0;
			transmit8bitUSART(znacznik_numer_zapytania);
		}

		if(licznik_20ms >= 2){

			licznik_20ms = 0;
			napiecie_silnik = zmierz_prad_bocznik();
			prad_bocznik = zmierz_napiecie_silnik();

			napiecie_silnik_liczba = oblicz_napiecie_silnik(napiecie_silnik);
			prad_bocznik_liczba = oblicz_prad_bocznik(prad_bocznik);

			predkosc = oblicz_predkosc(napiecie_silnik_liczba, prad_bocznik_liczba);			

			szerokosc_paska_prad_bocznik = oblicz_szerokosc_paska_prad_bocznika(prad_bocznik);
			szerokosc_paska_predkosci = oblicz_szerokosc_paska_predkosc(predkosc);

			max_predkosc = porownaj_1bytowe(max_speed_adress, predkosc, max_predkosc);

			rysuj_pasek_pradu(szerokosc_paska_prad_bocznik);
			rysuj_pasek_predkosci(szerokosc_paska_predkosci);
	
		}
			

		if(licznik_1s >= 100){
			licznik_1s = 0;
			//to jest licznik czasu, a do czego czas sluzy? - jeszcze nie wiem.
			//to jest zapytanie do o informacjê do karola.
		}

		if(licznik_3s >= 300){
			licznik_3s = 0;
			napiecie_srednie_cela = oblicz_napiecie_srednie_cela();
			napiecie_srednie_cela_liczba = oblicz_napiecie_srednie_cela_liczba();
			szerokosc_paska_napiecia_cela_real = oblicz_szerokosc_paska_napiecie_cela_real(napiecie_srednie_cela);

			ustaw_wyglad(szerokosc_paska_prad_bocznik, szerokosc_paska_predkosci, szerokosc_paska_napiecia_cela_real, 
				szerokosc_paska_napiecia_cela_teor, max_predkosc, napiecie_srednie_cela_liczba, temp_bms, temp_chl);

			/*brak temp_bms, temp_chl, szerokosc_paska_napiecia_teor*/
		}
	}
	return 0;
}




