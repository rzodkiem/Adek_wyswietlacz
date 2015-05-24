#ifndef INNE_H
#define INNE_H

#define volt_naladowania_max 3277
#define czerwony PORTB = (PORTB & ~(1<<PB6)) | (1<<PB7)
#define zielony PORTB = (PORTB & ~(1<<PB7)) | (1<<PB6)

void timer1_init();
void ADC_init();
float napiecie(uint16_t napieciex);
float prad(uint32_t pradx);
uint8_t speed(uint32_t pradx, uint16_t napieciex);
void take_all_data_from_bms();
void oblicz_srednie_napiecie();
void wyznacz_stan_baterii();
void paski_po_lewej();
void zmierz_prad_bocznik();
void zmierz_napiecie_silnik();

void zmierz_napiecie_silnik();
uint8_t alarm_prog_napiecia(uint16_t srednie_napiecie);
uint8_t alarm_nap_cela();
uint8_t alarm_no_communication_bms();
void ustaw_symbole_alarmow();
void ustaw_kolor_wyswietlacza();
void sprawdz_max_speed();
void wypelnij_tab_alarm();

#endif
