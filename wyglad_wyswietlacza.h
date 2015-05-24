#ifndef WYGLAD_WYSWIETLACZA_H
#define WYGLAD_WYSWIETLACZA_H

void rysuj_pasek_pradu(uint8_t dana);
void rysuj_pasek_predkosci(uint8_t dana);
void rysuj_pasek_napiecia_cela_real(uint8_t data);
void rysuj_pasek_napiecia_cela_teor(uint8_t data);
void ustaw_wyglad(uint8_t szer_prad, uint8_t szer_pred, uint8_t szer_nap_cel_real, uint8_t szer_nap_cel_teor, uint8_t max_speed, float nap_cel_real, uint8_t temp_bms, uint8_t temp_chl);

#endif
