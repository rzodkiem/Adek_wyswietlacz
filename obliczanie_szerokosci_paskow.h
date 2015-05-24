#ifndef OBLICZANIE_SZEROKOSCI_PASKOW_H
#define OBLICZANIE_SZEROKOSCI_PASKOW_H

uint8_t oblicz_napiecie_silnik(uint16_t data);
uint8_t oblicz_prad_bocznik(uint16_t data);
uint8_t oblicz_predkosc(uint8_t data_nap, uint8_t data_pr);
uint8_t oblicz_szerokosc_paska_prad_bocznika(uint16_t data);
uint8_t oblicz_szerokosc_paska_predkosc(uint8_t data);
uint8_t oblicz_szerokosc_paska_napiecie_cela_real(uint16_t data);
float oblicz_napiecie_srednie_cela_liczba();
uint16_t oblicz_napiecie_srednie_cela();

#endif
