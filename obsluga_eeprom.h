#ifndef OBLSUGA_EEPROM_H
#define OBLSUGA_EEPROM_H


#define max_speed_adress 0x0001
//#define last_voltage_adress 0x0006
//#define czas_zapisany_adress 0x0008
//#define volt_zapisane_adress 0x000A
//#define v_naladowania_adress 0x000C
//#define bateria_volt_adress	0x000E

uint8_t EEPROM_read_byte(uint16_t uiAddress);
uint32_t EEPROM_read_word(uint16_t first_byte_adress);
void EEPROM_write_byte(uint16_t uiAddress, uint8_t ucData);
void EEPROM_write_word(uint16_t first_byte_adress, uint32_t ucData);
uint16_t EEPROM_read_word_2byte(uint16_t first_byte_adress);
void EEPROM_write_word_2byte(uint16_t first_byte_adress, uint16_t ucData);
uint8_t porownaj_1bytowe(uint16_t adres, uint8_t dana, uint8_t maxymalna);


#endif
