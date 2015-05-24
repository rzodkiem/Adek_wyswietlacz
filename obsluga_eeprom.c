#include <avr/io.h>
#include "obsluga_eeprom.h"

uint8_t EEPROM_read_byte(uint16_t uiAddress){ 
	while(EECR & (1<<EEWE)); 
	EEAR = uiAddress; 
	EECR |= (1<<EERE); 
	return EEDR; 
} 

uint32_t EEPROM_read_word(uint16_t first_byte_adress){
	uint32_t word = 0;
	for(int i = 3; i >=0; i--){
		word += ((uint32_t)(EEPROM_read_byte(first_byte_adress + 3 - i)) << (8*i));
	}
	return word;
}

uint16_t EEPROM_read_word_2byte(uint16_t first_byte_adress){
	uint16_t word = 0;
	for(int i = 1; i >=0; i--){
		word += ((uint16_t)(EEPROM_read_byte(first_byte_adress + 1 - i)) << (8*i));
	}
	return word;
}


void EEPROM_write_byte(uint16_t uiAddress, uint8_t ucData){ 
	while(EECR & (1<<EEWE));
	EEAR = uiAddress; 
	EEDR = ucData;  
	EECR |= (1<<EEMWE); 
	EECR |= (1<<EEWE);
}


void EEPROM_write_word(uint16_t first_byte_adress, uint32_t ucData){
	for(int i = 3; i >= 0; i--){
		EEPROM_write_byte(first_byte_adress + 3 - i, (uint8_t)((ucData >> (8*i)) & 0xff));
	}
}


void EEPROM_write_word_2byte(uint16_t first_byte_adress, uint16_t ucData){
	for(int i = 1; i >= 0; i--){
		EEPROM_write_byte(first_byte_adress + 1 - i, (uint8_t)((ucData >> (8*i)) & 0xff));
	}
}

uint8_t porownaj_1bytowe(uint16_t adres, uint8_t dana, uint8_t maxymalna){	
	if(dana > maxymalna){
		maxymalna = dana;
		EEPROM_write_byte(adres, maxymalna);
		return maxymalna;
	}
	else{
		return maxymalna;
	}
}

	


