#include <avr/io.h>
#include <stdlib.h>
#include "S1D15705.h"
#include "wyglad_wyswietlacza.h"
#include "graphic.h"

void rysuj_pasek_pradu(uint8_t dana){
	gruba_pozioma_czysc(2, 49, 66);
	gruba_pozioma(2, 49, dana);
}


void rysuj_pasek_predkosci(uint8_t dana){
	gruba_pozioma_czysc(94, 9, 66);
	gruba_pozioma(94, 9, dana);
}


void rysuj_pasek_napiecia_cela_real(uint8_t data){
	gruba_pozioma_czysc(2, 9, 66);
	gruba_pozioma(2, 9, data);
}


void rysuj_pasek_napiecia_cela_teor(uint8_t data){
	gruba_pozioma_czysc(2, 25, 66);
	gruba_pozioma(2, 25, data);
}

	

 
void ustaw_wyglad(uint8_t szer_prad, uint8_t szer_pred, uint8_t szer_nap_cel_real, 
				uint8_t szer_nap_cel_teor, uint8_t max_speed, float nap_cel_real, uint8_t temp_bms, uint8_t temp_chl)
{
	//inicjalizacja wyswietlacza i czyszczenie go;
	GLCD_Initialize();
	GLCD_Clear();
	
	//ustawianie paskow
	rysuj_pasek_pradu(szer_prad);
	rysuj_pasek_predkosci(szer_pred);
	rysuj_pasek_napiecia_cela_real(szer_nap_cel_real);
	rysuj_pasek_napiecia_cela_teor(szer_nap_cel_teor);


	//pierwszy prostokat lewa strona Volt - R
	GLCD_WriteStringXY(1,0,"Volt (");
	GLCD_WriteStringXY(55,0,")");
	GLCD_Rectangle(0, 7, 70, 10);
	GLCD_WriteStringXY(71,1,"R");

	char tab_nap_cel_real[4];
	dtostrf(nap_cel_real, 2, 1, tab_nap_cel_real); 
	GLCD_WriteStringXY(37, 0, tab_nap_cel_real);;


	//drugi prostokat lewa strona Volt - O
	GLCD_Rectangle(0, 23, 70, 10);
	GLCD_WriteStringXY(71,3,"O");


	//trzeci prostokat lewa strona - Curr
	GLCD_WriteStringXY(1,5,"Curr");
	GLCD_Rectangle(0, 47, 70, 10);



	//prostokat pierwszy prawa strona - V
	GLCD_WriteStringXY(92,0,"V (max:");
	GLCD_WriteStringXY(154,0,")");

	char tab_max_speed[3];
	itoa(max_speed, tab_max_speed, 10); 
	GLCD_WriteStringXY(136, 0, tab_max_speed);

	GLCD_Rectangle(92, 7, 70, 10);
	GLCD_Line(102, 17,102,19);
	GLCD_Line(112, 17,112,21);
	GLCD_Line(122, 17,122,19);
	GLCD_Line(132, 17,132,21);
	GLCD_Line(142, 17,142,19);
	GLCD_Line(152, 17,152,21);

	//ddrugi prostokat i napisy prawa strona



	GLCD_WriteStringXY(95,3,"TB:     st");
	char tab_temp_bms[3];
	itoa(temp_bms, tab_temp_bms, 10); 
	GLCD_WriteStringXY(131, 3, tab_temp_bms);

	GLCD_WriteStringXY(95,4,"TChl:   st");
	char tab_temp_chl[3];
	itoa(temp_chl, tab_temp_chl, 10); 
	GLCD_WriteStringXY(131, 4, tab_temp_chl);


	//tutaj komunikaty systemowe
	GLCD_WriteStringXY(95,5,"Sys:");

	GLCD_Rectangle(92, 22, 70, 40);


}

